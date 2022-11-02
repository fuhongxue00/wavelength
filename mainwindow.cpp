#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPrinter>
#include <QPrintPreviewDialog>
#include <QPainter>
#include <QPrintDialog>
#include <QDebug>
#include <QFileDialog>
#include "view.h"
#include "callout.h"
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QFileDialog>
#include <QDebug>
#include <QtWidgets/QGraphicsScene>
#include <QString>

QLineSeries mSeries_3;
QStringList mCSVList_3;
QStringList mCSVList_pos;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    widget = new View;
//    ui->myarea->setWidget(widget);
    this->setWindowTitle("烟幕反射率测量软件");
    initWaveLineChart();
    initWaveLineChart_2();

}

MainWindow::~MainWindow()
{
    delete ui;
}
//打印
/*void MainWindow::on_btn_print_clicked()
{
    QPrinter printer(QPrinter::HighResolution);
        if (QPrintDialog(&printer).exec() == QDialog::Accepted)
        {
            QPainter painter(&printer);
            painter.setRenderHint(QPainter::Antialiasing);
            ui->myarea->render(&painter);
        }


}*/

//输出为pdf
/*void MainWindow::on_btn_print_clicked()
{
    QPrinter printer(QPrinter::HighResolution);
    printer.setPageSize(QPrinter::A4);
    printer.setOrientation(QPrinter::Portrait);
    printer.setOutputFormat(QPrinter::PdfFormat);
    // file will be created in your build directory (where debug/release directories are)
    printer.setOutputFileName("波形图片.pdf");
    printer.setFullPage(true);

    QPainter painter;
    if(!painter.begin(&printer))
    {
        qDebug() << "Error!";
        return;
    }
    ui->myarea->render(&painter);
    painter.end();
}*/
//输出为图片
void MainWindow::on_btn_print_clicked()
{
// 记住，一定要初始化QPixmap的大小

QPixmap pixmap(ui->myarea->width(),
               ui->myarea->height());
pixmap.fill(Qt::white);
QPainter painter(&pixmap);
painter.setRenderHint(QPainter::/*HighQuality*/Antialiasing);
ui->myarea->render(&painter);
painter.end();
QString filePath = QFileDialog::getSaveFileName(this, "Save Image",
                   "", "BMP (*.bmp);;PNG (*.png);;JPEG (*.jpg *.jpeg);;All files (*.*)");
if (filePath == "" && pixmap.isNull())
{
    qDebug() << "Error!";
    return;
}
pixmap.save(filePath);
}






