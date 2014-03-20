#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap butPixmap(":/img/button");
    QIcon butIcon(butPixmap);
    ui->pushButton_2->setIcon(butIcon);
    qApp->setStyleSheet("#pushButton_2{border:5px;}");

    this->setWindowFlags(Qt::FramelessWindowHint);
    if(!QDir("pics").exists()) QDir().mkdir("pics");

}

MainWindow::~MainWindow()
{
    delete ui;
}


QPixmap MainWindow::makeImg(QString inText){
    QPixmap pixmap(300,150);
    pixmap.fill(Qt::blue);

    QPainter painter(&pixmap);
    painter.setPen(Qt::green);
    painter.setFont(QFont("Arial",45));
    painter.drawText(15,90,inText);
    //ui->label->setPixmap(pixmap);

    return pixmap;
}

QPixmap MainWindow::distortImg(QPixmap pixmap)
{
    QImage pixmapImg = pixmap.toImage();
    QPixmap pixmap2(pixmap.width(),pixmap.height());
    QPainter painter2(&pixmap2);

    // Distort text
    for(int x = 0; x < pixmap.width(); x++){
        for(int y = 0; y < pixmap.height(); y++){
            qsrand(x);
            float rand1 = qrand()%5;
            qsrand(y);
            float rand2 = qrand()%5;
            float sinx = sin(x/10+1)*5;
            float siny = qSin(y/10)*5;
            int newx = x+rand1+sinx;
            int newy = y+rand2+siny;
            if(newx < pixmap.width() && newy < pixmap.height()){
                if(rand1+rand2 > 1) {
                    painter2.setPen(pixmapImg.pixel(newx,newy));
                } else {
                    painter2.setPen(Qt::green);
                    painter2.drawRect(x,y,10,10);
                }
                painter2.drawRect(x,y,1,1);

            }
        }
    }

    ui->label->setPixmap(pixmap2);

    return pixmap2;

}





void MainWindow::on_pushButton_clicked()
{
    QString inText = ui->lineEdit->text();
    QFile newpic("pics/"+inText+".png");
    newpic.open(QIODevice::WriteOnly);
    qDebug() << "pics/"+inText+".png";
    distortImg(makeImg(inText)).save(&newpic,"PNG");

}

void MainWindow::on_pushButton_2_clicked()
{
    qApp->exit();
}
