#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qpushbutton.h>
#include "gamemanager.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
// Only supporting 1024x1024 images, formats: .png, /jpg
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void setManager(GameManager &manager);
    ~MainWindow();

private slots:
    void on_pB_start_clicked();

    void on_pB_restart_clicked();

    void on_sB_numberOfCells_valueChanged(int arg1);

    void on_comboBox_currentIndexChanged(int index);

    void handleButtonClick();

private:
    Ui::MainWindow *ui;
    GameManager* mManager;
    std::vector<std::vector<QPushButton*>> boardButtons;

    void createGridLayout(int n);
    void delete_board_layout();
};
#endif // MAINWINDOW_H
