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

#include "tcontrolnode.h"
#include "tnodegroup.h"

struct TControlNode::Private
{
    int index;
    QGraphicsItem *graphicParent;
    TControlNode *centralNode;
    TControlNode *leftNode;
    TControlNode *rightNode;
    bool unchanged;
    TNodeGroup *nodeGroup;
    QGraphicsScene *scene;
};

TControlNode::TControlNode(int index, TNodeGroup *nodeGroup, const QPointF & pos, 
                           QGraphicsItem *graphicParent, QGraphicsScene *scene, int level) : 
                           QGraphicsItem(), k(new Private)
                           // QGraphicsItem(0, scene), k(new Private)
{
    k->index  = index;
    k->graphicParent = 0;
    k->leftNode = 0;
    k->rightNode = 0;
    k->centralNode = 0;
    k->unchanged = true;
    k->nodeGroup = nodeGroup;
    k->scene = scene;
    
    QGraphicsItem::setCursor(QCursor(Qt::PointingHandCursor));
    setFlag(ItemIsSelectable, true);
    setFlag(ItemIsMovable, true);
    setFlag(ItemSendsGeometryChanges, true);
    setPos(pos);

    setZValue(level);
    setGraphicParent(graphicParent);
}

TControlNode::~TControlNode()
{    
}

void TControlNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *w)
{
    Q_UNUSED(option);
    Q_UNUSED(w);
    
    // SQA: Check Antialiasing management for this painter
    // bool antialiasing = painter->renderHints() & QPainter::Antialiasing;
    // painter->setRenderHint(QPainter::Antialiasing, antialiasing);

    QColor color;

    if (k->centralNode) {
        color = QColor("white");
    } else {
        color = QColor(55, 155, 55);
        color.setAlpha(200);
    }

    painter->setBrush(color);
    paintLinesToChildNodes(painter);
    painter->drawRoundRect(boundingRect());
}

void TControlNode::paintLinesToChildNodes(QPainter *painter)
{
    QMatrix inverted = sceneMatrix().inverted();
    painter->save();
    
    painter->setPen(QPen(QColor(Qt::gray)));
    painter->setRenderHint(QPainter::Antialiasing, true);

    if (k->rightNode) {
        if (k->rightNode->isVisible())
            painter->drawLine(inverted.map(pos()), inverted.map(k->rightNode->pos()));
    }

    if (k->leftNode) {
        if (k->leftNode->isVisible())
            painter->drawLine(inverted.map(pos()), inverted.map(k->leftNode->pos()));
    }
    
    painter->restore();
}

QRectF TControlNode::boundingRect() const
{
    QSizeF size(10, 10);
    QRectF rect(QPointF(-size.width()/2, -size.height()/2), size);

    if (k->rightNode) {
        if (k->rightNode->isVisible())
            rect = rect.united(k->rightNode->boundingRect());
    }

    if (k->leftNode) {
        if (k->leftNode->isVisible())
           rect = rect.united(k->leftNode->boundingRect());
    }

    return rect;
}

QVariant TControlNode::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionChange) {
        if (!k->unchanged) {
            if (qgraphicsitem_cast<QGraphicsPathItem*>(k->graphicParent)) {
                QPointF diff = value.toPointF() - pos();
                if (k->leftNode)
                    k->leftNode->moveBy(diff.x(), diff.y());

                if (k->rightNode)
                    k->rightNode->moveBy(diff.x(), diff.y());

                QPointF scenePos = k->graphicParent->mapFromScene(value.toPointF());

                if (k->nodeGroup)
                    k->nodeGroup->moveElementTo(k->index, scenePos);
           } 
        } else {
           k->unchanged = false;
        }
    } else if (change == QGraphicsItem::ItemSelectedChange) {
               if (value.toBool()) {
                   k->graphicParent->setSelected(true);
                   showChildNodes(true);
               } else {
                   if (k->leftNode) {
                       if (k->leftNode->isSelected())
                           k->leftNode->setVisible(true);
                       else
                           k->leftNode->setVisible(false);
                   }

                   if (k->rightNode) {
                       if (k->rightNode->isSelected())
                           k->rightNode->setVisible(true);
                       else
                           k->rightNode->setVisible(false);
                   }
                   update();
               }
    }

    return QGraphicsItem::itemChange(change, value);
}

