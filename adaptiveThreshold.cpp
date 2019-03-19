#include <opencv2/photo.hpp>
#include "opencv2/imgcodecs.hpp"
#include <opencv2/highgui.hpp>
/** @brief 自适应二值化
*@param _src     要二值化的灰度图
*@param _dst     二值化后的图
*@param maxValue    二值化后要设置的那个值
*@param method 块计算的方法（ADAPTIVE_THRESH_MEAN_C 平均值，ADAPTIVE_THRESH_GAUSSIAN_C 高斯分布加权和）
*@param type     二值化类型（CV_THRESH_BINARY 大于为最大值，CV_THRESH_BINARY_INV 小于为最大值）
*@param blockSize    块大小（奇数，大于1）
*@param delta 差值（负值也可以）
*/
void dkadaptiveThreshold(cv::InputArray _src, cv::OutputArray _dst, double maxValue,
    int method, int type, int blockSize, double delta)
{
    cv::Mat src = _src.getMat();

    // 原图必须是单通道无符号8位
    CV_Assert(src.type() == CV_8UC1);

    // 块大小必须大于1，并且是奇数
    CV_Assert(blockSize % 2 == 1 && blockSize > 1);
    cv::Size size = src.size();

    // 构建与原图像相同的图像
    _dst.create(size, src.type());
    cv::Mat dst = _dst.getMat();

    if (maxValue < 0)
    {
        // 二值化后值小于0，图像都为0
        dst = cv::Scalar(0);
        return;
    }

    // 用于比较的值
    cv::Mat mean;

    if (src.data != dst.data)
        mean = dst;

    if (method == CV_ADAPTIVE_THRESH_MEAN_C)
        // 计算平均值作为比较值
        cv::boxFilter(src, mean, src.type(), cv::Size(blockSize, blockSize),
        cv::Point(-1, -1), true, cv::BORDER_REPLICATE);
    else if (method == CV_ADAPTIVE_THRESH_GAUSSIAN_C)
        // 计算高斯分布和作为比较值
        cv::GaussianBlur(src, mean, cv::Size(blockSize, blockSize), 0, 0, cv::BORDER_REPLICATE);
    else
        CV_Error(CV_StsBadFlag, "Unknown/unsupported adaptive threshold method");

    int i, j;

    // 将maxValue夹到[0,255]的uchar范围区间，用作二值化后的值
    uchar imaxval = cv::saturate_cast<uchar>(maxValue);

    // 根据二值化类型计算delta值
    int idelta = type == CV_THRESH_BINARY ? cvCeil(delta) : cvFloor(delta);

    // 计算生成每个像素差对应的值表格，以后查表就可以。但像素差范围为什么是768，我确实认为512已经够了
    uchar tab[768];

    if (type == CV_THRESH_BINARY)
        for (i = 0; i < 768; i++)
            // i = src[j] - mean[j] + 255
            // i - 255 > -idelta ? imaxval : 0
            // = src[j] - mean[j] + 255 -255 > -idelta ? imaxval : 0
            // = src[j] > mean[j] - idelta ? imaxval : 0
            tab[i] = (uchar)(i - 255 > -idelta ? imaxval : 0);
    else if (type == CV_THRESH_BINARY_INV)
        for (i = 0; i < 768; i++)
            // i = src[j] - mean[j] + 255
            // i - 255 <= -idelta ? imaxval : 0
            // = src[j] - mean[j] + 255 - 255 <= -idelta ? imaxval : 0
            // = src[j] <= mean[j] - idelta ? imaxval : 0
            tab[i] = (uchar)(i - 255 <= -idelta ? imaxval : 0);
    else
        CV_Error(CV_StsBadFlag, "Unknown/unsupported threshold type");

    // 如果连续，加速运算
    if (src.isContinuous() && mean.isContinuous() && dst.isContinuous())
    {
        size.width *= size.height;
        size.height = 1;
    }

    // 逐像素计算src[j] - mean[j] + 255，并查表得到结果
    for (i = 0; i < size.height; i++)
    {
        const uchar* sdata = src.data + src.step*i;
        const uchar* mdata = mean.data + mean.step*i;
        uchar* ddata = dst.data + dst.step*i;

        for (j = 0; j < size.width; j++)
            // 将[-255, 255] 映射到[0, 510]然后查表
            ddata[j] = tab[sdata[j] - mdata[j] + 255];
    }
}

int main(int, char**argv)
{
    cv::Mat src = cv::imread("src.jpg", 0);
    cv::Mat bw;
    dkadaptiveThreshold(src, bw, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, 17, -7);
    cv::imwrite("adaptiveThreshold.jpg",bw);
}