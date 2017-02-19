#ifndef LAYOUTTOOLBOXWIDGET_H
#define LAYOUTTOOLBOXWIDGET_H


#include <QWidget>
#include "View.h"
#include "ui_LayoutToolboxWidget.h"

class LayoutToolboxWidget : public QWidget, public Ui::LayoutToolboxWidget
{
    Q_OBJECT
public:

    LayoutToolboxWidget(QWidget *parent = 0);
    ~LayoutToolboxWidget();
    
signals:
    
public slots:

    void setViewMode(View::viewMode mode);

    // Size
    void on_sizeHorizontalButton_clicked();
    void on_sizeHorizontalFrameButton_clicked();
    void on_sizeVerticalButton_clicked();
    void on_sizeVerticalFrameButton_clicked();
    void on_sizeRenderingAspectButton_clicked();
    void on_sizeOriginalAspectButton_clicked();

    // Rotate and flip
    void on_rotateClockwiseButton_clicked();
    void on_rotateCounterclockwiseButton_clicked();
    void on_flipHorizontalButton_clicked();
    void on_flipVerticalButton_clicked();

    // Align
    void on_alignHorizontalLeftButton_clicked();
    void on_alignHorizontalCenterButton_clicked();
    void on_alignHorizontalRightButton_clicked();
    void on_alignVerticalBottomButton_clicked();
    void on_alignVerticalCenterButton_clicked();
    void on_alignVerticalTopButton_clicked();
    void on_alignHorizontalLeftFrameButton_clicked();
    void on_alignHorizontalCenterFrameButton_clicked();
    void on_alignHorizontalRightFrameButton_clicked();
    void on_alignVerticalBottomFrameButton_clicked();
    void on_alignVerticalCenterFrameButton_clicked();
    void on_alignVerticalTopFrameButton_clicked();

    // Distribute
    void on_distributeHorizontalLeftButton_clicked();
    void on_distributeHorizontalCenterButton_clicked();
    void on_distributeHorizontalRightButton_clicked();
    void on_distributeHorizontalGapsButton_clicked();
    void on_distributeVerticalBottomButton_clicked();
    void on_distributeVerticalCenterButton_clicked();
    void on_distributeVerticalTopButton_clicked();
    void on_distributeVerticalGapsButton_clicked();


};

#endif // LAYOUTTOOLBOXWIDGET_H
