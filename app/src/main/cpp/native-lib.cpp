#include <jni.h>
#include <string>
#include <jni.h>
#include <opencv2/opencv.hpp>

using namespace cv;

extern "C"
JNIEXPORT void JNICALL
Java_com_rabiielbeji_ndk_1opencv_MainActivity_ConvertRGBtoGray(JNIEnv *env, jobject thiz,
                                                               jlong matAddrInput,
                                                               jlong matAddrResult) {

    cv::Mat &matInput = *(cv::Mat *)matAddrInput;

    cv::Mat &matResult = *(cv::Mat *)matAddrResult;


    cv::cvtColor(matInput, matResult, COLOR_RGBA2GRAY);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_rabiielbeji_ndk_1opencv_MainActivity_EdgeDetection(JNIEnv *env, jobject thiz,
                                                               jlong matAddrInput,
                                                               jlong matAddrResult) {

    cv::Mat &matInput = *(cv::Mat *)matAddrInput;

    cv::Mat &matResult = *(cv::Mat *)matAddrResult;

    cv::Mat imgGrayscale;        // grayscale of input image
    cv::Mat imgBlurred;            // intermediate blured image

    Mat gray, edge, draw;

    cv::cvtColor(matInput, imgGrayscale, COLOR_RGBA2GRAY);

    cv::GaussianBlur(imgGrayscale,            // input image
                     imgBlurred,                            // output image
                     cv::Size(3, 3),                        // smoothing window width and height in pixels
                     1.5);                                // sigma value, determines how much the image will be blurred


    cv::Canny(imgBlurred,            // input image
              matResult,                    // output image
              50,                        // low threshold
              200);                        // high threshold


}

extern "C"
JNIEXPORT void JNICALL
Java_com_rabiielbeji_ndk_1opencv_MainActivity_ConvertEdgeExtraction(JNIEnv *env, jobject thiz,
                                                                    jlong matAddrInput,
                                                                    jlong matAddrResult) {

    cv::Mat &matInput = *(cv::Mat *)matAddrInput;

    cv::Mat &matResult = *(cv::Mat *)matAddrResult;



}extern "C"
JNIEXPORT void JNICALL
Java_com_rabiielbeji_ndk_1opencv_MainActivity_rotateImage(JNIEnv *env, jobject thiz,
                                                          jlong matAddrInput,
                                                          jlong matAddrResult) {
    cv::Mat &matInput = *(cv::Mat *)matAddrInput;

    cv::Mat &matResult = *(cv::Mat *)matAddrResult;

    cv::Mat matResultT = matInput.t();

    cv::flip(matResultT, matResult, ROTATE_90_COUNTERCLOCKWISE);

    //matResult = matResultT;
}