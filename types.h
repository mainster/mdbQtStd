#ifndef TYPES_H
#define TYPES_H

#include <QWidget>
#include <QVariant>
#include <QMetaObject>
#include <QTypeInfo>
//#include <QtGui>
#include <QString>
#include <QObject>
#include <QMetaType>
//#include <QMainWindow>
#include <QItemSelection>
#include <QPen>
#include <QFont>
#include "debug.h"
#include "mdbQtStd.h"


namespace Qt {

enum ItemDataRoleCustom {
	BoarderRole = (Qt::UserRole << 1),
};
Q_ENUMS(ItemDataRoleCustom)

enum CompareFlag {
	CompNone,
	CompEqual,
	CompUnEqual,
};
Q_ENUMS(CompareFlag)

}

template<class T>
void resizeList(QList<T> & list, int newSize) {
	 int diff = newSize - list.size();
	 T t;
	 if (diff > 0) {
		  list.reserve(diff);
		  while (diff--) list.append(t);
	 } else if (diff < 0) list.erase(list.end() + diff, list.end());
}

template<class T>
QString listToString(QList<T> list, int fieldwidth = 1, int base = 10,
							QChar fillChar = '0', char joinSep = ' ', bool appendLength = true) {
	QStringList s;
	foreach (T t, list) {
		s << QString("%1").arg(t, fieldwidth, base, fillChar);
	}
	return (appendLength)
			? s.join(joinSep) + QString(" [length: %1]").arg(s.length())
			: s.join(joinSep);
}

template<class U, class T>
QList<U> listCast (QList<T> ts) {
	QList<U> us;
	foreach (T t, ts) {
		us << static_cast<U>(t);
	}
	return us;
}




/* ======================================================================== */
/*                            under construction                            */
/* ======================================================================== */
template<class T>
QList<QString> listObjectNames (QList<T> ts/*, const QString methodeName*/) {
	QList<QString> l;
	foreach (T t, ts)
		l << t->objectName();
	return l;
}

/* ======================================================================== */
/*										u_ID_t						                      */
/* ======================================================================== */
/*!
 * 31.05.2016:	Implementation
 * This struct contains a identifier member and a time stamp member. Together, the
 * typedef represents a real-uniq identifier. All non uID_t identifiers e.g.
 * QByteArray uid; are NOT absolut uniq due to the fact that the same id could hold
 * different fram data. In other words, id's fram data is time variant, uID_t fram
 * is time invariant ( or discret because of uID_t::tstamp )
 */
struct uID_t {
public:
	/*!
	 * Public constructors
	 */
	uID_t () :
		id(), tstamp(), rssi() { rssi = 7; }

	uID_t (QString id) :
		id(id), tstamp(), rssi() {	tstamp = QDateTime::currentDateTime(); }

	uID_t (QString id, QDateTime tstamp) :
		id(id), tstamp(tstamp) { }

	uID_t (QString id, QDateTime tstamp, quint8 rssi) :
		id(id), tstamp(tstamp), rssi(rssi) { }

	void setId (QString _id)			{	id = _id;		}
	void setTstamp (QDateTime _ts)	{	tstamp = _ts;	}
	void setRssi (quint8 _rssi)		{	rssi = _rssi;	}

	/*!
	 * \brief isValid methode validates the current uID_t instance
	 * \return
	 */
	bool isValid() const {
		if (id.length() && tstamp.isValid())
			return true;
		return false;
	}

	void clear() {
		id.clear();
		tstamp = QDateTime();
		rssi = 0;
	}

	/*!
	 * Member attributes
	 */
	QString		id;			//!< String which holds a non-unique identifier
	QDateTime	tstamp;		//!< QDateTime which holds a unique time stamp
	quint8		rssi;			//!< rssi integer value

	/**
	 * @brief operator == is used as compare operator between 2 uID_t instances. This
	 * operator doesn't compare the rssi value. To ensure uniqueness, comparing the two
	 * members uID_t::id's AND uID_t::tstamp's is sufficient.
	 * @param rhs
	 * @return
	 */
	bool operator==(const uID_t& rhs) const {
		return (rhs.id == this->id) && (rhs.tstamp == this->tstamp);
	}
};

/* ======================================================================== */
/*									 ItemStyle						                      */
/* ======================================================================== */
/*!
 * \brief The ItemStyle struct contains geometry and color information for cells
 * boarder customizations.
 */
