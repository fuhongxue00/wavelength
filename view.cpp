/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/
#include "mainwindow.h"
#include "view.h"
#include <QtGui/QResizeEvent>
#include <QtWidgets/QGraphicsScene>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtWidgets/QGraphicsTextItem>
#include "callout.h"
#include <QtGui/QMouseEvent>
#include <QValueAxis>

View::View(QWidget *parent)//构造函数后面加：,是对父类进行初始化或者是对类的成员进行初始化
    : QGraphicsView(new QGraphicsScene, parent),//对父类进行初始化
      m_coordX(0),
      m_coordY(0),
      m_coordpos(0),
      axistext_x(0),
      axistext_y(0),
      m_chart(0),
     // Tooltips是一个简短的信息消息，当用户与图形用户界面（GUI）中的元素交互时出现。Tooltips通常以两种方式触发：通过鼠标悬停或通过键盘悬停。
      m_tooltip(0)//构造函数，初始化
{
    setDragMode(QGraphicsView::NoDrag);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // chart
    m_chart = new QChart;
    m_chart->setMinimumSize(640, 480);
    m_chart->setTitle("烟幕反射率-时间曲线");
    m_chart->legend()->hide();
//    QPointer <QLineSeries> series = new QLineSeries;
//    series=&mSeries_3;
/*    series->append(0, 3);
    series->append(4, 5);
    series->append(5, 4.5);
    series->append(7, 1);
    series->append(11, 2);*/
//    QLineSeries *series = new QLineSeries;
//    series=&mSeries_3;

    m_chart->addSeries(&mSeries_3);



//    QSplineSeries *series2 = new QSplineSeries;
//    series2->append(1, 1.4);
//    series2->append(2.4, 3.5);
//    series2->append(3.7, 2.5);
//    series2->append(7, 4);
//    series2->append(10, 20);
//    m_chart->addSeries(series2);

    m_chart->createDefaultAxes();//设置默认的坐标轴




    m_chart->setAcceptHoverEvents(true);

    setRenderHint(QPainter::Antialiasing);
    scene()->addItem(m_chart);//将设置好的图表m_chart更新到scene
   // m_chart->setPos(5,5);设置坐标轴标题和底部的x，y标签及其位置
    m_coordX = new QGraphicsSimpleTextItem(m_chart);
    m_coordX->setPos(m_chart->size().width()/2 -150, m_chart->size().height());
    m_coordX->setText("testX: ");

    m_coordY = new QGraphicsSimpleTextItem(m_chart);
    m_coordY->setPos(m_chart->size().width()/2+50 , m_chart->size().height());
    m_coordY->setText("Y: ");

    m_coordpos = new QGraphicsSimpleTextItem(m_chart);
    m_coordpos->setPos(m_chart->size().width()/2 + 150, m_chart->size().height());//位置信息
    m_coordpos->setText("position: ");

    axistext_x=new QGraphicsSimpleTextItem(m_chart);
    axistext_x->setPos(1500,670);//设置位置
    axistext_x->setText("时test间t/s");

    axistext_y=new QGraphicsSimpleTextItem(m_chart);
    axistext_y->setPos(50,40);//设置位置
    axistext_y->setText("反射率R");




    connect(&mSeries_3, &QLineSeries::clicked, this, &View::keepCallout);//点击
    connect(&mSeries_3, &QLineSeries::hovered, this, &View::tooltip);

//    connect(series2, &QSplineSeries::clicked, this, &View::keepCallout);
//    connect(series2, &QSplineSeries::hovered, this, &View::tooltip);

    this->setMouseTracking(true);
}

void View::resizeEvent(QResizeEvent *event)//大小变更之后相应的也要变更以确保数据是对的
{
    if (scene()) {
        scene()->setSceneRect(QRect(QPoint(0, 0), event->size()));
         m_chart->resize(event->size());
         m_coordX->setPos(m_chart->size().width()/2 - 150, m_chart->size().height() - 20);
         m_coordY->setPos(m_chart->size().width()/2 + 50, m_chart->size().height() - 20);

//            axistext_x->setPos(m_chart->size().width()-100 , m_chart->size().height());//设置位置

         m_coordpos->setPos(m_chart->size().width()/2 + 150, m_chart->size().height() - 20);
         const auto callouts = m_callouts;
         for (Callout *callout : callouts)
             callout->updateGeometry();
    }
    QGraphicsView::resizeEvent(event);
}

void View::mouseMoveEvent(QMouseEvent *event)//显示x,y坐标，底部设置显示文本
{   m_coordX->setText(QString("X: %1").arg(m_chart->mapToValue(event->pos()).x()));
    if (m_chart->mapToValue(event->pos()).x()>=0.1 && m_chart->mapToValue(event->pos()).x()<179.9)
    {m_coordY->setText(QString("Y: %1").arg(mCSVList_3.at(-1+(qRound(10*(m_chart->mapToValue(event->pos()).x()))))));
     m_coordpos->setText(QString("position: %1").arg(mCSVList_pos.at(-1+(qRound(10*(m_chart->mapToValue(event->pos()).x()))))));
    }//崩溃相关，和数据边界有关系，索引的时候可能超越数组边界
    else
    {
    m_coordY->setText(QString("Y: %1").arg(m_chart->mapToValue(event->pos()).y()));
   // m_coordY->setText(QString("error：超出边界"));
    m_coordpos->setText(QString("error：超出边界"));}
    QGraphicsView::mouseMoveEvent(event);
}

void View::keepCallout()//点击之后保持callout
{
    m_callouts.append(m_tooltip);
    m_tooltip = new Callout(m_chart);//保证点击之后callout仍然存在
}

void View::tooltip(QPointF point, bool state)//state改变，改变值，改变anchor，更新图片，显示
{
    if (m_tooltip == 0)
        m_tooltip = new Callout(m_chart);//用m_chart初始化的callout类

    if (state) {
        if (point.x()>=0.1&&point.x()<=179.9)
       {m_tooltip->setText(QString("X: %1 \nY: %2 ").arg(point.x()).arg(mCSVList_3.at(-1+(qRound(10*(point.x()))))));}//崩溃相关，和数据边界有关系，索引的时候可能超越数组边界
        else
       { m_tooltip->setText(QString("X: %1 \nY: %2 ").arg(point.x()).arg(point.y()));}
        m_tooltip->setAnchor(point);
        m_tooltip->setZValue(11);//Z 值决定同级（相邻）项目的堆叠顺序。 一个 Z 值高的同级项将始终绘制在另一个 Z 值较低的同级项之上。
        m_tooltip->updateGeometry();
        m_tooltip->show();
}
    else {
        m_tooltip->hide();
        }

}
