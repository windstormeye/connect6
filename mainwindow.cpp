#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

// 记录当前下子方
static bool isBlack;
// 记录下子次数
static int times;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*
     * 一些界面的初始化工作
     */
    this->setWindowTitle("六子棋");
    isBlack = true;

    /*
     * 棋盘的初始化
     */
    // 创建棋盘
    int btnX = 0;
    int btnY = 0;
    int btnW = 30;
    int btnH = 30;
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            Board[i][j] = 0;
            QPushButton *btn = new QPushButton(this);
            btnList.push_back(btn);
            btnX = j * 30;
            btnY = i * 30;
            btn->setGeometry(btnX, btnY, btnW, btnH);
            btn->setStyleSheet("border-image: url(:/new/prefix1/000.png);");
            connect(btn, SIGNAL(clicked(bool)), this, SLOT(btnClick()));
        }
    }
    // 设置窗体初始化大小
    this->resize(QSize(btnX + 30, btnY + 30));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::btnClick() {
    // 拿到触发当前槽函数的信号源对象
    QPushButton *btn = qobject_cast<QPushButton*>(sender());

    int x = btn->pos().x() / 30;
    int y = btn->pos().y() / 30;
    if (isBlack) {
        btn->setStyleSheet("border-image: url(:/new/prefix1/111.png);");
        btn->setEnabled(false);
        Board[y][x] = 1;

        times++;
        if (times == 2) {
            isBlack = false;
            times = 0;
        }
    } else {
        btn->setStyleSheet("border-image: url(:/new/prefix1/222.png);");
        btn->setEnabled(false);
        Board[y][x] = -1;
            times++;
        if (times == 2) {
            isBlack = true;
            times = 0;
        }
    }

    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            std::cout <<  Board[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << "=================" << std::endl;
}

void MainWindow::on_action_triggered()
{
    for (int i = 0; i < 15; i ++) {
        for (int j = 0; j < 15; j ++) {
            Board[i][j] = 0;
            QPushButton *btn = (QPushButton *)btnList[j+i*15];
            btn->setStyleSheet("border-image: url(:/new/prefix1/000.png);");
        }
    }
}

void MainWindow::on_actionPVP_triggered()
{
    qDebug("######");
}

void MainWindow::on_actionPVE_triggered()
{
    qDebug("%%%%%%");
}
