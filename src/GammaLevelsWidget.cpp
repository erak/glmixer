
#include <QtGui>
#include <cmath>

#include "RenderingManager.h"
#include "GammaLevelsWidget.moc"

#define GammaCorrection(color, gamma) pow(color, 1.f / gamma)
#define LevelsControlInputRange(color, minInput, maxInput)  qMin( qMax(color - minInput, 0.f) / (maxInput - minInput), 1.f)
#define LevelsControlInput(color, minInput, gamma, maxInput) GammaCorrection(LevelsControlInputRange(color, minInput, maxInput), gamma)
#define LevelsControlOutputRange(color, minOutput, maxOutput) ( minOutput*(1.f-color) + maxOutput*color  )
#define LevelsControl(color, minInput, gamma, maxInput, minOutput, maxOutput)   LevelsControlOutputRange(LevelsControlInput(color, minInput, gamma, maxInput), minOutput, maxOutput)



GammaLevelsWidget::GammaLevelsWidget(QWidget *parent) : QWidget(parent), source(0)
{
    setupUi(this);

    // replace dummy widget by plot
    gridLayoutGraphic->removeWidget ( plotWidget );
    delete plotWidget;
    plot = new GammaPlotArea(this);
    Q_CHECK_PTR(plot);
    plotWidget = (QWidget *) plot;
    gridLayoutGraphic->addWidget(plotWidget, 0, 1, 1, 1);
    QObject::connect(plot, SIGNAL(gammaChanged()), this, SLOT(updateSource()) );

    // setup plot
    plot->setPen(QPen( palette().color(QPalette::Highlight) ));
    plot->setAntialiased(true);

}

void GammaLevelsWidget::setAntialiasing(bool antialiased)
{
    plot->setAntialiased(antialiased);
}

void GammaLevelsWidget::connectSource(SourceSet::iterator csi){

    if ( RenderingManager::getInstance()->isValid(csi) ) {
        setEnabled(true);
        source = *csi;
        setValues(source->getGamma(), source->getGammaMinInput(), source->getGammaMaxInput(), source->getGammaMinOuput(), source->getGammaMaxOutput());

    } else {
        setEnabled(false);
        source = 0;
        setValues(1.f, 0.f, 1.f, 0.f, 1.f);
    }
}

void GammaLevelsWidget::setValues(float gamma, float minInput, float maxInput, float minOutput, float maxOutput){

    // setup values, with some sanity check
    plot->gamma = gamma;
    plot->xmin = qBound(minInput, 0.f, 1.f);
    plot->xmax = qBound(maxInput, 0.f, 1.f);
    plot->xmin = qMin(plot->xmax, plot->xmin);
    plot->ymin = qBound(minOutput, 0.f, 1.f);
    plot->ymax = qBound(maxOutput, 0.f, 1.f);
    plot->ymin = qMin(plot->ymax, plot->ymin);

    plot->update();

    QList<int> s = outSplit->sizes();
    int total = s[0] + s[1] + s[2];
    s[2] = plot->ymin * total;
    s[0] = total - total * plot->ymax;
    s[1] = total - s[0] - s[2];
    outSplit->setSizes(s);

    s = inSplit->sizes();
    total = s[0] + s[1] + s[2];
    s[0] = plot->xmin * total;
    s[2] = total - total * plot->xmax;
    s[1] = total - s[0] - s[2];
    inSplit->setSizes(s);
}

void GammaLevelsWidget::showEvent ( QShowEvent * event ){

    QWidget::showEvent(event);

    QList<int> s = outSplit->sizes();
    int total = s[0] + s[1] + s[2];
    s[2] = plot->ymin * total;
    s[0] = total - total * plot->ymax;
    s[1] = total - s[0] - s[2];
    outSplit->setSizes(s);

    s = inSplit->sizes();
    total = s[0] + s[1] + s[2];
    s[0] = plot->xmin * total;
    s[2] = total - total * plot->xmax;
    s[1] = total - s[0] - s[2];
    inSplit->setSizes(s);

    plot->update();
}


void GammaLevelsWidget::on_resetButton_clicked (){

    setValues(1.f, 0.f, 1.f, 0.f, 1.f);

    updateSource();
}

float GammaLevelsWidget::minOutput(){

    return plot->ymin;
}

float GammaLevelsWidget::maxOutput(){

    return plot->ymax;
}

float GammaLevelsWidget::minInput(){

    return plot->xmin;
}