void MainWindow::on_readDataButton_clicked()
{
    QString readDataString;

    QString fileName = QFileDialog::getOpenFileName(this,
                                                     tr("Open File"),
                                                     "",
                                                     "CSV Files(*.csv)",
                                                     0);
    if(!fileName.isNull())
    {
        //fileName是文件名
        qDebug() << fileName;

        QFile csvFile(fileName);

        mCSVList.clear();

        if(csvFile.open(QIODevice::ReadWrite))
        {
            QTextStream stream(&csvFile);
            while (!stream.atEnd())
            {
                mCSVList.push_back(stream.readLine().remove(QRegExp("\\s")));//移除空格
            }
            csvFile.close();
        }
        mWavePointBuffer.clear(); //清空画图数据


        int most=0;
            for(int j = 0; j < mCSVList.length(); j++)
            {
                bool ok;
                if(mCSVList.at(j).right(4).toInt(&ok,16)>most) most=mCSVList.at(j).right(4).toInt(&ok,16);
                mWavePointBuffer.append(QPointF(j*0.1, mCSVList.at(j).left(4).toInt(&ok,16)));//转换为16进制
            }
            ui->label->setText("特征距离："+QString::number(most));

        }
        mSeries->replace(mWavePointBuffer);//将mcvlist里面的数据取出来变为double

}
//画图
void MainWindow::initWaveLineChart()
{
    mAxisX = new QValueAxis();
    mAxisY = new QValueAxis();
    mSeries = new QLineSeries();
    mWaveLineChart = new QChart();

    //添加曲线到chart中
    mWaveLineChart->addSeries(mSeries);//mseries是数组

    mAxisX->setRange(0, 180);
    mAxisY->setRange(0, 10000);
   // mAxisY->setRange(0, 4096);

    mAxisX->setTitleText("时间t/s");
    mAxisY->setTitleText("烟幕反射B");

    mAxisX->setGridLineVisible(true);  //不显示线框
    mAxisY->setGridLineVisible(true);

    mAxisX->setLabelsVisible(true);    //不显示label具体数值
    mAxisY->setLabelsVisible(true);

    //把坐标轴添加到chart中，第二个参数是设置坐标轴的位置，
    //只有四个选项，下方：Qt::AlignBottom，左边：Qt::AlignLeft，右边：Qt::AlignRight，上方：Qt::AlignTop
    mWaveLineChart->addAxis(mAxisX, Qt::AlignBottom);
    mWaveLineChart->addAxis(mAxisY, Qt::AlignLeft);

    //把曲线关联到坐标轴
    mSeries->attachAxis(mAxisX);
    mSeries->attachAxis(mAxisY);
    mSeries->setColor(QColor(Qt::black));//设置线的颜色

    mWaveLineChart->layout()->setContentsMargins(0, 0, 0, 0); //设置外边界全部为0
    mWaveLineChart->setMargins(QMargins(0, 0, 0, 0));         //设置内边界全部为0
    mWaveLineChart->setBackgroundRoundness(0);                //设置背景区域无圆角

    mWaveLineChart->legend()->hide();                         //不显示注释
    ui->waveGraphicsView->setChart(mWaveLineChart);
}


void MainWindow::on_readDataButton_2_clicked()
{
    QString readDataString;

    QString fileName = QFileDialog::getOpenFileName(this,
                                                     tr("Open File"),
                                                     "",
                                                     "CSV Files(*.csv)",
                                                     0);
    if(!fileName.isNull())
    {
        //fileName是文件名
        qDebug() << fileName;

        QFile csvFile(fileName);

        mCSVList_2.clear();

        if(csvFile.open(QIODevice::ReadWrite))
        {
            QTextStream stream(&csvFile);
            while (!stream.atEnd())
            {
                mCSVList_2.push_back(stream.readLine().remove(QRegExp("\\s")));
            }
            csvFile.close();
        }
        mWavePointBuffer_2.clear(); //清空画图数据

            int most=0;
            for(int j = 0; j < mCSVList_2.length(); j++)
            {
                bool ok;
                if(mCSVList_2.at(j).right(4).toInt(&ok,16)>most) most=mCSVList_2.at(j).right(4).toInt(&ok,16);
                mWavePointBuffer_2.append(QPointF(j*0.1, mCSVList_2.at(j).left(4).toInt(&ok,16)));
            }

            ui->label_2->setText("特征距离："+QString::number(most));


        }
        mSeries_2->replace(mWavePointBuffer_2);

}

//初始化2
void MainWindow::initWaveLineChart_2()
{
    mAxisX_2 = new QValueAxis();
    mAxisY_2 = new QValueAxis();
    mSeries_2 = new QLineSeries();
    mWaveLineChart_2 = new QChart();

    //添加曲线到chart中
    mWaveLineChart_2->addSeries(mSeries_2);//mseries是数组

    mAxisX_2->setRange(0, 180);
    mAxisY_2->setRange(0, 10000);
   // mAxisY->setRange(0, 4096);

    mAxisX_2->setTitleText("时间t/s");
    mAxisY_2->setTitleText("靶板反射A");

    mAxisX_2->setGridLineVisible(true);  //不显示线框
    mAxisY_2->setGridLineVisible(true);

    mAxisX_2->setLabelsVisible(true);    //不显示label具体数值
    mAxisY_2->setLabelsVisible(true);

    //把坐标轴添加到chart中，第二个参数是设置坐标轴的位置，
    //只有四个选项，下方：Qt::AlignBottom，左边：Qt::AlignLeft，右边：Qt::AlignRight，上方：Qt::AlignTop
    mWaveLineChart_2->addAxis(mAxisX_2, Qt::AlignBottom);
    mWaveLineChart_2->addAxis(mAxisY_2, Qt::AlignLeft);

    //把曲线关联到坐标轴
    mSeries_2->attachAxis(mAxisX_2);
    mSeries_2->attachAxis(mAxisY_2);
    mSeries_2->setColor(QColor(Qt::black));//设置线的颜色

    mWaveLineChart_2->layout()->setContentsMargins(0, 0, 0, 0); //设置外边界全部为0
    mWaveLineChart_2->setMargins(QMargins(0, 0, 0, 0));         //设置内边界全部为0
    mWaveLineChart_2->setBackgroundRoundness(0);                //设置背景区域无圆角

    mWaveLineChart_2->legend()->hide();                         //不显示注释
    ui->waveGraphicsView_2->setChart(mWaveLineChart_2);           //把设置好的QChart与QChartView进行绑定
}
//求解反射率

