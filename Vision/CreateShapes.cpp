/* Class CreatesShapes by Liam Lawrence on 11.28.16
 * Takes a frame and draws a specified shape on the largest contour
 */

#include "opencv2/videoio.hpp"
#include "opencv2/opencv.hpp"
#include "CreateShapes.hpp"
#include "iostream"

using namespace std;

// Draws two bounding shapes
cv::Point CreateShapes::shapes(cv::Mat &frame, int idx, vector<vector<Point>> contours) {
    if (contours.size() <= 0) {
        return cv::Point(-1, -1); //VERY VERY IMPORTANT!!! If there are no contours, just return a blank point!!!
    }

    cv::Point center;
    Point pt1, pt2;
    Point circleCenter;

    // Draws a bounding rectangle on the frame
    cv::Rect rect = boundingRect(contours[idx]);
    pt1.x = rect.x;
    pt1.y = rect.y;
    pt2.x = rect.x + rect.width;
    pt2.y = rect.y + rect.height;
    cv::rectangle(frame, pt1, pt2, Scalar(255,204,0), 2);

    // Draws a bounding circle in the center of the rectangle
    center.x = (pt1.x + pt2.x) / 2;
    center.y = (pt1.y + pt2.y) / 2;
    cv::circle(frame, center, 5, Scalar(255,204,0), 2);

    return circleCenter;
}

// Finds the angles the robot needs to turn
std::vector<float> CreateShapes::findAngles(float cx, float cy, float focalLength, cv::Point circleCenter) {
    if (circleCenter.x == -1 && circleCenter.y == -1) {
        return std::vector<float>();
    }
    std::vector<float> angles;
    angles.push_back(cx - circleCenter.x);                        //xDif
    angles.push_back(cy - circleCenter.y);                        //yDif
    angles.push_back(atan(circleCenter.x - cx) / focalLength);    //yaw
    angles.push_back(atan(circleCenter.y - cy) / focalLength);    //pitch

    return angles;
}