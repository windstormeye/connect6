#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QList <QPushButton *> btnList;
    int Board[15][15];

public slots:
    void btnClick();

private slots:
    void on_action_triggered();
    void on_actionPVP_triggered();
    void on_actionPVE_triggered();
};

#endif // MAINWINDOW_H
