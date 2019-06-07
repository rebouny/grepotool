/********************************************************************************
** Form generated from reading UI file 'table_export.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TABLE_EXPORT_H
#define UI_TABLE_EXPORT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TableExport
{
public:
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QListWidget *_avail;
    QVBoxLayout *verticalLayout;
    QToolButton *_add;
    QToolButton *_remove;
    QToolButton *_up;
    QToolButton *_down;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QListWidget *_sel;
    QCheckBox *_only_sel;
    QTabWidget *_tab;
    QWidget *tab;
    QGridLayout *gridLayout;
    QTableWidget *_text;
    QWidget *tab_2;
    QGridLayout *gridLayout_2;
    QTextEdit *_bbcode;
    QWidget *tab_3;
    QGridLayout *gridLayout_3;
    QTextEdit *_bbcode_table;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *TableExport)
    {
        if (TableExport->objectName().isEmpty())
            TableExport->setObjectName(QStringLiteral("TableExport"));
        TableExport->resize(812, 420);
        verticalLayout_4 = new QVBoxLayout(TableExport);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label = new QLabel(TableExport);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout_3->addWidget(label);

        _avail = new QListWidget(TableExport);
        _avail->setObjectName(QStringLiteral("_avail"));

        verticalLayout_3->addWidget(_avail);


        horizontalLayout->addLayout(verticalLayout_3);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        _add = new QToolButton(TableExport);
        _add->setObjectName(QStringLiteral("_add"));

        verticalLayout->addWidget(_add);

        _remove = new QToolButton(TableExport);
        _remove->setObjectName(QStringLiteral("_remove"));

        verticalLayout->addWidget(_remove);

        _up = new QToolButton(TableExport);
        _up->setObjectName(QStringLiteral("_up"));

        verticalLayout->addWidget(_up);

        _down = new QToolButton(TableExport);
        _down->setObjectName(QStringLiteral("_down"));

        verticalLayout->addWidget(_down);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_2 = new QLabel(TableExport);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout_2->addWidget(label_2);

        _sel = new QListWidget(TableExport);
        _sel->setObjectName(QStringLiteral("_sel"));

        verticalLayout_2->addWidget(_sel);


        horizontalLayout->addLayout(verticalLayout_2);


        verticalLayout_4->addLayout(horizontalLayout);

        _only_sel = new QCheckBox(TableExport);
        _only_sel->setObjectName(QStringLiteral("_only_sel"));

        verticalLayout_4->addWidget(_only_sel);

        _tab = new QTabWidget(TableExport);
        _tab->setObjectName(QStringLiteral("_tab"));
        QFont font;
        font.setFamily(QStringLiteral("MS Sans Serif"));
        _tab->setFont(font);
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayout = new QGridLayout(tab);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        _text = new QTableWidget(tab);
        _text->setObjectName(QStringLiteral("_text"));

        gridLayout->addWidget(_text, 0, 0, 1, 1);

        _tab->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        gridLayout_2 = new QGridLayout(tab_2);
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        _bbcode = new QTextEdit(tab_2);
        _bbcode->setObjectName(QStringLiteral("_bbcode"));
        _bbcode->setLineWrapMode(QTextEdit::NoWrap);
        _bbcode->setReadOnly(true);

        gridLayout_2->addWidget(_bbcode, 0, 0, 1, 1);

        _tab->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        gridLayout_3 = new QGridLayout(tab_3);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, -1);
        _bbcode_table = new QTextEdit(tab_3);
        _bbcode_table->setObjectName(QStringLiteral("_bbcode_table"));
        _bbcode_table->setLineWrapMode(QTextEdit::NoWrap);
        _bbcode_table->setReadOnly(true);

        gridLayout_3->addWidget(_bbcode_table, 0, 0, 1, 1);

        _tab->addTab(tab_3, QString());

        verticalLayout_4->addWidget(_tab);

        buttonBox = new QDialogButtonBox(TableExport);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_4->addWidget(buttonBox);


        retranslateUi(TableExport);
        QObject::connect(buttonBox, SIGNAL(accepted()), TableExport, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), TableExport, SLOT(reject()));

        _tab->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(TableExport);
    } // setupUi

    void retranslateUi(QDialog *TableExport)
    {
        TableExport->setWindowTitle(QApplication::translate("TableExport", "Copy table to Clipboard", 0));
        label->setText(QApplication::translate("TableExport", "Available columns", 0));
        _add->setText(QApplication::translate("TableExport", "...", 0));
        _remove->setText(QApplication::translate("TableExport", "...", 0));
        _up->setText(QApplication::translate("TableExport", "...", 0));
        _down->setText(QApplication::translate("TableExport", "...", 0));
        label_2->setText(QApplication::translate("TableExport", "Selected columns", 0));
        _only_sel->setText(QApplication::translate("TableExport", "Only selected items", 0));
        _tab->setTabText(_tab->indexOf(tab), QApplication::translate("TableExport", "Plain Text", 0));
        _tab->setTabText(_tab->indexOf(tab_2), QApplication::translate("TableExport", "Plain BBCode", 0));
        _tab->setTabText(_tab->indexOf(tab_3), QApplication::translate("TableExport", "BBCode table", 0));
    } // retranslateUi

};

namespace Ui {
    class TableExport: public Ui_TableExport {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TABLE_EXPORT_H
