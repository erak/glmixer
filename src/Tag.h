#ifndef TAG_H
#define TAG_H

#include <QColor>
#include "Source.h"


class Tag
{

    QString label;
    QColor color;
    SourceList sources;

    static Tag *defaultTag;
    static QList<Tag *> tags;

public:
    Tag(QString l = "Default", QColor c = QColor(255,255,60));

    static void apply(Source *s, Tag* t);
    static void remove(Source *s);
    static Tag *getDefault();

    QString getLabel() const;
    void setLabel(const QString &value);
    QColor getColor() const;
    void setColor(const QColor &value);
};


#endif // TAG_H
