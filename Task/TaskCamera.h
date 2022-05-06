#ifndef _TASK_CAMERA_H_
#define _TASK_CAMERA_H_

#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <QObject>
#include <QThread>
#include <QMutex>

class TaskCamera : public QThread
{
    Q_OBJECT
public:
    TaskCamera(int pCount,int nCount,QObject* parent = nullptr);
    ~TaskCamera();

    void Close();
    bool Open();
    void SetTrain();

signals:
    void UpdateMat(cv::Mat);
    void PaintInfoWrite(QStringList);
    void PaintWriteFinish(int,int);
    void VoiceIdentify(int);

protected:
    void run();

private:
    //照片的Label量
    int _pCountLabel;
    //照片的第几个人物
    int _nCountLabel;
    //是否训练
    bool _isTrain = false;
    //关闭线程
    bool _isClose = false;
    //锁
    QMutex _mux;
private:
    //摄像头图片帧
    cv::Mat _cvCameraPaint;
    //摄像头
    cv::VideoCapture _cvCamera;
};


#endif //_TASK_CAMERA_H_
