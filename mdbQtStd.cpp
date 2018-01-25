//#include <QtGui>
//#include <QWidget>
#include <QtCore>
#include <QObject>
#include <QVariant>
#include <QTypeInfo>
#include <QString>
#include <QMetaType>
//#include <QMainWindow>

#include "mdbQtStd.h"
#include "types.h"

QString MdbQtStd::ddgbStyleShtA = "QGroupBox {"
		"background-color: qlineargradient("
		"x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #E0E0E0, stop: 1 #FFFFFF);"
		"border: 2px solid gray; border-radius: 5px;"
		"margin-top: 4ex;"          /* leave space at the top for the title */
		"}"

		"QGroupBox::title {"
		"subcontrol-origin: margin;"
		"subcontrol-position: top center; "  /* position at the top center */
		"padding: 0 3px;"
		"background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
		"stop: 0 #FFOECE, stop: 1 #FFFFFF);}";

QString MdbQtStd::ddgbCheckableStyleSht =
		" QGroupBox::indicator {"
		"    width: 13px;"
		"    height: 13px;"
		"}"
		"QGroupBox::indicator:unchecked {"
		"    image: url(://iconClose.png);"
		"}"
		"QGroupBox {"
		"background-color: qlineargradient("
		"x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #E0E0E0, stop: 1 #FFFFFF);"
		"border: 2px solid gray; border-radius: 5px;"
		"margin-top: 4ex;"          /* leave space at the top for the title */
		"}"

		"QGroupBox::title {"
		"subcontrol-origin: margin;"
		"subcontrol-position: top center; "  /* position at the top center */
		"padding: 0 3px;"
		"background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
		"stop: 0 #FFOECE, stop: 1 #FFFFFF);}";

QString MdbQtStd::ddgbStyleShtInpFrm =
		" QGroupBox {"
		"   background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
		"   stop: 0 #E0E0E0, stop: 1 #FFFFFF);"
		"   border: 2px solid red;"
		"   border-radius: 5px;"
		"   margin-top: 3ex; /* leave space at the top for the title */"
		" }"
		""
		" QGroupBox::title {"
		"   subcontrol-origin: boarder; /* margin boarder padding content */"
		"   subcontrol-position: top center; /* position at the top center */"
		"   padding: 0 3px"
		" }";

QString MdbQtStd::ddtvStyleShtA =
		" QTableView{"
		"  background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #E0E0E0, stop: 1 #FFFFFF);"
		"  border: 0px solid gray;"
		"  border-radius: 5px;"
		"  margin-top: 10px; /* leave space at the top for the title */"
		"}";

QString MdbQtStd::ddgbStyleShtCenterHead =
	  " QGroupBox {"
	  "      background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #E0E0E0, stop: 1 #FFFFFF);"
	  "      border: 2px solid gray;"
	  "      border-radius: 5px;"
	  "   margin-top: 1ex; /* leave space at the top for the title */"
	  "      font: italic 9pt \"Arial\";"
	  "   font-weight: bold;"
	  "   color: black;"
	  " }"
	  ""
	  " QGroupBox::title {"
	  "   subcontrol-origin: margin; /* margin boarder padding content */"
	  "   subcontrol-position: top center; /* position at the top center */"
	  "   top: 3px;   "
	  "   padding: 0px 6px"
	  " }";

