#include <yolo2dnn.h>
#include <fstream>
#include <minoronject.h>
#include <majorobject.h>

using namespace cv;
using namespace cv::dnn;
using namespace std;

const float INPUT_WIDTH = 640.0;
const float INPUT_HEIGHT = 640.0;
const float SCORE_THRESHOLD = 0.2;
const float NMS_THRESHOLD = 0.4;
const float CONFIDENCE_THRESHOLD = 0.4;

struct Detection
{
    int class_id;
    float confidence;
    cv::Rect box;
};

cv::Mat format_yolov5(const cv::Mat &source) {
    int col = source.cols;
    int row = source.rows;
    int _max = MAX(col, row);
    cv::Mat result = cv::Mat::zeros(_max, _max, CV_8UC3);
    source.copyTo(result(cv::Rect(0, 0, col, row)));
    return result;
}


Yolo2Dnn::Yolo2Dnn()
{

    // Загрузка имен классов из файла
    //string src = "../resources/classes/minor.names";
    string src = "../resources/classes/minor.names";
    ifstream classNamesFile(src);
    string className;
    while (getline(classNamesFile, className))
        classNamesMinor.push_back(className);
    classNamesFile.close();
    src = "../resources/classes/major.names";
    ifstream classNamesFile2(src);
    while (getline(classNamesFile2, className))
        classNamesMajor.push_back(className);

    // Загрузка моделей сети
    //string netFile = "/home/horatio/Documents/Projects/Diplom2/diplom2023-modul_classification/resources/models/helmet_2023_05_03.onnx";
    string netFile = "../resources/models/100ep_s_best.onnx";
    netMinor = readNet(netFile);
    netMinor.setPreferableBackend(cv::dnn::DNN_BACKEND_CUDA);
    netMinor.setPreferableTarget(cv::dnn::DNN_TARGET_CUDA_FP16);
    netFile = "../resources/models/yolov5n.onnx";
    netMajor = readNet(netFile);
    netMajor.setPreferableBackend(cv::dnn::DNN_BACKEND_CUDA);
    netMajor.setPreferableTarget(cv::dnn::DNN_TARGET_CUDA_FP16);
}

vector<shared_ptr<DetectObject>> Yolo2Dnn::detect(cv::Mat &inputImage)
{
    vector<shared_ptr<DetectObject>> listMajorObjects = detectDnn<MajorObject>(inputImage, classNamesMajor, netMajor);
    vector<shared_ptr<DetectObject>> listMinorObjects = detectDnn<MinorOnject>(inputImage, classNamesMinor, netMinor);

    vector<shared_ptr<DetectObject>> buf;
    for (const auto &item : listMajorObjects)
        for (const auto &clName : allowedClasses)
            if (item->className == clName)
                buf.push_back(item);
    listMajorObjects = buf;
/*
    for (auto majorObject : listMajorObjects)
        majorObject->displayObject(inputImage, RED);
    for (auto minorObject : listMinorObjects)
        minorObject->displayObject(inputImage, WHITE);
*/


    return comparison(listMajorObjects, listMinorObjects);
}

