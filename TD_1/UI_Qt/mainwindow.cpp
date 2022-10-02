/***************************************************************
 * @Project:        missile_trajectory
 * @Copyright(C):   2022-2023, zhujunfan
 * @Author:         zhujunfan
 * @Email:          zhujf0801@163.com
 * @Version:        0.1.1
 * @Since:          2022-09-20
 ************************************************************/
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "setinitdata.h"
#include "setconstdata.h"
#include <QtCharts/QLineSeries>
#include <QtCharts/QChartView>
#include <QPen>
#include <QtDataVisualization/Q3DScatter>
#include <QDebug>
#include <QVector>
#include <math.h>
#include <unistd.h>
#include <stdio.h>
#include "data.h"
#include "RK4.h"
#include <fstream>

using namespace QtDataVisualization;
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(1080, 720);
    this->setWindowTitle(QString("弹道仿真"));

    ui->pushButton_3->setEnabled(false);
    ui->pushButton_4->setEnabled(false);
    ui->pushButton_5->setEnabled(false);
    ui->comboBox->setEnabled(false);

    SetInitData * initDataWindow = new SetInitData;
    SetConstData * constDataWindow = new SetConstData;

    connect(ui->action, &QAction::triggered, [=](){
        initDataWindow->show();
    });

    connect(ui->action_6, &QAction::triggered, [=](){
       constDataWindow->show();
    });

    connect(ui->action_3, &QAction::triggered, this, &MainWindow::close);  //开始界面退出按钮
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::close);

    connect(ui->comboBox, &QComboBox::currentTextChanged, [=](){
        int index = ui->comboBox->currentIndex();
        //qDebug() << index;

        QChart *chart = new QChart;
        QValueAxis* axisX = new QValueAxis;
        QValueAxis* axisY = new QValueAxis;
        QLineSeries *series = new QLineSeries;
        QPen * pen_1 = new QPen;

        switch (index) {
        case 0:
            chart->setTitle("导弹x-time坐标图"); //设置标题

            ui->graphicsView->setChart(chart);  //将QChart对象设置到QChartView图表上

            //设置坐标轴
            axisX->setTitleText("time(s)"); //设置标题
            //axisX->setRange(1960, 2020); //设置范围
            axisX->setTickCount(7);      //设置主刻度个数
            axisX->setLineVisible(true); //设置轴线和刻度线可见性
            axisX->setGridLineVisible(true); //设置网格线可见性

            axisY->setTitleText("x(m)"); //设置标题
            //axisY->setRange(0, 20);       //设置范围
            axisY->setTickCount(21);      //设置主刻度个数
            axisY->setLineVisible(true); //设置轴线和刻度线可见性
            axisY->setGridLineVisible(true); //设置网格线可见性

            //设置序列1
            //series->setName("中国");    //设置序列名
            //series->setColor(QColor(255,0,0)); //设置序列颜色

            //添加数据点到序列
            for(int i = 0; i < time_MAX_0/time_INCRE_0; i++)
                series->append(i*time_INCRE_0, dataRecord_x[i]);

            pen_1->setWidth(3);
            series->setPen(* pen_1);

            //给Qchart添加序列
            chart->addSeries(series);

            //把序列设置到坐标轴
            chart->setAxisX(axisX, series);
            chart->setAxisY(axisY, series);
            break;
        case 1:
            chart->setTitle("导弹y-time坐标图"); //设置标题

            ui->graphicsView->setChart(chart);  //将QChart对象设置到QChartView图表上

            //设置坐标轴
            axisX->setTitleText("time(s)"); //设置标题
            //axisX->setRange(1960, 2020); //设置范围
            axisX->setTickCount(7);      //设置主刻度个数
            axisX->setLineVisible(true); //设置轴线和刻度线可见性
            axisX->setGridLineVisible(true); //设置网格线可见性

            axisY->setTitleText("y(m)"); //设置标题
            //axisY->setRange(0, 20);       //设置范围
            axisY->setTickCount(21);      //设置主刻度个数
            axisY->setLineVisible(true); //设置轴线和刻度线可见性
            axisY->setGridLineVisible(true); //设置网格线可见性

            //设置序列1
            //series->setName("中国");    //设置序列名
            //series->setColor(QColor(255,0,0)); //设置序列颜色

            //添加数据点到序列
            for(int i = 0; i < time_MAX_0/time_INCRE_0; i++)
                series->append(i*time_INCRE_0, dataRecord_y[i]);

            pen_1->setWidth(3);
            series->setPen(* pen_1);

            //给Qchart添加序列
            chart->addSeries(series);

            //把序列设置到坐标轴
            chart->setAxisX(axisX, series);
            chart->setAxisY(axisY, series);
            break;
        case 2:
            chart->setTitle("导弹z-time坐标图"); //设置标题

            ui->graphicsView->setChart(chart);  //将QChart对象设置到QChartView图表上

            //设置坐标轴
            axisX->setTitleText("time(s)"); //设置标题
            //axisX->setRange(1960, 2020); //设置范围
            axisX->setTickCount(7);      //设置主刻度个数
            axisX->setLineVisible(true); //设置轴线和刻度线可见性
            axisX->setGridLineVisible(true); //设置网格线可见性

            axisY->setTitleText("z(m)"); //设置标题
            //axisY->setRange(0, 20);       //设置范围
            axisY->setTickCount(21);      //设置主刻度个数
            axisY->setLineVisible(true); //设置轴线和刻度线可见性
            axisY->setGridLineVisible(true); //设置网格线可见性

            //设置序列1
            //series->setName("中国");    //设置序列名
            //series->setColor(QColor(255,0,0)); //设置序列颜色

            //添加数据点到序列
            for(int i = 0; i < time_MAX_0/time_INCRE_0; i++)
                series->append(i*time_INCRE_0, -dataRecord_z[i]);

            pen_1->setWidth(3);
            series->setPen(* pen_1);

            //给Qchart添加序列
            chart->addSeries(series);

            //把序列设置到坐标轴
            chart->setAxisX(axisX, series);
            chart->setAxisY(axisY, series);
            break;
        case 3:
            chart->setTitle("导弹u-time坐标图"); //设置标题

            ui->graphicsView->setChart(chart);  //将QChart对象设置到QChartView图表上

            //设置坐标轴
            axisX->setTitleText("time(s)"); //设置标题
            //axisX->setRange(1960, 2020); //设置范围
            axisX->setTickCount(7);      //设置主刻度个数
            axisX->setLineVisible(true); //设置轴线和刻度线可见性
            axisX->setGridLineVisible(true); //设置网格线可见性

            axisY->setTitleText("u(m/s)"); //设置标题
            //axisY->setRange(0, 20);       //设置范围
            axisY->setTickCount(21);      //设置主刻度个数
            axisY->setLineVisible(true); //设置轴线和刻度线可见性
            axisY->setGridLineVisible(true); //设置网格线可见性

            //设置序列1
            //series->setName("中国");    //设置序列名
            //series->setColor(QColor(255,0,0)); //设置序列颜色

            //添加数据点到序列
            for(int i = 0; i < time_MAX_0/time_INCRE_0; i++)
                series->append(i*time_INCRE_0, dataRecord_u[i]);

            pen_1->setWidth(3);
            series->setPen(* pen_1);

            //给Qchart添加序列
            chart->addSeries(series);

            //把序列设置到坐标轴
            chart->setAxisX(axisX, series);
            chart->setAxisY(axisY, series);
            break;
        case 4:
            chart->setTitle("导弹v-time坐标图"); //设置标题

            ui->graphicsView->setChart(chart);  //将QChart对象设置到QChartView图表上

            //设置坐标轴
            axisX->setTitleText("time(s)"); //设置标题
            //axisX->setRange(1960, 2020); //设置范围
            axisX->setTickCount(7);      //设置主刻度个数
            axisX->setLineVisible(true); //设置轴线和刻度线可见性
            axisX->setGridLineVisible(true); //设置网格线可见性

            axisY->setTitleText("v(m/s)"); //设置标题
            //axisY->setRange(0, 20);       //设置范围
            axisY->setTickCount(21);      //设置主刻度个数
            axisY->setLineVisible(true); //设置轴线和刻度线可见性
            axisY->setGridLineVisible(true); //设置网格线可见性

            //设置序列1
            //series->setName("中国");    //设置序列名
            //series->setColor(QColor(255,0,0)); //设置序列颜色

            //添加数据点到序列
            for(int i = 0; i < time_MAX_0/time_INCRE_0; i++)
                series->append(i*time_INCRE_0, dataRecord_v[i]);

            pen_1->setWidth(3);
            series->setPen(* pen_1);

            //给Qchart添加序列
            chart->addSeries(series);

            //把序列设置到坐标轴
            chart->setAxisX(axisX, series);
            chart->setAxisY(axisY, series);
            break;
        case 5:
            chart->setTitle("导弹w-time坐标图"); //设置标题

            ui->graphicsView->setChart(chart);  //将QChart对象设置到QChartView图表上

            //设置坐标轴
            axisX->setTitleText("time(s)"); //设置标题
            //axisX->setRange(1960, 2020); //设置范围
            axisX->setTickCount(7);      //设置主刻度个数
            axisX->setLineVisible(true); //设置轴线和刻度线可见性
            axisX->setGridLineVisible(true); //设置网格线可见性

            axisY->setTitleText("w(m/s)"); //设置标题
            //axisY->setRange(0, 20);       //设置范围
            axisY->setTickCount(21);      //设置主刻度个数
            axisY->setLineVisible(true); //设置轴线和刻度线可见性
            axisY->setGridLineVisible(true); //设置网格线可见性

            //设置序列1
            //series->setName("中国");    //设置序列名
            //series->setColor(QColor(255,0,0)); //设置序列颜色

            //添加数据点到序列
            for(int i = 0; i < time_MAX_0/time_INCRE_0; i++)
                series->append(i*time_INCRE_0, dataRecord_w[i]);

            pen_1->setWidth(3);
            series->setPen(* pen_1);

            //给Qchart添加序列
            chart->addSeries(series);

            //把序列设置到坐标轴
            chart->setAxisX(axisX, series);
            chart->setAxisY(axisY, series);
            break;
        case 6:
            chart->setTitle("导弹mass-time坐标图"); //设置标题

            ui->graphicsView->setChart(chart);  //将QChart对象设置到QChartView图表上

            //设置坐标轴
            axisX->setTitleText("time(s)"); //设置标题
            //axisX->setRange(1960, 2020); //设置范围
            axisX->setTickCount(7);      //设置主刻度个数
            axisX->setLineVisible(true); //设置轴线和刻度线可见性
            axisX->setGridLineVisible(true); //设置网格线可见性

            axisY->setTitleText("mass(kg)"); //设置标题
            //axisY->setRange(0, 20);       //设置范围
            axisY->setTickCount(21);      //设置主刻度个数
            axisY->setLineVisible(true); //设置轴线和刻度线可见性
            axisY->setGridLineVisible(true); //设置网格线可见性

            //设置序列1
            //series->setName("中国");    //设置序列名
            //series->setColor(QColor(255,0,0)); //设置序列颜色

            //添加数据点到序列
            for(int i = 0; i < time_MAX_0/time_INCRE_0; i++)
                series->append(i*time_INCRE_0, dataRecord_mass[i]);

            pen_1->setWidth(3);
            series->setPen(* pen_1);

            //给Qchart添加序列
            chart->addSeries(series);

            //把序列设置到坐标轴
            chart->setAxisX(axisX, series);
            chart->setAxisY(axisY, series);
            break;
        case 7:
            chart->setTitle("导弹Velocity-time坐标图"); //设置标题

            ui->graphicsView->setChart(chart);  //将QChart对象设置到QChartView图表上

            //设置坐标轴
            axisX->setTitleText("time(s)"); //设置标题
            //axisX->setRange(1960, 2020); //设置范围
            axisX->setTickCount(7);      //设置主刻度个数
            axisX->setLineVisible(true); //设置轴线和刻度线可见性
            axisX->setGridLineVisible(true); //设置网格线可见性

            axisY->setTitleText("V(m/s)"); //设置标题
            //axisY->setRange(0, 20);       //设置范围
            axisY->setTickCount(21);      //设置主刻度个数
            axisY->setLineVisible(true); //设置轴线和刻度线可见性
            axisY->setGridLineVisible(true); //设置网格线可见性

            //设置序列1
            //series->setName("中国");    //设置序列名
            //series->setColor(QColor(255,0,0)); //设置序列颜色

            //添加数据点到序列
            for(int i = 0; i < time_MAX_0/time_INCRE_0; i++)
                series->append(i*time_INCRE_0, dataRecord_Velocity[i]);

            pen_1->setWidth(3);
            series->setPen(* pen_1);

            //给Qchart添加序列
            chart->addSeries(series);

            //把序列设置到坐标轴
            chart->setAxisX(axisX, series);
            chart->setAxisY(axisY, series);
            break;
        case 8:
            chart->setTitle("导弹θ-time坐标图"); //设置标题

            ui->graphicsView->setChart(chart);  //将QChart对象设置到QChartView图表上

            //设置坐标轴
            axisX->setTitleText("time(s)"); //设置标题
            //axisX->setRange(1960, 2020); //设置范围
            axisX->setTickCount(7);      //设置主刻度个数
            axisX->setLineVisible(true); //设置轴线和刻度线可见性
            axisX->setGridLineVisible(true); //设置网格线可见性

            axisY->setTitleText("θ(°)"); //设置标题
            //axisY->setRange(0, 20);       //设置范围
            axisY->setTickCount(21);      //设置主刻度个数
            axisY->setLineVisible(true); //设置轴线和刻度线可见性
            axisY->setGridLineVisible(true); //设置网格线可见性

            //设置序列1
            //series->setName("中国");    //设置序列名
            //series->setColor(QColor(255,0,0)); //设置序列颜色

            //添加数据点到序列
            for(int i = 0; i < time_MAX_0/time_INCRE_0; i++)
                series->append(i*time_INCRE_0, dataRecord_theta[i]*180/PI);

            pen_1->setWidth(3);
            series->setPen(* pen_1);

            //给Qchart添加序列
            chart->addSeries(series);

            //把序列设置到坐标轴
            chart->setAxisX(axisX, series);
            chart->setAxisY(axisY, series);
            break;
        case 9:
            chart->setTitle("导弹Φ-time坐标图"); //设置标题

            ui->graphicsView->setChart(chart);  //将QChart对象设置到QChartView图表上

            //设置坐标轴
            axisX->setTitleText("time(s)"); //设置标题
            //axisX->setRange(1960, 2020); //设置范围
            axisX->setTickCount(7);      //设置主刻度个数
            axisX->setLineVisible(true); //设置轴线和刻度线可见性
            axisX->setGridLineVisible(true); //设置网格线可见性

            axisY->setTitleText("Φ(°)"); //设置标题
            //axisY->setRange(0, 20);       //设置范围
            axisY->setTickCount(21);      //设置主刻度个数
            axisY->setLineVisible(true); //设置轴线和刻度线可见性
            axisY->setGridLineVisible(true); //设置网格线可见性

            //设置序列1
            //series->setName("中国");    //设置序列名
            //series->setColor(QColor(255,0,0)); //设置序列颜色

            //添加数据点到序列
            for(int i = 0; i < time_MAX_0/time_INCRE_0; i++)
                series->append(i*time_INCRE_0, dataRecord_phi[i]*180/PI);

            pen_1->setWidth(3);
            series->setPen(* pen_1);

            //给Qchart添加序列
            chart->addSeries(series);

            //把序列设置到坐标轴
            chart->setAxisX(axisX, series);
            chart->setAxisY(axisY, series);
            break;
        case 10:
            chart->setTitle("导弹ψ-time坐标图"); //设置标题

            ui->graphicsView->setChart(chart);  //将QChart对象设置到QChartView图表上

            //设置坐标轴
            axisX->setTitleText("time(s)"); //设置标题
            //axisX->setRange(1960, 2020); //设置范围
            axisX->setTickCount(7);      //设置主刻度个数
            axisX->setLineVisible(true); //设置轴线和刻度线可见性
            axisX->setGridLineVisible(true); //设置网格线可见性

            axisY->setTitleText("ψ(°)"); //设置标题
            //axisY->setRange(0, 20);       //设置范围
            axisY->setTickCount(21);      //设置主刻度个数
            axisY->setLineVisible(true); //设置轴线和刻度线可见性
            axisY->setGridLineVisible(true); //设置网格线可见性

            //设置序列1
            //series->setName("中国");    //设置序列名
            //series->setColor(QColor(255,0,0)); //设置序列颜色

            //添加数据点到序列
            for(int i = 0; i < time_MAX_0/time_INCRE_0; i++)
                series->append(i*time_INCRE_0, dataRecord_psi[i]*180/PI);

            pen_1->setWidth(3);
            series->setPen(* pen_1);

            //给Qchart添加序列
            chart->addSeries(series);

            //把序列设置到坐标轴
            chart->setAxisX(axisX, series);
            chart->setAxisY(axisY, series);
            break;
        case 11:
            chart->setTitle("导弹α-time坐标图"); //设置标题

            ui->graphicsView->setChart(chart);  //将QChart对象设置到QChartView图表上

            //设置坐标轴
            axisX->setTitleText("time(s)"); //设置标题
            //axisX->setRange(1960, 2020); //设置范围
            axisX->setTickCount(7);      //设置主刻度个数
            axisX->setLineVisible(true); //设置轴线和刻度线可见性
            axisX->setGridLineVisible(true); //设置网格线可见性

            axisY->setTitleText("α(°)"); //设置标题
            //axisY->setRange(0, 20);       //设置范围
            axisY->setTickCount(21);      //设置主刻度个数
            axisY->setLineVisible(true); //设置轴线和刻度线可见性
            axisY->setGridLineVisible(true); //设置网格线可见性

            //设置序列1
            //series->setName("中国");    //设置序列名
            //series->setColor(QColor(255,0,0)); //设置序列颜色

            //添加数据点到序列
            for(int i = 0; i < time_MAX_0/time_INCRE_0; i++)
                series->append(i*time_INCRE_0, dataRecord_alpha[i]*180/PI);

            pen_1->setWidth(3);
            series->setPen(* pen_1);

            //给Qchart添加序列
            chart->addSeries(series);

            //把序列设置到坐标轴
            chart->setAxisX(axisX, series);
            chart->setAxisY(axisY, series);
            break;
        case 12:
            chart->setTitle("导弹β-time坐标图"); //设置标题

            ui->graphicsView->setChart(chart);  //将QChart对象设置到QChartView图表上

            //设置坐标轴
            axisX->setTitleText("time(s)"); //设置标题
            //axisX->setRange(1960, 2020); //设置范围
            axisX->setTickCount(7);      //设置主刻度个数
            axisX->setLineVisible(true); //设置轴线和刻度线可见性
            axisX->setGridLineVisible(true); //设置网格线可见性

            axisY->setTitleText("β(°)"); //设置标题
            //axisY->setRange(0, 20);       //设置范围
            axisY->setTickCount(21);      //设置主刻度个数
            axisY->setLineVisible(true); //设置轴线和刻度线可见性
            axisY->setGridLineVisible(true); //设置网格线可见性

            //设置序列1
            //series->setName("中国");    //设置序列名
            //series->setColor(QColor(255,0,0)); //设置序列颜色

            //添加数据点到序列
            for(int i = 0; i < time_MAX_0/time_INCRE_0; i++)
                series->append(i*time_INCRE_0, dataRecord_beta[i]*180/PI);

            pen_1->setWidth(3);
            series->setPen(* pen_1);

            //给Qchart添加序列
            chart->addSeries(series);

            //把序列设置到坐标轴
            chart->setAxisX(axisX, series);
            chart->setAxisY(axisY, series);
            break;
        case 13:
            chart->setTitle("导弹θv-time坐标图"); //设置标题

            ui->graphicsView->setChart(chart);  //将QChart对象设置到QChartView图表上

            //设置坐标轴
            axisX->setTitleText("time(s)"); //设置标题
            //axisX->setRange(1960, 2020); //设置范围
            axisX->setTickCount(7);      //设置主刻度个数
            axisX->setLineVisible(true); //设置轴线和刻度线可见性
            axisX->setGridLineVisible(true); //设置网格线可见性

            axisY->setTitleText("θv(°)"); //设置标题
            //axisY->setRange(0, 20);       //设置范围
            axisY->setTickCount(21);      //设置主刻度个数
            axisY->setLineVisible(true); //设置轴线和刻度线可见性
            axisY->setGridLineVisible(true); //设置网格线可见性

            //设置序列1
            //series->setName("中国");    //设置序列名
            //series->setColor(QColor(255,0,0)); //设置序列颜色

            //添加数据点到序列
            for(int i = 0; i < time_MAX_0/time_INCRE_0; i++)
                series->append(i*time_INCRE_0, dataRecord_theta_V[i]*180/PI);

            pen_1->setWidth(3);
            series->setPen(* pen_1);

            //给Qchart添加序列
            chart->addSeries(series);

            //把序列设置到坐标轴
            chart->setAxisX(axisX, series);
            chart->setAxisY(axisY, series);
            break;
        case 14:
            chart->setTitle("导弹ψv-time坐标图"); //设置标题

            ui->graphicsView->setChart(chart);  //将QChart对象设置到QChartView图表上

            //设置坐标轴
            axisX->setTitleText("time(s)"); //设置标题
            //axisX->setRange(1960, 2020); //设置范围
            axisX->setTickCount(7);      //设置主刻度个数
            axisX->setLineVisible(true); //设置轴线和刻度线可见性
            axisX->setGridLineVisible(true); //设置网格线可见性

            axisY->setTitleText("ψv(°)"); //设置标题
            //axisY->setRange(0, 20);       //设置范围
            axisY->setTickCount(21);      //设置主刻度个数
            axisY->setLineVisible(true); //设置轴线和刻度线可见性
            axisY->setGridLineVisible(true); //设置网格线可见性

            //设置序列1
            //series->setName("中国");    //设置序列名
            //series->setColor(QColor(255,0,0)); //设置序列颜色

            //添加数据点到序列
            for(int i = 0; i < time_MAX_0/time_INCRE_0; i++)
                series->append(i*time_INCRE_0, dataRecord_psi_V[i]*180/PI);

            pen_1->setWidth(3);
            series->setPen(* pen_1);

            //给Qchart添加序列
            chart->addSeries(series);

            //把序列设置到坐标轴
            chart->setAxisX(axisX, series);
            chart->setAxisY(axisY, series);
            break;
        case 15:
            chart->setTitle("导弹x-y坐标图"); //设置标题

            ui->graphicsView->setChart(chart);  //将QChart对象设置到QChartView图表上

            //设置坐标轴
            axisX->setTitleText("x(m)"); //设置标题
            //axisX->setRange(1960, 2020); //设置范围
            axisX->setTickCount(7);      //设置主刻度个数
            axisX->setLineVisible(true); //设置轴线和刻度线可见性
            axisX->setGridLineVisible(true); //设置网格线可见性

            axisY->setTitleText("y(m)"); //设置标题
            //axisY->setRange(0, 20);       //设置范围
            axisY->setTickCount(21);      //设置主刻度个数
            axisY->setLineVisible(true); //设置轴线和刻度线可见性
            axisY->setGridLineVisible(true); //设置网格线可见性

            //设置序列1
            //series->setName("中国");    //设置序列名
            //series->setColor(QColor(255,0,0)); //设置序列颜色

            //添加数据点到序列
            for(int i = 0; i < time_MAX_0/time_INCRE_0; i++)
                series->append(dataRecord_x[i], dataRecord_y[i]);

            pen_1->setWidth(3);
            series->setPen(* pen_1);

            //给Qchart添加序列
            chart->addSeries(series);

            //把序列设置到坐标轴
            chart->setAxisX(axisX, series);
            chart->setAxisY(axisY, series);
            break;
        case 16:
            chart->setTitle("导弹x-z坐标图"); //设置标题

            ui->graphicsView->setChart(chart);  //将QChart对象设置到QChartView图表上

            //设置坐标轴
            axisX->setTitleText("x(m)"); //设置标题
            //axisX->setRange(1960, 2020); //设置范围
            axisX->setTickCount(7);      //设置主刻度个数
            axisX->setLineVisible(true); //设置轴线和刻度线可见性
            axisX->setGridLineVisible(true); //设置网格线可见性

            axisY->setTitleText("z(m)"); //设置标题
            //axisY->setRange(0, 20);       //设置范围
            axisY->setTickCount(21);      //设置主刻度个数
            axisY->setLineVisible(true); //设置轴线和刻度线可见性
            axisY->setGridLineVisible(true); //设置网格线可见性

            //设置序列1
            //series->setName("中国");    //设置序列名
            //series->setColor(QColor(255,0,0)); //设置序列颜色

            //添加数据点到序列
            for(int i = 0; i < time_MAX_0/time_INCRE_0; i++)
                series->append(dataRecord_x[i], -dataRecord_z[i]);

            pen_1->setWidth(3);
            series->setPen(* pen_1);

            //给Qchart添加序列
            chart->addSeries(series);

            //把序列设置到坐标轴
            chart->setAxisX(axisX, series);
            chart->setAxisY(axisY, series);
            break;
        case 17:
            chart->setTitle("导弹y-z坐标图"); //设置标题

            ui->graphicsView->setChart(chart);  //将QChart对象设置到QChartView图表上

            //设置坐标轴
            axisX->setTitleText("y(m)"); //设置标题
            //axisX->setRange(1960, 2020); //设置范围
            axisX->setTickCount(7);      //设置主刻度个数
            axisX->setLineVisible(true); //设置轴线和刻度线可见性
            axisX->setGridLineVisible(true); //设置网格线可见性

            axisY->setTitleText("z(m)"); //设置标题
            //axisY->setRange(0, 20);       //设置范围
            axisY->setTickCount(21);      //设置主刻度个数
            axisY->setLineVisible(true); //设置轴线和刻度线可见性
            axisY->setGridLineVisible(true); //设置网格线可见性

            //设置序列1
            //series->setName("中国");    //设置序列名
            //series->setColor(QColor(255,0,0)); //设置序列颜色

            //添加数据点到序列
            for(int i = 0; i < time_MAX_0/time_INCRE_0; i++)
                series->append(dataRecord_y[i], -dataRecord_z[i]);

            pen_1->setWidth(3);
            series->setPen(* pen_1);

            //给Qchart添加序列
            chart->addSeries(series);

            //把序列设置到坐标轴
            chart->setAxisX(axisX, series);
            chart->setAxisY(axisY, series);
            break;
        }

    });//combobox

    connect(ui->pushButton_4, &QPushButton::clicked, [=](){
        float time_index = ui->lineEdit->text().toFloat();
        int int_index = time_index / time_INCRE_0;
        ui->lineEdit_2->setText(QString::number(dataRecord_x[int_index]));
        ui->lineEdit_3->setText(QString::number(dataRecord_y[int_index]));
        ui->lineEdit_4->setText(QString::number(dataRecord_z[int_index]));
        ui->lineEdit_5->setText(QString::number(dataRecord_u[int_index]));
        ui->lineEdit_6->setText(QString::number(dataRecord_v[int_index]));
        ui->lineEdit_7->setText(QString::number(dataRecord_w[int_index]));
        ui->lineEdit_8->setText(QString::number(dataRecord_mass[int_index]));
        ui->lineEdit_9->setText(QString::number(dataRecord_Velocity[int_index]));
        ui->lineEdit_10->setText(QString::number(dataRecord_theta[int_index]*180/PI));
        ui->lineEdit_11->setText(QString::number(dataRecord_phi[int_index]*180/PI));
        ui->lineEdit_12->setText(QString::number(dataRecord_psi[int_index]*180/PI));
        ui->lineEdit_13->setText(QString::number(dataRecord_alpha[int_index]*180/PI));
        ui->lineEdit_14->setText(QString::number(dataRecord_beta[int_index]*180/PI));
    });

    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::mainLoop);//pushbutton

    connect(ui->pushButton_5, &QPushButton::clicked, [=](){
        system("touch data_x.txt data_y.txt data_z.txt");
        ofstream ofs_x;
        ofs_x.open("./data_x.txt", ios::out);
        for(int i = 0; i<time_MAX_0/time_INCRE_0; i++)
            ofs_x << dataRecord_x[i] << endl;
        ofs_x.close();

        ofstream ofs_y;
        ofs_y.open("./data_y.txt", ios::out);
        for(int i = 0; i<time_MAX_0/time_INCRE_0; i++)
            ofs_y << dataRecord_y[i] << endl;
        ofs_y.close();

        ofstream ofs_z;
        ofs_z.open("./data_z.txt", ios::out);
        for(int i = 0; i<time_MAX_0/time_INCRE_0; i++)
            ofs_z << dataRecord_z[i] << endl;
        ofs_z.close();
        system("python3 draw_carve.py");

        //system("rm ./data_tmp.txt");
    });

    connect(ui->pushButton_3, &QPushButton::clicked, [=](){
        Q3DScatter * m_3Dgraph = new Q3DScatter;
        m_3Dgraph->setFlags(m_3Dgraph->flags()^Qt::FramelessWindowHint);

        //设置阴影类型（无）
        m_3Dgraph->setShadowQuality(QAbstract3DGraph::ShadowQualityNone);

        QWidget *container = QWidget::createWindowContainer(m_3Dgraph);
        //container->setParent(this);

        QScatter3DSeries *series_1 = new QScatter3DSeries;
        QScatterDataArray data;

        for(int i = 0; i<(time_MAX_0/time_INCRE_0); i++)
        {
            xyz.setX(dataRecord_x[i]);
            xyz.setY(-dataRecord_z[i]);
            xyz.setZ(dataRecord_y[i]);

            data.append(xyz);
        }

//        data.append(QVector3D(0.5f, 0.5f, 0.5f));
//        data.append(QVector3D(-0.3f, -0.5f, -0.4f));
//        data.append(QVector3D(0.0f, -0.3f, 0.2f));
        //data << QVector3D(0.5f, 0.5f, 0.5f) << QVector3D(-0.3f, -0.5f, -0.4f) << QVector3D(0.0f, -0.3f, 0.2f);
        series_1->dataProxy()->addItems(data);
        series_1->setItemSize(0.03);
        m_3Dgraph->addSeries(series_1);


        m_3Dgraph->show();
        container->resize(QSize(1200, 900));
        container->show();
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mainLoop()
{
    int time_MAX = time_MAX_0;
    float time_INCRE = time_INCRE_0;
    int step = time_MAX / time_INCRE;

    Init_state();

    float state_pr_tmp[13];
    float * state_pr = state_pr_tmp;

    for(int i = 0; i < 13; i++){
        state_missile[i] = state_0[i];
        state_pr[i] = state_0[i];
    }

    for(int j = 0; j < step; j++)
    {
        for(int k = 0; k < 13; k++)
            state_missile[k] = state_pr[k];

        state_pr = RK4(j*time_INCRE, state_missile, time_INCRE);

        dataRecord_x.append(pos_x);
        dataRecord_y.append(pos_y);
        dataRecord_z.append(pos_z);
        dataRecord_u.append(u);
        dataRecord_v.append(v);
        dataRecord_w.append(w);
        dataRecord_mass.append(mass);
        dataRecord_Velocity.append(velocity);
        dataRecord_theta.append(theta);
        dataRecord_phi.append(phi);
        dataRecord_psi.append(psi);
        dataRecord_alpha.append(alpha);
        dataRecord_beta.append(beta);
        dataRecord_theta_V.append(theta_V);
        dataRecord_psi_V.append(psi_V);

//            printf("velicity = %f\n",velocity);
//            printf("u = %f\t\tv = %f\t\tw = %f\n",u, v, w);
//            printf("x = %f\t\ty = %f\t\tz = %f\n",pos_x, pos_y, pos_z);
//            printf("x_dot = %f\t\ty_dot = %f\t\tz_dot = %f\n", velocity_x, velocity_y, velocity_z);
//            printf("theta = %f\t\tphi = %f\t\tpsi = %f\n",theta *180/PI, phi*180/PI, psi*180/PI);
//            printf("alpha = %f\t\tbeta = %f\t\tmass = %f\n", alpha * 180/PI, beta*180/PI, mass);
//            printf("drag = %f\t\tlift = %f\t\tlateral_force = %f\n", drag, lift, lateral_force);
//            printf("u_dot = %f\t\tv_dot = %f\t\tw_dot = %f\n", u_dot, v_dot, w_dot);
//            printf("p = %f\t\tq = %f\t\tr = %f\n", p* 180/PI, q* 180/PI, r* 180/PI);
//            printf("t = %f\n",j*time_INCRE);
    }

    ui->pushButton_3->setEnabled(true);
    ui->pushButton_4->setEnabled(true);
    ui->pushButton_5->setEnabled(true);
    ui->comboBox->setEnabled(true);

    emit ui->comboBox->currentTextChanged("位置x");
    emit ui->pushButton_4->click();
}

