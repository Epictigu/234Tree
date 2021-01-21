#include "showknot.h"
#include "tree.h"
#include <cstdlib>
#include <iostream>
#include "rbtree.h"

#include <QApplication>

BTree *example_3()
{
  BTree *test = new BTree;
  test->insert(1);
  test->insert(5);
  test->insert(20);
  test->insert(9);
  test->insert(8);
  test->insert(22);
  test->insert(19);
  test->insert(29);
  test->insert(7);
  test->insert(4);
  test->insert(14);
  test->insert(24);
  test->insert(18);
  test->insert(3);
  test->insert(11);
  test->insert(10);
  test->insert(17);
  test->insert(21);
  test->insert(2);
  test->insert(15);
  return test;
}

/**
 * @brief Startfunktion zum Erstellen eines zufällligen Baums und Anzeigen über ShowKnot::Display.
 *      Programmparameter sind optional, können aber bei Bedarf für einen modifizierten Zufallsbaum verwendet werden.
 *      Parameter:
 *      1. Maximale Anzahl an Knoten
 *      2. Mindestwert der Knoten
 *      3. Maximalwert der Knoten
 *      Die Startfunktion ist nur ein Beispiel und sollte natürlich durch den eigenen Code ausgewechselt werden.
 * @param argc - Anzahl der Parameter
 * @param argv - Liste der Parameter
 * @return Programmablauf
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    struct TreeNode* tree = NULL;
    srand (time(NULL));

    int x = 10;         //anzahl
    int rMi = 0;        //rand min
    int rMa = 100;      //rand max

    int t = 0;

    cout << argc << endl;

    if(argc > 1){
        t = atoi(argv[1]); if (t < 0 || t > 2) t = 0;
        if(argc > 2){
            x = atoi(argv[2]); if (x < 0) x = 10;
            if(argc > 3){
                rMi = atoi(argv[3]); if(rMi == 0) rMi = 0;
                if(argc > 4){
                   rMa = atoi(argv[4]); if(rMa == 0) rMa = 100; rMa -= rMi;
                }
            }
        } else {
            if(t == 2) x = 3;
        }
    }

    cout << rMi << " - " << rMa << " | " << x << endl;
    if(rMa < rMi || rMa <= 0 || rMi < 0 || x < 0){
        return -1;
    }

    if(t == 0){
        for (int i = 0; i < x; i++) {
            int random = (rand() % (rMa + 1)) + rMi;
            tree = tree::TreeInsert(tree, random, "Info zu Schluessel " + std::to_string(random));
        }

        ShowKnot::display(tree);
    } else if(t == 1){
        BTree *baum = example_3();
        baum->BTree_Print();
        ShowKnot::display(baum->getWurzel());
    } else if(t == 2){
        RedBlackTree tree1;

        tree1.TreeExampleFullLevelN(x);
        tree1.treePrint1();

        ShowKnot::display(tree1.getWurzel(), tree1.getNil());
    }

    return a.exec();
}