void TControlNode::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (k->centralNode) {
        setSelected(true);
        k->centralNode->setSelected(true);

        if (k->centralNode->left()) {
            if (k->centralNode->left() != this)
                k->centralNode->left()->setSelected(false);
        }

        if (k->centralNode->right()) {
            if (k->centralNode->right() != this)
                k->centralNode->right()->setSelected(false);
        }

    } else {
        setSeletedChilds(false);
    }

    k->graphicParent->setSelected(true);
    showChildNodes(true);
  
    // These instructions are required for painting updates
    QGraphicsItem::mousePressEvent(event); 
    event->accept();

    // SQA: Possible code for the future
    // k->nodeGroup->emitNodeClicked(Pressed);
}

void TControlNode::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    #ifdef TUP_DEBUG
        #ifdef Q_OS_WIN
            qDebug() << "[TControlNode::mouseReleaseEvent()]";
        #else
           T_FUNCINFO;
        #endif
    #endif

    Q_UNUSED(event);

    k->nodeGroup->emitNodeClicked(Released);

    // SQA: Why this instruction makes the system crash in Qt 4.7? 
    // QGraphicsItem::mouseReleaseEvent(event);
    // event->accept();
}

void TControlNode::mouseMoveEvent(QGraphicsSceneMouseEvent * event)
{
    /* SQA: Check if this code is required for other features than Position tween
    foreach (QGraphicsItem *item, scene()->selectedItems()) {
             if (qgraphicsitem_cast<TControlNode*>(item)) {
                 if (!k->centralNode) { 
                     if (item != this)
                         item->moveBy(event->pos().x(), event->pos().y());
                 }
             } 
    }
    */

    setPos(event->scenePos());
    event->accept();
}

void TControlNode::setLeft(TControlNode *left)
{
    if (k->leftNode)
        delete k->leftNode;

    k->leftNode = left;
    k->leftNode->setVisible(false);
    k->leftNode->setCentralNode(this);
    k->leftNode->setZValue(zValue()+1);
}

void TControlNode::setRight(TControlNode *right)
{
    if (right)
        delete k->rightNode;

    k->rightNode = right;
    k->rightNode->setVisible(false);
    k->rightNode->setCentralNode(this);
    k->rightNode->setZValue(zValue()+2);
}

void TControlNode::setCentralNode(TControlNode *centralNode)
{
    k->centralNode = centralNode;
}

void TControlNode::showChildNodes(bool visible)
{
    if (k->leftNode)
        k->leftNode->setVisible(visible);

    if (k->rightNode)
        k->rightNode->setVisible(visible);
}

void TControlNode::setSeletedChilds(bool select)
{
    if (k->leftNode)
        k->leftNode->setSelected(select);

    if (k->rightNode)
        k->rightNode->setSelected(select);
}

TControlNode *TControlNode::left()
{
    return k->leftNode;
}

TControlNode *TControlNode::right()
{
    return k->rightNode;
}

TControlNode *TControlNode::centralNode()
{
    return k->centralNode;
}

int TControlNode::index() const
{
    return k->index;
}

void TControlNode::setGraphicParent(QGraphicsItem *newParent)
{
    k->graphicParent = newParent;
}

QGraphicsItem * TControlNode::graphicParent()
{
    return k->graphicParent;
}

void TControlNode::hasChanged(bool unchanged)
{
    k->unchanged = unchanged;
}

void TControlNode::resize(qreal factor)
{
    setScale(factor);
}
