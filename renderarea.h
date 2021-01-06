#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QPen>
#include "knotpos.h"
#include <QGraphicsView>

using namespace std;

/**
 * @brief Klasse zum Anzeigen eines Baumes innerhalb einer QGraphicsScene.
 *  Die Ausgabe erfolgt über die Implementation des QGraphicsViews.
 *  Knotenübergabe erfolgt über KnotPos-Objekte.
 */
class RenderArea : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit RenderArea(int deltaX, int deltaY, QWidget *parent = nullptr);

    void setPen(const QPen &pen);
    void setBrush(const QBrush &brush);
    void addKnot(knotpos *knot);
    void drawLine(knotpos *pos1, knotpos *pos2);

    QGraphicsView *view;                                        //View für die Ausgabe

    static const int zFont = 2;                                 //Zeichenreihenfolge für die Schrift
    static const int zCircle = 1;                               //Zeichenreihenfolge für die Knoten
    static const int zLine = 0;                                 //Zeichenreihenfolge für die Linien

    constexpr static const double scaleFactor = 1.1;            //Zoomveränderungs-Faktor
    constexpr static const double scaleMin = .1;                //Minimaler Zoom-Faktor
    constexpr static const double scaleMax = 2.0;               //Maximaler Zoom-Faktor

protected:
    void wheelEvent(QGraphicsSceneWheelEvent *event) override;

private:
    double currentScale = 1.0;                                  //Momentaner Zoom
    int deltaX;                                                 //Verschiebung in x-Richtung
    int deltaY;                                                 //Verschiebung in y-Richtung

    QPen pen;                                                   //Pen mit gewünschten Zeichenattributen
    QBrush brush;                                               //Brush mit gewünschten Füllattributen
};

#endif
