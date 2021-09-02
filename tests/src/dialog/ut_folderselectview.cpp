/*
* Copyright (C) 2019 ~ 2020 Deepin Technology Co., Ltd.
*
* Author:     ningyuchuang <ningyuchuang@uniontech.com>
* Maintainer: ningyuchuang <ningyuchuang@uniontech.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "folderselectdialog.h"
#include "ut_folderselectview.h"
#include "leftview.h"
#include "leftviewdelegate.h"
#include "leftviewsortfilter.h"

ut_folderselectview_test::ut_folderselectview_test()
{
}

TEST_F(ut_folderselectview_test, mousePressEvent)
{
    FolderSelectView selectview;
    QPointF localPos(30, 20);
    QMouseEvent *mousePressEvent = new QMouseEvent(QEvent::MouseButtonPress, localPos, localPos, localPos, Qt::LeftButton, Qt::LeftButton, Qt::NoModifier, Qt::MouseEventSource::MouseEventSynthesizedByQt);
    selectview.mousePressEvent(mousePressEvent);
    EXPECT_EQ(mousePressEvent->pos().y(), selectview.m_touchPressPointY)
        << "event->pos().y()";
    delete mousePressEvent;
}

TEST_F(ut_folderselectview_test, mouseReleaseEvent)
{
    FolderSelectView selectview;
    QPointF localPos(30, 20);
    QMouseEvent *mousePressEvent = new QMouseEvent(QEvent::MouseButtonRelease, localPos, localPos, localPos, Qt::LeftButton, Qt::LeftButton, Qt::NoModifier, Qt::MouseEventSource::MouseEventSynthesizedByQt);
    selectview.mouseReleaseEvent(mousePressEvent);
    EXPECT_FALSE(selectview.m_isTouchSliding);
    delete mousePressEvent;
}

TEST_F(ut_folderselectview_test, keyPressEvent)
{
    FolderSelectView selectview;
    QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Up, Qt::NoModifier, "test");
    selectview.keyPressEvent(event);
    delete event;
    event = new QKeyEvent(QEvent::KeyPress, Qt::Key_PageDown, Qt::NoModifier, "test");
    selectview.keyPressEvent(event);
    delete event;
    event = new QKeyEvent(QEvent::KeyPress, Qt::Key_PageUp, Qt::NoModifier, "test");
    selectview.keyPressEvent(event);
    delete event;
    event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Home, Qt::NoModifier, "test");
    selectview.keyPressEvent(event);
    delete event;
}

TEST_F(ut_folderselectview_test, mouseMoveEvent)
{
    FolderSelectView selectview;
    QPointF localPos(30, 20);
    QMouseEvent *mouseMoveEvent = new QMouseEvent(QEvent::MouseMove, localPos, localPos, localPos, Qt::LeftButton, Qt::LeftButton, Qt::NoModifier, Qt::MouseEventSource::MouseEventSynthesizedByQt);
    selectview.mouseMoveEvent(mouseMoveEvent);
    EXPECT_EQ(Qt::NoModifier, mouseMoveEvent->modifiers());
    delete mouseMoveEvent;
}

TEST_F(ut_folderselectview_test, doTouchMoveEvent)
{
    FolderSelectView selectview;
    QPointF localPos(30, 20);
    QMouseEvent *mouseMoveEvent = new QMouseEvent(QEvent::MouseMove, localPos, localPos, localPos, Qt::LeftButton, Qt::LeftButton, Qt::NoModifier, Qt::MouseEventSource::MouseEventSynthesizedByQt);
    selectview.m_isTouchSliding = false;
    selectview.doTouchMoveEvent(mouseMoveEvent);
    EXPECT_TRUE(selectview.m_isTouchSliding) << "m_isTouchSliding is false";
    selectview.doTouchMoveEvent(mouseMoveEvent);
    EXPECT_TRUE(selectview.m_isTouchSliding) << "m_isTouchSliding is true";
    delete mouseMoveEvent;
}

TEST_F(ut_folderselectview_test, handleTouchSlideEvent)
{
    FolderSelectView selectview;
    QPoint localPos(30, 20);
    selectview.handleTouchSlideEvent(20, 40, localPos);
    EXPECT_EQ(20, selectview.m_touchPressPointY);
}
