#ifndef LEVELDELEGATEITEM_H
#define LEVELDELEGATEITEM_H

#include <QStyledItemDelegate>
#include <QComboBox>

class LevelDelegateItem : public QStyledItemDelegate
{
public:
    LevelDelegateItem();

    virtual QWidget *	createEditor ( QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
    virtual void	setEditorData ( QWidget * editor, const QModelIndex & index ) const;
    virtual void	setModelData ( QWidget * editor, QAbstractItemModel * model, const QModelIndex & index ) const;
    virtual QSize	sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const;
    virtual void	updateEditorGeometry ( QWidget * editor, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
private:
    QStringList m_data;
};

#endif // LEVELDELEGATEITEM_H
