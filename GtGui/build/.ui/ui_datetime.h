/********************************************************************************
** Form generated from reading UI file 'datetime.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATETIME_H
#define UI_DATETIME_H

#include <QtCore/QDate>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DateTime
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QToolButton *_reset;
    QVBoxLayout *verticalLayout;
    QTimeEdit *_time;
    QCalendarWidget *_date;

    void setupUi(QWidget *DateTime)
    {
        if (DateTime->objectName().isEmpty())
            DateTime->setObjectName(QStringLiteral("DateTime"));
        DateTime->resize(216, 179);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DateTime->sizePolicy().hasHeightForWidth());
        DateTime->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(DateTime);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        _reset = new QToolButton(DateTime);
        _reset->setObjectName(QStringLiteral("_reset"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/reset_time.ico"), QSize(), QIcon::Normal, QIcon::Off);
        _reset->setIcon(icon);

        horizontalLayout->addWidget(_reset);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        _time = new QTimeEdit(DateTime);
        _time->setObjectName(QStringLiteral("_time"));
        _time->setAlignment(Qt::AlignCenter);
        _time->setMaximumDate(QDate(2000, 1, 1));

        verticalLayout->addWidget(_time);


        horizontalLayout->addLayout(verticalLayout);


        verticalLayout_2->addLayout(horizontalLayout);

        _date = new QCalendarWidget(DateTime);
        _date->setObjectName(QStringLiteral("_date"));
        sizePolicy.setHeightForWidth(_date->sizePolicy().hasHeightForWidth());
        _date->setSizePolicy(sizePolicy);
        _date->setMinimumDate(QDate(2000, 1, 1));
        _date->setMaximumDate(QDate(2199, 12, 31));
        _date->setFirstDayOfWeek(Qt::Monday);
        _date->setDateEditEnabled(true);

        verticalLayout_2->addWidget(_date);


        retranslateUi(DateTime);

        QMetaObject::connectSlotsByName(DateTime);
    } // setupUi

    void retranslateUi(QWidget *DateTime)
    {
        DateTime->setWindowTitle(QApplication::translate("DateTime", "Form", 0));
#ifndef QT_NO_TOOLTIP
        _reset->setToolTip(QApplication::translate("DateTime", "Reset time to current time", 0));
#endif // QT_NO_TOOLTIP
        _reset->setText(QString());
#ifndef QT_NO_TOOLTIP
        _time->setToolTip(QApplication::translate("DateTime", "Time", 0));
#endif // QT_NO_TOOLTIP
        _time->setDisplayFormat(QApplication::translate("DateTime", "HH:mm:ss", 0));
    } // retranslateUi

};

namespace Ui {
    class DateTime: public Ui_DateTime {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATETIME_H
