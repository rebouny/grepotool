/********************************************************************************
** Form generated from reading UI file 'world_news.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WORLD_NEWS_H
#define UI_WORLD_NEWS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_News
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QToolButton *tb;
    QTextBrowser *text;

    void setupUi(QFrame *News)
    {
        if (News->objectName().isEmpty())
            News->setObjectName(QStringLiteral("News"));
        News->resize(615, 455);
        News->setFrameShape(QFrame::StyledPanel);
        News->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(News);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(News);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        tb = new QToolButton(News);
        tb->setObjectName(QStringLiteral("tb"));

        gridLayout->addWidget(tb, 0, 1, 1, 1);

        text = new QTextBrowser(News);
        text->setObjectName(QStringLiteral("text"));

        gridLayout->addWidget(text, 1, 0, 1, 2);


        retranslateUi(News);

        QMetaObject::connectSlotsByName(News);
    } // setupUi

    void retranslateUi(QFrame *News)
    {
        News->setWindowTitle(QApplication::translate("News", "Towns", 0));
        label->setText(QApplication::translate("News", "TextLabel", 0));
        tb->setText(QApplication::translate("News", "...", 0));
    } // retranslateUi

};

namespace Ui {
    class News: public Ui_News {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WORLD_NEWS_H
