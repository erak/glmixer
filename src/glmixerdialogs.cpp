#include "glmixerdialogs.moc"

#include "RenderingManager.h"


int CaptureDialog::getWidth()
{
    return presetsSizeComboBox->itemData(presetsSizeComboBox->currentIndex()).toInt();
}

CaptureDialog::CaptureDialog(QWidget *parent, QImage capture, QString caption): QDialog(parent), img(capture) {

    QVBoxLayout *verticalLayout;
    QLabel *Question, *Display, *Info, *Property;
    QDialogButtonBox *DecisionButtonBox;

    setObjectName(QString::fromUtf8("CaptureDialog"));
    setWindowTitle(tr( "GLMixer - Frame capture"));
    verticalLayout = new QVBoxLayout(this);
    verticalLayout->setSpacing(9);

    Question = new QLabel(this);
    Question->setText(caption);
    verticalLayout->addWidget(Question);

    Display = new QLabel(this);
    Display->setPixmap(QPixmap::fromImage(img).scaledToWidth(400));
    verticalLayout->addWidget(Display);

    Info = new QLabel(this);
    Info->setText(tr("Original size: %1 x %2 px").arg(img.width()).arg(img.height()) );
    verticalLayout->addWidget(Info);


    QGroupBox *sizeGroupBox = new QGroupBox(this);
    sizeGroupBox->setTitle(tr("Pixel resolution"));
    sizeGroupBox->setFlat(true);
    verticalLayout->addWidget(sizeGroupBox);

    QHBoxLayout *horizontalLayout = new QHBoxLayout(sizeGroupBox);

    Property = new QLabel(sizeGroupBox);
    Property->setText(tr("Width x Height "));
    horizontalLayout->addWidget(Property);

    presetsSizeComboBox = new QComboBox(sizeGroupBox);
    int w = img.width();
    double ar = (double) img.height() / (double) img.width();
    presetsSizeComboBox->addItem(QString::fromUtf8("%1 x %2 (original)").arg(w).arg((int)((double) w * ar)));
    w = (int) ( (double) img.width() * 0.8 );
    presetsSizeComboBox->addItem(QString::fromUtf8("%1 x %2 (80%)").arg(w).arg((int)((double) w * ar)), QVariant(w));
    w = (int) ( (double) img.width() * 0.6 );
    presetsSizeComboBox->addItem(QString::fromUtf8("%1 x %2 (60%)").arg(w).arg((int)((double) w * ar)), QVariant(w));
    w = (int) ( (double) img.width() * 0.4 );
    presetsSizeComboBox->addItem(QString::fromUtf8("%1 x %2 (40%)").arg(w).arg((int)((double) w * ar)), QVariant(w));
    w = (int) ( (double) img.width() * 0.2 );
    presetsSizeComboBox->addItem(QString::fromUtf8("%1 x %2 (20%)").arg(w).arg((int)((double) w * ar)), QVariant(w));
    horizontalLayout->addWidget(presetsSizeComboBox);

    DecisionButtonBox = new QDialogButtonBox(this);
    DecisionButtonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
    verticalLayout->addWidget(DecisionButtonBox);

    QObject::connect(DecisionButtonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(DecisionButtonBox, SIGNAL(rejected()), this, SLOT(reject()));
}


bool RenderingSourceDialog::getRecursive()
{
    return recursiveButton->isChecked();
}

RenderingSourceDialog::RenderingSourceDialog(QWidget *parent): QDialog(parent)
{

    QVBoxLayout *verticalLayout;
    QLabel *Question, *Display, *Info;
    QDialogButtonBox *DecisionButtonBox;
    QHBoxLayout *horizontalLayout;
    QToolButton *nonrecursiveButton;

    setObjectName(QString::fromUtf8("RenderingSourceDialog"));
    setWindowTitle(tr( "GLMixer - New Rendering Source"));
    verticalLayout = new QVBoxLayout(this);
    verticalLayout->setSpacing(9);

    Question = new QLabel(this);
    Question->setText(tr(" Choose recursive or non-recursive loop-back:"));
    verticalLayout->addWidget(Question);

    Display = new QLabel(this);
    Display->setText(tr("Recursive \t\t\tSimple"));
    verticalLayout->addWidget(Display);

    horizontalLayout = new QHBoxLayout(this);
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    horizontalLayout->setContentsMargins(0, 0, 0, 0);
    recursiveButton = new QToolButton(this);
    recursiveButton->setObjectName(QString::fromUtf8("recursiveButton"));
    recursiveButton->setCheckable(true);
    recursiveButton->setChecked(true);
    recursiveButton->setAutoExclusive(true);
    QPixmap i(QString::fromUtf8(":/glmixer/images/loopback_recursive.png")) ;
    recursiveButton->setIcon( QIcon(i) );
    recursiveButton->setIconSize( i.size() );

    horizontalLayout->addWidget(recursiveButton);

    nonrecursiveButton = new QToolButton(this);
    nonrecursiveButton->setObjectName(QString::fromUtf8("nonrecursiveButton"));
    nonrecursiveButton->setCheckable(true);
    nonrecursiveButton->setAutoExclusive(true);
    i = QPixmap(QString::fromUtf8(":/glmixer/images/loopback_non_recursive.png")) ;
    nonrecursiveButton->setIcon( QIcon(i) );
    nonrecursiveButton->setIconSize( i.size() );

    horizontalLayout->addWidget(nonrecursiveButton);

    verticalLayout->addLayout(horizontalLayout);

    Info = new QLabel(this);
    Info->setStyleSheet("font: italic 9pt");
    if (RenderingManager::getInstance()->useFboBlitExtension())
        Info->setText(tr("Rendering mode optimal (Frame Buffer Blit enabled)."));
    else
        Info->setText(tr("Rendering mode not optimal (Frame Buffer Blit disabled).") );
    verticalLayout->addWidget(Info);

    DecisionButtonBox = new QDialogButtonBox(this);
    DecisionButtonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
    verticalLayout->addWidget(DecisionButtonBox);

    QObject::connect(DecisionButtonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(DecisionButtonBox, SIGNAL(rejected()), this, SLOT(reject()));
}



SourceFileEditDialog::SourceFileEditDialog(QWidget *parent, Source *source, QString caption): QDialog(parent), s(source) {

    QVBoxLayout *verticalLayout;
    QDialogButtonBox *DecisionButtonBox;

    setObjectName(QString::fromUtf8("SourceEditDialog"));
    setWindowTitle(caption);
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    verticalLayout = new QVBoxLayout(this);
    verticalLayout->setSpacing(9);

    sourcedisplay = new SourceDisplayWidget(this, SourceDisplayWidget::GRID);
    sourcedisplay->setMinimumSize(QSize(160, 100));
    sourcedisplay->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    sourcedisplay->setSource(s);
    verticalLayout->addWidget(sourcedisplay);

    specificSourcePropertyBrowser = SourcePropertyBrowser::createSpecificPropertyBrowser(s, this);
    specificSourcePropertyBrowser->setDisplayPropertyTree(false);
    specificSourcePropertyBrowser->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    verticalLayout->addWidget(specificSourcePropertyBrowser);

    DecisionButtonBox = new QDialogButtonBox(this);
    DecisionButtonBox->setStandardButtons(QDialogButtonBox::Ok);
    DecisionButtonBox->addButton("Replace by another source", QDialogButtonBox::RejectRole);
    verticalLayout->addWidget(DecisionButtonBox);

    QObject::connect(DecisionButtonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(DecisionButtonBox, SIGNAL(rejected()), this, SLOT(reject()));
    QObject::connect(DecisionButtonBox, SIGNAL(rejected()), parent, SLOT(replaceCurrentSource()));
}




void setupAboutDialog(QDialog *AboutGLMixer)
{
    AboutGLMixer->resize(420, 270);
    AboutGLMixer->setWindowTitle("About GLMixer");
    QGridLayout *gridLayout = new QGridLayout(AboutGLMixer);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    QLabel *Icon = new QLabel(AboutGLMixer);
    Icon->setPixmap(QPixmap(QString::fromUtf8(":/glmixer/icons/glmixer_64x64.png")));
    QLabel *Title = new QLabel(AboutGLMixer);
    Title->setStyleSheet(QString::fromUtf8("font: 14pt \"Sans Serif\";"));
    QLabel *VERSION = new QLabel(AboutGLMixer);
    VERSION->setStyleSheet(QString::fromUtf8("font: 14pt \"Sans Serif\";"));
    QLabel *textsvn = new QLabel(AboutGLMixer);
    QLabel *SVN = new QLabel(AboutGLMixer);
    QTextBrowser *textBrowser = new QTextBrowser(AboutGLMixer);
    textBrowser->setOpenExternalLinks (true);
    QDialogButtonBox *validate = new QDialogButtonBox(AboutGLMixer);
    validate->setOrientation(Qt::Horizontal);
    validate->setStandardButtons(QDialogButtonBox::Close);

    gridLayout->addWidget(Icon, 0, 0, 1, 1);
    gridLayout->addWidget(Title, 0, 1, 1, 1);
    gridLayout->addWidget(VERSION, 0, 2, 1, 1);
    gridLayout->addWidget(textsvn, 1, 1, 1, 1);
    gridLayout->addWidget(SVN, 1, 2, 1, 1);
    gridLayout->addWidget(textBrowser, 2, 0, 1, 3);
    gridLayout->addWidget(validate, 3, 0, 1, 3);

    Icon->setText(QString());
    Title->setText(QObject::tr("Graphic Live Mixer"));
    textBrowser->setHtml(QObject::tr("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
    "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
    "p, li { white-space: pre-wrap; }\n"
    "</style></head><body style=\" font-family:'Sans Serif'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
    "<p>GLMixer is a video mixing software for live performance.</p>\n"
    "<p>Author:	Bruno Herbelin<br>\n"
    "Contact:	bruno.herbelin@gmail.com<br>\n"
    "License: 	GNU GPL version 3</p>\n"
    "<p>Copyright 2009-2014 Bruno Herbelin</p>\n"
    "<p>Updates and source code at: <br>\n"
    "   	<a href=\"http://sourceforge.net/projects/glmixer//\"><span style=\" text-decoration: underline; color:#7d400a;\">http://sourceforge.net/projects/glmixer/</span>"
    "</a></p>"
    "<p>GLMixer is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation.</p>"
    "<p>GLMixer is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details (see http://www.gnu.org/licenses).</p>"
    "</body></html>"));

    VERSION->setText( QString("%1").arg(QCoreApplication::applicationVersion()) );

#ifdef GLMIXER_REVISION
    SVN->setText(QString("%1").arg(GLMIXER_REVISION));
    textsvn->setText(QObject::tr("SVN repository revision:"));
#endif

    QObject::connect(validate, SIGNAL(rejected()), AboutGLMixer, SLOT(reject()));

}


QString getStringFromTime(double time)
{
    int s = (int) time;
    time -= s;
    int h = s / 3600;
    int m = (s % 3600) / 60;
    s = (s % 3600) % 60;
    int ds = (int) (time * 100.0);
    return QString("%1h %2m %3.%4s").arg(h, 2).arg(m, 2, 10, QChar('0')).arg(s, 2, 10, QChar('0')).arg(ds, 2, 10, QChar('0'));
}

double getTimeFromString(QString line)
{
    bool ok = false;
    double h, m, s;

    QStringList parts = line.split('h', QString::SkipEmptyParts);
    if (parts.size()!=2)    return -1;
    h = (double) parts[0].toInt(&ok);
    if (!ok) return -1;
    parts = parts[1].split('m', QString::SkipEmptyParts);
    if (parts.size()!=2)    return -1;
    m = (double) parts[0].toInt(&ok);
    if (!ok) return -1;
    parts = parts[1].split('s', QString::SkipEmptyParts);
    s = parts[0].toDouble(&ok);
    if (!ok) return -1;

    return (h * 3600.0) + (m * 60.0) + s;
}

class timeValidator : public QValidator
{
  public:
    timeValidator(QObject *parent) : QValidator(parent) { }

    QValidator::State validate ( QString & input, int & pos ) const {
      if( input.isEmpty() )
          return QValidator::Invalid;
      double t = getTimeFromString(input);
      if( t < 0 )
          return QValidator::Intermediate;
      return QValidator::Acceptable;
    }
};


TimeInputDialog::TimeInputDialog(QWidget *parent, double time, double min, double max, double fps, bool asframe): QDialog(parent), _t(time), _min(min), _max(max), _fps(fps)
{

        QVBoxLayout *verticalLayout;
        QLabel *Question, *Guide, *Property;
        QDialogButtonBox *DecisionButtonBox;

        setObjectName(QString::fromUtf8("TimeInputDialog"));
        setWindowTitle(tr( "GLMixer - Seek to time in video"));
        setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

        verticalLayout = new QVBoxLayout(this);
        verticalLayout->setSpacing(9);

        Question = new QLabel(this);
        verticalLayout->addWidget(Question);
        Guide = new QLabel(this);
        Guide->setStyleSheet("font-size: 9pt");
        verticalLayout->addWidget(Guide);
        Entry = new QLineEdit(this);
        verticalLayout->addWidget(Entry);
        Info = new QLabel(this);
        verticalLayout->addWidget(Info);
        DecisionButtonBox = new QDialogButtonBox(this);
        DecisionButtonBox->setStandardButtons(QDialogButtonBox::Cancel);
        Ok = DecisionButtonBox->addButton("Go", QDialogButtonBox::AcceptRole);
        verticalLayout->addWidget(DecisionButtonBox);

        QObject::connect(DecisionButtonBox, SIGNAL(accepted()), this, SLOT(accept()));
        QObject::connect(DecisionButtonBox, SIGNAL(rejected()), this, SLOT(reject()));

        if (asframe) {
            Question->setText(tr("Please enter target frame"));
            Guide->setText(tr("Values must be between %1 and %2").arg((int)(_min*_fps)).arg((int)(_max*_fps)));
            Entry->setText( QString::number((int)(_t*_fps)) );
            QValidator *validator = new QIntValidator((int)(_min*_fps), (int)(_max*_fps), this);
            Entry->setValidator(validator);
            QObject::connect(Entry, SIGNAL(textChanged(const QString &)), this, SLOT(validateFrameInput(const QString &)));
        }
        else {
            Question->setText(tr("Please enter target time"));
            Guide->setText(tr("Format must be '__h __m __s'\nValues must be between %1 and %2").arg(getStringFromTime(_min)).arg(getStringFromTime(_max)));
            Entry->setText( getStringFromTime(_t) );
            timeValidator *validator = new timeValidator(this);
            Entry->setValidator(validator);
            QObject::connect(Entry, SIGNAL(textChanged(const QString &)), this, SLOT(validateTimeInput(const QString &)));
        }

}

void TimeInputDialog::validateTimeInput(const QString &s)
{
    Ok->setEnabled(false);

    if( Entry->hasAcceptableInput()) {
        _t = getTimeFromString(s);
        Entry->setStyleSheet("");

        if ( _t > _max ) {
            Info->setText( tr("Target %1 is passed the maximum").arg(_t));
        }
        else if ( _t < _min ) {

            Info->setText( tr("Target %1 is before the minimum").arg(_t));
        }
        else {
            Info->setText( tr("Ready to jump to %1").arg(_t));
            Ok->setEnabled(true);
        }
    }
    else {
        Entry->setStyleSheet("color: rgb(155, 0, 5)");
        Info->setText("Invalid entry");
    }

}

void TimeInputDialog::validateFrameInput(const QString &s)
{
    Ok->setEnabled(false);

    bool ok = false;
    int f = s.toInt(&ok);

    if( ok && Entry->hasAcceptableInput()) {

        _t = (double) f / _fps;

        Entry->setStyleSheet("");
        Info->setText( tr("Ready to jump to %1").arg(_t));
        Ok->setEnabled(true);
    }
    else {
        Entry->setStyleSheet("color: rgb(155, 0, 5)");
        Info->setText("Invalid entry");
    }

}
