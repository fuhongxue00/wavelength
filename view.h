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

#ifndef VIEW_H
#define VIEW_H
#include <QtWidgets/QGraphicsView>
#include <QtCharts/QChartGlobal>
#include <QLineSeries>

QT_BEGIN_NAMESPACE
class QGraphicsScene;//图形
class QMouseEvent;//鼠标事件
class QResizeEvent;//大小改变
QT_END_NAMESPACE

QT_CHARTS_BEGIN_NAMESPACE
class QChart;
QT_CHARTS_END_NAMESPACE

class Callout;

QT_CHARTS_USE_NAMESPACE
extern QStringList mCSVList_3;
extern  QLineSeries mSeries_3;
extern QStringList mCSVList_pos;
class View: public QGraphicsView//声明view类，继承自QGraphicsView
{
    Q_OBJECT

public:
    View(QWidget *parent = 0);

protected:
    void resizeEvent(QResizeEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

public slots:
    void keepCallout();
    void tooltip(QPointF point, bool state);

private:
    QGraphicsSimpleTextItem *m_coordX;//下面的两个显示：x
    QGraphicsSimpleTextItem *m_coordY;//下面的两个显示：y
    QGraphicsSimpleTextItem *m_coordpos;
    QGraphicsSimpleTextItem *axistext_x;//坐标轴x标题
    QGraphicsSimpleTextItem *axistext_y;//坐标轴y标题
    QChart *m_chart;
    Callout *m_tooltip;
    QList<Callout *> m_callouts;


};

#endif
