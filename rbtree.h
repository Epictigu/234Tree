#ifndef RBTREE_H
#define RBTREE_H

#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <math.h>

using namespace std;

/**
 * Struktur für TreeNode
 */
struct RBTreeNode {
    RBTreeNode* up;       //Parent
    int key;            //key
    RBTreeNode* left;     //Linker Teilbaum
    RBTreeNode* right;    //Rechter Teilbaum
    string color;       //Farbe rot oder schwarz
};

typedef RBTreeNode *Nodeptr;      //Pointer auf TreeNode

/**
 * RedBlackTree Klasse
 */
class RedBlackTree
{
private:
    Nodeptr root;           //Wurzel
    Nodeptr nil;            //NIL zeigt auf Wurzel
    int count;              //Zum Zählen der Schlüsselvergleiche in TreeSearch()

    /**
     * Erstellt einen neuen Knoten.
     * @param node
     * @param up
     */
    void newTreeNode(Nodeptr node, Nodeptr up)
    {
        node->up = up;
        node->key = 0;
        node->left = nullptr;
        node->right = nullptr;
        node->color = "BLACK";
    }

    /**
     * Wird nach TreeInsert aufgerufen.
     * TreeInsertFixRB ist da, um Verletztungen der Eigenschaften von RB Bäumen, die in TreeInsert verursacht werden können, wiederherzustellen.
     * 3 Fälle die auftreten können:
     * 1: node's Onkel y ist rot,
     * 2: y ist schwarz und node ein rechtes Kind,
     * 3: y ist schwarz und node ein linkes Kind.
     * @param node
     */
    void treeInsertFixRB(Nodeptr node)
    {
        Nodeptr y;

        while(node->up->color == "RED")
        {
            if(node->up == node->up->up->right)
            {
                y = node->up->up->left;
                if(y->color == "RED")                   //Fall 1
                {
                    node->up->color = "BLACK";
                    y->color = "BLACK";
                    node->up->up->color = "RED";
                    node = node->up->up;
                }
                else
                {
                    if(node == node->up->left)          //Fall 2
                    {
                        node = node->up;
                        treeRightRotate(node);
                    }
                    node->up->color = "BLACK";          //Fall 3
                    node->up->up->color = "RED";
                    treeLeftRotate(node->up->up);
                }
            }
            else
            {
                y = node->up->up->right;
                if(y->color == "RED")
                {
                    node->up->color = "BLACK";
                    y->color = "BLACK";
                    node->up->up->color = "RED";
                    node = node->up->up;
                }
                else
                {
                    if(node == node->up->right)
                    {
                        node = node->up;
                        treeLeftRotate(node);
                    }
                    node->up->color = "BLACK";
                    node->up->up->color = "RED";
                    treeRightRotate(node->up->up);
                }
            }
        }

        root->color = "BLACK";
    }

    /**
     * Gib den Baum tree auf der Konsole aus, um 90 Grad nach links gedreht.
     * Rücke jede Zeile mit sovielen Tabs ein, wie in indentation angegeben.
     * @param root
     * @param indentation
     */
    void treePrint(Nodeptr root, int indentation) {
        int i;
        if (root!=nil) {
            treePrint(root->right, indentation+1);
            for (i=0;i <indentation; i++) {
                cout << "\t";
            }
            cout << "(key: " << root->key  <<", " << root->color <<")" << "\n\n\n";
            treePrint(root->left, indentation+1);
        }
    }

public:

    /**
     * RedBlackTree Konstruktor.
     */
    RedBlackTree()
    {
        nil = new RBTreeNode;
        nil->color = "BLACK";
        nil->left = nullptr;
        nil->right = nullptr;
        root = nil;
        count = 0;
    }

    /**
     * getCount, gibt die count Variable zurück.
     * @return
     */
    int getCount(){return count;}


    RBTreeNode* getWurzel(){
        return root;
    }

