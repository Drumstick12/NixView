#ifndef MAINVIEWWIDGET_HPP
#define MAINVIEWWIDGET_HPP

#include <QWidget>
#include <nix.hpp>
#include <QtGui>
#include <RawTreeView.hpp>
#include <InfoWidget.hpp>
#include <boost/optional.hpp>

namespace Ui {
class MainViewWidget;
}

class MainViewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainViewWidget(std::string& nix_file_path, QWidget *parent = 0);
    ~MainViewWidget();

public slots:
    void data_combo_box_changed(int);
    void activate_info_widget();
    void item_info_requested(QTreeWidgetItem*, int);

signals:
    void item_info_found(std::string, std::string, std::string, boost::optional<std::basic_string<char>>);

private:
    Ui::MainViewWidget *ui;
    nix::File nix_file;

    RawTreeView* rtv;
    InfoWidget* iw;

    void populate_data_stacked_widget();

    void connect_widgets();
};

#endif // MAINVIEWWIDGET_HPP
