/********************************************************************************
** Form generated from reading UI file 'units.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UNITS_H
#define UI_UNITS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Units
{
public:
    QGridLayout *gridLayout;
    QToolButton *_slow;
    QToolButton *_biri;
    QToolButton *_fire;
    QToolButton *_brander;
    QToolButton *_fast;
    QToolButton *_trireme;
    QToolButton *_kolo;
    QToolButton *_sword;
    QToolButton *_slinger;
    QToolButton *_archer;
    QToolButton *_hoplite;
    QToolButton *_rider;
    QToolButton *_chariot;
    QToolButton *_catapult;
    QToolButton *_godsent;
    QToolButton *_griffin;
    QToolButton *_boar;
    QToolButton *_cerberus;
    QToolButton *_centaur;
    QToolButton *_medusa;
    QToolButton *_minotaur;
    QToolButton *_zyklop;
    QToolButton *_manti;
    QToolButton *_fury;
    QToolButton *_pega;
    QToolButton *_harpy;
    QToolButton *_hydra;

    void setupUi(QWidget *Units)
    {
        if (Units->objectName().isEmpty())
            Units->setObjectName(QStringLiteral("Units"));
        Units->resize(329, 184);
        gridLayout = new QGridLayout(Units);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        _slow = new QToolButton(Units);
        _slow->setObjectName(QStringLiteral("_slow"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/big_transporter.png"), QSize(), QIcon::Normal, QIcon::Off);
        _slow->setIcon(icon);
        _slow->setIconSize(QSize(40, 40));
        _slow->setCheckable(true);
        _slow->setAutoRaise(true);

        gridLayout->addWidget(_slow, 0, 0, 1, 1);

        _biri = new QToolButton(Units);
        _biri->setObjectName(QStringLiteral("_biri"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icons/bireme.png"), QSize(), QIcon::Normal, QIcon::Off);
        _biri->setIcon(icon1);
        _biri->setIconSize(QSize(40, 40));
        _biri->setCheckable(true);
        _biri->setAutoRaise(true);

        gridLayout->addWidget(_biri, 0, 1, 1, 1);

        _fire = new QToolButton(Units);
        _fire->setObjectName(QStringLiteral("_fire"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/icons/attack_ship.png"), QSize(), QIcon::Normal, QIcon::Off);
        _fire->setIcon(icon2);
        _fire->setIconSize(QSize(40, 40));
        _fire->setCheckable(true);
        _fire->setAutoRaise(true);

        gridLayout->addWidget(_fire, 0, 2, 1, 1);

        _brander = new QToolButton(Units);
        _brander->setObjectName(QStringLiteral("_brander"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/icons/demolition_ship.png"), QSize(), QIcon::Normal, QIcon::Off);
        _brander->setIcon(icon3);
        _brander->setIconSize(QSize(40, 40));
        _brander->setCheckable(true);
        _brander->setAutoRaise(true);

        gridLayout->addWidget(_brander, 0, 3, 1, 1);

        _fast = new QToolButton(Units);
        _fast->setObjectName(QStringLiteral("_fast"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/icons/small_transporter.png"), QSize(), QIcon::Normal, QIcon::Off);
        _fast->setIcon(icon4);
        _fast->setIconSize(QSize(40, 40));
        _fast->setCheckable(true);
        _fast->setAutoRaise(true);

        gridLayout->addWidget(_fast, 0, 4, 1, 1);

        _trireme = new QToolButton(Units);
        _trireme->setObjectName(QStringLiteral("_trireme"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/icons/trireme.png"), QSize(), QIcon::Normal, QIcon::Off);
        _trireme->setIcon(icon5);
        _trireme->setIconSize(QSize(40, 40));
        _trireme->setCheckable(true);
        _trireme->setAutoRaise(true);

        gridLayout->addWidget(_trireme, 0, 5, 1, 1);

        _kolo = new QToolButton(Units);
        _kolo->setObjectName(QStringLiteral("_kolo"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/icons/colonize_ship.png"), QSize(), QIcon::Normal, QIcon::Off);
        _kolo->setIcon(icon6);
        _kolo->setIconSize(QSize(40, 40));
        _kolo->setCheckable(true);
        _kolo->setAutoRaise(true);

        gridLayout->addWidget(_kolo, 0, 6, 1, 1);

        _sword = new QToolButton(Units);
        _sword->setObjectName(QStringLiteral("_sword"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/icons/sword.png"), QSize(), QIcon::Normal, QIcon::Off);
        _sword->setIcon(icon7);
        _sword->setIconSize(QSize(40, 40));
        _sword->setCheckable(true);
        _sword->setAutoRaise(true);

        gridLayout->addWidget(_sword, 1, 0, 1, 1);

        _slinger = new QToolButton(Units);
        _slinger->setObjectName(QStringLiteral("_slinger"));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/icons/slinger.png"), QSize(), QIcon::Normal, QIcon::Off);
        _slinger->setIcon(icon8);
        _slinger->setIconSize(QSize(40, 40));
        _slinger->setCheckable(true);
        _slinger->setAutoRaise(true);

        gridLayout->addWidget(_slinger, 1, 1, 1, 1);

        _archer = new QToolButton(Units);
        _archer->setObjectName(QStringLiteral("_archer"));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/icons/archer.png"), QSize(), QIcon::Normal, QIcon::Off);
        _archer->setIcon(icon9);
        _archer->setIconSize(QSize(40, 40));
        _archer->setCheckable(true);
        _archer->setAutoRaise(true);

        gridLayout->addWidget(_archer, 1, 2, 1, 1);

        _hoplite = new QToolButton(Units);
        _hoplite->setObjectName(QStringLiteral("_hoplite"));
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/icons/hoplite.png"), QSize(), QIcon::Normal, QIcon::Off);
        _hoplite->setIcon(icon10);
        _hoplite->setIconSize(QSize(40, 40));
        _hoplite->setCheckable(true);
        _hoplite->setAutoRaise(true);

        gridLayout->addWidget(_hoplite, 1, 3, 1, 1);

        _rider = new QToolButton(Units);
        _rider->setObjectName(QStringLiteral("_rider"));
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/icons/rider.png"), QSize(), QIcon::Normal, QIcon::Off);
        _rider->setIcon(icon11);
        _rider->setIconSize(QSize(40, 40));
        _rider->setCheckable(true);
        _rider->setAutoRaise(true);

        gridLayout->addWidget(_rider, 1, 4, 1, 1);

        _chariot = new QToolButton(Units);
        _chariot->setObjectName(QStringLiteral("_chariot"));
        QIcon icon12;
        icon12.addFile(QStringLiteral(":/icons/chariot.png"), QSize(), QIcon::Normal, QIcon::Off);
        _chariot->setIcon(icon12);
        _chariot->setIconSize(QSize(40, 40));
        _chariot->setCheckable(true);
        _chariot->setAutoRaise(true);

        gridLayout->addWidget(_chariot, 1, 5, 1, 1);

        _catapult = new QToolButton(Units);
        _catapult->setObjectName(QStringLiteral("_catapult"));
        QIcon icon13;
        icon13.addFile(QStringLiteral(":/icons/catapult.png"), QSize(), QIcon::Normal, QIcon::Off);
        _catapult->setIcon(icon13);
        _catapult->setIconSize(QSize(40, 40));
        _catapult->setCheckable(true);
        _catapult->setAutoRaise(true);

        gridLayout->addWidget(_catapult, 1, 6, 1, 1);

        _godsent = new QToolButton(Units);
        _godsent->setObjectName(QStringLiteral("_godsent"));
        QIcon icon14;
        icon14.addFile(QStringLiteral(":/icons/godsent.png"), QSize(), QIcon::Normal, QIcon::Off);
        _godsent->setIcon(icon14);
        _godsent->setIconSize(QSize(40, 40));
        _godsent->setCheckable(true);
        _godsent->setAutoRaise(true);

        gridLayout->addWidget(_godsent, 2, 0, 1, 1);

        _griffin = new QToolButton(Units);
        _griffin->setObjectName(QStringLiteral("_griffin"));
        QIcon icon15;
        icon15.addFile(QStringLiteral(":/icons/griffin.png"), QSize(), QIcon::Normal, QIcon::Off);
        _griffin->setIcon(icon15);
        _griffin->setIconSize(QSize(40, 40));
        _griffin->setCheckable(true);
        _griffin->setAutoRaise(true);

        gridLayout->addWidget(_griffin, 3, 6, 1, 1);

        _boar = new QToolButton(Units);
        _boar->setObjectName(QStringLiteral("_boar"));
        QIcon icon16;
        icon16.addFile(QStringLiteral(":/icons/calydonian_boar.png"), QSize(), QIcon::Normal, QIcon::Off);
        _boar->setIcon(icon16);
        _boar->setIconSize(QSize(40, 40));
        _boar->setCheckable(true);
        _boar->setAutoRaise(true);

        gridLayout->addWidget(_boar, 2, 6, 1, 1);

        _cerberus = new QToolButton(Units);
        _cerberus->setObjectName(QStringLiteral("_cerberus"));
        QIcon icon17;
        icon17.addFile(QStringLiteral(":/icons/cerberus.png"), QSize(), QIcon::Normal, QIcon::Off);
        _cerberus->setIcon(icon17);
        _cerberus->setIconSize(QSize(40, 40));
        _cerberus->setCheckable(true);
        _cerberus->setAutoRaise(true);

        gridLayout->addWidget(_cerberus, 2, 5, 1, 1);

        _centaur = new QToolButton(Units);
        _centaur->setObjectName(QStringLiteral("_centaur"));
        QIcon icon18;
        icon18.addFile(QStringLiteral(":/icons/centaur.png"), QSize(), QIcon::Normal, QIcon::Off);
        _centaur->setIcon(icon18);
        _centaur->setIconSize(QSize(40, 40));
        _centaur->setCheckable(true);
        _centaur->setAutoRaise(true);

        gridLayout->addWidget(_centaur, 2, 4, 1, 1);

        _medusa = new QToolButton(Units);
        _medusa->setObjectName(QStringLiteral("_medusa"));
        QIcon icon19;
        icon19.addFile(QStringLiteral(":/icons/medusa.png"), QSize(), QIcon::Normal, QIcon::Off);
        _medusa->setIcon(icon19);
        _medusa->setIconSize(QSize(40, 40));
        _medusa->setCheckable(true);
        _medusa->setAutoRaise(true);

        gridLayout->addWidget(_medusa, 2, 2, 1, 1);

        _minotaur = new QToolButton(Units);
        _minotaur->setObjectName(QStringLiteral("_minotaur"));
        QIcon icon20;
        icon20.addFile(QStringLiteral(":/icons/minotaur.png"), QSize(), QIcon::Normal, QIcon::Off);
        _minotaur->setIcon(icon20);
        _minotaur->setIconSize(QSize(40, 40));
        _minotaur->setCheckable(true);
        _minotaur->setAutoRaise(true);

        gridLayout->addWidget(_minotaur, 2, 1, 1, 1);

        _zyklop = new QToolButton(Units);
        _zyklop->setObjectName(QStringLiteral("_zyklop"));
        QIcon icon21;
        icon21.addFile(QStringLiteral(":/icons/zyklop.png"), QSize(), QIcon::Normal, QIcon::Off);
        _zyklop->setIcon(icon21);
        _zyklop->setIconSize(QSize(40, 40));
        _zyklop->setCheckable(true);
        _zyklop->setAutoRaise(true);

        gridLayout->addWidget(_zyklop, 2, 3, 1, 1);

        _manti = new QToolButton(Units);
        _manti->setObjectName(QStringLiteral("_manti"));
        QIcon icon22;
        icon22.addFile(QStringLiteral(":/icons/manticore.png"), QSize(), QIcon::Normal, QIcon::Off);
        _manti->setIcon(icon22);
        _manti->setIconSize(QSize(40, 40));
        _manti->setCheckable(true);
        _manti->setAutoRaise(true);

        gridLayout->addWidget(_manti, 3, 1, 1, 1);

        _fury = new QToolButton(Units);
        _fury->setObjectName(QStringLiteral("_fury"));
        QIcon icon23;
        icon23.addFile(QStringLiteral(":/icons/fury.png"), QSize(), QIcon::Normal, QIcon::Off);
        _fury->setIcon(icon23);
        _fury->setIconSize(QSize(40, 40));
        _fury->setCheckable(true);
        _fury->setAutoRaise(true);

        gridLayout->addWidget(_fury, 3, 5, 1, 1);

        _pega = new QToolButton(Units);
        _pega->setObjectName(QStringLiteral("_pega"));
        QIcon icon24;
        icon24.addFile(QStringLiteral(":/icons/pegasus.png"), QSize(), QIcon::Normal, QIcon::Off);
        _pega->setIcon(icon24);
        _pega->setIconSize(QSize(40, 40));
        _pega->setCheckable(true);
        _pega->setAutoRaise(true);

        gridLayout->addWidget(_pega, 3, 4, 1, 1);

        _harpy = new QToolButton(Units);
        _harpy->setObjectName(QStringLiteral("_harpy"));
        QIcon icon25;
        icon25.addFile(QStringLiteral(":/icons/harpy.png"), QSize(), QIcon::Normal, QIcon::Off);
        _harpy->setIcon(icon25);
        _harpy->setIconSize(QSize(40, 40));
        _harpy->setCheckable(true);
        _harpy->setAutoRaise(true);

        gridLayout->addWidget(_harpy, 3, 2, 1, 1);

        _hydra = new QToolButton(Units);
        _hydra->setObjectName(QStringLiteral("_hydra"));
        QIcon icon26;
        icon26.addFile(QStringLiteral(":/icons/hydra.png"), QSize(), QIcon::Normal, QIcon::Off);
        _hydra->setIcon(icon26);
        _hydra->setIconSize(QSize(40, 40));
        _hydra->setCheckable(true);
        _hydra->setAutoRaise(true);

        gridLayout->addWidget(_hydra, 3, 3, 1, 1);


        retranslateUi(Units);

        QMetaObject::connectSlotsByName(Units);
    } // setupUi

    void retranslateUi(QWidget *Units)
    {
        Units->setWindowTitle(QApplication::translate("Units", "Form", 0));
        _slow->setText(QString());
        _biri->setText(QString());
        _fire->setText(QString());
        _brander->setText(QString());
        _fast->setText(QString());
        _trireme->setText(QString());
        _kolo->setText(QString());
        _sword->setText(QString());
        _slinger->setText(QString());
        _archer->setText(QString());
        _hoplite->setText(QString());
        _rider->setText(QString());
        _chariot->setText(QString());
        _catapult->setText(QString());
        _godsent->setText(QString());
        _griffin->setText(QString());
        _boar->setText(QString());
        _cerberus->setText(QString());
        _centaur->setText(QString());
        _medusa->setText(QString());
        _minotaur->setText(QString());
        _zyklop->setText(QString());
        _manti->setText(QString());
        _fury->setText(QString());
        _pega->setText(QString());
        _harpy->setText(QString());
        _hydra->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Units: public Ui_Units {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UNITS_H
