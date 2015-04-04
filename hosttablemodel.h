#ifndef ANDROIDHOSTTABLEMODEL_H
#define ANDROIDHOSTTABLEMODEL_H

#include <QMutexLocker>
#include <time.h>
#include <QAbstractTableModel>
#include <QHostAddress>
#include <QStringList>
#include <QTimer>
#include <vector>
#include <map>
using std::vector;
using std::map;

struct Addr
{
    QString host;
    quint16 port;
};

struct HostItem
{
    QString info;
    Addr addr;
    QString address;
    time_t lastAccessTime;
    bool checked;
};

class HostTableModel: public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit HostTableModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;              //重载QAbstractItemModel的rowCount函数
    int columnCount(const QModelIndex &parent = QModelIndex()) const;           //重载QAbstractItemModel的columnCount函数
    QVariant data(const QModelIndex &index, int role) const;                    //重载QAbstractItemModel的data函数
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;      //重载QAbstractItemModel的headerData函数
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    time_t getTimeout() const;
    void setTimeout(const time_t &value);

public slots:
    void putItem(QString info, QString host, quint16 port);
    void cleanTimeoutItem();
    void cleanAll();

public slots:
    void selectAll();
    void unselectAll();
    void reverseSelect();

private:
    map<QString, HostItem*> mItemIndex;
    vector<HostItem*> mItemList;
    QStringList headList;
    QMutex mMutex;
    QTimer mTimer;
    time_t mTimeout;
};

#endif // ANDROIDHOSTTABLEMODEL_H