    RBTreeNode* getNil(){
        return nil;
    }

    /**
     * Rotiert einen bestimmten Knoten im Baum nach rechts.
     * @param rotateThisNode
     */
    void treeRightRotate(Nodeptr rotateThisNode)
    {
        Nodeptr x = rotateThisNode;
        Nodeptr y = x->left;
        x->left = y->right;
        if (y->right != nil)
            y->right->up = x;
        y->up = x->up;
        if (x->up == nil)
            this->root = y;
        else if (x == x->up->right)
            x->up->right = y;
        else
            x->up->left = y;
        y->right = x;
        x->up = y;
    }


    /**
     * Rotiert einen bestimmten Knoten im Baum nach links.
     * @param rotateThisNode
     */
    void treeLeftRotate(Nodeptr rotateThisNode)
    {
        Nodeptr x = rotateThisNode;
        Nodeptr y = x->right;
        x->right = y->left;
        if (y->left != nil)
            y->left->up = x;
        y->up = x->up;

        if (x->up == nil)
            this->root = y;
        else if (x == x->up->left)
            x->up->left = y;
        else
            x->up->right = y;
        y->left = x;
        x->up = y;
    }


    /**
     * Fuege den Knoten node in den RB Baum ein.
     * @param key
     * @return
     */
    struct RBTreeNode* treeInsert(int key)
    {
        Nodeptr node = new RBTreeNode;
        node->up = nullptr;
        node->key = key;
        node->left = nil;
        node->right = nil;
        node->color = "RED";        //Knoten wird zuerst ROT gesetzt

        Nodeptr y = nil;
        Nodeptr x = this->root;

        while (x != nil)
        {
            y = x;
            if (node->key < x->key)
                x = x->left;
            else
                x = x->right;
        }
        node->up = y;
        if (y == nil)
            root = node;
        else if (node->key < y->key)
            y->left = node;
        else
            y->right = node;

        treeInsertFixRB(node);      //Hilfsprozedur, die die Farben und Annordnungen korrigieren soll

        return node;
    }


    /**
     * Sucht einen Schlüssel im Rot-Schwarz Baum und zählt die Schlüsselvergleiche dabei.
     * @param node
     * @param key
     */
    void TreeSearch(RedBlackTree node, int key)
    {
        Nodeptr temp;
        temp = this->root;
        while(temp != nullptr)
        {
            count++;
            if(temp->key == key)
            {
                cout<<"\nKnoten gefunden: ";
                cout<<"\nSchluesselvergleiche: ";
                // count++;
                return;
            }
            else
                {
                count++;
                if (temp->key > key)
                    temp = temp->left;
                else
                    temp = temp->right;
            }

        }
        cout<<"\n Knoten nicht gefunden\n";
        //cout<<"\n Schluesselvergleiche: ";
        return;
    }


    /**
     * Erzeuge einen binaeren Suchbaum mit n Knoten. Als Schluessel werden 1, ..., n (in dieser Reihenfolge) eingefügt.
     * @param n
     */
    void TreeExampleSequenceN(int n)
    {
        Nodeptr tree = nullptr;

        for(int i = 1; i <= n; i++)
            tree = treeInsert(i);
    }


    /**
     * Erzeugt einen Baum mit n Ebenen.
     * @param n
     * @return
     */
    struct RBTreeNode* TreeExampleFullLevelN(int n)
    {
        Nodeptr tree = nullptr;

        for(int i = n; i >= 1; --i)
        {
            for(int j = 0; j < pow(2, n -i); j++)
            {
                tree = treeInsert(pow(2, i-1) + (pow(2, i) * j));
                //count++;
            }
        }
        return tree;
    }


    /**
     * Gib den Baum tree auf der Konsole aus, um 90 Grad nach links gedreht.
     */
    void treePrint1()
    {
        cout << "\n\n";
        treePrint(this->root, 0);
    }
};

#endif
