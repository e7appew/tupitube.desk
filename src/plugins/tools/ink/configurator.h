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

#ifndef CONFIGURATOR_H
#define CONFIGURATOR_H

#include "tglobal.h"

#include <QSpinBox>
#include <QCheckBox>
#include <QDoubleSpinBox>

/**
 * @author Gustav Gonzalez 
*/

class TUPITUBE_PLUGIN Configurator : public QWidget
{
    Q_OBJECT

    public:
        enum Structure { Basic = 0, Axial, Organic };

        Configurator(QWidget *parent = 0);
        ~Configurator();
        int spacingValue();
        qreal sizeToleranceValue();
        double smoothness() const;
        bool showBorder();
        int borderSizeValue();

    signals:
        void updateSpacing(int value);
        void updateSizeTolerance(int value);

    private:
        QSpinBox *spacingBox;
        QSpinBox *sizeBox;
        QCheckBox *borderOption;
        QSpinBox *borderSizeBox;
        QDoubleSpinBox *smoothBox;
};

#endif
