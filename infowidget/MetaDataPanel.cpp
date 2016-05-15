#include "MetaDataPanel.hpp"
#include "ui_MetaDataPanel.h"
#include "common/Common.hpp"
#include "model/nixtreemodelitem.h"
#include "model/nixmetadatatreemodel.h"
#include <ostream>

MetaDataPanel::MetaDataPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MetaDataPanel)
{
    ui->setupUi(this);
}


void MetaDataPanel::setDataModel(NixTreeModel *_nix_model) {
    proxy_model = new NixProxyModel(this);
    proxy_model->setSourceModel(_nix_model);
    ui->treeView->setModel(proxy_model);
    std::vector<int> hidden_columns = {2,3,4,5,6,7,10};
    for (int c : hidden_columns)
        ui->treeView->setColumnHidden(c, true);
    set_proxy_model();
}


void MetaDataPanel::set_proxy_model() {
    clear_metadata_panel();
    proxy_model->set_filter_mode(3);
    proxy_model->set_metadata_only_mode(true);
}


void MetaDataPanel::update_metadata_panel(QModelIndex qml) {
    if (qml.isValid()) {
        NixTreeModelItem *item = static_cast<NixTreeModelItem*>(qml.internalPointer());
        if (item->nixType() == NixType::NIX_SECTION) {
            nix::Section metadata = item->itemData().value<nix::Section>();
            NixMetadataTreeModel *model = new NixMetadataTreeModel();
            if (metadata) {
                model->setEntity(metadata);
            }
            ui->treeView->setModel(model);
        }
    }
    else
        clear_metadata_panel();
}


void MetaDataPanel::clear_metadata_panel() {
    proxy_model->set_block_mode(true);
    proxy_model->refresh();
}


void MetaDataPanel::resize_to_content(QModelIndex) {
    for (int c = 0; c < ui->treeView->model()->columnCount();c++)
        ui->treeView->resizeColumnToContents(c);
}

//getter
const QTreeView* MetaDataPanel::get_tree_view() {
    return ui->treeView;
}


MetaDataPanel::~MetaDataPanel() {
    delete ui;
}
