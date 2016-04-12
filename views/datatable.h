#ifndef DATATABLE_H
#define DATATABLE_H

#include <QWidget>
#include <QModelIndex>
#include <nix.hpp>
#include "model/NixModelItem.hpp"
#include <QStandardItemModel>
#include <QStringList>

namespace Ui {
class DataTable;
}

class DataTable : public QWidget
{
    Q_OBJECT

public:
    explicit DataTable(QWidget *parent = 0);
    ~DataTable();

    void set_entity(const QModelIndex qml);
    bool can_draw(const QModelIndex qml) const;

private:
    Ui::DataTable *ui;
    nix::DataArray array;
    QStandardItemModel *model;

    void build_model();
    QStringList axis_labels(const nix::DataArray &array, size_t dim) const;

};

#endif // DATATABLE_H