#include "Tag.h"

Tag *Tag::defaultTag = 0;
QList<Tag *> Tag::tags;


Tag::Tag(QString l, QColor c): label(l), color(c)
{

}

QString Tag::getLabel() const
{
    return label;
}

void Tag::setLabel(const QString &value)
{
    label = value;
}

QColor Tag::getColor() const
{
    return color;
}

void Tag::setColor(const QColor &value)
{
    color = value;
}

Tag *Tag::getDefault()
{
    if (!Tag::defaultTag)
        Tag::defaultTag = new Tag();
    return Tag::defaultTag;
}

void Tag::apply(Source *s, Tag *t)
{
    if (!s)
        return;

    s->setTag(t);
    t->sources.insert(s);

    //tODO remove source from previous tag
}


void Tag::remove(Source *s)
{
    if (!s)
        return;

    Tag *t = s->getTag();

    SourceList::iterator it = t->sources.find(s);
    if ( it != t->sources.end() )
        t->sources.erase(it);

    s->setTag( Tag::getDefault() );
}
