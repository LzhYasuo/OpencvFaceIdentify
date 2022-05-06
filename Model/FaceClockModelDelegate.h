#ifndef FACE_CLOCK_MODEL_DELEGATE_H_
#define FACE_CLOCK_MODEL_DELEGATE_H_

#include <QObject>
#include <QAbstractTableModel>
#include <QItemDelegate>

class FaceClockModelItem
{
public:
    FaceClockModelItem();
    ~FaceClockModelItem();

    QString GetName() const
    {
        return _name;
    }
    void SetName(const QString &name)
    {
        _name = name;
    }

    QString GetId() const
    {
        return _id;
    }
    void SetId(const QString &id)
    {
        _id = id;
    }

    QString GetDateTime() const
    {
        return _dateTime;
    }
    void SetDateTime(QString datetime)
    {
        _dateTime = datetime;
    }

private:
    QString _name;
    QString _id;
    QString _dateTime;
};

class FaceClockTableModel: public QAbstractTableModel
{
    Q_OBJECT
public:
    FaceClockTableModel(QObject* parent = nullptr);
    ~FaceClockTableModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::DisplayRole);
    void RefrushModel(FaceClockModelItem);
    void setHorizontalHeaderList(QStringList hHeadList);
    void setVerticalHeaderList(QStringList VHeadList);
    void RefrushModelData();
    void PushBackData(QList<QStringList> data);
    void PopBackData();
private:
    QStringList horizontal_header_list;
    QStringList vertical_header_list;
    QList<FaceClockModelItem> Ary_row_List;
};

class FaceClockModelDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit FaceClockModelDelegate(QObject *parent = nullptr);
    virtual ~FaceClockModelDelegate();

    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    int Get_ClickedRow() const
    {
        return ClickedRow;
    }
    void Set_ClickedRow(int row)
    {
        ClickedRow = row;
    }
private:
    int ClickedRow = -1;
};


#endif //FACE_CLOCK_MODEL_DELEGATE_H_
