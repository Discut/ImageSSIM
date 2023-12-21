#include <iostream>
#include "opencv2/opencv.hpp"
#include "DllExport.h"

using namespace cv;
using namespace std;

static const double C1 = 6.5025, C2 = 58.5225;
Mat Compare_SSIM(Mat image1, Mat image2)
{
    Mat validImage1, validImage2;
    image1.convertTo(validImage1, CV_32F); // 数据类型转换为 float,防止后续计算出现错误
    image2.convertTo(validImage2, CV_32F);

    Mat image1_1 = validImage1.mul(validImage1); // 图像乘积
    Mat image2_2 = validImage2.mul(validImage2);
    Mat image1_2 = validImage1.mul(validImage2);

    Mat gausBlur1, gausBlur2, gausBlur12;
    GaussianBlur(validImage1, gausBlur1, Size(11, 11), 1.5); // 高斯卷积核计算图像均值
    GaussianBlur(validImage2, gausBlur2, Size(11, 11), 1.5);
    GaussianBlur(image1_2, gausBlur12, Size(11, 11), 1.5);

    Mat imageAvgProduct = gausBlur1.mul(gausBlur2); // 均值乘积
    Mat u1Squre = gausBlur1.mul(gausBlur1);         // 各自均值的平方
    Mat u2Squre = gausBlur2.mul(gausBlur2);

    Mat imageConvariance, imageVariance1, imageVariance2;
    Mat squreAvg1, squreAvg2;
    GaussianBlur(image1_1, squreAvg1, Size(11, 11), 1.5); // 图像平方的均值
    GaussianBlur(image2_2, squreAvg2, Size(11, 11), 1.5);

    imageConvariance = gausBlur12 - gausBlur1.mul(gausBlur2); // 计算协方差
    imageVariance1 = squreAvg1 - gausBlur1.mul(gausBlur1);    // 计算方差
    imageVariance2 = squreAvg2 - gausBlur2.mul(gausBlur2);

    auto member = ((2 * gausBlur1.mul(gausBlur2) + C1).mul(2 * imageConvariance + C2));
    auto denominator = ((u1Squre + u2Squre + C1).mul(imageVariance1 + imageVariance2 + C2));

    Mat ssim;
    divide(member, denominator, ssim);
    return ssim;
}

double SSIM_Percent(const char *imgPath1, const char *imgPath2)
{
    double sum = 0.0f;
    auto img1 = imread(imgPath1);
    auto img2 = imread(imgPath2);
    auto height = 0;
    auto width = 0;
    // resize both images to the same size
    height = img1.size().height < img2.size().height ? img1.size().height : img2.size().height;
    width = img1.size().width < img2.size().width ? img1.size().width : img2.size().width;
    cv::resize(img1, img1, cv::Size(width, height));
    cv::resize(img2, img2, cv::Size(width, height));
    auto result = Compare_SSIM(img1, img2);
    auto meanResult = mean(result);
    int channels = result.channels();

    for (auto depthIndex = 0; depthIndex < channels; ++depthIndex)
    {
        sum += meanResult[depthIndex];
    }
    sum /= channels;

    return sum;
}

double C_SSIM_Percent(const char *imgPath1, const char *imgPath2)
{
    return SSIM_Percent(imgPath1, imgPath2);
}
