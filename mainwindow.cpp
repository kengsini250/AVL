#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    //avl->add(new Node(10,X,Y));
    //avl->add(new Node(8));
//    avl->add(new Node(12));
    //avl->add(new Node(6));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    
    QPainter painter(this);
    auto arr = avl->getArr();
    for(auto n=arr.begin();n!=arr.end();n++){
        painter.drawEllipse((*n)->x,(*n)->y,50,50);
        painter.drawText((*n)->x + 20,(*n)->y + 27,QString::number((*n)->data));
    }
    
}

