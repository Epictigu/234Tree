#include<iostream>
#include<ctime>
#include<cmath>
#include<iomanip>
#include"BTreeFinal.h"
#include"showknot.h"

/*******************************************************************************
                            TO DO
*******************************************************************************/
// Alles fertig

using namespace std;
int RANDOMKEY = 50;

// ============================================================================
// Konstrukor der Klasse BTreeNode
// ============================================================================

BTreeNode::BTreeNode(int t_, bool blatt_)                               // Konstruktor
{
  if (t_ < 0)
  {
    throw Error(1);
  }
  t = t_;                                                               // Grad bestimmt die Anzahl der Schlüssel und Nachfolger
  blatt = blatt_;                                                       // Indikator um zu sehen ob es ein Blatt ist oder nicht
  keys = new int[2*t-1];                                                // Speicher Allokieren für Schlüssel
  C = new BTreeNode *[2*t];                                             // Speicher allokieren für Anzahl der möglichen Nachfolger
  n=0;                                                                  // aktuelle Anzahl der Schlüssel in dem Knoten
}

/*******************************************************************************
                           BTreeNode Methoden
*******************************************************************************/
void BTreeNode::delete_all(){
  //Idee: rekursiv ähnlich wie BTree_Print()?
}

// ============================================================================
// Einfügen eines Schlüssels in einen nicht vollen Knoten
// ============================================================================

// Diese Methode wird innerhalb der Insert-Methode aufgerufen, wenn der
// aktuelle Knoten nicht voll ist
// Parameter k = Wert der als Key gespeichert werden soll

void BTreeNode::insertNonFull(int k)
{
    // keine Parameterprüfungnotwendig, da k auch negativ sein darf!?

    int i = n-1;                                                         // Setzt i für die aktuell vorhandene Anzahl an Knoten (n-1, da index bei 0 anfängt zu zählen)

    if (blatt == true)                                                   // Wenn der Knoten noch keine Kinder hat
    {
        while (i >= 0 && k < keys[i])                                    // Ist der einzufügende Wert kleiner als an Knoten-Index i
        {
            keys[i+1] = keys[i];                                         // Wird der vorhandene Wert um einen Index nach hinten geschoben
            i--;                                                         // Fängt hinten im Array an nach hinten zu schieben
        }
        keys[i+1] = k;                                                   // Sobald der Key an Stelle i kleiner als k ist, kann k dahinter eingefügt werden
        n++;                                                             // Die Anzahl der aktuellen Knoten wird erhöht
    }
    else                                                                 // else tritt ein, wenn Blatt bereits Kinder hat
    {
        while (i >= 0 && k < keys[i])
        {
            i--;                                                         // Es wird die Stelle gesucht, an der k theoretisch eingefügt werden sollte
        }
        if (C[i+1]->n == 2*t-1)                                          // Wenn Kindknoten auch schon voll dann:
        {
            splitChild(C[i+1], i+1);                                     // Über splitChild wird der Knoten aufgespalten
            if (k > keys[i+1])                                             // i wird an die richtige Position in C gebracht
                i++;
        }
        C[i+1]->insertNonFull(k);                                        // ansonsten: k wird in den entsprechenden Kindknoten eingefügt
    }
}


// ============================================================================
// Knoten aufteilen
// ============================================================================

// Hilfsroutine für das Einfügen eines Knotens
// Ist der Knoten voll, in dem eigentlich eingefügt werden soll, dann muss dieser
// Knoten aufgespalten werden
// Parameter *y = Kindknoten an der entprechende Stelle vom Vaterknoten der
// abgespaltet / hochgeschoben wird
// Parameter i = Stelle an der der neue Kindknoten gemacht werden soll

