/***************************************************************
 * @Project:        missile_trajectory
 * @Copyright(C):   2022-2023, zhujunfan
 * @Author:         zhujunfan
 * @Email:          zhujf0801@163.com
 * @Version:        0.1.1
 * @Since:          2022-09-20
 ************************************************************/
#include "setinitdata.h"
#include "ui_setinitdata.h"
#include "data.h"

SetInitData::SetInitData(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetInitData)
{
    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::clicked, [=](){
        x_0 = ui->lineEdit_4->text().toFloat();
        y_0 = ui->lineEdit->text().toFloat();
        z_0 = ui->lineEdit_3->text().toFloat();

        theta_0 = ui->lineEdit_2->text().toFloat() * PI / 180;
        phi_0 = ui->lineEdit_10->text().toFloat() * PI / 180;
        psi_0 = ui->lineEdit_9->text().toFloat() * PI / 180;

        q_0 = ui->lineEdit_6->text().toFloat() * PI / 180;
        r_0 = ui->lineEdit_5->text().toFloat() * PI / 180;

        mass_0 = ui->lineEdit_8->text().toFloat();

        velocity_0 = ui->lineEdit_11->text().toFloat();

        time_MAX_0 = ui->lineEdit_12->text().toFloat();
        time_INCRE_0 = ui->lineEdit_7->text().toFloat();

        this->hide();
    });
}

SetInitData::~SetInitData()
{
    delete ui;
}
