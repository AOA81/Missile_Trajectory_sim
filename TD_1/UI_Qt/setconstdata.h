/***************************************************************
 * @Project:        missile_trajectory
 * @Copyright(C):   2022-2023, zhujunfan
 * @Author:         zhujunfan
 * @Email:          zhujf0801@163.com
 * @Version:        0.1.1
 * @Since:          2022-09-20
 ************************************************************/
#ifndef SETCONSTDATA_H
#define SETCONSTDATA_H

#include <QWidget>
#include <QVector>

namespace Ui {
class SetConstData;
}

class SetConstData : public QWidget
{
    Q_OBJECT

public:
    explicit SetConstData(QWidget *parent = 0);
    ~SetConstData();

private:
    Ui::SetConstData *ui;
};

#endif // SETCONSTDATA_H
