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

    int judga_line(int ln, int XS, int YS, int dx, int dy);
    int judga(int ln);

    void clearBoard();
    void NoEnableBoard();
private:
    Ui::MainWindow *ui;
    QList <QPushButton *> btnList;
    int Board[15][15];

public slots:
    void btnClick();

private slots:
    void on_action_triggered();
};

#endif // MAINWINDOW_H
