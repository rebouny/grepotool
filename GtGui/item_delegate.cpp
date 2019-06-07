/* towns_model.cpp  - Town data model

Copyright (c) 2013 P. Vorpahl

This file is part of Grepotool, a free utility for the browsergame 
Grepolis which is the intellectual property of InnoGames GmbH.

Grepotool is free Software: you can redistribute it and/or modify 
it under the terms of the GNU Lesser General Public License as 
published by the Free Software Foundation, either version 3 of the 
License, or any later version. Alternatively, you may use it under 
the terms of the GNU General Public License as published by the Free 
Software Foundation, either version 3 of the License, or any later 
version.

Grepotool is distributed in the hope that it will be useful, but 
WITHOUT ANY WARRANTY; without even the implied warranty of 
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License 
along with 'Grepotool; see the files 'GPL.txt' and 'LGPL.txt' in 
the base directory of your installation. If not, see 
'http://www.gnu.org/licenses/'.
*/
#include "table_model.h"


#include <QApplication>
#include <QPainter>
#include <QMouseEvent>
#include <QItemDelegate>

ItemDelegate::ItemDelegate(QObject *parent ): QAbstractItemDelegate (parent)
{
}

void ItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,	const QModelIndex &index) const
{
	const TableModel * tm = dynamic_cast <const TableModel *> (index.model());

	if (!tm) return ;
	QItemDelegate it;

	QRect check_r; // checkbox rect
	QRect deco_r; // decoration rect
	QRect content_r = option.rect;  // content rect

	painter->save();
	painter->setPen(Qt::NoPen);


    QStyle *style = QApplication::style();
	int margin = style->pixelMetric(QStyle::PM_FocusFrameHMargin, 0, 0) + 1;

	QVariant data    = index.model()->data(index, Qt::DisplayRole);
	QVariant chk     =  index.model()->data(index, Qt::CheckStateRole);
	QPixmap dec      =  index.model()->data(index, Qt::DecorationRole).value<QPixmap>();
	Qt::Alignment al = (Qt::AlignmentFlag) index.model()->data(index, Qt::TextAlignmentRole).toInt() | Qt::AlignVCenter;

	if (!dec.isNull()) deco_r = dec.rect();
	if (chk.isValid ()) {
		QStyleOptionButton optt;
        optt.QStyleOption::operator=(option);				
		check_r = QApplication::style()->subElementRect(QStyle::SE_ViewItemCheckIndicator, &optt, 0);
	}


	// do the layout
	doLayout (option, &check_r, &deco_r, &content_r, false);

	if (option.state & QStyle::State_Selected) {

		painter->fillRect(option.rect, option.palette.highlight());
		painter->setPen(option.palette.highlightedText().color());

	} else {
		painter->setPen(option.palette.text().color());
	}

	if (chk.isValid()) {	

		// checkstate
		QStyleOptionViewItem opt(option);
		opt.rect = check_r;
		opt.state = opt.state & ~QStyle::State_HasFocus;		
		Qt::CheckState state = (Qt::CheckState) chk.toInt();
		switch (state) {
			case Qt::Unchecked:
				opt.state |= QStyle::State_Off;
				break;
			case Qt::PartiallyChecked:
		        opt.state |= QStyle::State_NoChange;
			    break;
			case Qt::Checked:
				opt.state |= QStyle::State_On;
				break;
		}
		QApplication::style()->drawPrimitive(QStyle::PE_IndicatorViewItemCheck, &opt, painter, 0);
	}

	if (!dec.isNull()) {
		painter->drawPixmap (deco_r.x(), deco_r.y(), dec);		
	}

	content_r.setWidth (content_r.width()-2*margin);
	content_r.setLeft  (content_r.left() + margin);
	//content_r.setRight (content_r.right() - margin);

	if (data.type() == QVariant::String) {
		
		QTextOption topt (al);
		topt.setWrapMode(QTextOption::NoWrap);		
		
		painter->drawText (content_r, QFontMetrics (option.font).elidedText (data.toString(), Qt::ElideRight, content_r.width()), topt);

	} else if(data.type() == QVariant::Pixmap) {

		QPixmap pm =  data.value<QPixmap> ();
		painter->setClipping (true);
		painter->setClipRect (content_r);
		int px = content_r.left() + (content_r.width() - pm.width())/2;
		int py = content_r.top() + (content_r.height() - pm.height())/2;
		painter->drawPixmap (px, py, pm);

	} else if (data.type() == QVariant::Color) {

		painter->fillRect(content_r, data.value<QColor>());
	}
	painter->restore ();
}

