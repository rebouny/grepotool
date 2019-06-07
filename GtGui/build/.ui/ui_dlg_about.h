/********************************************************************************
** Form generated from reading UI file 'dlg_about.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLG_ABOUT_H
#define UI_DLG_ABOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_DlgAbout
{
public:
    QTextBrowser *_text;
    QTextBrowser *_text_2;
    QTextBrowser *_text_3;
    QPushButton *pushButton;

    void setupUi(QDialog *DlgAbout)
    {
        if (DlgAbout->objectName().isEmpty())
            DlgAbout->setObjectName(QStringLiteral("DlgAbout"));
        DlgAbout->resize(499, 228);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DlgAbout->sizePolicy().hasHeightForWidth());
        DlgAbout->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/gt.ico"), QSize(), QIcon::Normal, QIcon::Off);
        DlgAbout->setWindowIcon(icon);
        DlgAbout->setStyleSheet(QLatin1String("background-image:url(:/icons/splash.png);\n"
"background-repeat:no-repeat;\n"
"background-position:left top;\n"
"background-attachment:fixed;\n"
""));
        _text = new QTextBrowser(DlgAbout);
        _text->setObjectName(QStringLiteral("_text"));
        _text->setGeometry(QRect(0, 0, 304, 76));
        QPalette palette;
        QBrush brush(QColor(240, 240, 240, 0));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush);
        QBrush brush1(QColor(240, 240, 240, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush1);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Active, QPalette::Window, brush);
        QBrush brush2(QColor(246, 246, 246, 0));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush2);
        QBrush brush3(QColor(0, 0, 0, 0));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::NoRole, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::NoRole, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::NoRole, brush3);
        _text->setPalette(palette);
        _text->setStyleSheet(QStringLiteral(""));
        _text->setFrameShape(QFrame::NoFrame);
        _text->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        _text->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        _text->setTextInteractionFlags(Qt::LinksAccessibleByKeyboard|Qt::LinksAccessibleByMouse);
        _text->setOpenExternalLinks(true);
        _text_2 = new QTextBrowser(DlgAbout);
        _text_2->setObjectName(QStringLiteral("_text_2"));
        _text_2->setGeometry(QRect(1, 164, 368, 58));
        QPalette palette1;
        QBrush brush4(QColor(255, 255, 255, 0));
        brush4.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush4);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush4);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        _text_2->setPalette(palette1);
        _text_2->setStyleSheet(QLatin1String("background-image:url(:/icons/splash.png);\n"
"background-repeat:no-repeat;\n"
"background-position:left bottom;\n"
"background-attachment:fixed;"));
        _text_2->setFrameShape(QFrame::NoFrame);
        _text_2->setFrameShadow(QFrame::Plain);
        _text_2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        _text_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        _text_3 = new QTextBrowser(DlgAbout);
        _text_3->setObjectName(QStringLiteral("_text_3"));
        _text_3->setGeometry(QRect(0, 0, 501, 236));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::Light, brush1);
        palette2.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Light, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Light, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        _text_3->setPalette(palette2);
        _text_3->setStyleSheet(QLatin1String("background-image:url(:/icons/about.png);\n"
"background-repeat:no-repeat;\n"
"background-position:-360 0;\n"
"background-attachment:fixed;"));
        _text_3->setFrameShape(QFrame::NoFrame);
        _text_3->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        _text_3->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        _text_3->setTextInteractionFlags(Qt::LinksAccessibleByKeyboard|Qt::LinksAccessibleByMouse);
        _text_3->setOpenExternalLinks(true);
        pushButton = new QPushButton(DlgAbout);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(398, 168, 75, 23));
        _text_3->raise();
        _text->raise();
        _text_2->raise();
        pushButton->raise();

        retranslateUi(DlgAbout);
        QObject::connect(pushButton, SIGNAL(clicked()), DlgAbout, SLOT(accept()));

        QMetaObject::connectSlotsByName(DlgAbout);
    } // setupUi

    void retranslateUi(QDialog *DlgAbout)
    {
        DlgAbout->setWindowTitle(QApplication::translate("DlgAbout", "Grepotool 1.0 alpha", 0));
        _text->setHtml(QApplication::translate("DlgAbout", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Grepotool is a free utility for the browsergame </span><a href=\"http://www.grepolis.com\"><span style=\" font-size:8pt; text-decoration: underline; color:#0000ff;\">Grepolis</span></a><span style=\" font-size:8pt;\"> which is the intellectual property of InnoGames GmbH. </span></p></body></html>", 0));
        _text_2->setHtml(QApplication::translate("DlgAbout", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Grepotool is free Software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or any later version. </span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Please scroll down for more...</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; marg"
                        "in-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Grepotool is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. </span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">You should have received a copy of the GNU General Public License along with Grepotool; see the file 'GPL.txt' in the base directory of your installation. If not, see </span><a href=\"http://www.gnu.org/licenses/\"><span style"
                        "=\" font-size:8pt; text-decoration: underline; color:#0000ff;\">'http://www.gnu.org/licenses/'</span></a><span style=\" font-size:8pt;\">.</span></p></body></html>", 0));
        _text_3->setHtml(QApplication::translate("DlgAbout", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<table border=\"0\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px;\" width=\"100%\" cellspacing=\"2\" cellpadding=\"0\">\n"
"<tr>\n"
"<td></td>\n"
"<td width=\"130\">\n"
"<p align=\"right\" style=\"-qt-paragraph-type:empty; margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"></p>\n"
"<p align=\"right\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">\302\251 by P.Vorpahl </span><img src=\":/icons/icons/player.ico\" width=\"16\" height=\"16\" /><span style=\" font-siz"
                        "e:8pt; font-weight:600;\">.Pete.</span><span style=\" font-size:8pt;\"><br /></span></p>\n"
"<p align=\"center\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><a href=\"https://www.paypal.com/cgi-bin/webscr?method=POST&amp;cmd=_s-xclick&amp;hosted_button_id=BFPE2L5XF8Y48\"><span style=\" font-size:8pt; text-decoration: underline; color:#0000ff;\">Donate</span></a></p>\n"
"<p align=\"right\" style=\"-qt-paragraph-type:empty; margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"></p>\n"
"<p align=\"right\" style=\"-qt-paragraph-type:empty; margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:12pt;\"></p>\n"
"<p align=\"right\" style=\"-qt-paragraph-type:empty; margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:8pt;\"></p>\n"
"<p align=\""
                        "right\" style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt; color:#ffffff;\">Graphics by</span><img src=\":/icons/icons/player.ico\" width=\"16\" height=\"16\" /><span style=\" font-size:8pt; font-weight:600; color:#ffffff;\">Ziltoid</span></p></td></tr></table></body></html>", 0));
        pushButton->setText(QApplication::translate("DlgAbout", "Ok", 0));
    } // retranslateUi

};

namespace Ui {
    class DlgAbout: public Ui_DlgAbout {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLG_ABOUT_H
