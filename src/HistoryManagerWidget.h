#ifndef HISTORYMANAGERWIDGET_H
#define HISTORYMANAGERWIDGET_H

#include <QAbstractTableModel>
#include <QTableView>

#include "HistoryManager.h"


class HistoryManagerModel : public QAbstractTableModel
{

public:
    explicit HistoryManagerModel(QWidget *parent = 0);

    // set history to display
    void setHistoryMap(const QMultiMap<qint64, HistoryManager::Event *> &map);

    // implementation of QAbstractTable
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

private:
    QMultiMap<qint64, HistoryManager::Event *> _historyMap;

};

class HistoryManagerWidget : public QTableView
{
    Q_OBJECT

public:
    explicit HistoryManagerWidget(QWidget *parent = 0);

    void setHistoryManager(HistoryManager *hm);

public slots:
    void updateHistory();

private:
    HistoryManager *_history;
    HistoryManagerModel _historyModel;
};

#endif // HISTORYMANAGERWIDGET_H
