#include "common.h"
#include "testbuttonframe.moc"

#include <QtGui>

//QString TestButtonFrame::ssDefault = "QFrame {border: 1px solid black;border-radius : 5px;background-color: rgb(130, 130, 130);} QFrame:hover { background-color: rgb(150, 150, 150); } ";
//QString TestButtonFrame::ssSet = "QFrame {border: 1px solid black;border-radius : 5px;background-color: rgb(130, 150, 130);} QFrame:hover { background-color: rgb(100, 150, 100); } ";

TestButtonFrame::TestButtonFrame(QWidget * parent, Qt::WindowFlags f):QWidget(parent, f) {

    setMouseTracking ( true );

    assignedBrushColor = palette().color(QPalette::Highlight);
    assignedPenColor = palette().color(QPalette::Highlight);
    unassignedBrushColor = palette().color(QPalette::Button);
    unassignedPenColor = palette().color(QPalette::Mid);

    reset();
}

bool TestButtonFrame::event(QEvent *event)
{
    if (event->type() == QEvent::ToolTip) {
        QHelpEvent *helpEvent = static_cast<QHelpEvent *>(event);

        if (hover != View::INPUT_NONE) {
            QToolTip::showText(helpEvent->globalPos(), View::userInputLabel(hover, true));
        } else {
            QToolTip::hideText();
            event->ignore();
        }

        return true;
    }
    return QWidget::event(event);
}


void TestButtonFrame::leaveEvent(QEvent *event){

    hover = View::INPUT_NONE;
    emit inputChanged("");
    repaint();
}


void TestButtonFrame::tabletEvent(QTabletEvent *event){

    if( event->pointerType() == QTabletEvent::Eraser && event->pressure() > 0.01) {

        QMouseEvent e(QEvent::MouseButtonPress, QPoint(event->x(),event->y()), Qt::XButton1, Qt::XButton1, event->modifiers());

        mousePressEvent(&e);

        event->accept();
    }
    else
        event->ignore();
}

void TestButtonFrame::mousePressEvent(QMouseEvent *event){

    int b;
    // which action box was clicked ?
    View::UserInput clicked = View::INPUT_NONE;
    for (b = 0; b < View::INPUT_NONE; ++b) {
        if ( qareamap[(View::UserInput) b].contains(event->pos()) ) {
            clicked = (View::UserInput) b;
            break;
        }
    }

    // special case; SELECT MUST have a modifier
    if (clicked == View::INPUT_SELECT && QApplication::keyboardModifiers() == Qt::NoModifier ) {
        qCritical()<< tr("Selection action *must* use a modifier key (e.g. [CTRL]).");
        return;
    }

    // discard all other actions with the same button and modifiers
    for (b = 0; b < View::INPUT_NONE; ++b) {
        if ( qbuttonmap[(View::UserInput) b] == event->buttons() && qmodifiermap[(View::UserInput) b] == QApplication::keyboardModifiers()) {
            qbuttonmap[(View::UserInput) b] = Qt::NoButton;
            qmodifiermap[(View::UserInput) b] = Qt::NoModifier;
        }
    }

    // assign button and modifiers to this action
    qbuttonmap[clicked] = event->buttons();
    qmodifiermap[clicked] = QApplication::keyboardModifiers();
    emit inputChanged( View::userInputDescription(clicked, qbuttonmap, qmodifiermap));

    update();
}

void TestButtonFrame::mouseMoveEvent(QMouseEvent *event){

    QString text;
    hover = View::INPUT_NONE;
    QString action;
    for (int b = 0; b < View::INPUT_NONE; ++b) {
        if ( qareamap[(View::UserInput) b].contains(event->pos()) ) {
            hover = (View::UserInput) b;
            emit inputChanged( View::userInputDescription(hover, qbuttonmap, qmodifiermap));
            break;
        }
    }
    update();
}


void TestButtonFrame::paintEvent(QPaintEvent *event){

    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.fillRect(event->rect(), palette().window());

    QFont f = font();
    f.setPixelSize(12);
    painter.setFont(f);
    QColor colortext, colorbrush;

    int w = event->rect().width();
    for (int b = 0; b < View::INPUT_NONE; ++b) {

        if ( qbuttonmap[(View::UserInput) b] == Qt::NoButton ) {
            colorbrush = unassignedBrushColor;
            painter.setPen(unassignedPenColor);
            colortext = palette().color(QPalette::ButtonText);
        } else {
            colorbrush = assignedBrushColor;
            painter.setPen(assignedPenColor);
            colortext = palette().color(QPalette::HighlightedText);
        }

        if (b != hover)
            colorbrush.setAlpha(128);

        painter.setBrush(QBrush(colorbrush));
        qareamap[(View::UserInput) b].setRect( w * b / View::INPUT_NONE + b, 1, w / View::INPUT_NONE - View::INPUT_NONE, event->rect().height() -1 );
        painter.drawRoundRect(qareamap[(View::UserInput) b], 20, 20);

        if (b == View::INPUT_SELECT )
            painter.drawRoundRect(qareamap[(View::UserInput) b].adjusted(4, 4, -4, -4), 20, 20);

        painter.setPen(colortext);
        painter.drawText(qareamap[(View::UserInput) b], Qt::AlignCenter, View::userInputLabel((View::UserInput) b));

    }

    painter.end();
}


void TestButtonFrame::setConfiguration(QMap<int, int> buttonmap, QMap<int, int> modifiermap) {

    QMapIterator<int, int> i(buttonmap);
    while ( i.hasNext() ) {
        i.next();
        qbuttonmap [ (View::UserInput) i.key() ] = Qt::MouseButtons(i.value());
    }

    QMapIterator<int, int> j(modifiermap);
    while ( j.hasNext() ) {
        j.next();
        qmodifiermap [ (View::UserInput) j.key() ] = Qt::KeyboardModifiers(j.value());
    }

    update();
}

void TestButtonFrame::reset() {

    qbuttonmap = View::defaultMouseButtonsMap();
    qmodifiermap = View::defaultModifiersMap();

    update();
}


void TestButtonFrame::unset() {

    QMapIterator<View::UserInput,Qt::KeyboardModifiers> i(qmodifiermap);
    while ( i.hasNext() ) {
        i.next();
        qmodifiermap[i.key()] = Qt::NoModifier;;
    }
    QMapIterator<View::UserInput,Qt::MouseButtons> j(qbuttonmap);
    while ( j.hasNext() ) {
        j.next();
        qbuttonmap[j.key()] = Qt::NoButton;
    }

    update();
}

