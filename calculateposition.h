#ifndef CALCULATEPOSITION_H
#define CALCULATEPOSITION_H

#include "tree.h"
#include "knotpos.h"
#include "renderarea.h"
#include "showknot.h"
#include "BTreeFinal.h"

/**
 * @brief Klasse zum Berechnen der Positionen.
 */
class calculateposition
{
public:
    calculateposition();
    static knotpos *positionen_eintragen(struct TreeNode* tree,int delta_x, int delta_y, RenderArea* renderArea);               //öffentliche Aufruf Funktion
    static knotpos *positionen_eintragen(BTreeNode* tree,int delta_x, int delta_y, RenderArea* renderArea);                     //öffentliche Aufruf Funktion
private:
    static knotpos *positionen_berechnen(struct TreeNode* tree, int *konstanten, int tiefe, int atm_x, RenderArea* renderArea); //Erstellung der Knoten mit Positionen
    static knotpos *positionen_berechnen(BTreeNode* tree, int *konstanten, int tiefe, RenderArea* renderArea);       //Erstellung der Knoten mit Positionen
    static int letzte_breite(knotpos* lead);                                                                                    //berechnung letzter y position
    static int dynamische_groesse(int tiefe, int size);                                                                         //Berechnung der Größe abhängig von der Tiefe
};

#endif // CALCULATEPOSITION_H
