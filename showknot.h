#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "renderarea.h"
#include "BTreeFinal.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ShowKnot; }
QT_END_NAMESPACE

/**
 * @brief Klasse zum erstellen eines Fensters zur Baumanzeige.
 *  Übergeben muss die Klasse ein Objekt vom Typ TreeNode bekommen.
 *  Der generelle Aufruf erfolgt über die static-Funktion display.
 */
class ShowKnot : public QMainWindow
{
    Q_OBJECT

public:
    ShowKnot(struct TreeNode* tree);
    ShowKnot(BTreeNode *tree);
    RenderArea* getRenderArea();

    static ShowKnot* display(struct TreeNode* tree);
    static ShowKnot* display(BTreeNode *tree);

private:
    void penChanged();
    void brushChanged();

    static const int deltaX = 100;              //deltaX zur Weitergabe an Graphics und Berechnung
    static const int deltaY = 150;              //deltaY zur Weitergabe an Graphics und Berechnung

    RenderArea *scene;                          //Grafische Darstellung des Baumes

};

#endif
