////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2005 Silicon Graphics, Inc. All Rights Reserved.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License as published by the Free
// Software Foundation; either version 2.1 of the License, or (at your option)
// any later version.
//
// This library is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
// details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this library; if not, write to the Free Software Foundation, Inc.,
// 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
////////////////////////////////////////////////////////////////////////////////
  

#ifndef ATTACHCOLLECTORDIALOG_H
#define ATTACHCOLLECTORDIALOG_H

#include <qvariant.h>
#include <qdialog.h>
#include <qpopupmenu.h>

#include "CollectorListObject.hxx"  // For getting pid list off a host...
#include "CollectorEntryClass.hxx"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QFrame;
class QPushButton;
class QLabel;
class QComboBox;
class QListView;
class QListViewItem;

class ManageCollectorsDialog : public QDialog
{
    Q_OBJECT

public:
    ManageCollectorsDialog( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0, int exp_id = -1 );
    ~ManageCollectorsDialog();

    QPushButton* buttonHelp;
    QPushButton* buttonOk;
    QPushButton* buttonCancel;

    QLabel* attachHostLabel;
    QComboBox * attachHostComboBox;
    QListView* attachCollectorsListView;

    QString selectedCollectors();
    void updateAttachedCollectorsList();

    CollectorListObject *clo;

    void contextMenuRequested( QListViewItem *item, const QPoint &pos, int col );

protected:
    QVBoxLayout* ManageCollectorsDialogLayout;
    QHBoxLayout* Layout1;
    QSpacerItem* Horizontal_Spacing2;

protected slots:
    virtual void languageChange();

public slots:
    virtual void attachHostComboBoxActivated();

private:
    int expID;

};

#endif // ATTACHCOLLECTORDIALOG_H
