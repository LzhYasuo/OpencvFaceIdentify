#include "OpenCVGLWidget.h"
#include <QPainter>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <QResizeEvent>
#include <QDebug>
#include <QShowEvent>
#include <QBitmap>
#include <QPainter>

OpenCVGLWidget::OpenCVGLWidget(QWidget *parent)
    :QOpenGLWidget (parent)
{
    this->setStyleSheet("border:10px solid rgb(85,255,255);");
}

OpenCVGLWidget::~OpenCVGLWidget()
{

}

void OpenCVGLWidget::resizeEvent(QResizeEvent *e)
{
    QBitmap bmp(size());
    bmp.fill();
    QPainter p(&bmp);
    p.setRenderHint(QPainter::SmoothPixmapTransform);
    //只要上边角圆弧
    int arcR = 230; //圆弧大小
    QRect rect = this->rect().adjusted(0, 0, 0, 0);
    QPainterPath path;
    //逆时针
    path.moveTo(arcR, 0);
    //左上角
    path.arcTo(0, 0, arcR * 2, arcR * 2, 90.0f, 90.0f);
    path.lineTo(0, rect.height()-arcR);
    //左下角
    path.arcTo(0, rect.height() - arcR * 2 , arcR * 2, arcR * 2, 180.0f, 90.0f);
    path.lineTo(rect.width(), rect.height());
    //右下角
    path.arcTo(rect.width() - arcR * 2, rect.height() - arcR * 2 , arcR * 2, arcR * 2, 270.0f, 90.0f);
    path.lineTo(rect.width(), arcR);
    //右上角
    path.arcTo(rect.width() - arcR * 2, 0, arcR * 2, arcR * 2, 0.0f, 90.0f);
    path.lineTo(arcR, 0);
    p.drawPath(path);
    //此行代码必须添加，不然无法达到正常的显示
    p.fillPath(path, QBrush(Qt::red));
    setMask(bmp);

    return QWidget::resizeEvent(e);
}


void OpenCVGLWidget::ShowImg(cv::Mat mat)
{
#if 1
    //图片格式应该是rgb888
    QImage::Format fmt = QImage::Format_RGB888;
    int pixSize = 3;
    //如果是灰度图 因为rgb是 w*h*3 而灰度图则是 w*h*1;
    if(mat.type() == CV_8UC1)
    {
        fmt = QImage::Format_Grayscale8;
        pixSize = 1;
    }
    if(fmt != img.format() || img.isNull())
    {
        //图片的大小应是上文的 w*h*pixSize (PixSize决定是rgb图还是灰度图)
        delete img.bits();
        unsigned char* imgSize = new unsigned char[(this->width() - SubWidth) * (this->height() - SubHeight) * pixSize];
        img = QImage(imgSize,this->width() - SubWidth,this->height() - SubHeight,fmt);
    }
    cv::Mat des;
    cv::resize(mat,des,cv::Size(img.size().width(),img.size().height()));
    if(pixSize > 1)
    {
        //QT本身的颜色排序是BGR
        cv::cvtColor(des,des,cv::COLOR_BGR2RGB);
    }
    memcpy(img.bits(),des.data,des.cols * des.rows * des.elemSize());
    update();
#else
//    QImage::Format fmt = QImage::Format_RGB888;
//    int pixSize = 3;
//    if(mat.type() == CV_8UC1)
//    {
//        fmt = QImage::Format_Grayscale8;
//        pixSize = 1;
//    }
//    if(img.isNull() || img.format() != fmt)
//    {
//        delete img.bits();
//        uchar* buf = new uchar[(this->width() - SubWidth) * (this->height() - SubHeight) * pixSize];
//        img = QImage(buf,this->width() - SubWidth,this->height() - SubHeight,fmt);
//    }
//    cv::Mat des;
//    //设置图像大小
//    cv::resize(mat, des,cv::Size(img.size().width(),img.size().height()));
//    //设置图像颜色格式
//    if(pixSize > 1)
//        cv::cvtColor(des, des, cv::COLOR_BGR2RGB);
//    memcpy(img.bits(),des.data,des.rows * des.cols * des.elemSize());
    cv::resize(mat,mat,cv::Size(this->width(),this->height()));
    img = MatToQImage(mat);
    update();
#endif
}

QImage OpenCVGLWidget::MatToQImage(const cv::Mat& mat)
{
    switch (mat.type())
    {
    // 8-bit, 4 channel
    case CV_8UC4:
    {
        QImage image(mat.data,
                     mat.cols, mat.rows,
                     static_cast<int>(mat.step),
                     QImage::Format_ARGB32);

        return image;
    }

    // 8-bit, 3 channel
    case CV_8UC3:
    {
        QImage image(mat.data,
                     mat.cols, mat.rows,
                     static_cast<int>(mat.step),
                     QImage::Format_RGB888);

        return image.rgbSwapped();
    }

        // 8-bit, 1 channel
    case CV_8UC1:
    {
#if QT_VERSION >= QT_VERSION_CHECK(5, 5, 0)
        QImage image(mat.data,
                     mat.cols, mat.rows,
                     static_cast<int>(mat.step),
                     QImage::Format_Grayscale8);
#else
        static QVector<QRgb>  sColorTable;

        // only create our color table the first time
        if (sColorTable.isEmpty())
        {
            sColorTable.resize( 256 );

            for ( int i = 0; i < 256; ++i )
            {
                sColorTable[i] = qRgb( i, i, i );
            }
        }

        QImage image(mat.data,
                     mat.cols, mat.rows,
                     static_cast<int>(mat.step),
                     QImage::Format_Indexed8 );

        image.setColorTable(sColorTable);
#endif
        return image;
    }

    // wrong
    default:
        break;
    }
    return QImage();
}


void OpenCVGLWidget::paintEvent(QPaintEvent *e)
{
    QPainter p;
    p.begin(this);
    p.drawImage(QPointF(0, 0), img);
    p.end();
}
