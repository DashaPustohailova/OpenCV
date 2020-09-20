#include <opencv2/opencv.hpp>

using namespace cv;
int main(int argc, char** argv) {

    Mat image1 = imread("D:\main.jpg");

    Mat image2 = imread("D:\ma.jpg");
    Mat outImg1;
    Mat outImg2;
    Mat res;
    resize(image1, outImg1, cv::Size(), 0.5, 0.5);
    resize(image2, outImg2, cv::Size(), 0.5, 0.5);
    // imshow("input1", outImg1);
    // imshow("input2", outImg2);
    // cv::waitKey(0);


 /*
     cv::Mat image;

 //	if (argc == 2) {

         image = cv::imread("D:\main.jpg", CV_LOAD_IMAGE_UNCHANGED);

     //}

     //else

         Mat small_image = cv::imread("D:\own_12.jpg", CV_LOAD_IMAGE_UNCHANGED);

     if (image.empty())

         return -2;

     /*

     Строки программной модели, реализуемой студентом

     imshow("Test OpenCV", image);

     waitKey(0);

     return 0;

 }*/



    Mat input =  outImg1;

    Mat gray;
    cvtColor(input, gray, CV_BGR2GRAY);

    Mat templ =  outImg2;

    Mat img = input;
    Mat result;
    /// Create the result matrix
    int result_cols = img.cols - templ.cols + 1;
    int result_rows = img.rows - templ.rows + 1;

    result.create(result_cols, result_rows, CV_32FC1);

    int match_method = TM_CCORR;//CV_TM_SQDIFF;

    /// Do the Matching and Normalize
    matchTemplate(img, templ, result, match_method);
    normalize(result, result, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());

    /// Localizing the best match with minMaxLoc
    double minVal; double maxVal; cv::Point minLoc; cv::Point maxLoc;
    Point matchLoc;

    minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat());

    /// For SQDIFF and SQDIFF_NORMED, the best matches are lower values. For all the other methods, the higher the better
    if (match_method == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED)
    {
        matchLoc = minLoc;
    }
    else
    {
        matchLoc = maxLoc;
    }

    /// Show me what you got
   rectangle(input, matchLoc, cv::Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), cv::Scalar::all(0), 2, 8, 0);
    //cv::rectangle(result, matchLoc, cv::Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), cv::Scalar::all(0), 2, 8, 0);

    res.create(result_cols, result_rows, CV_32FC1);
    matchTemplate(input, templ, res, TM_CCORR);
    normalize(res, res, 0, 1, NORM_MINMAX, -1, Mat());

    imshow("res", res);
    imshow("input", input);
    imshow("template", templ);

    imwrite("../outputData/TemplateMatch.jpg", input);
    waitKey(0);

    return 0;
}