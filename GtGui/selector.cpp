#include "selector.h"
#include <GtWorlddata.h>
#include <GtPlayers.h>
#include <GtTowns.h>
#include <GtAllys.h>
#include <QLabel>
#include <QKeyEvent>

Selector::Selector (QObject* p, SelType t):QObject(p),sel(-1),type(t){	
	edit = new QLineEdit;
	list = new QListWidget;
	goto_act = new QAction (this);
	goto_act->setIcon(QIcon(":/icons/icons/coord_goto2.ico"));

	list->setWindowFlags (list->windowFlags()|Qt::Popup|Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint);
	list->setFocusProxy(edit);
	list->installEventFilter(this);

	edit->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
	edit->setMinimumSize(QSize(160,20));
	connect (edit,SIGNAL (textEdited(const QString&)), this, SLOT(textEdited(const QString&)));
	connect (list, SIGNAL (itemActivated ( QListWidgetItem *) ), this, SLOT(itemActivated ( QListWidgetItem *  ) ));
	connect (goto_act, SIGNAL(triggered()) , this, SLOT(gotoClicked()));
}


bool Selector::eventFilter(QObject *obj, QEvent *ev)
{
if (obj != list)
         return false;

     if (ev->type() == QEvent::MouseButtonPress) {
         list->hide();
         edit->setFocus();
         return true;
     }

     if (ev->type() == QEvent::KeyPress) {
		 QListWidgetItem * item = list->currentItem();

         bool consumed = false;
         int key = static_cast<QKeyEvent*>(ev)->key();
         switch (key) {
         case Qt::Key_Enter:
         case Qt::Key_Return:

			 if (item) 
				itemSelected (item->data(Qt::UserRole).toInt());

             // doneCompletion();
             consumed = true;

         case Qt::Key_Escape:
             edit->setFocus();
             list->hide();
             consumed = true;

         case Qt::Key_Up:
         case Qt::Key_Down:
         case Qt::Key_Home:
         case Qt::Key_End:
         case Qt::Key_PageUp:
         case Qt::Key_PageDown:
             break;

         default:
             edit->setFocus();
             edit->event(ev);
             // list->hide();
             break;
         }

         return consumed;
     }

     return false;
}

void Selector::addToToolbar (QToolBar* b)
{
	QLabel *lab = new QLabel;	
	if (type == SelectTowns) {
		lab->setPixmap(QIcon(":/icons/icons/town.ico").pixmap(b->iconSize()));
	} else if (type == SelectPlayers) {
		lab->setPixmap(QIcon(":/icons/icons/player.ico").pixmap(b->iconSize()));
	} else if (type == SelectAllys) {
		lab->setPixmap(QIcon(":/icons/icons/ally.ico").pixmap(b->iconSize()));
	}
	b->addWidget (lab);
	b->addWidget (edit);
	if (type == SelectTowns) b->addAction (goto_act);
}


Selector::~Selector ()
{
	delete list;
}

void Selector::updateList ()
{
	sel = -1;
	edit->setText("");
}

int Selector::selection () const
{
	return sel;
}



void Selector::itemSelected ( int c)
{
	sel = c;
	if(c >= 0) {
		QString tx;			
		WorldData w = WorldData::currentWorld();
		if (type == SelectTowns) {
			const Town &to = w.towns()[c];
			tx = to.name;
			tx += QString(" (%1)").arg( (to.player_id<0)?tr("Ghost town") : w.players()[to.player_index].name);
		} else if (type == SelectPlayers) {
			tx = w.players()[c].name;
		} else if (type == SelectAllys) {
			tx = w.allys()[c].name;
		}
		edit->setText (tx);
	} else 
		edit->setText ("");

	list->hide();

	emit itemSelectedSignal (c);
}

void Selector::itemActivated ( QListWidgetItem * item )
{
	itemSelected (item->data(Qt::UserRole).toInt());
}

void Selector::textEdited (const QString &s)
{
	if (s.length()< 2) {
		list->hide();
		return;
	}

	list->clear();

	sel = -1;
	
	int mxl = 50;

	WorldData w = WorldData::currentWorld();
	if (type == SelectTowns) {
		int nt = w.towns().size();
		QVector <bool> add (nt);
		for (int i=0;i< nt && list->count()<mxl; ++i) {
			add[i] = false;
			const Town &to = w.towns()[i];
			QString tx = to.name;
			if(!tx.startsWith(s,Qt::CaseInsensitive)) continue;
			add[i] = true;
			tx += QString(" (%1)").arg( (to.ghost)?tr("Ghost town") : w.players()[to.player_index].name);
			QListWidgetItem *nit= new QListWidgetItem (tx);
			nit->setData(Qt::UserRole, i);
			list->addItem (nit);
		}
		for (int i=0;i< nt && list->count()<mxl; ++i) {
			if(add[i]) continue;
			const Town &to = w.towns()[i];
			QString tx = to.name;
			if(!tx.contains (s,Qt::CaseInsensitive)) continue;	
			tx += QString(" (%1)").arg( (to.ghost)?tr("Ghost town") : w.players()[to.player_index].name);
			QListWidgetItem *nit= new QListWidgetItem (tx);
			nit->setData(Qt::UserRole, i);
			list->addItem (nit);
		}
	} else if (type == SelectPlayers) {
		int nt = w.players().size();
		QVector <bool> add (nt);
		for (int i=0;i< nt && list->count()<mxl; ++i) {
			add[i] = false;
			const Player &to = w.players()[i];
			QString tx = to.name;
			if(!tx.startsWith(s,Qt::CaseInsensitive)) continue;
			add[i] = true;
			QListWidgetItem *nit= new QListWidgetItem (tx);
			nit->setData(Qt::UserRole, i);
			list->addItem (nit);
		}
		for (int i=0;i< nt && list->count()<mxl; ++i) {
			if(add[i]) continue;
			const Player &to = w.players()[i];
			QString tx = to.name;
			if(!tx.contains (s,Qt::CaseInsensitive)) continue;	
			QListWidgetItem *nit= new QListWidgetItem (tx);
			nit->setData(Qt::UserRole, i);
			list->addItem (nit);
		}
	} else if (type == SelectAllys) {
		int nt = w.allys().size();
		QVector <bool> add (nt);
		for (int i=0;i< nt && list->count()<mxl; ++i) {
			add[i] = false;
			const Ally &al = w.allys()[i];
			QString tx = al.name;
			if(!tx.startsWith(s,Qt::CaseInsensitive)) continue;
			add[i] = true;
			QListWidgetItem *nit= new QListWidgetItem (tx);
			nit->setData(Qt::UserRole, i);
			list->addItem (nit);
		}
		for (int i=0;i< nt && list->count()<mxl; ++i) {
			if(add[i]) continue;
			const Ally &al = w.allys()[i];
			QString tx = al.name;
			if(!tx.contains (s,Qt::CaseInsensitive)) continue;	
			QListWidgetItem *nit= new QListWidgetItem (tx);
			nit->setData(Qt::UserRole, i);
			list->addItem (nit);
		}
	}

	if(!list->count()) {
		list->hide();
	} else {
		popupList();
	}

}

void Selector::gotoClicked ()
{
	emit gotoClickedSignal (sel);
}

void Selector::popupList ()
{
	QPoint p (0,edit->height());
	p = edit->mapToGlobal(p);		
	list->updateGeometry();
	list->show();	
	list->move(p);
	edit->setFocus ();
}
