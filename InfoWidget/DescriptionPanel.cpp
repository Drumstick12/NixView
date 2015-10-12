#include "DescriptionPanel.hpp"
#include "ui_DescriptionPanel.h"
#include <common/Common.hpp>

DescriptionPanel::DescriptionPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DescriptionPanel)
{
    ui->setupUi(this);
}

void DescriptionPanel::update_description_panel(QVariant v)
{
    if(v.canConvert<nix::Block>())
        update(v.value<nix::Block>());
    else if(v.canConvert<nix::DataArray>())
        update(v.value<nix::DataArray>());
    else if(v.canConvert<nix::MultiTag>())
        update(v.value<nix::MultiTag>());
    else if(v.canConvert<nix::Tag>())
        update(v.value<nix::Tag>());
    else if(v.canConvert<nix::Section>())
        update(v.value<nix::Section>());
    // TODO look for better solution
    else if(v.canConvert<nix::Property>())
        update_typeless(v.value<nix::Property>());
}

template<typename T>
void DescriptionPanel::update(T arg)
{
    std::stringstream ss;
    ss << "id: " << arg.id() << "\n"
       << "type: " << arg.type() << "\n"
       << "name: " << arg.name() << "\n"
       << "description: ";
    if (arg.definition().is_initialized())
        ss << arg.definition().get();
    else
        ss << "-";
    QString info_string = QString::fromStdString(ss.str());
    ui->info_text_edit->setText(info_string);
}

template<typename T>
void DescriptionPanel::update_typeless(T arg)
{
    std::stringstream ss;
    ss << "id: " << arg.id() << "\n"
       << "name: " << arg.name() << "\n"
       << "description: ";
    if (arg.definition().is_initialized())
        ss << arg.definition().get();
    else
        ss << "-";
    QString info_string = QString::fromStdString(ss.str());
    ui->info_text_edit->setText(info_string);
}

void DescriptionPanel::clear_description_panel()
{
    ui->info_text_edit->setText("");
}


DescriptionPanel::~DescriptionPanel()
{
    delete ui;
}