class ItemStyle {

public:
	ItemStyle() {}
	ItemStyle(const ItemStyle &other) {
		mRange = other.mRange;
		mSelection = other.mSelection;
		mIndexList = other.mIndexList;
		mPen = other.mPen;
	}
	ItemStyle(const QItemSelectionRange range, QColor color,
				 qreal width = 1, Qt::PenStyle style = Qt::SolidLine) : mRange(range) {
		mPen = QPen(QBrush(color), width, style);
	}
	ItemStyle(const QItemSelection selection, QColor color,
				 qreal width = 1, Qt::PenStyle style = Qt::SolidLine) : mSelection(selection) {
		mPen = QPen(QBrush(color), width, style);
	}
	ItemStyle(const QModelIndexList indexList, QColor color,
				 qreal width = 1, Qt::PenStyle style = Qt::SolidLine) : mIndexList(indexList) {
		mPen = QPen(QBrush(color), width, style);
	}
	ItemStyle(const QModelIndex topLeft, const int count, QColor color,
				 qreal width = 1, Qt::PenStyle style = Qt::SolidLine) {
		mPen = QPen(QBrush(color), width, style);
		appendIndexRng(topLeft, count);
	}
	ItemStyle(QList<int> addrRng, QColor color,
				 qreal width = 1, Qt::PenStyle style = Qt::SolidLine) : mAddrRng(addrRng)  {
		color.setAlphaF(.1);
		mPen = QPen(QBrush(color), width, style);
	}
	~ItemStyle() {}

	QPen pen() const { return mPen; }
	void setPen(const QPen &pen) { mPen = pen; }

	QModelIndexList getIndexes() {
		if (mRange.isEmpty() && mSelection.isEmpty()
			 && mIndexList.isEmpty()) {
			return QModelIndexList();
		}

//		INFO << mRange.isEmpty() << mSelection.isEmpty() << mIndexList.isEmpty();

		if (! mRange.isEmpty())
			return mRange.indexes();

		if (! mSelection.isEmpty())
			return mSelection.indexes();

		if (! mIndexList.isEmpty())
			return mIndexList;

//		WARN << QString("%1(%2): This line should never be reached").arg(__FILE__).arg(__LINE__);
		return QModelIndexList();
	}
	void debug(int verbosLevel = -1) const;
	QList<int> getAddrRng() const {
		return mAddrRng;
	}
	void setAddrRng(const QList<int> &addrRng) {
		mAddrRng = addrRng;
	}
	void appendIndexRng(const QModelIndex mi, const int count) {
		int r = mi.row();
		int c = mi.column();
		for (int k = 0; k < count; k++) {
			if (! mi.sibling(r, c).isValid()) {
				c = 0; r++;
			}
			mIndexList << mi.sibling(r, c++);
		}
	}

private:
	QItemSelectionRange mRange;
	QItemSelection mSelection;
	QModelIndexList mIndexList;
	QPen mPen;
	QList<int>	mAddrRng;
};

Q_DECLARE_METATYPE(ItemStyle)

/* ======================================================================== */
/*									 ItemStyle						                      */
/* ======================================================================== */
/*!
 * \brief The Cell struct holds data sources for ONE single item or cell.
 */
class Item {

public:
	Item() {}
	~Item() {}
	Item(const Item &other) {
		m_fram = other.m_fram;
		m_font = other.m_font;
		m_bground = other.m_bground;
		m_boarder = other.m_boarder;
	}
	Item(quint8 fram, QFont font, ItemStyle bground, ItemStyle boarder) :
		m_fram(fram), m_font(font), m_bground(bground), m_boarder(boarder) {}

	QFont font() const { return m_font; }
	void setFont(const QFont &font) { m_font = font; }
	quint8 fram() const { return m_fram; }
	void setFram(const quint8 &fram) { m_fram = fram; }
	ItemStyle style(const int &role = Qt::BackgroundRole) const {
		if ((role != Qt::BackgroundRole) && (role != Qt::BackgroundColorRole) &&
			 (role != Qt::BoarderRole))	return ItemStyle();

		switch (role) {
			case Qt::BackgroundColorRole: {
				return m_bground;
			}; break;

			case Qt::BoarderRole: {
				return m_boarder;
			}; break;

			default:
				return ItemStyle();
		}
	}
	bool setStyle(const ItemStyle &itm, int role = Qt::BackgroundRole) {
		if ((role != Qt::BackgroundRole) && (role != Qt::BackgroundColorRole) &&
			 (role != Qt::BoarderRole))	return false;

		switch (role) {
			case Qt::BackgroundRole: {
				m_bground = itm;
			}; break;

			case Qt::BoarderRole: {
				m_boarder = itm;
			}; break;

			default:
				return false;
		}
		return true;
	}

	QVariant getRoleData(const int &role) const {
		switch (role) {
			case Qt::DisplayRole:		/*break;*/
			case Qt::EditRole:			return quint8(m_fram); break;
			case Qt::FontRole:			return QFont(m_font); break;
			case Qt::BackgroundRole:	return QColor(m_bground.pen().color()); break;
			case Qt::BoarderRole:		return QVariant::fromValue(m_boarder); break;
			default:							return QVariant();
		}
	}
	// Protected Item:: member attributes

protected:
	quint8		m_fram;
	QFont			m_font;
	ItemStyle	m_bground;
	ItemStyle	m_boarder;
};

Q_DECLARE_METATYPE(Item)

#endif



