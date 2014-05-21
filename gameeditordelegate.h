#ifndef GAMEEDITORDELEGATE_H
#define GAMEEDITORDELEGATE_H

#include <QStyledItemDelegate>
#include "game.h"
class GameEditorDelegate : public QStyledItemDelegate
{
public:
    GameEditorDelegate(QMap<QString,Game*>& l);

    virtual QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index	) const;
    void setEditorData(QWidget *editor	, const QModelIndex &index);
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
private:
    QMap<QString,Game*> m_list;

};

#endif // GAMEEDITORDELEGATE_H