void MainWindow::on_pushButton_clicked()
{
    mWavePointBuffer_3.clear(); //清空画图数据
    mCSVList_3.clear();

        for(int j = 0; j < mCSVList_2.length(); j++)
        {
            bool ok;
        mWavePointBuffer_3.append(QPointF((j+1)*0.1, 0.7*mCSVList.at(j).left(4).toInt(&ok,16)/mCSVList_2.at(j).left(4).toInt(&ok,16)));//计算反射率核心
//      mCSVList_3.replace(j,QString::number(0.7*mCSVList.at(j).toDouble()/mCSVList_2.at(j).toDouble(),'f',2));
//      mCSVList_3.insert
//      mCSVList_3.insert(j*0.1,QString::number(0.7*mCSVList.at(j).toInt(&ok,16)/mCSVList_2.at(j).toInt(&ok,16),'f',3));//将数字转换为字符串存储起来
        mCSVList_3.insert(j+1,QString::number(0.7*mCSVList.at(j).left(4).toInt(&ok,16)/mCSVList_2.at(j).left(4).toInt(&ok,16)));//将数字转换为字符串存储起来
        mCSVList_pos.insert(j+1,QString::number(1.2*mCSVList.at(j).right(4).toInt(&ok,16)));
        }

     mSeries_3.replace(mWavePointBuffer_3);
     widget = new View;
     ui->myarea->setWidget(widget);


}
//打印数据
void MainWindow::on_printdata_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save File"),
                                                    "",
                                                    tr("CSV Files (*.csv)"));

    QStringList saveString;
    int i=1;

    if(!fileName.isNull())
    {
        //fileName是文件名
        qDebug() << fileName;
        QFile file(fileName);//文件命名


//        saveString = mCSVList_3+mCSVList_pos;
        int k=0;
        while(k<mCSVList_3.length()&&k<mCSVList_pos.length())
        {
            saveString.append(mCSVList_3[k]);
             saveString.append(mCSVList_pos[k]);
             if(k==1000)
             {
                 qDebug() << mCSVList_3[k];
//                 break;
             }
             k++;

        }




        if(file.open(QFile::WriteOnly | QFile::Text))		//检测文件是否打开
        {
            QTextStream out(&file);					        //分行写入文件
    //        ui->procDataProgressBar->setRange(0, saveString.length() - 1);
    //        ui->procDataProgressBar->setValue(0);
    //        ui->procDataProgressBar->setVisible(true);

            bool alt=true;
            Q_FOREACH(QString str, saveString)
            {
    //            out << str +"\t" +i*0.1 +"\n";
             if (alt==true)out <<  i*0.1;
             out <<  ",";
             out <<  str;

             if(alt==false)
             {
                 out << "\n";
                  i++;
             }
             alt=!alt;
    //            ui->procDataProgressBar->setValue(i);

            }
    //        ui->procDataProgressBar->setVisible(false);
            file.close();
        }
    }
    else
    {
        //选择取消
        qDebug() << "cancel";
    }
}