void BTreeNode::splitChild(BTreeNode *y, int i)
{
    if(y == nullptr)
    {
      throw Error(3);
    }
    if (i < 0)
    {
      throw Error(2);
    }

    BTreeNode *z = new BTreeNode(y->t, y->blatt);                         // Neuer Knoten der Grad und Blattwert vom übergebenen Knoten erhält
    z->n = t - 1;                                                         // Setzt aktuelle Anzahl der Knoten auf Grad - 1

    for (int j = 0; j < t-1; j++)
    {
        z->keys[j] = y->keys[j+t];                                        // Der neuen Knoten erhält die keys die hinter dem key stehen der
    }                                                                     // hochgeschoben werden soll

    if (y->blatt == false)                                                // Wenn der übergebene Knoten bereits Kinder hat
    {
        for (int j = 0; j < t; j++)
            z->C[j] = y->C[j+t];                                          //
    }

    y->n = t - 1;                                                         // Da in y die überzähligen Knoten abgespaltet wurden,
                                                                          // Ist in y nur noch 1 Knoten vorhanden
    for (int j = n; j >= i+1; j--)                                        //
    {
        C[j+1] = C[j];                                                    // Kindknoten werden verschoben
    }

    C[i+1] = z;                                                           // Stelle an der der neue abgespaltete Knoten z steht

    for (int j = n-1; j >= i; j--)
    {
        keys[j+1] = keys[j];                                              //
    }

    keys[i] = y->keys[t-1];

    n++;
}


// ============================================================================
// Primitive Ausgabe des BTree
// ============================================================================

// Gibt den Baum in einer Baumstruktur aus. Hat ein Knoten mehrere Kindknoten,
// kann der Vaterknoten nicht so geprintet werden, dass man direkt sie, welche
// Knoten da mit drinstecken -> eine Zeile zwischen

void BTreeNode::BTree_Print()
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (blatt == false)
        {
            C[i]->BTree_Print();
            cout << "      ";
        }
        cout << keys[i];
        cout << endl;
    }
    if (blatt == false)
    {
        C[i]->BTree_Print();
        cout << "      ";
    }
}

int BTreeNode::getN()
{
    return n;
}

BTreeNode *BTreeNode::getKnot(int n)
{
    return C[n];
}

int *BTreeNode::getKeys()
{
    return keys;
}

bool BTreeNode::getBlatt(){
    return blatt;
}


// ============================================================================
// Nach einem Schlüssel im BTree suchen
// ============================================================================

// Sucht, ob ein gegebener Schlüssel in dem 2-3-4 Baum vorhanden ist
// Parameter k = gesuchter Schlüssel

BTreeNode *BTreeNode::search(int k)
{
    int i = 0;

    while (i < n && k > keys[i])                                        // solange k größer als der aktuelle Schlüssel ist
    {
        i++;                                                            // wird der Index um 1 erhöht
    }

    if (keys[i] == k)                                                   // Hat der aktuelle Index den gesuchten Wert
    {
      cout<<"\n\nDer Key "<< keys[i]<<" ist vorhanden!\n";              // Wird der Wert zurückgegeben
      return this;
    }

    if (blatt == true)                                                  // wurde der gesuchte Wert nicht gefunden und es gibt keine Kinder
    {                                                                   // zum weitersuchen
        cout<<"\n\nDer Key "<<k<<" ist nicht vorhanden!\n";
        return nullptr;                                                 // wird ein nullptr zurückgegeben
    }

    return C[i]->search(k);                                             // Sind Kinder vorhanden in denen gesucht werden kann,
}                                                                       // wird rekursiv erneut search aufgerufen

// ============================================================================
// Nach einem Schlüssel im BTree suchen mit Zählung der Schlüsselvergleiche
// ============================================================================

// Sucht, ob ein gegebener Schlüssel in dem 2-3-4 Baum vorhanden ist
// Parameter k = gesuchter Schlüssel
// Parameter array = Zählvariabel für die Schlüsselvergleiche

BTreeNode *BTreeNode::testSearch(int k, int *array)
{
  array[0]++;
  int i = 0;

  while (i < n && k > keys[i])                                        // solange k größer als der aktuelle Schlüssel ist
  {
      i++;                                                            // wird der Index um 1 erhöht
  }

  if (keys[i] == k)                                                   // Hat der aktuelle Index den gesuchten Wert
  {
    return this;
  }

  if (blatt == true)                                                  // wurde der gesuchte Wert nicht gefunden und es gibt keine Kinder
  {                                                                   // zum weitersuchen
      return nullptr;                                                 // wird ein nullptr zurückgegeben
  }

  return C[i]->testSearch(k,array);                                             // Sind Kinder vorhanden in denen gesucht werden kann,
}                                                                       // wird rekursiv erneut search aufgerufen


