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

#ifndef TUPCAMERAWIDGET_H
#define TUPCAMERAWIDGET_H

#include "tglobal.h"
#include "tupexportwidget.h"
#include "tseparator.h"
#include "tupprojectrequest.h"
#include "tupprojectresponse.h"
#include "tuprequestbuilder.h"
#include "tcirclebuttonbar.h"
#include "tvhbox.h"
#include "tupscreen.h"
#include "tupcamerabar.h"
#include "tupcamerastatus.h"

#include <QMainWindow>
#include <QFrame>
#include <QLabel>
#include <QHBoxLayout>
#include <QApplication>
#include <QDesktopWidget>
#include <QProgressBar>

class TupProjectResponse;
class QCheckBox;
class TupCameraStatus;

/**
 * @author David Cuadrado 
*/

class TUPITUBE_EXPORT TupCameraWidget : public QFrame
{
    Q_OBJECT

    public:
        TupCameraWidget(TupProject *work, bool isNetworked = false, QWidget *parent = 0);
        ~TupCameraWidget();

        void updateFirstFrame();
        QSize sizeHint() const;
        void updateScenes(int sceneIndex);

    private slots:
        void setLoop();
        void selectScene(int index);
        void updateProgressBar(int advance);
        void updateSoundItems();

    public slots:
        bool handleProjectResponse(TupProjectResponse *event);
        void setFPS(int fps);
        void setStatusFPS(int fps);
        void updateFramesTotal(int sceneIndex);
        void exportDialog();
        void postDialog();
        void doPlay();
        void doPlayBack();
        void doPause();
        void doStop();
        void nextFrame();
        void previousFrame();
        void updateTimerPanel(int currentFrame);

    signals:
        void requestTriggered(const TupProjectRequest *event);
        void requestForExportVideoToServer(const QString &title, const QString &topics, const QString &description, int fps, const QList<int> indexes);
        // void requestForExportStoryboardToServer(const QString &title, const QString &topics, const QString &description, const QList<int> indexes);

    private:
        void addVideoHeader();
        void addProgressBar();
        void addTimerPanel();
        void addAnimationDisplay();
        void addControlsBar();
        void addStatusPanel(bool isNetworked);

        void setDimensionLabel(const QSize dimension);
        struct Private;
        Private *const k;
};

#endif
