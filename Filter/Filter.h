#ifndef _FILTER_H_
#define _FILTER_H_

#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <QVariant>
#include <QList>
#include <QObject>


enum FilterType
{
    Type_Voice,
    Type_WritePaint,
};

struct GetReturnData
{
    cv::Mat mat;
    QVariant value;
};

class AFilter
{
public:
    static AFilter* Get();
    virtual void Add(FilterType) = 0;
    virtual void SetValue(QList<QVariant>) = 0;
    virtual void Clear() = 0;
    virtual GetReturnData DoFilter(cv::Mat,cv::Mat = cv::Mat()) = 0;
protected:
    AFilter();
    virtual ~AFilter();
};

#endif //_FILTER_H_
