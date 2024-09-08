#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qpushbutton.h>
#include "board.h"
#include "engine.h"
#include "gamemanager.h"
#include "imageprocessor.h"


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
    ~MainWindow();

private slots:
    void on_pB_start_clicked();

    void on_pB_restart_clicked();

    void on_sB_numberOfCells_valueChanged(int arg1);

    void on_comboBox_currentIndexChanged(int index);

    void handleButtonClick();

    void on_savePB_clicked();

    void on_loadPB_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_undo_clicked();

    void on_shuffleCB_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    GameManager* mManager;
    std::vector<std::vector<QPushButton*>> boardButtons;
    Board* board;
    Engine *engine;
    Images currentImage;
    void createGridLayout(int n);
    void delete_board_layout();
    int shuffleAlgorithm;
};
#endif // MAINWINDOW_H