float GammaLevelsWidget::maxInput(){

    return plot->xmax;
}

float GammaLevelsWidget::gamma(){

    return plot->gamma;
}


void GammaLevelsWidget::on_inSplit_splitterMoved ( int pos, int index )
{
    int min = 0, max = 0;
    inSplit->getRange ( index, &min, &max );

    if (index == 1){
        plot->xmin = (float)(pos-min) / (float)(max-min);
        plot->xmax = qMax( plot->xmax, (plot->xmin + 0.01f));
    } else {
        plot->xmax = (float)(pos-min) / (float)(max-min);
        plot->xmin = qMin( (plot->xmax - 0.01f), plot->xmin);
    }

    updateSource();
}

void GammaLevelsWidget::on_outSplit_splitterMoved ( int pos, int index )
{
    int min = 0, max = 0;
    outSplit->getRange ( index, &min, &max );

    if (index == 2) {
        plot->ymin = 1.f - (float)(pos-min) / (float)(max-min);
        plot->ymax = qMax(plot->ymax, plot->ymin);
    } else {
        plot->ymax = 1.f - (float)(pos-min) / (float)(max-min);
        plot->ymin = qMin(plot->ymax, plot->ymin);
    }

    updateSource();
}

void GammaLevelsWidget::updateSource()
{
    plot->update();

    if (source)
        source->setGamma(plot->gamma, plot->xmin, plot->xmax, plot->ymin, plot->ymax);
}

GammaPlotArea::GammaPlotArea(QWidget *parent) : QWidget(parent), gamma(1.0), xmin(0.0), xmax(1.0), ymin(0.0), ymax(1.0)
{
    antialiased = false;

    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
}

QSize GammaPlotArea::minimumSizeHint() const
{
    return QSize(100, 50);
}

QSize GammaPlotArea::sizeHint() const
{
    return QSize(200, 200);
}

void GammaPlotArea::setPen(const QPen &pen)
{
    this->pen = pen;
    this->pen.setWidth(2);
    update();
}


void GammaPlotArea::setAntialiased(bool antialiased)
{
    this->antialiased = antialiased;
    update();
}

void GammaPlotArea::mouseMoveEvent ( QMouseEvent * event )
{
    if (event->buttons() != Qt::NoButton)
    {
        int y = qBound( 0, event->y(), this->height());
        gamma = ScaleToGamma( (1.f - ((float) y / (float) this->height()) ) * 1000.0 );

//        qDebug() << (1.f - ((float) y / (float) this->height()) ) * 1000.0;
//        qDebug() << gamma;
        emit gammaChanged();
    }
}


void GammaPlotArea::wheelEvent ( QWheelEvent * event )
{
    int lg = GammaToScale(gamma) + event->delta() / 2;
    gamma = ScaleToGamma( qBound(0, lg, 1000) );
    emit gammaChanged();
}

void GammaPlotArea::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    QPen p(Qt::DotLine);

    // draw grid
    if (!isEnabled())
        p.setColor(Qt::lightGray);
    else
        p.setColor(Qt::darkGray);
    painter.setPen(p);
    for (int x = 0; x < width(); x += width()/4)
        painter.drawLine(x, 0, x, height());
    for (int y = 0; y < height(); y += height() / 4)
        painter.drawLine(0, y, width(), y);

    // draw plot
    if (isEnabled()){
        painter.setPen(pen);
        if (antialiased)
            painter.setRenderHint(QPainter::Antialiasing, true);

        float incr = 1.f / (float)( NUM_POINTS_PLOT - 1);
        float x = 0.f;
        float y = 0.f;
        for (int i = 0; i < NUM_POINTS_PLOT; i++, x += incr) {

            y = LevelsControl(x, xmin, gamma, xmax, ymin, ymax);

            points[i].setX( (int) (x * (float) width() ) );
            points[i].setY( height() - (int)( y * (float) height() ) );

        }
        painter.drawPolyline(points, NUM_POINTS_PLOT);
        QPoint tp = points[NUM_POINTS_PLOT/2] + QPoint( gamma < 1 ? -50 : 5, gamma < 1 ? -10 : 10 );
        painter.drawText( tp, QString::number(gamma,'f',3));

    }

    // draw frame
    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setPen(palette().dark().color());
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(QRect(0, 0, width() - 1, height() - 1));

    QWidget::paintEvent(e);
}

