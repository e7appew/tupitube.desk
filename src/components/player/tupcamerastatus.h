/***************************************************************************
 *   Project TUPITUBE DESK                                                *
 *   Project Contact: info@maefloresta.com                                 *
 *   Project Website: http://www.maefloresta.com                           *
 *   Project Leader: Gustav Gonzalez <info@maefloresta.com>                *
 *                                                                         *
 *   Developers:                                                           *
 *   2010:                                                                 *
 *    Gustavo Gonzalez / xtingray                                          *
 *                                                                         *
 *   KTooN's versions:                                                     * 
 *                                                                         *
 *   2006:                                                                 *
 *    David Cuadrado                                                       *
 *    Jorge Cuadrado                                                       *
 *   2003:                                                                 *
 *    Fernado Roldan                                                       *
 *    Simena Dinas                                                         *
 *                                                                         *
 *   Copyright (C) 2010 Gustav Gonzalez - http://www.maefloresta.com       *
 *   License:                                                              *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 ***************************************************************************/

#ifndef TUPCAMERASTATUS_H
#define TUPCAMERASTATUS_H

#include "tupcamerawidget.h"
#include "tupexportwidget.h"
#include "tconfig.h"
#include "tseparator.h"

#include <QFrame>
#include <QLabel>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QComboBox>
#include <QStatusBar>
#include <QApplication>
#include <QSpinBox>

class TupCameraWidget;

class TUPITUBE_EXPORT TupCameraStatus : public QFrame
{
    Q_OBJECT

    public:
        TupCameraStatus(TupCameraWidget *camera = 0, bool isNetworked = false, QWidget *parent = 0);
        ~TupCameraStatus();

        void setScenes(TupProject *project);
        void setFPS(int frames);
        int getFPS();
        void setCurrentScene(int index);
        void setFramesTotal(const QString &frames);
        bool isLooping();

    signals:
        void sceneIndexChanged(int index);
        void muteEnabled(bool mute);

    private slots:
        void setDuration();
        void mute();

    private:
        struct Private;
        Private *const k;
};

#endif