/*******************************************************************************
                              BTree Methoden
*******************************************************************************/

// ============================================================================
// Konstruktor mit Parameter
// ============================================================================

// Konstruktor dem ein gewünschter Grad übergeben kann
// Parameter _t = Grad des 2-3-4 Baumes

BTree::BTree(int _t)
{
  if (_t < 0)
  {
    throw Error(1);
  }

  wurzel = nullptr;
  t = _t;
}

// ============================================================================
// Default Konstruktor
// ============================================================================

// Konstruktor mit dem Default-Grad 2

BTree::BTree()
{
  wurzel = nullptr;
  t=2;
}

// ============================================================================
// Überladener Index Operator für Methode BTreeNode search()
// ============================================================================

// In [] kann hinter dem Objektnamen direkt der gesuchte Wert angegeben werden

BTreeNode *BTree :: operator[](int x)
{
  return wurzel->search(x);
}


// ============================================================================
// Methoden die  eigentilch in BTreeNode stattfinden
// ============================================================================

// Die Wurzel ist Teil von BTree durch den -> kann man auf die Methode von
// BTreeNode zugreifen die den gleichen Namen hat und die relevanten Variabeln.
// Dadurch lässt es sich über ein BTree Objekt in der Main dennoch aufrufen


void BTree::BTree_Print()
{
  if (wurzel != nullptr)
    wurzel->BTree_Print();                                               // Siehe BTree_Print von BTreeNode
  else
    cout<<"\nException!"<<endl;
  return;
}

BTreeNode *BTree::search(int k)
{
  return (wurzel == nullptr)? nullptr : wurzel->search(k);               //siehe oben
}


BTreeNode *BTree::testSearch(int key, int *array)
{
  return (wurzel == nullptr)? nullptr : wurzel->testSearch(key,array);               //siehe oben
}
// ============================================================================
// Die Hauptmethode um neue Schlüssel hinzuzufügen
// ============================================================================

void BTree::insert(int k)
{
    if (wurzel == nullptr)                                                // Wenn der Baum komplett leer ist
    {
        wurzel = new BTreeNode(t, true);                                  // Speicher allokieren für Wurzel
        wurzel->keys[0] = k;                                              // Schlüssel einfügen
        wurzel->n=1;                                                      // Anzahl der aktuellen Werte im Knoten erhöhen
    }
    else                                                                  // Wenn Knoten nicht leer ist
    {
        if (wurzel->n == 2*t-1)                                           // Wenn der Knoten voll ist
        {

            BTreeNode *s = new BTreeNode(t, false);                       // Speicher allokieren für neuen Knoten (Kind)

            s->C[0] = wurzel;                                             // Mache alte Wurzel zum Kind des neuen Knoten
            s->splitChild(wurzel, 0);                                     // Spalte den Knoten auf

            int i = 0;
            if (s->keys[0] < k)
                i++;
            s->C[i]->insertNonFull(k);                                    // Keys werden neu zugeordnet

            wurzel = s;

        }else                                                             // wenn Knoten nicht voll
            wurzel->insertNonFull(k);                                     // Key einfügen
    }
}

BTreeNode *BTree::getWurzel(){
    return wurzel;
}

// ============================================================================
// Methoden zum Erstellen eines BTrees mit aufsteigenden Key-Werten
// ============================================================================

// Der Methode wird eine gewünschte Schlüsselanzahl übergeben. Anhand dieser
// wird eine Schleife hochgezählt und der Index als Key in dem Baum eingefügt,
// bis die gegebene Key-Anzahl erreicht wurde. */

BTree newTree(BTree tree, int keyAnzahl)
{
  for (int i = 1; i<= keyAnzahl; i++)
  {
    tree.insert(i);
  }
  return tree;
}

// ============================================================================
// Methoden zum Erstellen eines BTrees mit zufälligen Key-Werten
// ============================================================================

