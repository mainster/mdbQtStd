#include "globalsui.h"

globalsUi::globalsUi() {  }

QList<QTableView *> globalsUi::castToQTableView(const QList<QWidget *> os) {
	QList<QTableView *> tvs = QList<QTableView *>();

	foreach (QWidget *o, os) {
		if (qobject_cast<QTableView *>(o))
			tvs << qobject_cast<QTableView *>(o);
	}

	return tvs;
}
