/***************************************************************
 * @Project:        missile_trajectory
 * @Copyright(C):   2022-2023, zhujunfan
 * @Author:         zhujunfan
 * @Email:          zhujf0801@163.com
 * @Version:        0.1.1
 * @Since:          2022-09-20
 ************************************************************/
#include "setconstdata.h"
#include "ui_setconstdata.h"
#include <QDebug>
#include "data.h"

SetConstData::SetConstData(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetConstData)
{
    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::clicked, [=](){
        characteristic_area = ui->lineEdit_5->text().toFloat();
        characteristic_length = ui->lineEdit_7->text().toFloat();
        atmospheric_density = ui->lineEdit_9->text().toFloat();
        velocity_of_sound = ui->lineEdit_11->text().toFloat();
        net_wingspan = ui->lineEdit_13->text().toFloat();
        gravity = ui->lineEdit_14->text().toFloat();

        this->hide();
    });
}

SetConstData::~SetConstData()
{
    delete ui;
}
