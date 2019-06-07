/********************************************************************************
** Form generated from reading UI file 'specials.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPECIALS_H
#define UI_SPECIALS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Specials
{
public:
    QHBoxLayout *horizontalLayout;
    QToolButton *_meteorology;
    QToolButton *_cartography;
    QToolButton *_movement_boost;
    QToolButton *_lighthouse;
    QToolButton *_atlanta;

    void setupUi(QWidget *Specials)
    {
        if (Specials->objectName().isEmpty())
            Specials->setObjectName(QStringLiteral("Specials"));
        Specials->resize(259, 46);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Specials->sizePolicy().hasHeightForWidth());
        Specials->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(Specials);
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        _meteorology = new QToolButton(Specials);
        _meteorology->setObjectName(QStringLiteral("_meteorology"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/meteorology.png"), QSize(), QIcon::Normal, QIcon::Off);
        _meteorology->setIcon(icon);
        _meteorology->setIconSize(QSize(40, 40));
        _meteorology->setCheckable(true);
        _meteorology->setAutoRaise(true);

        horizontalLayout->addWidget(_meteorology);

        _cartography = new QToolButton(Specials);
        _cartography->setObjectName(QStringLiteral("_cartography"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icons/cartography.png"), QSize(), QIcon::Normal, QIcon::Off);
        _cartography->setIcon(icon1);
        _cartography->setIconSize(QSize(40, 40));
        _cartography->setCheckable(true);
        _cartography->setAutoRaise(true);

        horizontalLayout->addWidget(_cartography);

        _movement_boost = new QToolButton(Specials);
        _movement_boost->setObjectName(QStringLiteral("_movement_boost"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/icons/movement_boost.gif"), QSize(), QIcon::Normal, QIcon::Off);
        _movement_boost->setIcon(icon2);
        _movement_boost->setIconSize(QSize(40, 40));
        _movement_boost->setCheckable(true);
        _movement_boost->setAutoRaise(true);

        horizontalLayout->addWidget(_movement_boost);

        _lighthouse = new QToolButton(Specials);
        _lighthouse->setObjectName(QStringLiteral("_lighthouse"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/icons/lighthouse.png"), QSize(), QIcon::Normal, QIcon::Off);
        _lighthouse->setIcon(icon3);
        _lighthouse->setIconSize(QSize(40, 40));
        _lighthouse->setCheckable(true);
        _lighthouse->setAutoRaise(true);

        horizontalLayout->addWidget(_lighthouse);

        _atlanta = new QToolButton(Specials);
        _atlanta->setObjectName(QStringLiteral("_atlanta"));
        _atlanta->setIcon(icon3);
        _atlanta->setIconSize(QSize(40, 40));
        _atlanta->setCheckable(true);
        _atlanta->setAutoRaise(true);

        horizontalLayout->addWidget(_atlanta);


        retranslateUi(Specials);

        QMetaObject::connectSlotsByName(Specials);
    } // setupUi

    void retranslateUi(QWidget *Specials)
    {
        Specials->setWindowTitle(QApplication::translate("Specials", "Form", 0));
        _meteorology->setText(QString());
        _cartography->setText(QString());
        _movement_boost->setText(QString());
        _lighthouse->setText(QString());
        _atlanta->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Specials: public Ui_Specials {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPECIALS_H
