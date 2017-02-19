#ifndef FFGLEFFECTSELECTIONDIALOG_H
#define FFGLEFFECTSELECTIONDIALOG_H

#include <QDialog>
#include <QSettings>

namespace Ui {
class FFGLEffectSelectionDialog;
}

class FFGLEffectSelectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FFGLEffectSelectionDialog(QWidget *parent = 0, QSettings *settings = 0);
    ~FFGLEffectSelectionDialog();

    QString getSelectedFreeframePlugin() const { return selectedFreeframePlugin;}

public slots:
    void done(int r);
    void updateSourcePreview();

    void browseFreeframePlugin();
    void deleteFreeframePlugin();
    void showFreeframeHelp();

protected:
    void showEvent(QShowEvent *);

private:
    Ui::FFGLEffectSelectionDialog *ui;

    QString selectedFreeframePlugin;
    class Source *s;
    QSettings *appSettings;
};

#endif // FFGLEFFECTSELECTIONDIALOG_H
