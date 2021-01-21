#include "calculateposition.h"
#include <iostream>
#include "rbtree.h"

int xAdd = 0;

/**
 * @brief Methode zum Eintragen der Positionen.
 * @param tree
 *          Übergebener Baum
 * @param delta_x
 *          deltaX zur Verschiebung
 * @param delta_y
 *          deltaY zur Verschiebung
 * @param size
 *          Knotengröße
 * @param renderArea
 *          Zeichenobjekt
 * @return Startknoten
 */
knotpos* calculateposition::positionen_eintragen(struct TreeNode* tree,int delta_x, int delta_y, RenderArea* renderArea){
    int *konstanten = prepTree(delta_x, delta_y, renderArea);

    knotpos* start =nullptr;
    start = positionen_berechnen(tree, konstanten, 0, 1, renderArea);
    renderArea->addKnot(start);
    return start;
}


/**
 * @brief Methode zum Eintragen der Positionen eines 234 Baumes.
 * @param tree
 *          Übergebener Baum
 * @param delta_x
 *          deltaX zur Verschiebung
 * @param delta_y
 *          deltaY zur Verschiebung
 * @param size
 *          Knotengröße
 * @param renderArea
 *          Zeichenobjekt
 * @return Startknoten
 */
knotpos* calculateposition::positionen_eintragen(BTreeNode* tree,int delta_x, int delta_y, RenderArea* renderArea){
    int *konstanten = prepTree(delta_x, delta_y, renderArea);

    knotpos* start =nullptr;
    xAdd=konstanten[0];
    start = positionen_berechnen(tree, konstanten, 1, renderArea);
    renderArea->addKnot(start);
    return start;
}


/**
 * @brief Methode zum Eintragen der Positionen eines RB  Baumes.
 * @param tree
 *          Übergebener Baum
 * @param delta_x
 *          deltaX zur Verschiebung
 * @param delta_y
 *          deltaY zur Verschiebung
 * @param size
 *          Knotengröße
 * @param renderArea
 *          Zeichenobjekt
 * @return Startknoten
 */
knotpos* calculateposition::positionen_eintragen(struct RBTreeNode* tree,int delta_x, int delta_y, RenderArea* renderArea, struct RBTreeNode* nil){
    int *konstanten = prepTree(delta_x, delta_y, renderArea);

    knotpos* start =nullptr;
    start = positionen_berechnen(tree, konstanten, 0, 1, renderArea, nil);
    renderArea->addKnot(start);
    return start;
}



/**
 * @brief Methode zum Berechnen und Erstellen eines einfachen Knotens.
 *          Benutzt wird dafür eine exakte Version des gegebenen
 *          TreeNode Structs.
 * @param tree
 *          Übergebener Baum
 * @param konstanten
 *          optische konstante Werte zusammengefasst im array
 * @param atm
 *          die übergabe der actuellen positionen
 * @param tiefe
 *          die Stufe des Knotens
 * @param renderArea
 *          Zeichenobjekt
 * @return  position actueller Knoten
 *
 */
knotpos* calculateposition::positionen_berechnen(struct TreeNode* tree, int *konstanten, int atm, int tiefe, RenderArea* renderArea){
    knotpos *PosRight = nullptr, *PosLeft = nullptr;

    TreeNode* halter = tree->left;
    if(halter != nullptr){
        PosLeft = positionen_berechnen(halter, konstanten, atm,  tiefe +1, renderArea);
    }

    if(PosLeft != nullptr) {atm = letzte_breite(PosLeft);}

    atm += konstanten[0];

    halter = tree->right;
    if(halter != nullptr){
       PosRight = positionen_berechnen(halter, konstanten, atm, tiefe +1, renderArea);
    }
    int dicke = dynamische_groesse(tiefe);
    knotpos *me = new knotpos(atm, (tiefe - 1) * konstanten[1] + konstanten[0], dicke, tree->key, PosLeft, PosRight);
    renderArea->addKnot(me);


    return me;
}


/**
 * @brief Methode zum Berechnen und Erstellen eines 234 Knotens.
 *          Benutzt wird dafür eine leicht modifizierte Version des gegebenen
 *          234 Baumes, da im Original einzelne Getter fehlen.
 * @param tree
 *          Übergebener Baum
 * @param konstanten
 *          optische konstante Werte zusammengefasst im array
 * @param atm
 *          die übergabe der actuellen positionen
 * @param tiefe
 *          die Stufe des Knotens
 * @param renderArea
 *          Zeichenobjekt
 * @return  position actueller Knoten
 *
 */
