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




// helper function:
// finds a cosine of angle between vectors
// from pt0->pt1 and from pt0->pt2
double angle( Point pt1, Point pt2, Point pt0 )
{
    double dx1 = pt1.x - pt0.x;
    double dy1 = pt1.y - pt0.y;
    double dx2 = pt2.x - pt0.x;
    double dy2 = pt2.y - pt0.y;
    return (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}


/**
 * Find square of document in an image
 * @param image
 * @param squares
 */
void findSquares(cv::Mat& image, std::vector<std::vector<Point> >& squares)
{
    // blur will enhance edge detection
    cv::Mat blurred(image);
    medianBlur(image, blurred, 9);

    cv::Mat gray0(blurred.size(), CV_8U), gray;
    std::vector<std::vector<Point> > contours;

    // find squares in every color plane of the image
    for (int c = 0; c < 3; c++)
    {
        int ch[] = {c, 0};
        mixChannels(&blurred, 1, &gray0, 1, ch, 1);

        // try several threshold levels
        const int threshold_level = 2;
        for (int l = 0; l < threshold_level; l++)
        {
            // Use Canny instead of zero threshold level!
            // Canny helps to catch squares with gradient shading
            if (l == 0)
            {
                Canny(gray0, gray, 10, 20, 3); //

                // Dilate helps to remove potential holes between edge segments
                dilate(gray, gray, cv::Mat(), Point(-1,-1));
            }
            else
            {
                gray = gray0 >= (l+1) * 255 / threshold_level;
            }

            // Find contours and store them in a list
            findContours(gray, contours, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);

            // Test contours
            std::vector<Point> approx;
            for (size_t i = 0; i < contours.size(); i++)
            {
                // approxicv::Mate contour with accuracy proportional
                // to the contour perimeter
                approxPolyDP(cv::Mat(contours[i]), approx, arcLength(cv::Mat(contours[i]), true)*0.02, true);

                // Note: absolute value of an area is used because
                // area may be positive or negative - in accordance with the
                // contour orientation
                if (approx.size() == 4 &&
                    fabs(contourArea(cv::Mat(approx))) > 1000 &&
                    isContourConvex(cv::Mat(approx)))
                {
                    double maxCosine = 0;

                    for (int j = 2; j < 5; j++)
                    {
                        double cosine = fabs(angle(approx[j%4], approx[j-2], approx[j-1]));
                        maxCosine = MAX(maxCosine, cosine);
                    }

                    if (maxCosine < 0.3)
                        squares.push_back(approx);
                }
            }
        }
    }
}

/**
 * Draw square on the imahe
 * @param image
 * @param squares
 */
void drawSquares( Mat& image, const std::vector<std::vector<Point> >& squares )
{
    for( size_t i = 0; i < squares.size(); i++ )
    {
        const Point* p = &squares[i][0];
        int n = (int)squares[i].size();
        polylines(image, &p, &n, 1, true, Scalar(0,255,0), 3, cv::LINE_AA);
    }

}


extern "C"
JNIEXPORT void JNICALL
Java_com_rabiielbeji_ndk_1opencv_MainActivity_FindDocument(JNIEnv *env, jobject thiz,
                                                           jlong matAddrInput,
                                                           jlong matAddrResult) {

    cv::Mat &matInput = *(cv::Mat *)matAddrInput;

    cv::Mat &matResult = *(cv::Mat *)matAddrResult;

    std::vector<std::vector<Point> > squares;

    matResult = matInput.clone();

    //cv::cvtColor(matInput, matResult, COLOR_RGBA2RGB);


    findSquares(matInput, squares);
    drawSquares(matResult, squares);

}


