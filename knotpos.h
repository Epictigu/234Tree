#ifndef KNOTPOS_H
#define KNOTPOS_H

#include <QColor>

/**
 * @brief Klasse zum Speichern der Werte eines Knotens.
 */
class knotpos
{
public:
    knotpos(int x, int y, int size, int value);                                     //Konstruktor für Endknoten.
    knotpos(int x, int y, int size, int *value, int valueN);
    knotpos(int x, int y, int size, int value, knotpos *left, knotpos *right);      //Konstruktor für Knoten mit Nachbarn.

    /**
     * ---------------------------
     * Getter und Setter Methoden!
     * ---------------------------
     */

    int getX();
    int getY();
    int getSize();
    int getValue();
    int *getValues();
    int getValueN(){return valueN;}

    knotpos *getLeft();
    knotpos *getRight();
    knotpos *getParent(){return parent;}

    void setLeft(knotpos *k);
    void setRight(knotpos *k);

    void setSquare() {square = true;}
    void setColor(QColor *c) {color = c;}
    void setTextColor(QColor *c) {colorFont = c;}
    void setX(int x) {this->x = x;}
    void setXAdd(int xAdd) {this->xAdd = xAdd;}

    void setParent(knotpos *k);
    void setNil(){nil = true;}

    bool getSquare() {return square;}
    QColor *getColor() {return color;}
    QColor *getTextColor() {return colorFont;}
    int getXAdd(){return xAdd;}
    bool getNil(){return nil;}

    /**
     * ------------------------------------
     * Ende der Getter und Setter Methoden.
     * ------------------------------------
     */
private:
    int x;                                  //x-Position des Knotens
    int y;                                  //y-Position des Knotens
    int size;                               //Größe des Knotens
    int value = 0;                              //Textwert des Knotens
    int *values = nullptr;
    int valueN = -1;
    int xAdd = 0;

    QColor *color = nullptr;                //Optionale Knotenfarbe
    QColor *colorFont = nullptr;
    bool square = false;                    //Optionale Knotenform

    knotpos *leftK = nullptr;                         //Linker Knoten
    knotpos *rightK = nullptr;                        //Rechter Knoten

    knotpos *parent;

    bool nil = false;
};

#endif
