/***************************************************************
 * @Project:        missile_trajectory
 * @Copyright(C):   2022-2023, zhujunfan
 * @Author:         zhujunfan
 * @Email:          zhujf0801@163.com
 * @Version:        0.1.1
 * @Since:          2022-09-20
 ************************************************************/
#ifndef SETINITDATA_H
#define SETINITDATA_H

#include <QWidget>
#include <QVector>

namespace Ui {
class SetInitData;
}

class SetInitData : public QWidget
{
    Q_OBJECT

public:
    explicit SetInitData(QWidget *parent = 0);
    ~SetInitData();

private:
    Ui::SetInitData *ui;
};

#endif // SETINITDATA_H
