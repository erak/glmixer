#include <QBitmap>
#include <QListWidget>
#include <QMetaType>

#include "TagsManager.moc"
#include "ui_TagsManager.h"
#include "qtcolorpicker.h"

#include "RenderingManager.h"

TagsManager::TagsManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TagsManager)
{
    ui->setupUi(this);

    // add color picker
    colorpick = new QtColorPicker(this);
    colorpick->setStandardColors();
    colorpick->setCurrentColor(QColor("cyan"));
    ui->buttonsLayout->insertWidget(1, colorpick);

    // setup default tag
    selectTag(Tag::getDefault());

}

TagsManager::~TagsManager()
{
    delete ui;
}

QListWidgetItem *TagsManager::getTagItem(Tag *t)
{
    QListWidgetItem *item = NULL;

    // try to find the item for this tag
    QHash<Tag *, QListWidgetItem *>::Iterator it = tagsMap.find(t);

    if (it == tagsMap.end())
    // not found, create a new tag
    {
        // create icon
        QBitmap mask(":/glmixer/icons/tagMask.png");
        QPixmap pix(mask.width(), mask.height());
        pix.fill(t->getColor());
        pix.setMask(mask);
        QIcon icon;
        icon.addPixmap(pix, QIcon::Normal, QIcon::Off);
        icon.addPixmap(pix, QIcon::Selected, QIcon::Off);

        // create tag item
        item = new QListWidgetItem(icon,t->getLabel());

        // add to the lists
        ui->tagsListWidget->addItem(item);
        tagsMap[t] = item;
    }
    else
        // found, return it
        item = it.value();

    return item;
}

void TagsManager::createTag()
{
    // add task
    Tag *t = new Tag("Custom", colorpick->currentColor());

    // select item from tag
    selectTag(t);

    // edit text of tag
    currentItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable );
    ui->tagsListWidget->editItem(currentItem);
}


void TagsManager::deleteTag()
{

}

void TagsManager::selectTag(QListWidgetItem *i)
{

    qDebug() << "TagsManager::selectTag" << i->text();

}

void TagsManager::updateTag(QListWidgetItem *i)
{

    qDebug() << "TagsManager::updateTag" << i->text();

}

void TagsManager::selectTag(Tag *t)
{

    currentItem = getTagItem(t);
    ui->tagsListWidget->setCurrentItem(currentItem);

}

void TagsManager::useTag(QListWidgetItem *i)
{
    currentItem = i;
    Tag *t = Tag::getDefault();


    qDebug() << "TagsManager::useTag" << i->text();

    if (currentItem && currentSource)
    {
        QList<Tag *> tags = tagsMap.keys(currentItem);
        if (!tags.empty())
            t = tags.first();

        // apply the tag found
        Tag::apply(currentSource, t);



        qDebug() << "Tag::apply" << t->getLabel();

    }

    // allow delete non default
    ui->tagRemove->setEnabled(t != Tag::getDefault());
}


void TagsManager::connectSource(SourceSet::iterator csi)
{

    // enable / disable toolbox depending on availability of current source
    if (RenderingManager::getInstance()->isValid(csi)) {
        setEnabled(true);
        currentSource = *csi;

        selectTag( currentSource->getTag() );

    } else {
        setEnabled(false);
        currentSource = 0;

    }

}