QSize ItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index ) const
{
	const TableModel * tm = dynamic_cast <const TableModel *> (index.model());

	if (!tm) return QSize();

	QVariant data = index.model()->data(index, Qt::DisplayRole);
	QVariant chk  = index.model()->data(index, Qt::CheckStateRole);
	QPixmap  dec   = index.model()->data(index, Qt::DecorationRole).value<QPixmap>();
	int w = 0;
	int h = tm->iconSize().height();

    QStyle *style = QApplication::style();
	int margin = style->pixelMetric(QStyle::PM_FocusFrameHMargin, 0, 0) + 1;

	QRect check_r; // checkbox rect
	QRect deco_r; // decoration rect
	QRect content_r = option.rect;  // content rect
	if (!dec.isNull()) deco_r = dec.rect();
	if (chk.isValid ()) {
		QStyleOptionButton optt;
        optt.QStyleOption::operator=(option);				
		check_r = QApplication::style()->subElementRect(QStyle::SE_ViewItemCheckIndicator, &optt, 0);
	}

	// do the layout
	doLayout (option, &check_r, &deco_r, &content_r, true);

	if (chk.isValid()) {	
		w += check_r.width();
	}

	if (!dec.isNull()) w += deco_r.width();

	if (data.type() == QVariant::String) {

		w  += QFontMetrics (option.font).width( data.toString() );
		w += 2*margin;

	} else if(data.type() == QVariant::Pixmap) {

		w += data.value<QPixmap> ().width();
		w += 2*margin;

	} else if(data.type() == QVariant::Color) {

		w += tm->iconSize().width();
		w += 2*margin;
	}
	return QSize(w,h);
}

// Handle Mouse events on the item
bool ItemDelegate::editorEvent ( QEvent * ev, QAbstractItemModel * model, 
		const QStyleOptionViewItem & option, const QModelIndex & index )
{
	TableModel * tm = dynamic_cast <TableModel *> (model);

	if (!tm) return false;
		
	QVariant chk  = tm->data(index, Qt::CheckStateRole);

	if (!chk.isValid()) return false;


	
    if ((ev->type() == QEvent::MouseButtonRelease)
		|| (ev->type() == QEvent::MouseButtonDblClick)) {
			
			QStyleOptionButton optt;
			optt.QStyleOption::operator=(option);				



			QRect br = QApplication::style()->subElementRect(QStyle::SE_ViewItemCheckIndicator, &optt, 0);
	        QRect emptyRect;
		    doLayout(option, &br, &emptyRect, &emptyRect, false);


			QMouseEvent *me = static_cast<QMouseEvent*>(ev);
			if (me->button() != Qt::LeftButton || !br.contains(me->pos()))
				return false;

			// eat the double click events inside the check rect
			if (ev->type() == QEvent::MouseButtonDblClick)
				return true;

			Qt::CheckState state = (Qt::CheckState) chk.toInt();
			
			state = (state == Qt::Checked) ? Qt::Unchecked : Qt::Checked;  
			
			tm->setItemCheckState (index, state);
	}
	return false;
}





