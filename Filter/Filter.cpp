#include "Filter.h"
#include "FilterAction.h"

class XFilter : public AFilter
{
public:
    virtual void Add(FilterType);
    virtual void Clear();
    virtual GetReturnData DoFilter(cv::Mat,cv::Mat = cv::Mat());
    virtual void SetValue(QList<QVariant>);
    XFilter();
    virtual ~XFilter();

signals:
    void CameraIdentify();

private:
    QList<QVariant> _valueList;
    QList<FilterType> _taskList;
    FilterAction _action;
};


AFilter *AFilter::Get()
{
    static XFilter cx;
    return &cx;
}

AFilter::AFilter()
{

}

AFilter::~AFilter()
{

}

void XFilter::Add(FilterType task)
{
    _taskList.push_back(task);
}

void XFilter::Clear()
{
    _taskList.clear();
}

GetReturnData XFilter::DoFilter(cv::Mat mat1, cv::Mat mat2)
{
    GetReturnData data;
    _action.SetMat(mat1,mat2);
    for(auto& i : _taskList)
    {
        switch (i)
        {
            case Type_Voice:
            {
                const int PCANum = _action.VoiceAction();
                data.value = PCANum;
                break;
            }
            case Type_WritePaint:
            {
                const int pCountNum = _valueList.at(0).toInt();
                const int nCountNum = _valueList.at(1).toInt();
                const bool isWrite = _action.WritePaintAction(pCountNum,nCountNum);
                data.value = isWrite;
                break;
            }
        }
    }
    data.mat = _action.GetMat();
    return data;
}

void XFilter::SetValue(QList<QVariant> valueList)
{
    _valueList = valueList;
}

XFilter::XFilter()
{

}

XFilter::~XFilter()
{

}