QString MdbQtStd::gbStyleShtCenterPROPERTYS =
		"QGroupBox#tva[selected=false] { border: 2px solid gray;  }"
		"QGroupBox#tva[selected=true] { border: 1px dashed rgb(55, 55, 55);   }"
		""
		"QGroupBox#tvb[selected=false] { border: 2px solid gray;  }"
		"QGroupBox#tvb[selected=true] { border: 1px dashed rgb(55, 55, 55);   }"
		""
		"QGroupBox#tvc[selected=false] { border: 2px solid gray;  }"
		"QGroupBox#tvc[selected=true] { border: 1px dashed rgb(55, 55, 55);   }"
		""
		"QGroupBox#tvl1[selected=false] { border: 2px solid gray;  }"
		"QGroupBox#tvl1[selected=true] { border: 1px dashed rgb(55, 55, 55);   }"
		""
		" QGroupBox {"
		"   background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #E0E0E0, stop: 1 #FFFFFF);"
		"   border-radius: 5px;"
		"   margin-top: 1ex; /* leave space at the top for the title */"
		"   font: italic 9pt \"Arial\";"
		"   font-weight: bold;"
		"   color: black;"
		"}"
		""
		"QGroupBox::title {"
		"   subcontrol-origin: margin; /* margin boarder padding content */"
		"   subcontrol-position: top center; /* position at the top center */"
		"   top: 3px;   "
		"   padding: 0px 6px"
		"} ";

QStringList MdbQtStd::strLst = QStringList();

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

QByteArray	MdbQtStd::htmlNotify = "<font color=\"Lime\">@</font><br>";
QFont			MdbQtStd::fontStat	= QFont();
QString		MdbQtStd::defaultFontString = "Monospace,9,-1,5,50,0,0,0,0,0";

bool MdbQtStd::storeFont(const QByteArray objName, const QFont &font) {
	QSETTINGS;
	config.setValue(objName + "/lastFont", font.toString());
	return true;
}
bool MdbQtStd::storeFont(const QString objName, const QFont &font) {
	QSETTINGS;
	config.setValue(objName + "/lastFont", font.toString());
	return true;
}
QFont MdbQtStd::restoreFont(const QString objName, bool *ok) {
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
QList<quint8> MdbQtStd::seqUInt(quint8 i, int count, int lBound, int step) {
	QList<quint8> il;
	for (int k=lBound; k<count; k+=step) {
		il << i;
	}
	return il;
}
QStringList MdbQtStd::objToStrLst(QObjectList &lst) {

	strLst.clear();
	foreach (QObject *o, lst) {
		strLst << o->objectName();
	}
	return strLst;
}
QString MdbQtStd::objToStr(QObjectList &lst, QString sep) {

	strLst.clear();
	foreach (QObject *o, lst) {
		strLst << o->objectName();
	}
	return strLst.join(sep);
}
QList<int> MdbQtStd::seqInt(int i, int count, int lBound, int step) {
	QList<int> il;
	for (int k=lBound; k<count; k+=step) {
		il << i;
	}
	return il;
}
QList<int> MdbQtStd::seqRandi( int count, int minVal, int maxVal, int seed) {
	Q_UNUSED(minVal);Q_UNUSED(maxVal);Q_UNUSED(seed);

	QList<int> il;
	for (int k=0; k<count; k++) {
		il << RANDI();
	}
	return il;
}
QList<quint8> MdbQtStd::seqRandui( int count, quint8 minVal, quint8 maxVal, int seed) {
	Q_UNUSED(minVal);Q_UNUSED(maxVal);Q_UNUSED(seed);

	QList<quint8> il;
	for (int k=0; k<count; k++) {
		il << RANDUI();
	}
	return il;
}
QStringList MdbQtStd::seqString(QString str, int count, int lBound, int step) {
	QStringList sl;
	for (int k=lBound; k<count; k+=step) {
		if (str.contains("%"))
			sl << str.arg(k);
		else
			sl << str;
	}
	return sl;
}
QList<QFont> MdbQtStd::seqFont(QFont font, int count, int lBound, int step) {
	QList<QFont> fl;
	for (int k=lBound; k<count; k+=step)
		fl << font;
	return fl;
}
QList<ItemStyle> MdbQtStd::seqItemStyle(ItemStyle s, int count, int lBound, int step) {
	QList<ItemStyle> bl;
	for (int k=lBound; k<count; k+=step) {
		bl << s;
	}
	return bl;
}
QList<QColor> MdbQtStd::seqColor(QColor color, int count, int lBound, int step) {
	QList<QColor> cl;
	for (int k=lBound; k<count; k+=step)
		cl << color;
	return cl;
}


