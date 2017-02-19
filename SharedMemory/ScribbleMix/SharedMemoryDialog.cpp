/*
 * SharedMemoryDialog.cpp
 *
 *  Created on: Aug 6, 2011
 *      Author: bh
 */

#include <QtDebug>
#include <QAbstractListModel>

#include "SharedMemoryManager.h"

#include "SharedMemoryDialog.moc"

void fillModel(QStandardItemModel *model, QMap<qint64, QVariantMap> map)
{

    // do not add elements of the map which are already in the model
	// and remove elements from the model if they are not in the map
    for (int r = 0; r < model->rowCount(); ++r) {
    	qint64 key = model->item(r)->data(Qt::UserRole).toLongLong();
    	if ( map.count(key) )
    		map.remove(key);
    	else
    		model->removeRow(r);
    }

    // add the remaining elements of the map to the model
	QMapIterator<qint64, QVariantMap> i(map);
	while (i.hasNext()) {
		i.next();

		// try to get an icon
		QPixmap icon;
		QVariant variant = i.value()["icon"];
		if (variant.isValid())
			icon = variant.value<QPixmap>();
		else
                        icon = QPixmap(":/icons/gear.png");

		// create list item
		QStandardItem  *item = new QStandardItem(QIcon(icon), i.value()["program"].toString());
		item->setData(i.key(), Qt::UserRole );

		// setup a tooltip to inform user
	    QString tooltip = QString("%1 (%2x%3)").arg(i.value()["info"].toString()).arg(i.value()["size"].toSize().width()).arg(i.value()["size"].toSize().height());
	    item->setData(tooltip, Qt::ToolTipRole );

	    // append item
		model->appendRow(item);
	}

}


SharedMemoryDialog::SharedMemoryDialog(QWidget *parent) : QDialog(parent), selectedItem(0)  {

    setupUi(this);

    listExistingShmModel = new QStandardItemModel(0, 0, this);
    listExistingShm->setModel(listExistingShmModel);

    connect(listExistingShm->selectionModel(), SIGNAL( selectionChanged(const QItemSelection &, const QItemSelection &) ), this, SLOT( setCurrent(const QItemSelection &, const QItemSelection &) )  );
}

SharedMemoryDialog::~SharedMemoryDialog() {


	delete listExistingShmModel;

}

void SharedMemoryDialog::done(int r){

	killTimer(updateListTimer);

	QDialog::done(r);
}


void SharedMemoryDialog::timerEvent(QTimerEvent *) {

	fillModel(listExistingShmModel, SharedMemoryManager::getInstance()->getSharedMap());

}


qint64 SharedMemoryDialog::getSelectedId(){

	if (selectedItem)
		return selectedItem->data(Qt::UserRole).toLongLong();

	return 0;
}

QString SharedMemoryDialog::getSelectedProcess(){

	if (selectedItem)
		return selectedItem->data(Qt::DisplayRole).toString();

	return QString();
}

void SharedMemoryDialog::showEvent(QShowEvent *e){

	// clear selection
        listExistingShm->clearSelection();

	// start the update of the list of existing shared memory clients
	fillModel(listExistingShmModel, SharedMemoryManager::getInstance()->getSharedMap());
	updateListTimer = startTimer(1000);

	QWidget::showEvent(e);
}



void SharedMemoryDialog::setCurrent(const QItemSelection & selected, const QItemSelection &) {

	static QPushButton *okbutton = buttonBox->addButton(QDialogButtonBox::Ok);;

	if (selected.isEmpty()) {

		// cannot Ok this dialog without a selection
		okbutton->hide();

		// no item selected
		selectedItem = 0;

	} else
	{
		// can confirm
		okbutton->show ();

		// read parameters of currently selected item
		selectedItem = listExistingShmModel->itemFromIndex(selected.indexes().first());

	}

}

void SharedMemoryDialog::setupUi(QDialog *SharedMemoryDialog)
{
    if (SharedMemoryDialog->objectName().isEmpty())
        SharedMemoryDialog->setObjectName(QString::fromUtf8("SharedMemoryDialog"));

    SharedMemoryDialog->resize(234, 406);

    verticalLayout = new QVBoxLayout(SharedMemoryDialog);
    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));

    label_2 = new QLabel(SharedMemoryDialog);
    label_2->setObjectName(QString::fromUtf8("label_2"));
    QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
    label_2->setSizePolicy(sizePolicy1);

    verticalLayout->addWidget(label_2);

    listExistingShm = new QListView(SharedMemoryDialog);
    listExistingShm->setObjectName(QString::fromUtf8("listExistingShm"));
    QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Maximum);
    sizePolicy2.setHorizontalStretch(0);
    sizePolicy2.setVerticalStretch(0);
    sizePolicy2.setHeightForWidth(listExistingShm->sizePolicy().hasHeightForWidth());
    listExistingShm->setSizePolicy(sizePolicy2);
    listExistingShm->setEditTriggers(QAbstractItemView::NoEditTriggers);
    listExistingShm->setTabKeyNavigation(true);
    listExistingShm->setProperty("showDropIndicator", QVariant(false));
    listExistingShm->setDragDropMode(QAbstractItemView::DragDrop);
    listExistingShm->setIconSize(QSize(32, 32));
    listExistingShm->setSpacing(8);
    listExistingShm->setViewMode(QListView::IconMode);

    verticalLayout->addWidget(listExistingShm);

    buttonBox = new QDialogButtonBox(SharedMemoryDialog);
    buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel);

    verticalLayout->addWidget(buttonBox);


    SharedMemoryDialog->setWindowTitle(QApplication::translate("SharedMemoryDialog", "Shared Memory Dialog", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("SharedMemoryDialog", "Select a program to connect to:", 0, QApplication::UnicodeUTF8));

    QObject::connect(buttonBox, SIGNAL(accepted()), SharedMemoryDialog, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), SharedMemoryDialog, SLOT(reject()));

    QMetaObject::connectSlotsByName(SharedMemoryDialog);
} // setupUi


