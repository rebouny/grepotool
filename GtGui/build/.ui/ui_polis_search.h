/********************************************************************************
** Form generated from reading UI file 'polis_search.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POLIS_SEARCH_H
#define UI_POLIS_SEARCH_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_PolisSearch
{
public:
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout;
    QGridLayout *lay;
    QCheckBox *cbally;
    QLineEdit *al;
    QCheckBox *cbghosts;
    QToolButton *del;
    QCheckBox *inact1;
    QCheckBox *inact3;
    QGridLayout *gridLayout;
    QTimeEdit *time;
    QCheckBox *cbocean;
    QSpinBox *ocean;
    QCheckBox *cbmaxdist;
    QSpinBox *dist;
    QCheckBox *cbmaxtime;
    QVBoxLayout *verticalLayout_2;
    QListWidget *_allys;
    QLabel *result;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *PolisSearch)
    {
        if (PolisSearch->objectName().isEmpty())
            PolisSearch->setObjectName(QStringLiteral("PolisSearch"));
        PolisSearch->resize(557, 260);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PolisSearch->sizePolicy().hasHeightForWidth());
        PolisSearch->setSizePolicy(sizePolicy);
        gridLayout_2 = new QGridLayout(PolisSearch);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        lay = new QGridLayout();
        lay->setObjectName(QStringLiteral("lay"));
        cbally = new QCheckBox(PolisSearch);
        cbally->setObjectName(QStringLiteral("cbally"));

        lay->addWidget(cbally, 0, 0, 1, 1);

        al = new QLineEdit(PolisSearch);
        al->setObjectName(QStringLiteral("al"));

        lay->addWidget(al, 0, 1, 1, 2);

        cbghosts = new QCheckBox(PolisSearch);
        cbghosts->setObjectName(QStringLiteral("cbghosts"));

        lay->addWidget(cbghosts, 1, 0, 1, 2);

        del = new QToolButton(PolisSearch);
        del->setObjectName(QStringLiteral("del"));

        lay->addWidget(del, 1, 2, 1, 1);

        inact1 = new QCheckBox(PolisSearch);
        inact1->setObjectName(QStringLiteral("inact1"));

        lay->addWidget(inact1, 2, 0, 1, 2);

        inact3 = new QCheckBox(PolisSearch);
        inact3->setObjectName(QStringLiteral("inact3"));

        lay->addWidget(inact3, 3, 0, 1, 2);


        verticalLayout->addLayout(lay);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        time = new QTimeEdit(PolisSearch);
        time->setObjectName(QStringLiteral("time"));

        gridLayout->addWidget(time, 0, 1, 1, 1);

        cbocean = new QCheckBox(PolisSearch);
        cbocean->setObjectName(QStringLiteral("cbocean"));

        gridLayout->addWidget(cbocean, 1, 0, 1, 1);

        ocean = new QSpinBox(PolisSearch);
        ocean->setObjectName(QStringLiteral("ocean"));

        gridLayout->addWidget(ocean, 1, 1, 1, 1);

        cbmaxdist = new QCheckBox(PolisSearch);
        cbmaxdist->setObjectName(QStringLiteral("cbmaxdist"));

        gridLayout->addWidget(cbmaxdist, 2, 0, 1, 1);

        dist = new QSpinBox(PolisSearch);
        dist->setObjectName(QStringLiteral("dist"));
        dist->setMinimum(1);
        dist->setMaximum(300);

        gridLayout->addWidget(dist, 2, 1, 1, 1);

        cbmaxtime = new QCheckBox(PolisSearch);
        cbmaxtime->setObjectName(QStringLiteral("cbmaxtime"));

        gridLayout->addWidget(cbmaxtime, 0, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);


        gridLayout_2->addLayout(verticalLayout, 0, 0, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        _allys = new QListWidget(PolisSearch);
        _allys->setObjectName(QStringLiteral("_allys"));

        verticalLayout_2->addWidget(_allys);

        result = new QLabel(PolisSearch);
        result->setObjectName(QStringLiteral("result"));

        verticalLayout_2->addWidget(result);


        gridLayout_2->addLayout(verticalLayout_2, 0, 1, 1, 1);

        buttonBox = new QDialogButtonBox(PolisSearch);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_2->addWidget(buttonBox, 1, 1, 1, 1);


        retranslateUi(PolisSearch);
        QObject::connect(buttonBox, SIGNAL(accepted()), PolisSearch, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), PolisSearch, SLOT(reject()));

        QMetaObject::connectSlotsByName(PolisSearch);
    } // setupUi

    void retranslateUi(QDialog *PolisSearch)
    {
        PolisSearch->setWindowTitle(QApplication::translate("PolisSearch", "Polis search", 0));
        cbally->setText(QApplication::translate("PolisSearch", "Only certain allys", 0));
        cbghosts->setText(QApplication::translate("PolisSearch", "Include ghost towns", 0));
        del->setText(QApplication::translate("PolisSearch", "...", 0));
        inact1->setText(QApplication::translate("PolisSearch", "Player inactive for at least one day", 0));
        inact3->setText(QApplication::translate("PolisSearch", "Player inactive for at least three days", 0));
        cbocean->setText(QApplication::translate("PolisSearch", "Restrict search to a single ocean", 0));
        cbmaxdist->setText(QApplication::translate("PolisSearch", "Max distance to current map center", 0));
        cbmaxtime->setText(QApplication::translate("PolisSearch", "Max travel time from my towns", 0));
        result->setText(QApplication::translate("PolisSearch", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class PolisSearch: public Ui_PolisSearch {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POLIS_SEARCH_H
