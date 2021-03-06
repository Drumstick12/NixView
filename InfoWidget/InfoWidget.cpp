#include "InfoWidget.hpp"
#include "ui_InfoWidget.h"
#include <sstream>
#include "common/Common.hpp"

InfoWidget::InfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InfoWidget)
{
    ui->setupUi(this);

    mp = new MetaDataPanel();
    ui->verticalLayout_page_meta->addWidget(mp);

    dp = new DescriptionPanel();
    ui->verticalLayout_page_meta->addWidget(dp);

    tp = new TagPanel();
    ui->verticalLayout_page_tag->addWidget(tp);

    connect_widgets();
}

void InfoWidget::update_info_widget(QVariant v)
{
    if(v.canConvert<nix::Tag>() || v.canConvert<nix::MultiTag>())
    {
        ui->verticalLayout_page_tag->addWidget(dp);
        ui->stackedWidget->setCurrentIndex(1);
    }
    else
    {
        ui->verticalLayout_page_meta->addWidget(dp);
        ui->stackedWidget->setCurrentIndex(0);
    }

    dp->update_description_panel(v);
    mp->update_metadata_panel(v);
    tp->update_tag_panel(v);
}

void InfoWidget::update_info_widget()
{
    dp->clear_description_panel();
    mp->clear_metadata_panel();
    tp->clear_tag_panel();
}

void InfoWidget::connect_widgets()
{
    QObject::connect(mp->get_tree_widget(), SIGNAL(expanded(QModelIndex)), mp, SLOT(resize_to_content(QModelIndex)));
    QObject::connect(mp->get_tree_widget(), SIGNAL(collapsed(QModelIndex)), mp, SLOT(resize_to_content(QModelIndex)));
    QObject::connect(tp->get_tag_table(), SIGNAL(currentCellChanged(int,int,int,int)), tp, SLOT(tag_item_requested(int, int, int, int)));

    QObject::connect(tp->get_reference_tree(), SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),
                     tp, SLOT(currentItemChanged_reference_helper(QTreeWidgetItem*,QTreeWidgetItem*)));
    QObject::connect(tp->get_feature_tree(), SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),
                     tp, SLOT(currentItemChanged_feature_helper(QTreeWidgetItem*,QTreeWidgetItem*)));
    QObject::connect(tp->get_tag_table(), SIGNAL(currentCellChanged(int,int,int,int)),
                     tp, SLOT(tag_item_requested(int,int,int,int)));
}

// getter
const MetaDataPanel* InfoWidget::get_metadata_panel()
{
    return mp;
}

InfoWidget::~InfoWidget()
{
    delete ui;
}


