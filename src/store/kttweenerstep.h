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

#ifndef KTTWEENERSTEP_H
#define KTTWEENERSTEP_H

#include <ktabstractserializable.h>
#include <QPointF>

#include "ktglobal_store.h"

/**
 * @author David Cuadrado \<krawek@gmail.com\>
*/
class STORE_EXPORT KTTweenerStep : public KTAbstractSerializable
{
    public:
        enum Type {
            None = 0x0,
            Position = 0x01,
            Translation = 0x02,
            Rotation = 0x04,
            Shear = 0x8,
            Scale = 0x10
        };
        
        KTTweenerStep(int index);
        
        ~KTTweenerStep();
        
        void setPosition(const QPointF &pos);
        void setTranslation(double dx, double dy);
        void setRotation(double angle);
        void setShear(double sh, double sv);
        void setScale(double sx, double sy);
        
        QPointF position() const;
        double horizontalScale() const;
        double verticalScale() const;
        double horizontalShear() const;
        double verticalShear() const;
        double rotation() const;
        double xTranslation() const;
        double yTranslation() const;
        
        bool has(Type type) const;
        int index() const;
    
        virtual QDomElement toXml(QDomDocument& doc) const;
        virtual void fromXml(const QString& xml);
        
    private:
        struct Private;
        Private *const k;
};

#endif
