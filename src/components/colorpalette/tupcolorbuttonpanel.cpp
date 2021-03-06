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

#include "tupcolorbuttonpanel.h"
#include "tupcolorbutton.h"
#include "timagebutton.h"

#include <QBoxLayout>
#include <QColorDialog>
#include <QDebug>

struct TupColorButtonPanel::Private
{
    QList<TupColorButton *> baseColors;
    Qt::BrushStyle style;
    int currentColorIndex;
    TupColorButton *trans;
};

TupColorButtonPanel::TupColorButtonPanel(Qt::BrushStyle style, const QSize &baseColorCellSize, int spacing,
                                         const QString &buttonParams, QWidget *parent) : QWidget(parent), k(new Private)
{
    k->style = style;
    k->currentColorIndex = -1;
    this->spacing = spacing;

    setPanel(baseColorCellSize, buttonParams);
}

void TupColorButtonPanel::setPanel(const QSize &cellSize, const QString &buttonParams)
{
    TCONFIG->beginGroup("ColorPalette");
    QString colorName = TCONFIG->value("BarColor0", "transparent").toString(); 
    QColor color0 = QColor(colorName);

    QBrush transBrush(color0, k->style);
    k->trans = new TupColorButton(0, tr("Transparent"), transBrush, cellSize, buttonParams);
    connect(k->trans, &TupColorButton::clicked, this, &TupColorButtonPanel::updateSelection);
    k->baseColors << k->trans;

    TCONFIG->beginGroup("ColorPalette");
    colorName = TCONFIG->value("BarColor1", "#000").toString(); 
    QColor color1 = QColor(colorName);

    QBrush blackBrush(color1, k->style);
    TupColorButton *black = new TupColorButton(1, tr("Black"), blackBrush, cellSize, buttonParams);
    connect(black, &TupColorButton::clicked, this, &TupColorButtonPanel::updateSelection);
    k->baseColors << black;

    TCONFIG->beginGroup("ColorPalette");
    colorName = TCONFIG->value("BarColor2", "#fff").toString(); 
    QColor color2 = QColor(colorName);

    QBrush whiteBrush(color2, k->style);
    TupColorButton *white = new TupColorButton(2, tr("White"), whiteBrush, cellSize, buttonParams);
    connect(white, &TupColorButton::clicked, this, &TupColorButtonPanel::updateSelection);
    k->baseColors << white;

    TCONFIG->beginGroup("ColorPalette");
    colorName = TCONFIG->value("BarColor3", "#f00").toString();               
    QColor color3 = QColor(colorName);

    QBrush redBrush(color3, k->style);
    TupColorButton *red = new TupColorButton(3, tr("Red"), redBrush, cellSize, buttonParams);
    connect(red, &TupColorButton::clicked, this, &TupColorButtonPanel::updateSelection);
    k->baseColors << red;

    TCONFIG->beginGroup("ColorPalette");
    colorName = TCONFIG->value("BarColor4", "#0f0").toString();
    QColor color4 = QColor(colorName);

    QBrush greenBrush(color4, k->style);
    TupColorButton *green = new TupColorButton(4, tr("Green"), greenBrush, cellSize, buttonParams);
    connect(green, &TupColorButton::clicked, this, &TupColorButtonPanel::updateSelection);
    k->baseColors << green;

    TCONFIG->beginGroup("ColorPalette");
    colorName = TCONFIG->value("BarColor5", "#00f").toString();
    QColor color5 = QColor(colorName);

    QBrush blueBrush(color5, k->style);
    TupColorButton *blue = new TupColorButton(5, tr("Blue"), blueBrush, cellSize, buttonParams);
    connect(blue, &TupColorButton::clicked, this, &TupColorButtonPanel::updateSelection);
    k->baseColors << blue;

    TImageButton *settings = new TImageButton(QPixmap(THEME_DIR + "icons/settings.png"), 22, this, true);
    settings->setToolTip(tr("Customize Colors Bar"));
    connect(settings, SIGNAL(clicked()), this, SLOT(customizeColors()));

    TImageButton *reset = new TImageButton(QPixmap(THEME_DIR + "icons/reset_color_bar.png"), 22, this, true);
    reset->setToolTip(tr("Reset Colors Bar"));
    connect(reset, SIGNAL(clicked()), this, SLOT(resetColors()));

    QBoxLayout *bottomLayout = new QHBoxLayout(this);
    bottomLayout->setAlignment(Qt::AlignHCenter);
    bottomLayout->setContentsMargins(3, 5, 3, 3);

    bottomLayout->setSpacing(spacing);

    bottomLayout->addWidget(k->trans);
    bottomLayout->addWidget(black);
    bottomLayout->addWidget(white);
    bottomLayout->addWidget(red);
    bottomLayout->addWidget(green);
    bottomLayout->addWidget(blue);
    bottomLayout->addWidget(settings);
    bottomLayout->addWidget(reset);
}

