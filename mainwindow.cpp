#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "test.h"

#define X 350
#define Y 30

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    avl = new AVL;
    connect(ui->pushButton,&QPushButton::clicked,this,[this]{
        if(avl->isEmpty())
            avl->add(new Node(ui->lineEdit->text().toInt(),X,Y));
        else
            avl->add(new Node(ui->lineEdit->text().toInt()));

        update();
        ui->lineEdit->clear();
    });

#if TEST
    int s = 1000000;
    for(int i=0;i<100;i++)
        avlTest(s);
#endif
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::avlTest(int times)
{
    for (int i = 1; i <= times; i++) {
        avl->add(new Node(i));
    }
    for (int i = 1; i <= times; i++) {
        avl->remove(i);
    }
}

void MainWindow::paintEvent(QPaintEvent *)
{
#if DRAW
    QPainter painter(this);
    auto arr = avl->getArr();
    for(auto n=arr.begin();n!=arr.end();n++){
        painter.drawEllipse((*n)->x,(*n)->y,50,50);
        painter.drawText((*n)->x + 20,(*n)->y + 27,QString::number((*n)->data));
    }
#endif
}

