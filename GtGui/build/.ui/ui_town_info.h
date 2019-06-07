/********************************************************************************
** Form generated from reading UI file 'town_info.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TOWN_INFO_H
#define UI_TOWN_INFO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_TownInfo
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *_town;
    QToolButton *_goto;
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
    QToolButton *_any;
    QToolButton *_zeus;
    QToolButton *_hera;
    QToolButton *_poseidon;
    QToolButton *_athene;
    QToolButton *_hades;
    QToolButton *_artemis;
    QToolButton *_meteorology;
    QToolButton *_cartography;
    QToolButton *_lighthouse;
    QFrame *line;
    QFrame *line_2;
    QToolButton *_godsent;
    QToolButton *_griffin;
    QToolButton *_manti;
    QToolButton *_boar;
    QToolButton *_medusa;
    QToolButton *_minotaur;
    QToolButton *_zyklop;
    QToolButton *_hydra;
    QToolButton *_harpy;
    QToolButton *_cerberus;
    QToolButton *_centaur;
    QToolButton *_pega;
    QToolButton *_fury;
    QToolButton *_atlanta;
    QSpacerItem *verticalSpacer;
    QButtonGroup *_specials;
    QButtonGroup *_gods;

    void setupUi(QFrame *TownInfo)
    {
        if (TownInfo->objectName().isEmpty())
            TownInfo->setObjectName(QStringLiteral("TownInfo"));
        TownInfo->resize(383, 277);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(TownInfo->sizePolicy().hasHeightForWidth());
        TownInfo->setSizePolicy(sizePolicy);
        TownInfo->setFrameShape(QFrame::StyledPanel);
        TownInfo->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(TownInfo);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setContentsMargins(9, 9, 9, 9);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        _town = new QLabel(TownInfo);
        _town->setObjectName(QStringLiteral("_town"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(_town->sizePolicy().hasHeightForWidth());
        _town->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(_town);

        _goto = new QToolButton(TownInfo);
        _goto->setObjectName(QStringLiteral("_goto"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/town_goto.ico"), QSize(), QIcon::Normal, QIcon::Off);
        _goto->setIcon(icon);

        horizontalLayout->addWidget(_goto);


        verticalLayout->addLayout(horizontalLayout);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        _slow = new QToolButton(TownInfo);
        _slow->setObjectName(QStringLiteral("_slow"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icons/big_transporter.png"), QSize(), QIcon::Normal, QIcon::Off);
        _slow->setIcon(icon1);
        _slow->setIconSize(QSize(40, 40));
        _slow->setCheckable(false);
        _slow->setAutoRaise(true);

        gridLayout->addWidget(_slow, 2, 0, 1, 1);

        _biri = new QToolButton(TownInfo);
        _biri->setObjectName(QStringLiteral("_biri"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/icons/bireme.png"), QSize(), QIcon::Normal, QIcon::Off);
        _biri->setIcon(icon2);
        _biri->setIconSize(QSize(40, 40));
        _biri->setCheckable(false);
        _biri->setAutoRaise(true);

        gridLayout->addWidget(_biri, 2, 1, 1, 1);

        _fire = new QToolButton(TownInfo);
        _fire->setObjectName(QStringLiteral("_fire"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/icons/attack_ship.png"), QSize(), QIcon::Normal, QIcon::Off);
        _fire->setIcon(icon3);
        _fire->setIconSize(QSize(40, 40));
        _fire->setCheckable(false);
        _fire->setAutoRaise(true);

        gridLayout->addWidget(_fire, 2, 2, 1, 1);

        _brander = new QToolButton(TownInfo);
        _brander->setObjectName(QStringLiteral("_brander"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/icons/demolition_ship.png"), QSize(), QIcon::Normal, QIcon::Off);
        _brander->setIcon(icon4);
        _brander->setIconSize(QSize(40, 40));
        _brander->setCheckable(false);
        _brander->setAutoRaise(true);

        gridLayout->addWidget(_brander, 2, 3, 1, 1);

        _fast = new QToolButton(TownInfo);
        _fast->setObjectName(QStringLiteral("_fast"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/icons/small_transporter.png"), QSize(), QIcon::Normal, QIcon::Off);
        _fast->setIcon(icon5);
        _fast->setIconSize(QSize(40, 40));
        _fast->setCheckable(false);
        _fast->setAutoRaise(true);

        gridLayout->addWidget(_fast, 2, 4, 1, 1);

        _trireme = new QToolButton(TownInfo);
        _trireme->setObjectName(QStringLiteral("_trireme"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/icons/trireme.png"), QSize(), QIcon::Normal, QIcon::Off);
        _trireme->setIcon(icon6);
        _trireme->setIconSize(QSize(40, 40));
        _trireme->setCheckable(false);
        _trireme->setAutoRaise(true);

        gridLayout->addWidget(_trireme, 2, 5, 1, 1);

        _kolo = new QToolButton(TownInfo);
        _kolo->setObjectName(QStringLiteral("_kolo"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/icons/colonize_ship.png"), QSize(), QIcon::Normal, QIcon::Off);
        _kolo->setIcon(icon7);
        _kolo->setIconSize(QSize(40, 40));
        _kolo->setCheckable(false);
        _kolo->setAutoRaise(true);

        gridLayout->addWidget(_kolo, 2, 6, 1, 1);

        _sword = new QToolButton(TownInfo);
        _sword->setObjectName(QStringLiteral("_sword"));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/icons/sword.png"), QSize(), QIcon::Normal, QIcon::Off);
        _sword->setIcon(icon8);
        _sword->setIconSize(QSize(40, 40));
        _sword->setCheckable(false);
        _sword->setAutoRaise(true);

        gridLayout->addWidget(_sword, 3, 0, 1, 1);

        _slinger = new QToolButton(TownInfo);
        _slinger->setObjectName(QStringLiteral("_slinger"));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/icons/slinger.png"), QSize(), QIcon::Normal, QIcon::Off);
        _slinger->setIcon(icon9);
        _slinger->setIconSize(QSize(40, 40));
        _slinger->setCheckable(false);
        _slinger->setAutoRaise(true);

        gridLayout->addWidget(_slinger, 3, 1, 1, 1);

        _archer = new QToolButton(TownInfo);
        _archer->setObjectName(QStringLiteral("_archer"));
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/icons/archer.png"), QSize(), QIcon::Normal, QIcon::Off);
        _archer->setIcon(icon10);
        _archer->setIconSize(QSize(40, 40));
        _archer->setCheckable(false);
        _archer->setAutoRaise(true);

        gridLayout->addWidget(_archer, 3, 2, 1, 1);

        _hoplite = new QToolButton(TownInfo);
        _hoplite->setObjectName(QStringLiteral("_hoplite"));
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/icons/hoplite.png"), QSize(), QIcon::Normal, QIcon::Off);
        _hoplite->setIcon(icon11);
        _hoplite->setIconSize(QSize(40, 40));
        _hoplite->setCheckable(false);
        _hoplite->setAutoRaise(true);

        gridLayout->addWidget(_hoplite, 3, 3, 1, 1);

        _rider = new QToolButton(TownInfo);
        _rider->setObjectName(QStringLiteral("_rider"));
        QIcon icon12;
        icon12.addFile(QStringLiteral(":/icons/rider.png"), QSize(), QIcon::Normal, QIcon::Off);
        _rider->setIcon(icon12);
        _rider->setIconSize(QSize(40, 40));
        _rider->setCheckable(false);
        _rider->setAutoRaise(true);

        gridLayout->addWidget(_rider, 3, 4, 1, 1);

        _chariot = new QToolButton(TownInfo);
        _chariot->setObjectName(QStringLiteral("_chariot"));
        QIcon icon13;
        icon13.addFile(QStringLiteral(":/icons/chariot.png"), QSize(), QIcon::Normal, QIcon::Off);
        _chariot->setIcon(icon13);
        _chariot->setIconSize(QSize(40, 40));
        _chariot->setCheckable(false);
        _chariot->setAutoRaise(true);

        gridLayout->addWidget(_chariot, 3, 5, 1, 1);

        _catapult = new QToolButton(TownInfo);
        _catapult->setObjectName(QStringLiteral("_catapult"));
        QIcon icon14;
        icon14.addFile(QStringLiteral(":/icons/catapult.png"), QSize(), QIcon::Normal, QIcon::Off);
        _catapult->setIcon(icon14);
        _catapult->setIconSize(QSize(40, 40));
        _catapult->setCheckable(false);
        _catapult->setAutoRaise(true);

        gridLayout->addWidget(_catapult, 3, 6, 1, 1);

        _any = new QToolButton(TownInfo);
        _gods = new QButtonGroup(TownInfo);
        _gods->setObjectName(QStringLiteral("_gods"));
        _gods->addButton(_any);
        _any->setObjectName(QStringLiteral("_any"));
        QIcon icon15;
        icon15.addFile(QStringLiteral(":/icons/anygod.png"), QSize(), QIcon::Normal, QIcon::Off);
        _any->setIcon(icon15);
        _any->setIconSize(QSize(40, 40));
        _any->setCheckable(true);
        _any->setChecked(true);
        _any->setAutoRaise(true);

        gridLayout->addWidget(_any, 0, 0, 1, 1);

        _zeus = new QToolButton(TownInfo);
        _gods->addButton(_zeus);
        _zeus->setObjectName(QStringLiteral("_zeus"));
        QIcon icon16;
        icon16.addFile(QStringLiteral(":/icons/zeus.png"), QSize(), QIcon::Normal, QIcon::Off);
        _zeus->setIcon(icon16);
        _zeus->setIconSize(QSize(40, 40));
        _zeus->setCheckable(true);
        _zeus->setAutoRaise(true);

        gridLayout->addWidget(_zeus, 0, 1, 1, 1);

        _hera = new QToolButton(TownInfo);
        _gods->addButton(_hera);
        _hera->setObjectName(QStringLiteral("_hera"));
        QIcon icon17;
        icon17.addFile(QStringLiteral(":/icons/hera.png"), QSize(), QIcon::Normal, QIcon::Off);
        _hera->setIcon(icon17);
        _hera->setIconSize(QSize(40, 40));
        _hera->setCheckable(true);
        _hera->setAutoRaise(true);

        gridLayout->addWidget(_hera, 0, 2, 1, 1);

        _poseidon = new QToolButton(TownInfo);
        _gods->addButton(_poseidon);
        _poseidon->setObjectName(QStringLiteral("_poseidon"));
        QIcon icon18;
        icon18.addFile(QStringLiteral(":/icons/poseidon.png"), QSize(), QIcon::Normal, QIcon::Off);
        _poseidon->setIcon(icon18);
        _poseidon->setIconSize(QSize(40, 40));
        _poseidon->setCheckable(true);
        _poseidon->setAutoRaise(true);

        gridLayout->addWidget(_poseidon, 0, 3, 1, 1);

        _athene = new QToolButton(TownInfo);
        _gods->addButton(_athene);
        _athene->setObjectName(QStringLiteral("_athene"));
        QIcon icon19;
        icon19.addFile(QStringLiteral(":/icons/athena.png"), QSize(), QIcon::Normal, QIcon::Off);
        _athene->setIcon(icon19);
        _athene->setIconSize(QSize(40, 40));
        _athene->setCheckable(true);
        _athene->setAutoRaise(true);

        gridLayout->addWidget(_athene, 0, 4, 1, 1);

        _hades = new QToolButton(TownInfo);
        _gods->addButton(_hades);
        _hades->setObjectName(QStringLiteral("_hades"));
        QIcon icon20;
        icon20.addFile(QStringLiteral(":/icons/hades.png"), QSize(), QIcon::Normal, QIcon::Off);
        _hades->setIcon(icon20);
        _hades->setIconSize(QSize(40, 40));
        _hades->setCheckable(true);
        _hades->setAutoRaise(true);

        gridLayout->addWidget(_hades, 0, 5, 1, 1);

        _artemis = new QToolButton(TownInfo);
        _gods->addButton(_artemis);
        _artemis->setObjectName(QStringLiteral("_artemis"));
        QIcon icon21;
        icon21.addFile(QStringLiteral(":/icons/artemis.png"), QSize(), QIcon::Normal, QIcon::Off);
        _artemis->setIcon(icon21);
        _artemis->setIconSize(QSize(40, 40));
        _artemis->setCheckable(true);
        _artemis->setAutoRaise(true);

        gridLayout->addWidget(_artemis, 0, 6, 1, 1);

        _meteorology = new QToolButton(TownInfo);
        _specials = new QButtonGroup(TownInfo);
        _specials->setObjectName(QStringLiteral("_specials"));
        _specials->setExclusive(false);
        _specials->addButton(_meteorology);
        _meteorology->setObjectName(QStringLiteral("_meteorology"));
        QIcon icon22;
        icon22.addFile(QStringLiteral(":/icons/meteorology.png"), QSize(), QIcon::Normal, QIcon::Off);
        _meteorology->setIcon(icon22);
        _meteorology->setIconSize(QSize(40, 40));
        _meteorology->setCheckable(true);
        _meteorology->setAutoRaise(true);

        gridLayout->addWidget(_meteorology, 2, 8, 1, 1);

        _cartography = new QToolButton(TownInfo);
        _specials->addButton(_cartography);
        _cartography->setObjectName(QStringLiteral("_cartography"));
        QIcon icon23;
        icon23.addFile(QStringLiteral(":/icons/cartography.png"), QSize(), QIcon::Normal, QIcon::Off);
        _cartography->setIcon(icon23);
        _cartography->setIconSize(QSize(40, 40));
        _cartography->setCheckable(true);
        _cartography->setAutoRaise(true);

        gridLayout->addWidget(_cartography, 3, 8, 1, 1);

        _lighthouse = new QToolButton(TownInfo);
        _specials->addButton(_lighthouse);
        _lighthouse->setObjectName(QStringLiteral("_lighthouse"));
        QIcon icon24;
        icon24.addFile(QStringLiteral(":/icons/lighthouse.png"), QSize(), QIcon::Normal, QIcon::Off);
        _lighthouse->setIcon(icon24);
        _lighthouse->setIconSize(QSize(40, 40));
        _lighthouse->setCheckable(true);
        _lighthouse->setAutoRaise(true);

        gridLayout->addWidget(_lighthouse, 5, 8, 1, 1);

        line = new QFrame(TownInfo);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 1, 0, 1, 7);

        line_2 = new QFrame(TownInfo);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_2, 0, 7, 6, 1);

        _godsent = new QToolButton(TownInfo);
        _godsent->setObjectName(QStringLiteral("_godsent"));
        QIcon icon25;
        icon25.addFile(QStringLiteral(":/icons/godsent.png"), QSize(), QIcon::Normal, QIcon::Off);
        _godsent->setIcon(icon25);
        _godsent->setIconSize(QSize(40, 40));
        _godsent->setCheckable(false);
        _godsent->setAutoRaise(true);

        gridLayout->addWidget(_godsent, 4, 0, 1, 1);

        _griffin = new QToolButton(TownInfo);
        _griffin->setObjectName(QStringLiteral("_griffin"));
        QIcon icon26;
        icon26.addFile(QStringLiteral(":/icons/griffin.png"), QSize(), QIcon::Normal, QIcon::Off);
        _griffin->setIcon(icon26);
        _griffin->setIconSize(QSize(40, 40));
        _griffin->setCheckable(false);
        _griffin->setAutoRaise(true);

        gridLayout->addWidget(_griffin, 5, 6, 1, 1);

        _manti = new QToolButton(TownInfo);
        _manti->setObjectName(QStringLiteral("_manti"));
        QIcon icon27;
        icon27.addFile(QStringLiteral(":/icons/manticore.png"), QSize(), QIcon::Normal, QIcon::Off);
        _manti->setIcon(icon27);
        _manti->setIconSize(QSize(40, 40));
        _manti->setCheckable(false);
        _manti->setAutoRaise(true);

        gridLayout->addWidget(_manti, 5, 1, 1, 1);

        _boar = new QToolButton(TownInfo);
        _boar->setObjectName(QStringLiteral("_boar"));
        QIcon icon28;
        icon28.addFile(QStringLiteral(":/icons/calydonian_boar.png"), QSize(), QIcon::Normal, QIcon::Off);
        _boar->setIcon(icon28);
        _boar->setIconSize(QSize(40, 40));
        _boar->setCheckable(false);
        _boar->setAutoRaise(true);

        gridLayout->addWidget(_boar, 4, 6, 1, 1);

        _medusa = new QToolButton(TownInfo);
        _medusa->setObjectName(QStringLiteral("_medusa"));
        QIcon icon29;
        icon29.addFile(QStringLiteral(":/icons/medusa.png"), QSize(), QIcon::Normal, QIcon::Off);
        _medusa->setIcon(icon29);
        _medusa->setIconSize(QSize(40, 40));
        _medusa->setCheckable(false);
        _medusa->setAutoRaise(true);

        gridLayout->addWidget(_medusa, 4, 2, 1, 1);

        _minotaur = new QToolButton(TownInfo);
        _minotaur->setObjectName(QStringLiteral("_minotaur"));
        QIcon icon30;
        icon30.addFile(QStringLiteral(":/icons/minotaur.png"), QSize(), QIcon::Normal, QIcon::Off);
        _minotaur->setIcon(icon30);
        _minotaur->setIconSize(QSize(40, 40));
        _minotaur->setCheckable(false);
        _minotaur->setAutoRaise(true);

        gridLayout->addWidget(_minotaur, 4, 1, 1, 1);

        _zyklop = new QToolButton(TownInfo);
        _zyklop->setObjectName(QStringLiteral("_zyklop"));
        QIcon icon31;
        icon31.addFile(QStringLiteral(":/icons/zyklop.png"), QSize(), QIcon::Normal, QIcon::Off);
        _zyklop->setIcon(icon31);
        _zyklop->setIconSize(QSize(40, 40));
        _zyklop->setCheckable(false);
        _zyklop->setAutoRaise(true);

        gridLayout->addWidget(_zyklop, 4, 3, 1, 1);

        _hydra = new QToolButton(TownInfo);
        _hydra->setObjectName(QStringLiteral("_hydra"));
        QIcon icon32;
        icon32.addFile(QStringLiteral(":/icons/hydra.png"), QSize(), QIcon::Normal, QIcon::Off);
        _hydra->setIcon(icon32);
        _hydra->setIconSize(QSize(40, 40));
        _hydra->setCheckable(false);
        _hydra->setAutoRaise(true);

        gridLayout->addWidget(_hydra, 5, 3, 1, 1);

        _harpy = new QToolButton(TownInfo);
        _harpy->setObjectName(QStringLiteral("_harpy"));
        QIcon icon33;
        icon33.addFile(QStringLiteral(":/icons/harpy.png"), QSize(), QIcon::Normal, QIcon::Off);
        _harpy->setIcon(icon33);
        _harpy->setIconSize(QSize(40, 40));
        _harpy->setCheckable(false);
        _harpy->setAutoRaise(true);

        gridLayout->addWidget(_harpy, 5, 2, 1, 1);

        _cerberus = new QToolButton(TownInfo);
        _cerberus->setObjectName(QStringLiteral("_cerberus"));
        QIcon icon34;
        icon34.addFile(QStringLiteral(":/icons/cerberus.png"), QSize(), QIcon::Normal, QIcon::Off);
        _cerberus->setIcon(icon34);
        _cerberus->setIconSize(QSize(40, 40));
        _cerberus->setCheckable(false);
        _cerberus->setAutoRaise(true);

        gridLayout->addWidget(_cerberus, 4, 5, 1, 1);

        _centaur = new QToolButton(TownInfo);
        _centaur->setObjectName(QStringLiteral("_centaur"));
        QIcon icon35;
        icon35.addFile(QStringLiteral(":/icons/centaur.png"), QSize(), QIcon::Normal, QIcon::Off);
        _centaur->setIcon(icon35);
        _centaur->setIconSize(QSize(40, 40));
        _centaur->setCheckable(false);
        _centaur->setAutoRaise(true);

        gridLayout->addWidget(_centaur, 4, 4, 1, 1);

        _pega = new QToolButton(TownInfo);
        _pega->setObjectName(QStringLiteral("_pega"));
        QIcon icon36;
        icon36.addFile(QStringLiteral(":/icons/pegasus.png"), QSize(), QIcon::Normal, QIcon::Off);
        _pega->setIcon(icon36);
        _pega->setIconSize(QSize(40, 40));
        _pega->setCheckable(false);
        _pega->setAutoRaise(true);

        gridLayout->addWidget(_pega, 5, 4, 1, 1);

        _fury = new QToolButton(TownInfo);
        _fury->setObjectName(QStringLiteral("_fury"));
        QIcon icon37;
        icon37.addFile(QStringLiteral(":/icons/fury.png"), QSize(), QIcon::Normal, QIcon::Off);
        _fury->setIcon(icon37);
        _fury->setIconSize(QSize(40, 40));
        _fury->setCheckable(false);
        _fury->setAutoRaise(true);

        gridLayout->addWidget(_fury, 5, 5, 1, 1);

        _atlanta = new QToolButton(TownInfo);
        _atlanta->setObjectName(QStringLiteral("_atlanta"));
        _atlanta->setEnabled(false);
        QIcon icon38;
        icon38.addFile(QStringLiteral(":/icons/atlanta.png"), QSize(), QIcon::Normal, QIcon::Off);
        _atlanta->setIcon(icon38);
        _atlanta->setIconSize(QSize(40, 40));
        _atlanta->setCheckable(true);
        _atlanta->setAutoRaise(true);

        gridLayout->addWidget(_atlanta, 0, 8, 1, 1);


        verticalLayout->addLayout(gridLayout);

        verticalSpacer = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(TownInfo);

        QMetaObject::connectSlotsByName(TownInfo);
    } // setupUi

    void retranslateUi(QFrame *TownInfo)
    {
        TownInfo->setWindowTitle(QApplication::translate("TownInfo", "Frame", 0));
        _town->setText(QApplication::translate("TownInfo", "TextLabel", 0));
        _goto->setText(QApplication::translate("TownInfo", "...", 0));
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
        _any->setText(QString());
        _zeus->setText(QString());
        _hera->setText(QString());
        _poseidon->setText(QString());
        _athene->setText(QString());
        _hades->setText(QString());
        _artemis->setText(QString());
        _meteorology->setText(QString());
        _cartography->setText(QString());
        _lighthouse->setText(QString());
        _godsent->setText(QString());
        _griffin->setText(QString());
        _manti->setText(QString());
        _boar->setText(QString());
        _medusa->setText(QString());
        _minotaur->setText(QString());
        _zyklop->setText(QString());
        _hydra->setText(QString());
        _harpy->setText(QString());
        _cerberus->setText(QString());
        _centaur->setText(QString());
        _pega->setText(QString());
        _fury->setText(QString());
#ifndef QT_NO_TOOLTIP
        _atlanta->setToolTip(QApplication::translate("TownInfo", "Atlanta", 0));
#endif // QT_NO_TOOLTIP
        _atlanta->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class TownInfo: public Ui_TownInfo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TOWN_INFO_H