template<typename T>
vector<shared_ptr<DetectObject> > Yolo2Dnn::detectDnn(cv::Mat &inputImage, vector<string> &clNames, cv::dnn::dnn4_v20211004::Net &model)
{
    vector<shared_ptr<DetectObject>> listResult;

    std::vector<Detection> output;

    cv::Mat blob;
    auto formattedImage = format_yolov5(inputImage);
    cv::dnn::blobFromImage(formattedImage, blob, 1./255., cv::Size(INPUT_WIDTH, INPUT_HEIGHT), cv::Scalar(), true, false);
    model.setInput(blob);
    std::vector<cv::Mat> outputs;
    model.forward(outputs, model.getUnconnectedOutLayersNames());
    float x_factor = formattedImage.cols / INPUT_WIDTH;
    float y_factor = formattedImage.rows / INPUT_HEIGHT;
    float *data = (float *)outputs[0].data;
    const int dimensions = 5 + clNames.size();
    const int rows = 25200;
    std::vector<int> class_ids;
    std::vector<float> confidences;
    std::vector<cv::Rect> boxes;
    for (int i = 0; i < rows; ++i)
    {
        float confidence = data[4];
            if (confidence >= CONFIDENCE_THRESHOLD)
            {
                float * classes_scores = data + 5;
                cv::Mat scores(1, clNames.size(), CV_32FC1, classes_scores);
                cv::Point class_id;
                double max_class_score;
                minMaxLoc(scores, 0, &max_class_score, 0, &class_id);
                if (max_class_score > SCORE_THRESHOLD)
                {
                    confidences.push_back(confidence);
                    class_ids.push_back(class_id.x);
                    float x = data[0];
                    float y = data[1];
                    float w = data[2];
                    float h = data[3];
                    int left = int((x - 0.5 * w) * x_factor);
                    int top = int((y - 0.5 * h) * y_factor);
                    int width = int(w * x_factor);
                    int height = int(h * y_factor);
                    boxes.push_back(cv::Rect(left, top, width, height));
                }
            }
            data += dimensions;
    }

    std::vector<int> nms_result;
    cv::dnn::NMSBoxes(boxes, confidences, SCORE_THRESHOLD, NMS_THRESHOLD, nms_result);
    for (int i = 0; i < nms_result.size(); i++)
    {
        int idx = nms_result[i];
        Detection result;
        result.class_id = class_ids[idx];
        result.confidence = confidences[idx];
        result.box = boxes[idx];
        output.push_back(result);
    }

    int detections = output.size();
    for (int i = 0; i < detections; ++i)
    {
        auto detection = output[i];
        auto box = detection.box;
        auto classId = detection.class_id;
        shared_ptr<DetectObject> newObject = make_shared<T>();


        // Проверяем значения квадрата
        if (box.x < 0)
            box.x = 1;
        if (box.x > inputImage.cols)
            box.x = inputImage.cols-1;

        if ( (box.x+box.width) > inputImage.cols)
            box.width = inputImage.cols - box.x - 1;

        if (box.y < 0)
            box.y = 1;

        if (box.y > inputImage.rows)
            box.y = inputImage.rows - 1;

        if ( (box.y + box.height) > inputImage.rows)
            box.height = inputImage.rows - box.y - 1;

        newObject->rect = box;

        newObject->className = clNames[classId];
        listResult.push_back(newObject);
    }
    return listResult;
}

vector<shared_ptr<DetectObject> > Yolo2Dnn::comparison(vector<shared_ptr<DetectObject>> &listMajorObjects, vector<shared_ptr<DetectObject>> &listMinorObjects)
{
    for (auto &majorObject : listMajorObjects)
        for (auto &minorObject : listMinorObjects)
        {
            // Проверка координат. Если примерно совпадают - добавляем минорный объект в список к мажорным
            if (between(majorObject->rect, minorObject->rect))
                majorObject->addProperty(minorObject);
        }
    return listMajorObjects;
}

bool Yolo2Dnn::between(cv::Rect major, cv::Rect minor)
{
    bool result = false;
    if ((minor.x >= major.x && minor.x <= (major.x+major.width) && minor.y >= major.y && minor.y <= (major.y+major.height)))
        result = true;
    else if
    (((minor.x+minor.width) >= major.x && (minor.x+minor.width) <= (major.x+major.width) && minor.y >= major.y && minor.y <= (major.y+major.height)))
        result = true;
    else if
    (((minor.x+minor.width) >= major.x && (minor.x+minor.width) <= (major.x+major.width) && (minor.y+minor.height) >= major.y && (minor.y+minor.height) <= (major.y+major.height)))
        result = true;
    else if
    ((minor.x >= major.x && minor.x <= (major.x+major.width) && (minor.y+minor.height) >= major.y && (minor.y+minor.height) <= (major.y+major.height)))
        result = true;
    return result;
}

