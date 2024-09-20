#ifndef TEXTWRAPDELEGATE_H
#define TEXTWRAPDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>

class TextWrapDelegate : public QStyledItemDelegate {
    Q_OBJECT
  public:
    TextWrapDelegate(QObject* parent = nullptr);

  //   // QAbstractItemDelegate interface
  // public:
  //   virtual QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option,
  //                                 const QModelIndex& index) const override;
  //   virtual void setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const override;

    // QAbstractItemDelegate interface
public:
    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    // QAbstractItemDelegate interface
public:
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif  // TEXTWRAPDELEGATE_H
