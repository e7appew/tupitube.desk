/***************************************************************************
 *   Project TUPITUBE DESK                                                *
 *   Project Contact: info@maefloresta.com                                 *
 *   Project Website: http://www.maefloresta.com                           *
 *   Project Leader: Gustav Gonzalez <info@maefloresta.com>                *
 *                                                                         *
 *   Developers:                                                           *
 *   2010:                                                                 *
 *    Gustav Gonzalez / xtingray                                           *
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

#ifndef COMPOSERTWEENER_H
#define COMPOSERTWEENER_H

#include "tglobal.h"
#include "tuptoolplugin.h"
#include "configurator.h"
#include "tweenerpanel.h"
#include "tupprojectresponse.h"

#include <QPointF>
#include <QKeySequence>
#include <QGraphicsPathItem>
#include <QPainterPath>
#include <QMatrix>
#include <QGraphicsLineItem>
#include <QGraphicsView>
#include <QDomDocument>

/**
 * @author Gustav Gonzalez 
 *
*/

class TUPITUBE_PLUGIN Tweener : public TupToolPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.maefloresta.tupi.TupToolInterface" FILE "composedtool.json")

    public:
        Tweener();
        virtual ~Tweener();
        virtual void init(TupGraphicsScene *scene);

        virtual QStringList keys() const;
        virtual void press(const TupInputDeviceInformation *input, TupBrushManager *brushManager, TupGraphicsScene *scene);
        virtual void move(const TupInputDeviceInformation *input, TupBrushManager *brushManager, TupGraphicsScene *scene);
        virtual void release(const TupInputDeviceInformation *input, TupBrushManager *brushManager, TupGraphicsScene *scene);
        virtual void updateScene(TupGraphicsScene *scene);
        virtual QMap<QString, TAction *>actions() const;
        virtual QWidget *configurator();
        virtual void aboutToChangeTool();
        virtual void saveConfig();

        int toolType() const;
        void aboutToChangeScene(TupGraphicsScene *scene);
        // bool isComplete() const;

        virtual void sceneResponse(const TupSceneResponse *event);
        virtual void layerResponse(const TupLayerResponse *event);
        virtual void frameResponse(const TupFrameResponse *event);

    private:
        int framesCount();
        void setupActions();
        int maxZValue();
        void clearSelection();
        void removeTweenFromProject(const QString &name);
        void disableSelection();

    private:
        struct Private;
        Private *const k;

    private slots:
        void updateCurrentTweenerType(TweenerPanel::TweenerType type);
        void applyReset();
        void applyTween();
        void removeTween(const QString &name);
        void setCreatePath();
        void setSelect();
        void setEditEnv();
        void updateMode(TweenerPanel::Mode mode);
        void updateStartPoint(int index);
        void setCurrentTween(const QString &name);
        void setPath(bool isEnabled, bool reset);
        void tweenListMode();

    public slots:
        void updatePath();
};

#endif
