#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QMessageBox>

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
        if (judga(15)) {
            // QMessageBox点击按钮后右响应的
            int nRet = QMessageBox::question(NULL, "提示", "白子获胜，是否重新开始", QMessageBox::Yes, QMessageBox::No);
            // 选择是
            if (QMessageBox::Yes == nRet) {
                clearBoard();
            }
            // 选择否
            if (QMessageBox::No == nRet) {
                NoEnableBoard();
            }
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
        if (judga(15)) {
            // QMessageBox点击按钮后右响应的
            int nRet = QMessageBox::question(NULL, "提示", "白子获胜，是否重新开始", QMessageBox::Yes, QMessageBox::No);
            // 选择是
            if (QMessageBox::Yes == nRet) {
                clearBoard();
            }
            // 选择否
            if (QMessageBox::No == nRet) {
                NoEnableBoard();
            }
        }
    }

//    for (int i = 0; i < 15; i++) {
//        for (int j = 0; j < 15; j++) {
//            std::cout <<  Board[i][j];
//        }
//        std::cout << std::endl;
//    }
//    std::cout << "=================" << std::endl;
}

// 棋盘不可点击
void MainWindow::NoEnableBoard() {
    for (int i = 0; i < 15; i ++) {
        for (int j = 0; j < 15; j ++) {
            QPushButton *btn = (QPushButton *)btnList[j+i*15];
            btn->setEnabled(false);
        }
    }
}

// 清空棋盘
void MainWindow::clearBoard() {
    for (int i = 0; i < 15; i ++) {
        for (int j = 0; j < 15; j ++) {
            Board[i][j] = 0;
            QPushButton *btn = (QPushButton *)btnList[j+i*15];
            btn->setStyleSheet("border-image: url(:/new/prefix1/000.png);");
            btn->setEnabled(true);
        }
    }
}

// 菜单栏——操作——清空
void MainWindow::on_action_triggered()
{
   clearBoard();
}

// 判赢
// ln:棋盘大小  XS:起始x坐标  YS：起始y坐标  dx：在x方向上的增量  dy：在y方向上的增量
int MainWindow::judga_line(int ln, int XS, int YS, int dx, int dy) {
      if((XS <ln) && (YS<ln)  //起点坐标在棋盘内
        && (XS >=0) && (YS >=0)
        && (dx != 0 || dy != 0))        //坐标增量不为同时0
      {
        if (((XS + dx * 5) > ln) || ((XS + dx * 5)<0) || //判断终点坐标
          ((YS + dy * 5)>ln) || ((YS + dy * 5) < 0) || //在棋盘外
          (0 == Board[XS][YS]))
        {
            return 0;  //不在棋盘内，或者起点是没下子
        }
        else
        {
          int i = 0;
          for (i = 1; i < 6; ++i){
            if (Board[XS][YS] != Board[XS + (dx * i)][YS + (dy * i)])
            {
              return 0;  //如果不是连续5个一样的
            }
          }
          return 1;  //五个都一样，且都在棋盘内
        }
      }
      return 0;  //其他情况
}

// 判断是否形成六子连珠
int MainWindow::judga(int ln) {
    int i = 0, j = 0;
      //纵向成六子连线判断
      for (i = 0; i<(ln - 5); ++i){
        for (j = 0; j<ln; ++j){
          if (judga_line(ln, i, j, 1, 0)){
            return 1;
          }
        }
      }

        //横向成六子连线判断
      for (i = 0; i<ln; ++i){
        for (j = 0; j<(ln - 5); ++j){
          if (judga_line(ln, i, j, 0, 1)){
            return 1;
          }
        }
      }

        //左上到右下成六子连线判断
      for (i = 0; i<(ln - 5); ++i){
        for (j = 0; j<(ln - 5); ++j){
          if (judga_line(ln, i, j, 1, 1)){
            return 1;
          }
        }
      }

        //左下到右上成六子连线判断
      for (i = ln-1; i>(ln - 5); --i){
        for (j = 0; j <(ln - 5); ++j){
          if (judga_line(ln, i, j, -1, 1)){
            return 1;
          }
        }
      }

      return 0;  //没能赢
}

