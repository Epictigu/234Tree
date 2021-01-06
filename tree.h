#ifndef TREE_H
#define TREE_H

// Struktur fuer binaere Suchbaume
#include <string>
using namespace std;

struct TreeNode {
    struct TreeNode* up;
    int key;
    string info;
    struct TreeNode* left;
    struct TreeNode* right;
};

class tree {
public:
    static struct TreeNode* NewTreeNode(int key, string info);
    static struct TreeNode* TreeExample1();
    static void TreePrint(struct TreeNode* tree);
    static void TreePrint(struct TreeNode* tree, int indentation);
    static struct TreeNode* TreeInsert(struct TreeNode* tree, int key, string info);
    static struct TreeNode* TreeSearch(struct TreeNode* tree, int key);
    static void TreeUpdate(struct TreeNode* tree, int key, string info);
    static struct TreeNode* TreeGenerateRandomTree(int n, int seed);
    static struct TreeNode* TreeExampleSequenceN(int n);
    static struct TreeNode* TreeExampleFullLevelN(int n);
};


#endif // TREE_H