TupColorButtonPanel::~TupColorButtonPanel()
{
}

void TupColorButtonPanel::updateSelection(int index)
{
    if (index != k->currentColorIndex) {
        if (k->currentColorIndex >= 0) {
            TupColorButton *button = (TupColorButton *) k->baseColors.at(k->currentColorIndex);
            button->setState(false);
        }

        TupColorButton *selection = (TupColorButton *) k->baseColors.at(index);
        QColor color = selection->color();
        k->currentColorIndex = index;

        emit clickColor(color);
    }
}

void TupColorButtonPanel::setState(int index, bool isSelected)
{
    if (index != k->currentColorIndex && k->currentColorIndex >= 0) {
        TupColorButton *button = (TupColorButton *) k->baseColors.at(k->currentColorIndex);
        button->setState(isSelected);
    }
}

void TupColorButtonPanel::resetPanel()
{
    if (k->currentColorIndex >= 0) {
        TupColorButton *button = (TupColorButton *) k->baseColors.at(k->currentColorIndex);
        button->setState(false);
        k->currentColorIndex = -1; 
    }
}

void TupColorButtonPanel::enableTransparentColor(bool flag)
{
    k->trans->setVisible(flag);
}

void TupColorButtonPanel::customizeColors()
{
    TupColorButton *button;

    if (k->currentColorIndex == -1) {
        button = k->trans;
        button->setState(true);
        k->currentColorIndex = 0;
    } else {
        button = (TupColorButton *) k->baseColors.at(k->currentColorIndex);
    }

    QColor color = QColorDialog::getColor(button->color(), this);
    if (color.isValid()) {
        button->setBrush(QBrush(color));
        QString index = QString::number(k->currentColorIndex);
        TCONFIG->beginGroup("ColorPalette");
        TCONFIG->setValue("BarColor" + index, color.name());
        TCONFIG->sync();

        emit clickColor(color);
    }
}

void TupColorButtonPanel::resetColors()
{
    foreach(TupColorButton *button, k->baseColors) {    
        button->setState(false);
        int index = button->index();
        QString number = QString::number(index);

        if (index == 0) {
            button->setBrush(QBrush(Qt::transparent));
            TCONFIG->beginGroup("ColorPalette");
            TCONFIG->setValue("BarColor" + number, "transparent");
        }

        if (index == 1) {
            button->setBrush(QBrush(Qt::black));
            TCONFIG->beginGroup("ColorPalette");
            TCONFIG->setValue("BarColor" + number, "#000");
        }

        if (index == 2) {
            button->setBrush(QBrush(Qt::white));
            TCONFIG->beginGroup("ColorPalette");
            TCONFIG->setValue("BarColor" + number, "#fff");
        }

        if (index == 3) {
            button->setBrush(QBrush(Qt::red));
            TCONFIG->beginGroup("ColorPalette");
            TCONFIG->setValue("BarColor" + number, "#f00");
        }

        if (index == 4) {
            button->setBrush(QBrush(Qt::green));
            TCONFIG->beginGroup("ColorPalette");
            TCONFIG->setValue("BarColor" + number, "#0f0");
        }

        if (index == 5) {
            button->setBrush(QBrush(Qt::blue));
            TCONFIG->beginGroup("ColorPalette");
            TCONFIG->setValue("BarColor" + number, "#00f");
        }
    }

    TCONFIG->sync();
}
