#ifndef NEWSOURCEDIALOG_H
#define NEWSOURCEDIALOG_H

#include <QDialog>
#include "Source.h"

namespace Ui {
class NewSourceDialog;
}

class NewSourceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewSourceDialog(QWidget *parent = 0);
    ~NewSourceDialog();

    Source::RTTI selectedType();

private:
    Ui::NewSourceDialog *ui;
};

#endif // NEWSOURCEDIALOG_H
