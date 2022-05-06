#include "RoundWidget.h"
#include <QBitmap>
#include <QPainter>

RoundWidget::RoundWidget()
{
//    this->setStyleSheet("border:5px solid rgb(85,255,255);");
}

RoundWidget::~RoundWidget()
{

}

void RoundWidget::resizeEvent(QResizeEvent *event)
{
    QBitmap bmp(size());
    bmp.fill();
    QPainter p(&bmp);
    p.setRenderHint(QPainter::SmoothPixmapTransform);
    //p.drawRoundedRect(bmp.rect(), 20, 20); //四个角都是圆弧
//    QPen pen;
//    pen.setWidth(5);
//    pen.setColor(QColor(85,255,255));
//    p.setPen(pen);
    //只要上边角圆弧
    int arcR = this->width() / 2; //圆弧大小
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

    return QWidget::resizeEvent(event);
}

void RoundWidget::paintEvent(QPaintEvent *event)
{

}
