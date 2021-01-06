// Struktur fuer binaere Suchbaume

#include <stdlib.h>
#include <iostream>
#include <string>
#include <time.h>
#include <math.h>
#include "tree.h"
using namespace std;


// Erzeuge einen neuen Knoten
struct TreeNode* tree::NewTreeNode(int key, string info) {
    struct TreeNode* node = new TreeNode();
    node->up = NULL;
    node->key = key;
    node->info = info;
    node->left = NULL;
    node->right = NULL;
    return(node);
}


// Erzeuge einen Beispielbaum (binaerer Suchbaum mit 5 Knoten)
// Schlechte Implementierung (ohne TreeInsert())
// Schlecht, denn je mehr Knoten im Baum sind, desto mehr Zeiger muessen (fehleranfaellig) von Hand gesetzt werden.
// Bis naechste Woche TreeInsert() bitte sauber implementieren, dann den unten auskommenierten Programmcode benutzen.
//struct TreeNode* TreeExample1() {
//    struct TreeNode* tree = NewTreeNode(40, "Info zu Schluessel 40");
//    tree->left = NewTreeNode(10, "Info zu Schluessel 10"); tree->left->up = tree;
//    tree->right = NewTreeNode(70, "Info zu Schluessel 70"); tree->right->up = tree;
//    tree->right->left = NewTreeNode(60, "Info zu Schluessel 60"); tree->right->left->up = tree->right;
//    tree->right->right = NewTreeNode(80, "Info zu Schluessel 80"); tree->right->right->up = tree->right;
//    return(tree);
//}

struct TreeNode* tree::TreeExample1() {
    struct TreeNode* tree = NULL;
    tree = tree::TreeInsert(tree, 40, "Info zu Schluessel 40");
    tree = tree::TreeInsert(tree, 10, "Info zu Schluessel 10");
    tree = tree::TreeInsert(tree, 70, "Info zu Schluessel 70");
    tree = tree::TreeInsert(tree, 60, "Info zu Schluessel 60");
    tree = tree::TreeInsert(tree, 80, "Info zu Schluessel 80");
    return(tree);
}





// Gib den Baum tree auf der Konsole aus, um 90 Grad nach links gedreht
// Rücke jede Zeile mit sovielen Tabs ein, wie in indentation angegeben
void tree::TreePrint(struct TreeNode* tree, int indentation) {
    int i;
    if (tree!=NULL) {
        TreePrint(tree->right, indentation+1);
        for (i=0;i <indentation; i++) {
            cout << "\t";
        }
    cout << "(key: " << tree->key << ", info: '" << tree->info << "')\n\n\n";
        TreePrint(tree->left, indentation+1);
    }
    return;
}


// Gib den Baum tree auf der Konsole aus, um 90 Grad nach links gedreht
void tree::TreePrint(struct TreeNode* tree) {
    cout << "\n\n";
    TreePrint(tree, 0);
}

// Fuege den Schluessel key mit Infoteil info in den binaeren Suchbaum tree ein
// Fuege den Schluessel key mit Infoteil info in den binaeren Suchbaum tree ein
struct TreeNode* tree::TreeInsert(struct TreeNode* tree, int key, string info) {
    // Einfuegen, wenn noch kein Knoten existiert
    if(tree == nullptr) {
        cout << "DEBUG (Insert): Lege ersten Knoten " << key << " an." << endl;
        tree = tree::NewTreeNode(key, info);
    }

    // Einfuegen, wenn bereits Knoten existieren

    else {

        // Pruefen, wo der Knoten eingefuegt werden soll
        // Ist der derzeit angeschaute Knoten..
        // ...groesser...
        if(tree->key > key) {
            // Schaue unten links...
            if(tree->left == nullptr) {
                // Lege Knoten an, falls noch kein Knoten existiert
                tree->left = tree::NewTreeNode(key, info);
                tree->left->up = tree;
                if(tree->up != nullptr) {
                    //cout << "DEBUG (Insert): Lege Knoten " << key << " links unter Knoten " << tree->up->key << " an." << endl;
                }
                else {
                    //cout << "DEBUG (Insert): Lege Knoten " << key << " links unter Wurzel " << tree->key << " an." << endl;
                }
            }

            else {
                TreeInsert(tree->left, key, info);
            }
        }

        // ...kleiner...
        else if(tree->key < key) {
            // Schaue unten rechts...
            if(tree->right == nullptr) {
                // Lege Knoten an, falls noch kein Knoten existiert
                tree->right = tree::NewTreeNode(key, info);
                tree->right->up = tree;
                if(tree->up != nullptr) {
                    //cout << "DEBUG (Insert): Lege Knoten " << key << " rechts unter Knoten " << tree->up->key << " an." << endl;
                }
                else {
                    //cout << "DEBUG (Insert): Lege Knoten " << key << " rechts unter Wurzel " << tree->key << " an." << endl;
                }
            }

            else {
                TreeInsert(tree->right, key, info);
            }

        }

        // oder existiert bereits ein Knoten mit gleichem Wert?
        else {
            //cout << "DEBUG (Insert): Knoten " << key << " existiert bereits." << endl;
        }
    }

    return tree; // Wurzel des Baums ausgeben
}



// Gib Zeiger auf den Knoten im binaeren Suchbaum tree zurueck, der den Schluessel key speichert
// Wenn der Schluessel nicht vorhanden ist soll NULL zurueckgegeben werden
struct TreeNode* tree::TreeSearch(struct TreeNode* tree, int key){
    if(tree->key == key){
        return tree;
    } else if(tree->key > key){
        TreeSearch(tree->left, key);
    } else if(tree->key < key){
        TreeSearch(tree->right, key);
    }
    return nullptr;
}
