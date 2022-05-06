#ifndef _DATA_EDIT_H_
#define _DATA_EDIT_H_

#include <QWidget>

class DataEdit : public QWidget
{
    Q_OBJECT
public:
    DataEdit(QWidget* parent = nullptr);
    ~DataEdit();

    QDateTime Get_Data() const;
};

#endif
