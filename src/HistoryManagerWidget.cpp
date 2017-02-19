#include "HistoryManagerWidget.moc"


HistoryManagerWidget::HistoryManagerWidget(QWidget *parent) : QTableView(parent)
{
    setModel(&_historyModel);

    setAutoScroll(true);

    setColumnWidth(0, 60);
    setColumnWidth(1, 100);
    setColumnWidth(2, 180);
    setColumnWidth(3, 220);
    setColumnWidth(4, 220);

}

void HistoryManagerWidget::setHistoryManager(HistoryManager *hm)
{
    _history = hm;
    updateHistory();
}

void HistoryManagerWidget::updateHistory()
{
    // reload the events
    _historyModel.setHistoryMap( _history->events() );

    // scroll to end of list
    scrollToBottom ();

    // resize height
    resizeRowsToContents();
//    resizeColumnsToContents();
}


HistoryManagerModel::HistoryManagerModel(QWidget *parent) : QAbstractTableModel(parent)
{

}


void HistoryManagerModel::setHistoryMap(const QMultiMap<qint64, HistoryManager::Event *> &map)
{
    _historyMap = map;
    reset();
}


int HistoryManagerModel::rowCount(const QModelIndex &parent) const
{
    return _historyMap.size();
}

int HistoryManagerModel::columnCount(const QModelIndex &parent) const
{
    return 5;
}

QVariant HistoryManagerModel::data(const QModelIndex &index, int role) const
{
    static QFont standardFont("Monospace", QFont().pointSize() * 0.8);
    static QFont keyFont("Monospace", QFont().pointSize() * 0.8, QFont::Bold, true);

    if (!index.isValid())
           return QVariant();

    QVariant returnvalue;
    if (role == Qt::TextAlignmentRole) {

        returnvalue = int(Qt::AlignRight | Qt::AlignVCenter);
    }
    else if (role == Qt::DisplayRole) {

        QMultiMap<qint64, HistoryManager::Event *>::const_iterator i = _historyMap.begin() + index.row();

        if ( index.column() == 0 )
            returnvalue = i.key();
        else if ( index.column() == 1 )
            returnvalue = i.value()->objectName();
        else if ( index.column() == 2 )
            returnvalue = i.value()->signature().section('(',0,0);
        else if ( index.column() == 3 )
            returnvalue = i.value()->arguments(HistoryManager::BACKWARD);
        else if ( index.column() == 4 )
            returnvalue = i.value()->arguments(HistoryManager::FORWARD);
    }


    return returnvalue;
}

QVariant HistoryManagerModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    QVariant returnvalue;
    if ( orientation == Qt::Horizontal ) {
        static QStringList header  = QStringList() << "t" << "object" << "method" << "before" << "after";
        returnvalue = header.at(section);
    }

    return returnvalue;
}
