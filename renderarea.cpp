#include "renderarea.h"
#include <QPainter>
#include <string>
#include <QTimeLine>
#include <QGraphicsSceneWheelEvent>
#include <QGraphicsLineItem>
#include <QStyleOptionGraphicsItem>
#include <QApplication>
#include <iostream>

/**
 * @brief Knostruktor zum Erstellen der Zeichenplatte.
 * @param deltaX
 *          Verschiebung auf X-Achse.
 * @param deltaY
 *          Verschiebung auf Y-Achse.
 * @param parent
 *          Obereres Zeichenobjekt.
 */
RenderArea::RenderArea(int deltaX, int deltaY, QWidget *parent) : QGraphicsScene(parent)
{
    this->deltaX = deltaX;
    this->deltaY = deltaY;

    setSceneRect(0, 0, 200, 200);

    view = new QGraphicsView(this);
    view->setDragMode(QGraphicsView::ScrollHandDrag);
    view->setRenderHint(QPainter::Antialiasing);
}

/**
 * @brief Event-Methode beim Drehen des Mausrades
 * @param event
 *          Mausrad-Event
 */
void RenderArea::wheelEvent(QGraphicsSceneWheelEvent *event){
    if(QApplication::keyboardModifiers().testFlag(Qt::ControlModifier)){
        view->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

        if(event->delta() > 0 && currentScale < scaleMax) {
            view->scale(scaleFactor, scaleFactor);
            currentScale *= scaleFactor;
        } else if (event->delta() < 0 && currentScale > scaleMin) {
            view->scale(1 / scaleFactor, 1 / scaleFactor);
            currentScale /= scaleFactor;
        }
    }
}

/**
 * @brief Methode zum Hinzufügen eines Knotens
 *  Fügt wenn vorhanden die entsprechenden Linien hinzu.
 * @param knot
 *          KnotPos-Objekt mit den eingespeicherten Attributen des Knotens.
 */
void RenderArea::addKnot(knotpos *knot){
    if(knot == nullptr)
        throw "Der übergebene Knoten darf nicht 'null' sein!";

    QBrush bC(brush);
    if(knot->getColor() != nullptr)
        bC.setColor((*knot->getColor()));
    else
        bC = brush;

    QAbstractGraphicsShapeItem *qE = nullptr;
    if(knot->getSquare())
        qE = addRect(knot->getX(),knot->getY(),knot->getSize()*2 + knot->getXAdd(),knot->getSize()*2, pen, bC);
    else
        qE = addEllipse(knot->getX(),knot->getY(),knot->getSize()*2 + knot->getXAdd(),knot->getSize()*2, pen, bC);
    qE->setZValue(zCircle);

    double d = 40.0 / knot->getSize();

    QFont f("Calibri");
    f.setWeight(QFont::Bold);
    f.setPointSize(18.0 / d);

    QString string;
    if(knot->getValueN() != -1){
        string = QString::number(knot ->getValues()[0]);
        for(int i = 1; i < knot->getValueN(); i++){
            string = string + ", " + QString::number(knot ->getValues()[i]);
        }
    } else {
        string = QString::number(knot ->getValue());
    }

    QGraphicsTextItem *text = addText(string, f);
    text->setPos(knot->getSize() + knot->getXAdd() / 2 - QFontMetrics(f).size(Qt::TextSingleLine, string).width() / 2 + knot->getX() - 4,
                 knot->getSize() - QFontMetrics(f).size(Qt::TextSingleLine, string).height() / 2 + knot->getY() - 4);
    text->setZValue(zFont);

    if(knot->getParent() != nullptr){
        drawLine(knot, knot->getParent());
    } else {
        if(knot->getLeft() != nullptr)
            drawLine(knot, knot->getLeft());
        if(knot->getRight() != nullptr)
            drawLine(knot, knot->getRight());
    }

    if(knot->getX() + knot->getSize()*2 + deltaX > width())
        setSceneRect(0, 0, knot->getX()+knot->getSize()*2 + deltaX, height());
    if(knot->getY() + knot->getSize()*2 + deltaY > height())
        setSceneRect(0, 0, width(), knot->getY()+knot->getSize()*2 + deltaY);
    update();
}

/**
 * @brief Methode zum Hinzufügen einer Linie.
 * @param pos1
 *          KnotPos-Objekt mit den eingespeicherten Attributen des 1. Knotens.
 * @param pos2
 *          KnotPos-Objekt mit den eingespeicherten Attributen des 2. Knotens.
 */
void RenderArea::drawLine(knotpos *pos1, knotpos *pos2){
    if(pos1 == nullptr || pos2 == nullptr)
        throw "Keiner der übergebenen Knoten darf 'null' sein!";

    QGraphicsLineItem *qL = addLine(pos1->getX() + pos1->getSize() + pos1->getXAdd() / 2,
                     pos1->getY() + pos1->getSize(),
                     pos2->getX() + pos2->getSize()+ pos2->getXAdd() / 2,
                     pos2->getY() + pos2->getSize());
    qL->setZValue(zLine);
}


/**
 * @brief Setter-Methode für einen veränderten Stift.
 * @param pen
 *          Übergebener neuer Stift
 */
void RenderArea::setPen(const QPen &pen)
{
    this->pen = pen;
    update();
}

/**
 * @brief Setter-Methode für einen veränderten Brush.
 * @param brush
 *          Übergebener neuer Brush
 */
void RenderArea::setBrush(const QBrush &brush)
{
    this->brush = brush;
    update();
}

