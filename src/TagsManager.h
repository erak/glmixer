#ifndef TAGSMANAGER_H
#define TAGSMANAGER_H

#include <QWidget>
#include <QHash>

#include "Tag.h"
#include "Source.h"
#include "SourceSet.h"


namespace Ui {
class TagsManager;
}

class TagsManager : public QWidget
{
    Q_OBJECT

public:
    explicit TagsManager(QWidget *parent = 0);
    ~TagsManager();

    QListWidgetItem *getTagItem(Tag *t);
    void selectTag(Tag *t);

public slots:

    void createTag();
    void deleteTag();
    void useTag(QListWidgetItem *i);
    void selectTag(QListWidgetItem *i);
    void updateTag(QListWidgetItem *i);

    // Source to operate
    void connectSource(SourceSet::iterator);
//    void connectSelection(SourceSet::iterator);

private:
    Ui::TagsManager *ui;
    class QtColorPicker *colorpick;

    QListWidgetItem *currentItem;
    Source *currentSource;

    QHash<Tag *, QListWidgetItem *> tagsMap;
};

#endif // TAGSMANAGER_H
