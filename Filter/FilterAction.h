#ifndef _FILTER_ACTION_H_
#define _FILTER_ACTION_H_

#include <QObject>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/face.hpp>

#include <QObject>

class FilterAction : public QObject
{
    Q_OBJECT
public:
    FilterAction(QObject* parent = nullptr);
    ~FilterAction();

    cv::Mat GetMat();
    void SetMat(cv::Mat,cv::Mat mat = cv::Mat());
    int VoiceAction();
    bool WritePaintAction(int,int);

signals:
    void Finish();

private:
    int _isSelete = 0;
    int _isSeleteCount = 0;
    cv::Mat _inputMat;
    cv::Mat _inputMat1;

private:
    cv::CascadeClassifier _cascade;
    cv::Ptr<cv::face::BasicFaceRecognizer> _modelPCA;

};

#endif //_FILTER_ACTION_H_
