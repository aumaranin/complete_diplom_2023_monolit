#include <simpleyolo.h>
#include <fstream>

using namespace cv;
using namespace cv::dnn;
using namespace std;


// Constants.
const float INPUT_WIDTH = 640.0;
const float INPUT_HEIGHT = 640.0;
const float SCORE_THRESHOLD = 0.5;
const float NMS_THRESHOLD = 0.45;
const float CONFIDENCE_THRESHOLD = 0.4;

// Text parameters.
const float FONT_SCALE = 0.7;
const int FONT_FACE = FONT_HERSHEY_SIMPLEX;
const int THICKNESS = 1;

// Colors.
/*
Scalar BLACK = Scalar(0,0,0);
Scalar BLUE = Scalar(255, 178, 50);
Scalar YELLOW = Scalar(0, 255, 255);
Scalar RED = Scalar(0,0,255);
*/


SimpleYolo::SimpleYolo()
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
}

vector<shared_ptr<DetectObject>> SimpleYolo::detect(cv::Mat &inputImage1)
{

    vector<shared_ptr<DetectObject>> listResult;


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
}


vector<cv::Mat> SimpleYolo::pre_process(cv::Mat &input_image)
{
    Mat blob;
    blobFromImage(input_image, blob, 1./255., Size(INPUT_WIDTH, INPUT_HEIGHT), Scalar(), true, false);
    net.setInput(blob);

    // Forward propagate.
    vector<Mat> outputs;
    net.forward(outputs, net.getUnconnectedOutLayersNames());
    return outputs;
}

cv::Mat SimpleYolo::post_process(cv::Mat &input_image, vector<cv::Mat> &outputs)
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


