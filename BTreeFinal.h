#ifndef BTREEFINAL_H
#define BTREEFINAL_H

#include <iostream>

/*==============================================================================
Authoren    : Ivonne Kneißig, Ramon Günther, Jana Bellmann
Datum       : v 1.7 29.11.2020
Description : Implementierung BTree (2-3-4 Bäume)
==============================================================================*/

/*******************************************************************************
                            Klasse Error
********************************************************************************
Für Fehlermeldungen
*/

class Error{
  public:
    Error(int a){
      nr=a;
    }
    void melde_fehler(){
      switch(nr){
        case 1:
        std::cerr<<"Fehler: Parameter darf nicht negativ sein\n\n";
        break;

        case 2:
        std::cerr<<"Fehler: Negativer Index\n\n";
        break;

        case 3:
        std::cerr<<"Fehler: null\n\n";
        break;

        default:
        std::cerr<<"Exception: Unbekannter Fehler bitte kontaktieren sie uns";
        break;
      }
    }
  private:
    int nr; //fehler nummer;
};

/*******************************************************************************
                            Klasse BTreeNode
********************************************************************************
Die Klasse BTreeNode stellt die Datenstruktur für einen Knoten des 2-3-4 Baumes
dar.
*/

class BTreeNode{
  private:
    bool blatt;                                                       // gibt an ob Knoten = Blatt oder nicht
    BTreeNode **C;                                                    // Array, dass Zeiger auf die Nachfolger enthält
    int *keys;                                                        // Array, dass die aktuellen Werte im Knoten enthält
    int n;                                                            // aktuelle Anzahl der Werte im Knoten
    int t;                                                            // Grad des Knotens zur Berechnung der Anzahl der maximalen Werte und Nachfolger
  public:
    BTreeNode(int _t,bool blatt_);                                    // Konstruktor
    void insertNonFull(int k);                                        // Insert eines neuen Key in einen noch nicht vollen Knoten
    void splitChild(BTreeNode *y, int i);                             // Spaltet Knoten auf, falls bereits voll
    BTreeNode *search(int k);                                         // Sucht nach einem bestimmten Wert im Baum
    BTreeNode *testSearch(int k, int *a);
    void BTree_Print();                                               // Gibt den Baum auf der Konsole aus
    void delete_all();
    int getN();
    BTreeNode *getKnot(int n);
    int *getKeys();
    bool getBlatt();
    friend class BTree;                                               // Klasse BTree für die Wurzel des Baumes
};

/*******************************************************************************
                              Klasse BTree
********************************************************************************
Die Klasse BTree stellt die Wurzel des 2-3-4 Baumes dar*/


class BTree{

  private:
    BTreeNode *wurzel;                                                // Wurzel des Baumes
    int t;                                                            // Grad des Baumes

  public:
    BTree(int _t);
    BTree();
    BTreeNode *operator[](int x);//Überladung für search
    void delete_all(){
      /*wurzel->delete_all();
      delete wurzel;
      cout<<"Wurzel wurde gelöscht";*/
    }
    BTreeNode *getWurzel();
    void insert(int k);
    void BTree_Print(); //existiert auch in BTreeNode
    BTreeNode* search(int k); //existiert auch in BTreeNode
    BTreeNode* testSearch(int k , int *a);
    BTree newTree(BTree tree, int keyAnzahl);
    BTree newRandomTree(BTree tree, int keyAnzahl);
    void TreePrint();
    BTree example_3(BTree tree);

};

#endif // BTREEFINAL_H
