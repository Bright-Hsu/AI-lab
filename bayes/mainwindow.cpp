#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<iostream>

using namespace std;

double p0=0;
double p1=1;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    lineSeries = new QLineSeries();
    chartView = new QChartView(this);
    lineSeries->setPointLabelsVisible(true);   //显示点坐标
    lineSeries->setName("P(E/S)——P(H/S)曲线");
    lineSeries->setPointsVisible();  //突出显示转折点
    lineSeries->setPointLabelsFormat("(@xPoint, @yPoint)");
    mChart = new QChart();
    mChart->addSeries(lineSeries);  //向折线图中添加此系列
    lineSeries->append(0,0);
    lineSeries->append(0.5,0.5);
    lineSeries->append(1,1);
    mChart->createDefaultAxes();    //创建默认坐标
    mChart->setTitle("默认图像");   //设置图表标题
    chartView->setChart(mChart);    //向chartview添加图表
    chartView->resize(QSize(500,400));   //重新设置大小
    chartView->setRenderHints(QPainter::Antialiasing);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    double ph = ui->doubleSpinBox->value();
    //double pe = ui->doubleSpinBox_2->value();
    double ls = ui->doubleSpinBox_3->value();
    double ln = ui->doubleSpinBox_4->value();
    p1 = ls * ph / ((ls - 1) * ph + 1);
    p0 = ln * ph / ((ln - 1) * ph + 1);

    qDebug()<<"正在刷新折线图";
    lineSeries->replace(0,0,p0);
    lineSeries->replace(1,ui->doubleSpinBox_2->value(),ui->doubleSpinBox->value());
    lineSeries->replace(2,1,p1);
    mChart->setTitle("当前输入对应的分段线性插值");
    qDebug()<<"刷新完成";

    return;
}


void MainWindow::on_pushButton_2_clicked()
{
    double ph = ui->doubleSpinBox->value();
    double pe = ui->doubleSpinBox_2->value();
    double ls = ui->doubleSpinBox_3->value();
    double ln = ui->doubleSpinBox_4->value();
    p1 = ls * ph / ((ls - 1) * ph + 1);
    p0 = ln * ph / ((ln - 1) * ph + 1);
    double pes = ui->doubleSpinBox_5->value();
    double phs = 0;
    if(0<=pes && pes<=pe){
        phs = p0 + pes * (ph - p0) / pe;
    }
    else{
        phs = p1 + (pes - 1) * (p1 - ph) / (1 - pe);
    }

    ui->doubleSpinBox_6->setValue(phs);
}

