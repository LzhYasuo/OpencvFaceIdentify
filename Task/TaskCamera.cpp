#include "TaskCamera.h"
#include "windows.h"
#include <QDebug>
#include "Filter/Filter.h"

TaskCamera::TaskCamera(int pCount,int nCount,QObject *parent)
    :_pCountLabel(pCount),
     _nCountLabel(nCount)
{
//    this->connect(AFilter::Get(),&);
}

TaskCamera::~TaskCamera()
{

}

void TaskCamera::Close()
{
    _isClose = true;
    this->quit();
    this->wait();
    this->deleteLater();
}

bool TaskCamera::Open()
{
    _mux.lock();
    const bool isOpen = _cvCamera.open(0);
    _mux.unlock();
    AFilter::Get()->Add(Type_Voice);
    if(!isOpen)
    {
        qDebug() << "Open Error";
        return false;
    }
    return true;
}

void TaskCamera::SetTrain()
{
    _isTrain = true;
    AFilter::Get()->Clear();
    AFilter::Get()->Add(Type_WritePaint);
}

void TaskCamera::run()
{
    bool isRead = false;
    int trainPaintCount = 0;
    int InfoClear = 0;
    while(1)
    {
        _mux.lock();
        if(_isClose)
        {
            _mux.unlock();
            break;
        }
        if(!_cvCamera.isOpened())
        {
            _mux.unlock();
            continue;
        }
        isRead = _cvCamera.read(_cvCameraPaint);
        if(!isRead || _cvCameraPaint.empty())
        {
            _mux.unlock();
            continue;
        }
        if(_isTrain)
        {
            if(trainPaintCount >= 10)
            {
                _isTrain = false;
                AFilter::Get()->Clear();
                AFilter::Get()->Add(Type_Voice);
                _nCountLabel += 1;
                _pCountLabel += trainPaintCount;
                emit PaintWriteFinish(_pCountLabel,_nCountLabel);
                trainPaintCount = 0;
            }
            QList<QVariant> list;
            list.push_back(trainPaintCount + _pCountLabel);
            list.push_back(_nCountLabel);
            AFilter::Get()->SetValue(list);
            GetReturnData data = AFilter::Get()->DoFilter(_cvCameraPaint);
            _cvCameraPaint = data.mat;
            if(data.value.toBool())
            {
                trainPaintCount++;
            }

            #if 0
            if(trainPaintCount == 10)
            {
                //如果训练的图片达到了10张
                //则退出训练模式 开始告诉训练类进行训练
                emit PaintInfoWrite(writeLabelList);
                _isTrain = false;
                trainPaintCount = 0;
                writeLabelList.clear();
                emit PaintWriteFinish();
            }
            const QString paintPath = (trainPath + QString::number(_pCountLabel) + ".jpg");
            const bool isWrite = cv::imwrite(paintPath.toStdString(),_cvCameraPaint);
            if(isWrite)
            {
                trainPaintCount += 1;
                const QString writeLabel = paintPath + ":" + _nCountLabel;
                writeLabelList.push_back(writeLabel);
            }
            #endif
        }
        else
        {
            //如果没有训练 就将图片开始进行识别
            GetReturnData data = AFilter::Get()->DoFilter(_cvCameraPaint);
            if(data.value != -1)
            {
                InfoClear = 0;
                emit VoiceIdentify(data.value.toInt());
            }
            _cvCameraPaint = data.mat;
        }
        emit UpdateMat(_cvCameraPaint);
        //摄像头判断

        Sleep(32);
        InfoClear++;
        if(InfoClear >= 40)
        {
            InfoClear = 0;
            emit VoiceIdentify(-1);
        }
        _mux.unlock();
    }
}
