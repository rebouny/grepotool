/********************************************************************************
** Form generated from reading UI file 'table.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TABLE_H
#define UI_TABLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Table
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *_head_l;
    QLabel *_info;
    QToolButton *_tb2;
    QToolButton *_ghosts;
    QTableView *_tab;

    void setupUi(QFrame *Table)
    {
        if (Table->objectName().isEmpty())
            Table->setObjectName(QStringLiteral("Table"));
        Table->resize(615, 335);
        Table->setFrameShape(QFrame::StyledPanel);
        Table->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(Table);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        _head_l = new QHBoxLayout();
        _head_l->setObjectName(QStringLiteral("_head_l"));
        _head_l->setContentsMargins(9, 0, 0, -1);
        _info = new QLabel(Table);
        _info->setObjectName(QStringLiteral("_info"));

        _head_l->addWidget(_info);

        _tb2 = new QToolButton(Table);
        _tb2->setObjectName(QStringLiteral("_tb2"));

        _head_l->addWidget(_tb2);

        _ghosts = new QToolButton(Table);
        _ghosts->setObjectName(QStringLiteral("_ghosts"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/ghost.png"), QSize(), QIcon::Normal, QIcon::Off);
        _ghosts->setIcon(icon);

        _head_l->addWidget(_ghosts);


        verticalLayout->addLayout(_head_l);

        _tab = new QTableView(Table);
        _tab->setObjectName(QStringLiteral("_tab"));
        _tab->setTabKeyNavigation(false);
        _tab->setSelectionMode(QAbstractItemView::ExtendedSelection);
        _tab->setSelectionBehavior(QAbstractItemView::SelectRows);
        _tab->setIconSize(QSize(30, 30));
        _tab->setSortingEnabled(true);
        _tab->horizontalHeader()->setMinimumSectionSize(35);
        _tab->horizontalHeader()->setStretchLastSection(true);
        _tab->verticalHeader()->setCascadingSectionResizes(true);
        _tab->verticalHeader()->setMinimumSectionSize(20);

        verticalLayout->addWidget(_tab);


        retranslateUi(Table);

        QMetaObject::connectSlotsByName(Table);
    } // setupUi

    void retranslateUi(QFrame *Table)
    {
        Table->setWindowTitle(QApplication::translate("Table", "Towns", 0));
        _info->setText(QString());
        _tb2->setText(QApplication::translate("Table", "...", 0));
        _ghosts->setText(QApplication::translate("Table", "...", 0));
#ifndef QT_NO_TOOLTIP
        _tab->setToolTip(QApplication::translate("Table", "Show ghost towns", 0));
#endif // QT_NO_TOOLTIP
    } // retranslateUi

};

namespace Ui {
    class Table: public Ui_Table {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TABLE_H
