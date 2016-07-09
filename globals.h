#ifndef GLOBALS_H
#define GLOBALS_H

#include <QWidget>
#include <QVariant>
#include <QTypeInfo>
#include <QTime>
#include <QtGui>
#include <QtCore/QtGlobal>
#include <QString>
#include <QSplitter>
#include <QSettings>
#include <QRect>
#include <QProcess>
#include <QObject>
#include <QMetaType>
#include <QMainWindow>
#include <QFont>
#include <QDebug>
#include <QComboBox>
#include <QtGlobal>
#include <QModelIndexList>

#include "types.h"
#include "debug.h"

#define	DEFAULT_CONFIG_PATH	QString( qgetenv("HOME") + "/.config/" )

/* ======================================================================== */
#include "locals.h"

#ifndef CONFIG_PATH
	#define CONFIG_PATH	QString( DEFAULT_CONFIG_PATH + PROJECT_NAME )
#endif

#ifndef CONFIG_FILE
	#define CONFIG_FILE	QString( QDir(CONFIG_PATH).absoluteFilePath("config") )
#endif

/* ======================================================================== */

#define GEOM QString("/Geometry")
#define STAT QString("/State")

/* ======================================================================== */
/*						Global namespace macro definitions								 */
/* ======================================================================== */
#define QSETTINGS QSettings config(CONFIG_FILE, QSettings::IniFormat);

#define     QSPLT_STORE     { QSETTINGS \
	QList<QSplitter *> spls = findChildren<QSplitter *>(); \
	foreach (QSplitter *sp, spls) \
	config.setValue(objectName() + "/" + sp->objectName(), sp->saveState()); \
	}
#define     QACTION_STORE     { QSETTINGS \
	QList<QAction *> acts = findChildren<QAction *>(QString(), Qt::FindDirectChildrenOnly); \
	foreach (QAction *act, acts) \
	config.setValue(objectName() + "/" + act->objectName(), act->isChecked()); \
	}
#define     QACTION_RESTORE     { QSETTINGS \
	QList<QAction *> acts = findChildren<QAction *>(QString(), Qt::FindDirectChildrenOnly); \
	foreach (QAction *act, acts) \
	act->setChecked( config.value(objectName() + "/" + act->objectName(), false).toBool()); \
	}
#define     QSPLT_RESTORE   { QSETTINGS \
	QList<QSplitter *> spls = findChildren<QSplitter *>(); \
	foreach (QSplitter *sp, spls) { \
	sp->restoreState(config.value(objectName() + "/" + sp->objectName(), " ").toByteArray()); } }
#define     QFONT_STORE (QFont font)   { \
	QSETTINGS;  config.setValue(objectName() + "/lastFont", font.toString()); \
	}
#define     QFONT_RESTORE   { \
	QFont f; \
	f=fromString(config.value("Console/lastFont","").toString()); \
	return f; \
	}

/**
 * For storing and restoring window geometrys from different Widget, with or
 * without splitters, the only thing to call in the destructor is QWIN_STORE;
 * and the only thing while instance construction ist QWIN_RESTORE;
 * No QSETTINGS, no QSPLT_RESTORE....
 */
#define     QWIN_STORE      { QSETTINGS; \
	QSPLT_STORE; \
	config.setValue(objectName() + GEOM, saveGeometry() ); \
	}
#define     QWIN_RESTORE    { QSETTINGS; \
	restoreGeometry(config.value(objectName()+GEOM,"").toByteArray()); \
	QSPLT_RESTORE; \
	}

#define VNAM(name) (QString(#name) \
	.replace(QString("->"), QString(".")) \
	.remove(QRegExp("\\(\\)")))

/*!
 * This macro sets o's objectName() to "o" AND returns the object. So this macro
 * could be used as in-placement function to set a objects name when passing it
 * to another function or constructor!!!!!!
 * For example:
 *
 * hSplitterA->addWidget( PONAM(views) );
 * vSplitterA->addWidget( PONAM(hSplitterA) );
 * PONAM(vSplitterA)->addWidget( PONAM(console) );
 *
 */
#define PONAM(o) (o->setObjectName(#o),o)		//!< Set pointed objects name
#define ONAM(o) (o.setObjectName(#o),o)		//!< Set objects name

