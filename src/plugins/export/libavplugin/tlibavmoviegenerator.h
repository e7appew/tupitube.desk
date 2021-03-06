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

#ifndef TLIBAVMOVIEGENERATOR_H
#define TLIBAVMOVIEGENERATOR_H

#include "tglobal.h"
#include "tmoviegenerator.h"

class TUPITUBE_PLUGIN TLibavMovieGenerator : public TMovieGenerator
{
    public:
        TLibavMovieGenerator(TMovieGeneratorInterface::Format format, int width, int height, int fps = 24, double duration = 0);
        TLibavMovieGenerator(TMovieGeneratorInterface::Format format, const QSize &size, int fps = 24, double duration = 0);
        ~TLibavMovieGenerator();
        virtual bool validMovieHeader();
        virtual QString getErrorMsg() const;
        void saveMovie(const QString &filename);

    protected:
        void createMovieFile(const QString &fileName);
        virtual void handle(const QImage &image);
        virtual bool beginVideo();
        virtual void endVideo();

    private:
        struct Private;
        Private *const k;
};

#endif
