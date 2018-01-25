#include "globalsui.h"

QStringList globalsUi::strLst = QStringList();

globalsUi::globalsUi() {  }

QList<QTableView *> globalsUi::castToQTableView(const QList<QWidget *> os) {
	QList<QTableView *> tvs = QList<QTableView *>();

	foreach (QWidget *o, os) {
		if (qobject_cast<QTableView *>(o))
			tvs << qobject_cast<QTableView *>(o);
	}

	return tvs;
}

QStringList globalsUi::widToStrLst(QWidgetList &lst) {

	strLst.clear();
	foreach (QWidget *w, lst) {
		strLst << w->objectName();
	}
	return strLst;
}

QString globalsUi::widToStr(QWidgetList &lst, QString sep) {

	strLst.clear();
	foreach (QWidget *w, lst) {
		strLst << w->objectName();
	}
	return strLst.join(sep);
}
