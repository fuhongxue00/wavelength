#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "view.h"
#include "callout.h"
#include <QValueAxis>
#include <QChart>
#include <QtCharts>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_btn_print_clicked();

    void on_readDataButton_clicked();

    void on_readDataButton_2_clicked();

    void on_pushButton_clicked();

    void on_printdata_clicked();

private:
    Ui::MainWindow *ui;
    View *widget;

    QStringList mCSVList;
    QValueAxis *mAxisY;
    QValueAxis *mAxisX;
    QLineSeries *mSeries;
    QChart *mWaveLineChart;
    QStringList mCSVList_2;
//    QStringList mCSVList_3;
    QValueAxis *mAxisY_2;
    QValueAxis *mAxisX_2;
    QLineSeries *mSeries_2;
    QChart *mWaveLineChart_2;
    void initWaveLineChart();
    void initWaveLineChart_2();
    QVector<QPointF> mWavePointBuffer;// mWavePointBuffer是文本数组
    QVector<QPointF> mWavePointBuffer_2;
    QVector<QPointF> mWavePointBuffer_3;
    QVector<QPointF> mWavePointBuffer_pos;
};
#endif // MAINWINDOW_H
