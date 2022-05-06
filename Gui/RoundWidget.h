#ifndef _ROUND_WIDGET_H_
#define _ROUND_WIDGET_H_

#include <QWidget>

class RoundWidget : public QWidget
{
public:
    RoundWidget();
    ~RoundWidget();

protected:
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
};

#endif // _ROUND_WIDGET_H_