knotpos* calculateposition::positionen_berechnen(BTreeNode* tree, int *konstanten, int tiefe, RenderArea* renderArea){
    int gaps = 10;

    int n = tree->getN();
    knotpos** children = new knotpos*[n + 1];
    int half = (n + 1) / 2;
    if(tree->getBlatt() == false && n > 0){
        for(int i = 0; i < half; i++){
            children[i] = positionen_berechnen(tree->getKnot(i), konstanten, tiefe +1, renderArea);
            xAdd+=children[i]->getSize() * 2 + gaps + children[i]->getXAdd();
        }
    }

    int dicke = dynamische_groesse(tiefe);
    knotpos *me = new knotpos(xAdd, (tiefe - 1) * konstanten[1] + konstanten[0], dicke, tree->getKeys(), n);
    if(n > 1)
        me->setXAdd(dicke * (n - 1));

    if(tree->getBlatt() == false)
        if((n + 1) % 2 == 0)
            xAdd+=me->getSize() * 2 + gaps + me->getXAdd();

    if(tree->getBlatt() == false && n > 0){
        for(int i = half; i < n + 1; i++){
            children[i] = positionen_berechnen(tree->getKnot(i), konstanten, tiefe +1, renderArea);
            xAdd+=children[i]->getSize() * 2 + gaps + children[i]->getXAdd();
        }
    }

    if(tree->getBlatt() == false)
        if((n + 1) % 2 == 1)
            me->setX(children[(n + 1) / 2]->getX()- (
                        ((me->getSize() * 2
                        + me->getXAdd())
                        - (children[(n + 1) / 2]->getSize() * 2
                        + children[(n + 1) / 2]->getXAdd()))
                    / 2));

    if(tree->getBlatt() == false)
        for(int i = 0; i <= n; i++){
            renderArea->drawLine(children[i], me);
            children[i]->setParent(me);
        }

    delete[] children;
    renderArea->addKnot(me);

    return me;
}


/**
 * @brief Methode zum Berechnen und Erstellen eines Rot-Schwarz Knotens.
 *          Benutzt wird dafür eine leicht modifizierte Version des gegebenen
 *          Rot-Schwarz Baumes, da im Original einzelne Getter fehlen.
 * @param tree
 *          Übergebener Baum
 * @param konstanten
 *          optische konstante Werte zusammengefasst im array
 * @param atm
 *          die übergabe der actuellen positionen
 * @param tiefe
 *          die Stufe des Knotens
 * @param renderArea
 *          Zeichenobjekt
 * @return  position actueller Knoten
 *
 */
knotpos* calculateposition::positionen_berechnen(struct RBTreeNode* tree, int *konstanten, int atm, int tiefe, RenderArea* renderArea, struct RBTreeNode* nil){
    if(tree == nullptr)
        return nullptr;

    knotpos *PosRight = nullptr, *PosLeft = nullptr;

    RBTreeNode* halter = tree->left;
    if(halter != nullptr){
        PosLeft = positionen_berechnen(halter, konstanten, atm,  tiefe +1, renderArea, nil);
    }

    if(PosLeft != nullptr) {atm = letzte_breite(PosLeft);}

    atm += konstanten[0];

    halter = tree->right;
    if(halter != nullptr){
       PosRight = positionen_berechnen(halter, konstanten, atm, tiefe +1, renderArea, nil);
    }
    int dicke = dynamische_groesse(tiefe);

    int key = 0;
    bool nilK = false;
    if(tree != nil) key = tree->key;
    else nilK = true;

    knotpos *me = new knotpos(atm, (tiefe - 1) * konstanten[1] + konstanten[0], dicke, key, PosLeft, PosRight);
    if(tree->color == "BLACK"){
        me->setTextColor(new QColor(Qt::white));
        me->setColor(new QColor(Qt::black));
    } else if(tree->color == "RED"){
        me->setTextColor(new QColor(Qt::white));
        me->setColor(new QColor(Qt::red));
    }
    if(nilK) me->setNil();
    renderArea->addKnot(me);

    return me;
}



/**
 * @brief suche der letzten position links von der aktuellen
 * @param lead
 *          übergebener Knoten
 * @return
 */
int calculateposition::letzte_breite(knotpos* lead){
    int zaehler = lead->getX();
    if(lead->getRight() != nullptr){
        zaehler = letzte_breite(lead->getRight());
    }
    else return zaehler;

    return zaehler;
}



/**
 * @brief änderung der Knotengröße abhängig von der Tiefe
 * @param tiefe
 *          die Stufe des Knotens
 * @return
 */
int calculateposition::dynamische_groesse(int tiefe){

    int size = 65;
    //knoten darf nicht kleiner werden als 25
    if(size - (size/10 * tiefe) >= 25){
        return size - (size/10 * tiefe);
    }
    else
        return 25;
}

/**
 * @brief Methode zur Parameterüberprüfung und eintragen der Werte.
 * @param delta_x
 *          deltaX zur Verschiebung
 * @param delta_y
 *          deltaY zur Verschiebung
 * @param renderArea
 *          Zeichenobjekt
 * @return konstantenArray
 */
int *calculateposition::prepTree(int delta_x, int delta_y, RenderArea* renderArea){
    if(renderArea == nullptr)
    {
        throw invalid_argument("Die uebergebene RenderArea ist ein Nullpointer.");
    }
    if(delta_x < 1)
    {
        throw invalid_argument("Die uebergebene delta_x ist zu klein.");
    }
    if(delta_y < 50)
    {
        throw invalid_argument("Die uebergebene delta_y ist zu klein.");
    }

    int *konstanten = new int[3] {0};
    konstanten[0] = delta_x;
    konstanten[1] = delta_y;
    if(delta_x >= delta_y){konstanten[2] = delta_x /2 -10;}
    else{konstanten[2] = delta_y /2 -10;}
    return konstanten;
}

