#ifndef MP_CHANNEL_SOURCE_SORT_FILTER_PROXY_SOURCE_H
#define MP_CHANNEL_SOURCE_SORT_FILTER_PROXY_SOURCE_H

#include <QSortFilterProxyModel>

namespace mp {
namespace model {

class RadioSourcesSortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:

	enum SortT
	{
		ByName,
		ByTop,
		ByLastPlayTime
	};

    RadioSourcesSortFilterProxyModel(QObject *parent = 0);

	int CategoryIdFilter() const;
	void SetCategoryIdFilter(int categoryId);

	const QString& NameFilter() const;
	void SetNameFilter(const QString& nameFilter);

	SortT SortType() const;
	void SetSortType(SortT sortBy);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const;

public:
	friend QAbstractListModel;
	Q_DISABLE_COPY(RadioSourcesSortFilterProxyModel)

private:
	int				m_categoryIdFilter;
	QString			m_nameFilter;
	SortT			m_sortBy;
};

} //namespace model
} //namespace mp

#ifdef BUILD_WITH_METATYPES
Q_DECLARE_METATYPE(mp::model::RadioSourcesSortFilterProxyModel);
#endif

#endif