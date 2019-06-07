/********************************************************************************
** Form generated from reading UI file 'simulator.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMULATOR_H
#define UI_SIMULATOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Simulator
{
public:
    QHBoxLayout *horizontalLayout_3;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *att_ico;
    QLabel *att;
    QHBoxLayout *horizontalLayout;
    QLabel *def_ico;
    QLabel *def;
    QFrame *att_top;
    QFrame *def_top;
    QFrame *att_mid;
    QFrame *def_mid;
    QFrame *def_bottom;
    QFrame *att_bottom;
    QVBoxLayout *verticalLayout;
    QPushButton *tb1;
    QPushButton *tb2;
    QPushButton *tb3;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *Simulator)
    {
        if (Simulator->objectName().isEmpty())
            Simulator->setObjectName(QStringLiteral("Simulator"));
        Simulator->resize(848, 362);
        horizontalLayout_3 = new QHBoxLayout(Simulator);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        att_ico = new QLabel(Simulator);
        att_ico->setObjectName(QStringLiteral("att_ico"));

        horizontalLayout_2->addWidget(att_ico);

        att = new QLabel(Simulator);
        att->setObjectName(QStringLiteral("att"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(att->sizePolicy().hasHeightForWidth());
        att->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(att);


        gridLayout->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        def_ico = new QLabel(Simulator);
        def_ico->setObjectName(QStringLiteral("def_ico"));

        horizontalLayout->addWidget(def_ico);

        def = new QLabel(Simulator);
        def->setObjectName(QStringLiteral("def"));
        sizePolicy.setHeightForWidth(def->sizePolicy().hasHeightForWidth());
        def->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(def);


        gridLayout->addLayout(horizontalLayout, 0, 1, 1, 1);

        att_top = new QFrame(Simulator);
        att_top->setObjectName(QStringLiteral("att_top"));
        att_top->setFrameShape(QFrame::StyledPanel);
        att_top->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(att_top, 1, 0, 1, 1);

        def_top = new QFrame(Simulator);
        def_top->setObjectName(QStringLiteral("def_top"));
        def_top->setFrameShape(QFrame::StyledPanel);
        def_top->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(def_top, 1, 1, 1, 1);

        att_mid = new QFrame(Simulator);
        att_mid->setObjectName(QStringLiteral("att_mid"));
        att_mid->setFrameShape(QFrame::StyledPanel);
        att_mid->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(att_mid, 2, 0, 1, 1);

        def_mid = new QFrame(Simulator);
        def_mid->setObjectName(QStringLiteral("def_mid"));
        def_mid->setFrameShape(QFrame::StyledPanel);
        def_mid->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(def_mid, 2, 1, 1, 1);

        def_bottom = new QFrame(Simulator);
        def_bottom->setObjectName(QStringLiteral("def_bottom"));
        def_bottom->setFrameShape(QFrame::StyledPanel);
        def_bottom->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(def_bottom, 3, 1, 1, 1);

        att_bottom = new QFrame(Simulator);
        att_bottom->setObjectName(QStringLiteral("att_bottom"));
        att_bottom->setFrameShape(QFrame::StyledPanel);
        att_bottom->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(att_bottom, 3, 0, 1, 1);


        horizontalLayout_3->addLayout(gridLayout);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tb1 = new QPushButton(Simulator);
        tb1->setObjectName(QStringLiteral("tb1"));

        verticalLayout->addWidget(tb1);

        tb2 = new QPushButton(Simulator);
        tb2->setObjectName(QStringLiteral("tb2"));

        verticalLayout->addWidget(tb2);

        tb3 = new QPushButton(Simulator);
        tb3->setObjectName(QStringLiteral("tb3"));

        verticalLayout->addWidget(tb3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout_3->addLayout(verticalLayout);


        retranslateUi(Simulator);

        QMetaObject::connectSlotsByName(Simulator);
    } // setupUi

    void retranslateUi(QWidget *Simulator)
    {
        Simulator->setWindowTitle(QApplication::translate("Simulator", "Form", 0));
        att_ico->setText(QApplication::translate("Simulator", "TextLabel", 0));
        att->setText(QApplication::translate("Simulator", "Test", 0));
        def_ico->setText(QApplication::translate("Simulator", "TextLabel", 0));
        def->setText(QApplication::translate("Simulator", "test2", 0));
        tb1->setText(QApplication::translate("Simulator", "Simulate", 0));
        tb2->setText(QApplication::translate("Simulator", "Reset", 0));
        tb3->setText(QApplication::translate("Simulator", "Reverse", 0));
    } // retranslateUi

};

namespace Ui {
    class Simulator: public Ui_Simulator {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMULATOR_H