// Der Methode wird eine gewünschte Schlüsselanzahl übergeben. Anhand dieser
// wird eine Schleife hochgezählt und mit jedem Schleifendurchlauf ein neuer
// Knoten hinzugefügt, der einen zufälligen Key-Wert enthält */

BTree newRandomTree(BTree tree, int keyAnzahl)
{
  srand(time(nullptr));
  for (int i = 0; i< keyAnzahl; i++)
  {
    int x = rand()%RANDOMKEY;
    tree.insert(x);
    cout << x << "\t";
  }
  cout << endl << endl;
  return tree;
}

/*******************************************************************************
                                Testbäume
*******************************************************************************/

BTree example_1(BTree test)
{
  test.insert(10);
  test.insert(20);
  test.insert(30);
  test.insert(40);
  test.insert(50);
  test.insert(60);
  test.insert(70);
  test.insert(80);
  test.insert(90);
  test.insert(100);

  return test;
}


BTree example_2(BTree test)
{

  test.insert(5);
  test.insert(10);
  test.insert(15);
  test.insert(20);
  test.insert(25);
  test.insert(30);
  test.insert(35);
  test.insert(40);
  test.insert(45);
  test.insert(50);
  test.insert(55);
  test.insert(60);
  test.insert(65);
  test.insert(70);
  test.insert(75);
  test.insert(80);
  test.insert(85);
  test.insert(90);
  test.insert(95);
  test.insert(100);
  test.insert(105);
  test.insert(110);
  test.insert(115);
  test.insert(120);
  return test;
}


void testi()
{
  BTree eins,zwei,drei,vier,fuenf,sechs,sieben,acht,neun,zehn,elf,zwoelf;
  int *array;
  array=new int [1];
  int summe[12];
  int k=0;
  array[0]=0;
  int knoten=1000;
  int j=0;
  cout<<"Knoten"<<"\t|   "<<"Anzahl"<<"\t|Durschnitt|"<<endl;
  cout<<"___________________________________"<<endl;
  while(j!=12){
    if(j==0)eins=newTree(eins,knoten);
    if(j==1)zwei=newTree(zwei,knoten);
    if(j==2)drei=newTree(drei,knoten);
    if(j==3)vier=newTree(vier,knoten);
    if(j==4)fuenf=newTree(fuenf,knoten);
    if(j==5)sechs=newTree(sechs,knoten);
    if(j==6)sieben=newTree(sieben,knoten);
    if(j==7)acht=newTree(acht,knoten);
    if(j==8)neun=newTree(neun,knoten);
    if(j==9)zehn=newTree(zehn,knoten);
    if(j==10)elf=newTree(elf,knoten);
    if(j==11)zwoelf=newTree(zwoelf,knoten);
    for(int i=0;i<=knoten;i++)
    {
     if(j==0)eins.testSearch(i,array);
     if(j==1)zwei.testSearch(i,array);
     if(j==2)drei.testSearch(i,array);
     if(j==3)vier.testSearch(i,array);
     if(j==4)fuenf.testSearch(i,array);
     if(j==5)sechs.testSearch(i,array);
     if(j==6)sieben.testSearch(i,array);
     if(j==7)acht.testSearch(i,array);
     if(j==8)neun.testSearch(i,array);
     if(j==9)zehn.testSearch(i,array);
     if(j==10)elf.testSearch(i,array);
     if(j==11)zwoelf.testSearch(i,array);
    }
    summe[k]=array[0]/knoten;
    j++;
    cout<<setw(8)<<left<<knoten<<"|\t"<<setw(8)<<right<<array[0]<<"|\t"<<setw(3)<<summe[k]<<"|"<<endl;
    k++;
    array[0]=0;
    if(j==1)knoten=3000;
    if(j==2)knoten=10000;
    if(j==3)knoten=30000;
    if(j==4)knoten=100000;
    if(j==5)knoten=300000;
    if(j==6)knoten=pow(2,10);
    if(j==7)knoten=pow(2,12);
    if(j==8)knoten=pow(2,14);
    if(j==9)knoten=pow(2,16);
    if(j==10)knoten=pow(2,18);
    if(j==11)knoten=pow(2,20);
  }
}


/*******************************************************************************
                                    Main
*******************************************************************************/

