#include <opencv2/opencv.hpp>

using namespace cv;
int main(int argc, char** argv) {

    Mat image1 = imread("D:\main.jpg");
    Mat image2 = imread("D:\own_12+2.jpg");
    //Mat image2 = imread("D:\ore.jpg");
    Mat outImg1;
    Mat outImg2;
    Mat res;
    resize(image1, outImg1, Size(), 0.4, 0.4);
    resize(image2, outImg2, Size(), 0.4, 0.4);
    Mat input = outImg1;
    Mat templ = outImg2;
    //Mat gray;
    double minVal; double maxVal; Point minLoc; Point maxLoc;
    Point matchLoc;
    int match_method = TM_CCORR_NORMED;// TM_CCORR;
    //cvtColor(input, gray, CV_BGR2GRAY);

    Mat result;

    int result_cols = input.cols - templ.cols + 1;
    int result_rows = input.rows - templ.rows + 1;

    result.create(result_cols, result_rows, CV_32FC1);

    // Do the Matching and Normalize
    matchTemplate(input, templ, result, match_method);
    normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());

    // Localizing the best match with minMaxLoc

    minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());

    if (match_method == TM_SQDIFF || match_method == TM_SQDIFF_NORMED)
    {
       matchLoc = minLoc;
    }
    else
    {
       matchLoc = maxLoc;
    }

    // Show result rectangle
    rectangle(input, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), 255, 2); 

    imshow("res", result);
    imshow("input", input);
    imshow("template", templ);

    waitKey(0);

    return 0;
}