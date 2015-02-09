#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QColor>
#include <QDebug>
#include <QLineEdit>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new Scene(this);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    ui->lineEdit->setText("0");
    ui->lineEdit_2->setText("0");
    ui->lineEdit_3->setText("100");
    ui->lineEdit_4->setText("10");

    item = new GeomItem(ui->lineEdit->text().toFloat(), ui->lineEdit_2->text().toFloat());
    scene->addItem(item);

    ui->comboBox->insertItems(0, QColor::colorNames());
    ui->comboBox->setCurrentIndex(80);

    scene->changeParams(ui->lineEdit_3->text().toFloat(), ui->lineEdit_4->text().toFloat(),
                        QColor(ui->comboBox->itemText(ui->comboBox->currentIndex())));
}

MainWindow::~MainWindow()
{
    delete item;
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    item->changePosition(ui->lineEdit->text().toFloat(), ui->lineEdit_2->text().toFloat());

    scene->changeParams(ui->lineEdit_3->text().toFloat(), ui->lineEdit_4->text().toFloat(),
                        QColor(ui->comboBox->itemText(ui->comboBox->currentIndex())) );

}

void MainWindow::mySlot(const QString &arg)
{
    qDebug() << arg;
}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    scene->changeParams(scene->getRadius(), scene->getNumberOfLines(),
                        QColor(arg1));
}