void ItemDelegate::doLayout(const QStyleOptionViewItem &option,
                             QRect *checkRect, QRect *pixmapRect, QRect *textRect,
                             bool hint) const
{
    QStyle *style = QApplication::style();
    const bool hasCheck = checkRect->isValid();
    const bool hasPixmap = pixmapRect->isValid();
    const bool hasText = textRect->isValid();
    const int textMargin = hasText ? style->pixelMetric(QStyle::PM_FocusFrameHMargin, 0, 0) + 1 : 0;
    const int pixmapMargin = hasPixmap ? style->pixelMetric(QStyle::PM_FocusFrameHMargin, 0, 0) + 1 : 0;
    const int checkMargin = hasCheck ? style->pixelMetric(QStyle::PM_FocusFrameHMargin, 0, 0) + 1 : 0;
    int x = option.rect.left();
    int y = option.rect.top();
    int w, h;

    textRect->adjust(-textMargin, 0, textMargin, 0); // add width padding
    if (textRect->height() == 0 && (!hasPixmap || !hint)) {
        //if there is no text, we still want to have a decent height for the item sizeHint and the editor size
        textRect->setHeight(option.fontMetrics.height());
    }

    QSize pm(0, 0);
    if (hasPixmap) {
        pm = pixmapRect->size();
        pm.rwidth() += 2 * pixmapMargin;
    }
    if (hint) {
        h = qMax(checkRect->height(), qMax(textRect->height(), pm.height()));
        if (option.decorationPosition == QStyleOptionViewItem::Left
            || option.decorationPosition == QStyleOptionViewItem::Right) {
            w = textRect->width() + pm.width();
        } else {
            w = qMax(textRect->width(), pm.width());
        }
    } else {
        w = option.rect.width();
        h = option.rect.height();
    }

    int cw = 0;
    QRect check;
    if (hasCheck) {
        cw = checkRect->width() + 2 * checkMargin;
        if (hint) w += cw;
        if (option.direction == Qt::RightToLeft) {
            check.setRect(x + w - cw, y, cw, h);
        } else {
            check.setRect(x + checkMargin, y, cw, h);
        }
    }

    // at this point w should be the *total* width

    QRect display;
    QRect decoration;
    switch (option.decorationPosition) {
    case QStyleOptionViewItem::Top: {
        if (hasPixmap)
            pm.setHeight(pm.height() + pixmapMargin); // add space
        h = hint ? textRect->height() : h - pm.height();

        if (option.direction == Qt::RightToLeft) {
            decoration.setRect(x, y, w - cw, pm.height());
            display.setRect(x, y + pm.height(), w - cw, h);
        } else {
            decoration.setRect(x + cw, y, w - cw, pm.height());
            display.setRect(x + cw, y + pm.height(), w - cw, h);
        }
        break; }
    case QStyleOptionViewItem::Bottom: {
        if (hasText)
            textRect->setHeight(textRect->height() + textMargin); // add space
        h = hint ? textRect->height() + pm.height() : h;

        if (option.direction == Qt::RightToLeft) {
            display.setRect(x, y, w - cw, textRect->height());
            decoration.setRect(x, y + textRect->height(), w - cw, h - textRect->height());
        } else {
            display.setRect(x + cw, y, w - cw, textRect->height());
            decoration.setRect(x + cw, y + textRect->height(), w - cw, h - textRect->height());
        }
        break; }
    case QStyleOptionViewItem::Left: {
        if (option.direction == Qt::LeftToRight) {
            decoration.setRect(x + cw, y, pm.width(), h);
            display.setRect(decoration.right() + 1, y, w - pm.width() - cw, h);
        } else {
            display.setRect(x, y, w - pm.width() - cw, h);
            decoration.setRect(display.right() + 1, y, pm.width(), h);
        }
        break; }
    case QStyleOptionViewItem::Right: {
        if (option.direction == Qt::LeftToRight) {
            display.setRect(x + cw, y, w - pm.width() - cw, h);
            decoration.setRect(display.right() + 1, y, pm.width(), h);
        } else {
            decoration.setRect(x, y, pm.width(), h);
            display.setRect(decoration.right() + 1, y, w - pm.width() - cw, h);
        }
        break; }
    default:
        qWarning("doLayout: decoration position is invalid");
        decoration = *pixmapRect;
        break;
    }

    if (!hint) { // we only need to do the internal layout if we are going to paint
        *checkRect = QStyle::alignedRect(option.direction, Qt::AlignCenter,
                                         checkRect->size(), check);
        *pixmapRect = QStyle::alignedRect(option.direction, option.decorationAlignment,
                                          pixmapRect->size(), decoration);
        // the text takes up all available space, unless the decoration is not shown as selected
        if (option.showDecorationSelected)
            *textRect = display;
        else
            *textRect = QStyle::alignedRect(option.direction, option.displayAlignment,
                                            textRect->size().boundedTo(display.size()), display);
    } else {
        *checkRect = check;
        *pixmapRect = decoration;
        *textRect = display;
    }
}

