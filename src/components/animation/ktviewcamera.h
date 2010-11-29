/***************************************************************************
 *   Project TUPI: Magia 2D                                                *
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
 *   the Free Software Foundation; either version 3 of the License, or     *
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

#ifndef KTVIEWCAMERA_H
#define KTVIEWCAMERA_H

#include "kcirclebuttonbar.h"
#include "kvhbox.h"

#include <QMainWindow>
#include <QFrame>
#include "ktanimationarea.h"
#include "ktcamerabar.h"
#include "ktcamerastatus.h"

class KTProjectResponse;
class QCheckBox;
class KTCameraStatus;

/**
 * @author David Cuadrado \<krawek@toonka.com\>
*/
class KTViewCamera : public QFrame
{
    Q_OBJECT

    public:
        KTViewCamera(KTProject *work, QWidget *parent = 0);
        ~KTViewCamera();

        QSize sizeHint() const;
        void updateSceneInfo();

    private slots:
        void showSceneInfo(const KTScene *scene);
        void setLoop();

    public slots:
        bool handleProjectResponse(KTProjectResponse *event);
        void setFPS(int fps);
        void updatePhotograms(KTProject *project);
        void exportDialog();
        void doPlay();
        void doPlayBack();
        void doStop();
        void nextFrame();
        void previousFrame();

    signals:
        void requestTriggered(const KTProjectRequest *event);

    private:
        QFrame *m_container;
        KTAnimationArea *m_animationArea;

        //class KTCameraStatus;
        KTCameraStatus *m_status;
    
        KTProject *project;
        //QCheckBox *m_loop;
};

#endif