#define RANDI() ( (int)(rand() / static_cast<double>( RAND_MAX/0xff )) )
#define RANDUI() ( (quint8)(rand() / static_cast<double>( RAND_MAX/0xff )) )

#define QT_MESSAGE_PATTERN_DEFAULT "%{if-category}%{category}: %{endif}%{message}"
#define QT_MESSAGE_PATTERN_FILE_LINE "%{if-category}%{category}: %{endif}%{file}(%{line})%{message}"

struct ItemStyle;
struct uID_t;

/*!
 * do-while() loop is a trick to let you define multi-statement macros and
 * call them like functions. Note the lack of trailing ';'
 */
#define qReturn(msg)		do { WARN << QString(msg); return; } while(0)
#define bReturn(msg)		do { WARN << QString(msg); return false; } while(0)
#define vReturn(msg)		do { WARN << QString(msg); return QVariant(); } while(0)
#define milReturn(msg)	do { WARN << QString(msg); return QModelIndexList(); } while(0)


#define IS_INVALID(x) ( (! x.isValid()) \
	? ( WARN << QString("Invalid index: %1(%2):").arg(__func__).arg(__LINE__), true ) \
	: ( false ) )

/* ======================================================================== */
/*						Global namespace function declaration							 */
/* ======================================================================== */
int getIndexOfMax(QList<int> in);
int getIndexOfMin(QList<int> in);

/* ======================================================================== */
/*										Class Globals						                */
/* ======================================================================== */
class Globals {

public:  /** Declarations */


	static QString
	ddgbStyleShtA,
	ddgbStyleShtInpFrm,
	ddgbCheckableStyleSht,
	ddtvStyleShtA,
	ddgbStyleShtCenterHead,
	gbStyleShtCenterPROPERTYS,
	STR_NOTIFY,
	defaultFontString;

	static QByteArray
	htmlNotify;

	explicit Globals() {}
	static Globals *getObjectPtr() {
		if(inst == 0)
			inst = new Globals();
		return inst;

	}

	void notify_os(QString msgBody,
						QString msgHead = "Globals",
						QString msgTime = "2000") {

		S_STR_NOTIFY = STR_NOTIFY
							.replace("@MSG_TIME@", msgTime)
							.replace("@APP@","SQL browser")
							.replace("@MSG_HEAD@", msgHead)
							.replace("@MSG_BODY@", msgBody);
		proc.start(STR_NOTIFY);
	}
	static QStringList widToStrLst(QWidgetList &lst);
	static QStringList objToStrLst(QObjectList &lst);
	static QString widToStr(QWidgetList &lst, QString sep = ",");
	static QString objToStr(QObjectList &lst, QString sep = ",");

	static QStringList seqString(		QString str,	int count,		int lBound = 0, int step = 1);
	static QList<QFont> seqFont(		QFont font,		int count,		int lBound = 0, int step = 1);
	static QList<QColor> seqColor(	QColor color,	int count,		int lBound = 0, int step = 1);
	static QList<quint8> seqInt(		quint8 i,		int count,		int lBound = 0, int step = 1);
	static QList<ItemStyle> seqItemStyle(	ItemStyle s,	int count,		int lBound = 0, int step = 1);
	static QList<int> seqRandi(		int count,		int minVal = 0, int maxVal = 100, int seed = 99);
	static QList<quint8> seqRandui(	int count, quint8	 minVal = 0, quint8 maxVal = 100, int seed = 99);
	static QVariant seq(QVariant v, quint16 count, qint16 lBound = 0, qint16 step = 1) {
		Q_UNUSED(lBound);Q_UNUSED(step);
		QStringList l;

		if (! QString("QString").compare(v.typeName())) {
			for (int k = lBound; k < count; k++) {
				if (v.value<QString>().contains("%"))
					l << v.value<QString>().arg(k);
				else
					l << v.value<QString>();
			}
		}
		return l;
	};

public slots:
	static bool storeFont(const QByteArray objName, const QFont &font);
	static bool storeFont(const QString objName, const QFont &font);
	static QFont restoreFont(const QString objName, bool *ok = 0);

private:
	static Globals * inst;
	QProcess proc;
	QString S_STR_NOTIFY;
	static QStringList strLst;
	static QFont		fontStat;
	static QFontInfo	*fontInfo;

};

#endif // GLOBALS_H
