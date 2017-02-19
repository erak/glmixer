/*
 * SelectionManager.h
 *
 *  Created on: Feb 10, 2013
 *      Author: bh
 */

#ifndef SELECTIONMANAGER_H_
#define SELECTIONMANAGER_H_

#include <QObject>
#include "SourceSet.h"


class SelectionManager: public QObject {

    Q_OBJECT

public:

    static SelectionManager *getInstance();

    /**
     * Selection management
     */
    void select(Source *s);
    void deselect(Source *s);
    void select(SourceList l);
    void deselect(SourceList l);
    bool isInSelection(Source *s) const;
    void setSelection(SourceList l);
    bool hasSelection() { return !_selectedSources.empty(); }
    SourceList::iterator selectionBegin() { return _selectedSources.begin(); }
    SourceList::iterator selectionEnd() { return _selectedSources.end(); }
    int selectionCount() { return _selectedSources.size(); }
    SourceList copySelection() { return SourceList (_selectedSources); }
    Source *selectionSource() { return _selectionSource; }

public slots:

    void clearSelection();
    void selectAll();
    void invertSelection();
    void selectCurrentSource();
    void updateSelectionSource();

signals:
    void selectionChanged(bool notempty);

private:

    SelectionManager();
    virtual ~SelectionManager();

    static SelectionManager *_instance;

    Source *_selectionSource;
    SourceList _selectedSources;
};

#endif /* SELECTIONMANAGER_H_ */
