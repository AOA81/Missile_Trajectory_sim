/***************************************************************
 * @Project:        missile_trajectory
 * @Copyright(C):   2022-2023, zhujunfan
 * @Author:         zhujunfan
 * @Email:          zhujf0801@163.com
 * @Version:        0.1.1
 * @Since:          2022-09-20
 ************************************************************/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>
#include <QtDataVisualization/Q3DScatter>
#include <QtDataVisualization/Q3DSurface>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QVector>


using namespace QtDataVisualization;


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



private:
    Ui::MainWindow *ui;
    void mainLoop();
    QVector<float> dataRecord_x;
    QVector<float> dataRecord_y;
    QVector<float> dataRecord_z;
    QVector<float> dataRecord_u;
    QVector<float> dataRecord_v;
    QVector<float> dataRecord_w;
    QVector<float> dataRecord_mass;
    QVector<float> dataRecord_Velocity;
    QVector<float> dataRecord_theta;
    QVector<float> dataRecord_phi;
    QVector<float> dataRecord_psi;
    QVector<float> dataRecord_alpha;
    QVector<float> dataRecord_beta;
    QVector<float> dataRecord_theta_V;
    QVector<float> dataRecord_psi_V;

    QVector3D xyz;
};

#endif // MAINWINDOW_H
