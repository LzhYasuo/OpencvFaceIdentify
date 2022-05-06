#ifndef FACE_INFO_MODEL_DELEGATE_H_
#define FACE_INFO_MODEL_DELEGATE_H_

#include <QObject>
#include <QAbstractTableModel>
#include <QItemDelegate>

class FaceInfoModelItem
{
public:
    FaceInfoModelItem();
    ~FaceInfoModelItem();

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

private:
    QString _name;
    QString _id;
};

class FaceInfoTableModel: public QAbstractTableModel
{
    Q_OBJECT
public:
    FaceInfoTableModel(QObject* parent = nullptr);
    ~FaceInfoTableModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::DisplayRole);
    void RefrushModel(FaceInfoModelItem);
    void setHorizontalHeaderList(QStringList hHeadList);
    void setVerticalHeaderList(QStringList VHeadList);
    void RefrushModelData();
    void PushBackData(QList<QStringList> data);
    void PopBackData();
private:
    QStringList horizontal_header_list;
    QStringList vertical_header_list;
    QList<FaceInfoModelItem> Ary_row_List;
};

class FaceInfoModelDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit FaceInfoModelDelegate(QObject *parent = nullptr);
    virtual ~FaceInfoModelDelegate();

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


#endif //FACE_INFO_MODEL_DELEGATE_H_
