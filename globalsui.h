#ifndef GLOBALSUI_H
#define GLOBALSUI_H

#include <QWidget>
#include <QtCore>
#include <QVariant>
#include <QTypeInfo>
#include <QtGlobal>
//#include <QTime>
#include <QtGui>
//#include <QtCore/QtGlobal>
//#include <QString>
//#include <QSplitter>
//#include <QSettings>
//#include <QRect>
//#include <QProcess>
#include <QObject>
#include <QMetaType>
//#include <QMainWindow>
//#include <QFont>
#include <QDebug>
//#include <QComboBox>
//#include <QModelIndexList>
#include <QTableView>

class globalsUi
{
public:
	globalsUi();
	void castToQTableView2(const QList<QObject *>& QObjects, QList<QTableView *>& tvs);
	static QStringList widToStrLst(QWidgetList &lst);
	static QString widToStr(QWidgetList &lst, QString sep = ",");
	QList<QTableView *> castToQTableView(const QList<QWidget *> os);

private:
	static QStringList strLst;

};

#endif // GLOBALSUI_H
