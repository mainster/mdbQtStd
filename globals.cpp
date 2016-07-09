#include <QtGui>
#include <QWidget>
#include <QObject>
#include <QVariant>
#include <QTypeInfo>
#include <QMainWindow>

#include <QMetaType>

#include "globals.h"
#include "types.h"
#include <QString>
#include "types.h"


int getIndexOfMax(QList<int> in) {
	std::vector<int>::iterator res;

	res = std::max_element(in.toVector().toStdVector().begin(), in.toVector().toStdVector().end());

	return std::distance(in.toVector().toStdVector().begin(), res);
}

int getIndexOfMin(QList<int> in) {
	std::vector<int>::iterator res;

	res = std::min_element(in.toVector().toStdVector().begin(), in.toVector().toStdVector().end());

	return std::distance(in.toVector().toStdVector().begin(), res);
}

QByteArray	Globals::htmlNotify = "<font color=\"Lime\">@</font><br>";
QFont			Globals::fontStat	= QFont();
QString		Globals::defaultFontString = "Monospace,9,-1,5,50,0,0,0,0,0";
//const quint8	Globals::COLS = 8;


bool Globals::storeFont(const QByteArray objName, const QFont &font) {
	QSETTINGS;
	config.setValue(objName + "/lastFont", font.toString());
	return true;
}
bool Globals::storeFont(const QString objName, const QFont &font) {
	QSETTINGS;
	config.setValue(objName + "/lastFont", font.toString());
	return true;
}
QFont Globals::restoreFont(const QString objName, bool *ok) {
	QSETTINGS;
	Q_UNUSED(ok)

	fontStat.initialize();

	foreach (const QString s, config.allKeys()) {
		if(! s.compare(objName + "/lastFont")) {
			fontStat.fromString(config.value(objName + "/lastFont", "").toString());
			break;
		}
	}

	return fontStat;
}
QList<quint8> Globals::seqInt(quint8 i, int count, int lBound, int step) {
	QList<quint8> il;
	for (int k=lBound; k<count; k+=step) {
		il << i;
	}
	return il;
}
QList<int> Globals::seqRandi( int count, int minVal, int maxVal, int seed) {
	Q_UNUSED(minVal);Q_UNUSED(maxVal);Q_UNUSED(seed);

	QList<int> il;
	for (int k=0; k<count; k++) {
		il << RANDI();
	}
	return il;
}
QList<quint8> Globals::seqRandui( int count, quint8 minVal, quint8 maxVal, int seed) {
	Q_UNUSED(minVal);Q_UNUSED(maxVal);Q_UNUSED(seed);

	QList<quint8> il;
	for (int k=0; k<count; k++) {
		il << RANDUI();
	}
	return il;
}
QStringList Globals::seqString(QString str, int count, int lBound, int step) {
	QStringList sl;
	for (int k=lBound; k<count; k+=step) {
		if (str.contains("%"))
			sl << str.arg(k);
		else
			sl << str;
	}
	return sl;
}
QList<QFont> Globals::seqFont(QFont font, int count, int lBound, int step) {
	QList<QFont> fl;
	for (int k=lBound; k<count; k+=step)
		fl << font;
	return fl;
}
QList<ItemStyle> Globals::seqItemStyle(ItemStyle s, int count, int lBound, int step) {
	QList<ItemStyle> bl;
	for (int k=lBound; k<count; k+=step) {
		bl << s;
	}
	return bl;
}
QList<QColor> Globals::seqColor(QColor color, int count, int lBound, int step) {
	QList<QColor> cl;
	for (int k=lBound; k<count; k+=step)
		cl << color;
	return cl;
}


