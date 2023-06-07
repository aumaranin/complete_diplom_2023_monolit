#include <simpleyolov5.h>
#include <fstream>
#include <minoronject.h>

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


SimpleYoloV5::SimpleYoloV5()
{

    // Загрузка имен классов из файла
    //string src = "/home/horatio/Documents/Projects/Diplom2/diplom2023-modul_classification/resources/classes/major.names";
    string src = "/home/horatio/Documents/Projects/Diplom2/diplom2023-modul_classification/resources/classes/minor.names";
    ifstream classNamesFile(src);
    string className;
    while (getline(classNamesFile, className))
        classNames.push_back(className);

    // Загрузка модели сети
    //string netFile = "/home/horatio/Documents/Projects/Diplom2/diplom2023-modul_classification/resources/models/yolov5s.onnx";
    string netFile = "/home/horatio/Documents/Projects/Diplom2/diplom2023-modul_classification/resources/models/helmet_2023_05_03.onnx";
    net = readNet(netFile);
    net.setPreferableBackend(cv::dnn::DNN_BACKEND_CUDA);
    net.setPreferableTarget(cv::dnn::DNN_TARGET_CUDA_FP16);
}

vector<shared_ptr<DetectObject>> SimpleYoloV5::detect(cv::Mat &inputImage)
{

    vector<shared_ptr<DetectObject>> listResult;

    std::vector<Detection> output;

    cv::Mat blob;
    auto formattedImage = format_yolov5(inputImage);
    cv::dnn::blobFromImage(formattedImage, blob, 1./255., cv::Size(INPUT_WIDTH, INPUT_HEIGHT), cv::Scalar(), true, false);
    net.setInput(blob);
    std::vector<cv::Mat> outputs;
    net.forward(outputs, net.getUnconnectedOutLayersNames());
    float x_factor = formattedImage.cols / INPUT_WIDTH;
    float y_factor = formattedImage.rows / INPUT_HEIGHT;
    float *data = (float *)outputs[0].data;
    const int dimensions = 5 + classNames.size();
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
                cv::Mat scores(1, classNames.size(), CV_32FC1, classes_scores);
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
        shared_ptr<DetectObject> newObject = make_shared<MinorOnject>();
        newObject->rect = box;
        newObject->className = classNames[classId];
        listResult.push_back(newObject);
    }

    return listResult;
}

/*
vector<shared_ptr<DetectObject>> SimpleYoloV5::detect(cv::Mat &inputImage)
{

    vector<shared_ptr<DetectObject>> listResult;

    std::vector<Detection> output;



    int detections = output.size();

    for (int i = 0; i < detections; ++i)
    {
        auto detection = output[i];
        auto box = detection.box;
        auto classId = detection.class_id;



    cv::VideoCapture inVid("/media/data/OBS videos/2023-05-03 12-48-39.mkv");

    //cv::VideoCapture inVid("/dev/video0");
    cv::Mat inputImage;
    inputImage = imread("/home/horatio/Documents/Projects/Diplom2/diplom2023-modul_classification/resources/images/test_image1.png");

    while (true)
    {
        inVid >> inputImage;
        vector<Mat> detections = pre_process(inputImage);
        Mat frame_clone = inputImage.clone();
        Mat outImage = post_process(frame_clone, detections);
        cv::imshow("Квартира", outImage);
        cv::waitKey(1);
    }

    vector<Mat> detections = pre_process(inputImage);
    Mat frame_clone = inputImage.clone();
    Mat outImage = post_process(frame_clone, detections);
    cv::imshow("Квартира", outImage);
    cv::waitKey(0);

    inVid.release();

    return listResult;
}*/

/*
vector<cv::Mat> SimpleYoloV5::pre_process(cv::Mat &input_image)
{
    Mat blob;
    blobFromImage(input_image, blob, 1./255., Size(INPUT_WIDTH, INPUT_HEIGHT), Scalar(), true, false);
    net.setInput(blob);

    // Forward propagate.
    vector<Mat> outputs;
    net.forward(outputs, net.getUnconnectedOutLayersNames());
    return outputs;
}

cv::Mat SimpleYoloV5::post_process(cv::Mat &input_image, vector<cv::Mat> &outputs)
{
    vector<int> class_ids;
    vector<float> confidences;
    vector<Rect> boxes;
    // Resizing factor.
    float x_factor = input_image.cols / INPUT_WIDTH;
    float y_factor = input_image.rows / INPUT_HEIGHT;

    float *data = (float *)outputs[0].data;

    const int dimensions = 5 + classNames.size();
    const int rows = 25200;
    // Iterate through 25200 detections.
    for (int i = 0; i < rows; ++i)
    {
        float confidence = data[4];
        // Discard bad detections and continue.
        if (confidence >= CONFIDENCE_THRESHOLD)
        {
            float * classes_scores = data + 5;
            // Create a 1x85 Mat and store class scores of 80 classes.
            Mat scores(1, classNames.size(), CV_32FC1, classes_scores);
            // Perform minMaxLoc and acquire index of best class score.
            Point class_id;
            double max_class_score;
            minMaxLoc(scores, 0, &max_class_score, 0, &class_id);
            // Continue if the class score is above the threshold.
            if (max_class_score > SCORE_THRESHOLD)
            {
                // Store class ID and confidence in the pre-defined respective vectors.

                confidences.push_back(confidence);
                class_ids.push_back(class_id.x);

                // Center.
                float cx = data[0];
                float cy = data[1];
                // Box dimension.
                float w = data[2];
                float h = data[3];
                // Bounding box coordinates.
                int left = int((cx - 0.5 * w) * x_factor);
                int top = int((cy - 0.5 * h) * y_factor);
                int width = int(w * x_factor);
                int height = int(h * y_factor);
                // Store good detections in the boxes vector.
                boxes.push_back(Rect(left, top, width, height));
            }

        }
        // Jump to the next column.
        data += dimensions;
    }
    // Perform Non Maximum Suppression and draw predictions.
    vector<int> indices;
    NMSBoxes(boxes, confidences, SCORE_THRESHOLD, NMS_THRESHOLD, indices);
    for (int i = 0; i < indices.size(); i++)
    {
        int idx = indices[i];
        Rect box = boxes[idx];

        int left = box.x;
        int top = box.y;
        int width = box.width;
        int height = box.height;

        //vector<string> allowedClasses{"person"};
        //std::string classObject = classNames[class_ids[idx]];
        //cout << "Class name: " << classObject << endl;

        if (confidences[idx]>0.5)
        {

        // Отрисовываем только нужные классы
         //for (string item : allowedClasses)
             //if ( classObject == (item + "\r"))
//             if ( classObject == (item))
  //           {
                // Draw bounding box.
                rectangle(input_image, Point(left, top), Point(left + width, top + height), RED, 3*THICKNESS);

                // Get the label for the class name and its confidence.
                //string label = format("%.2f", confidences[idx]);
                //label = classNames[class_ids[idx]] + ":" + label;
                // Draw class labels.
                //draw_label(input_image, label, left, top);
    //         }
        }
    }

    return input_image;
}


*/

