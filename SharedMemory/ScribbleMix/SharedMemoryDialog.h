/*
 * SharedMemoryDialog.h
 *
 *  Created on: Aug 6, 2011
 *      Author: bh
 */

#ifndef SHAREDMEMORYDIALOG_H_
#define SHAREDMEMORYDIALOG_H_


#include <QtGui>


class SharedMemoryDialog : public QDialog
{
    Q_OBJECT

public:
	SharedMemoryDialog(QWidget *parent = 0);
	virtual ~SharedMemoryDialog();

	qint64 getSelectedId();
	QString getSelectedProcess();

public Q_SLOTS:

	void done(int r);
	void setCurrent(const QItemSelection & selected, const QItemSelection & deselected);

protected:
	void showEvent(QShowEvent *);
        void timerEvent(QTimerEvent *event);

private:
        int updateListTimer;

        QStandardItemModel *listExistingShmModel;
        QStandardItem *selectedItem;

        void createPreview();

        void setupUi(QDialog *);
        QVBoxLayout *verticalLayout;
        QLabel *label_2;
        QListView *listExistingShm;
        QDialogButtonBox *buttonBox;
};

#endif /* SHAREDMEMORYDIALOG_H_ */
