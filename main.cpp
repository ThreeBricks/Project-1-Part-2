#include <iostream>
#include "avl.h"
#include "bst.h"
#include "arrs.h"


using namespace std;

int main()
{
    //Question 5a
    avl::AvlTree avlTree;
    Tree bstTreeRec;
    int * randArr=getRandomArray(10000);
    for(int i=0;i<10000;i++){
        avlTree.insertIter(randArr[i]);
        bstTreeRec.insertRec(bstTreeRec.getRoot(),randArr[i]);
    }
    preOrder(avlTree.getRoot());
    cout<<endl;
    bstTreeRec.preOrder(bstTreeRec.getRoot());
    cout<<endl;

    //Question 5c
    avl::AvlTree avlTree2;
    Tree bstTreeIter;
    randArr=getRandomArray(10000);
    for(int i=0;i<10000;i++){
        avlTree2.insertIter(randArr[i]);
        bstTreeIter.insertIter(bstTreeIter.getRoot(),randArr[i]);
    }
    preOrder(avlTree2.getRoot());
    cout<<endl;
    bstTreeIter.preOrder(bstTreeIter.getRoot());
    cout<<endl;

    avl::AvlTree avlTree3;
    Tree bstTreeIter2;
    randArr=getRandomArray(10000);
    for(int i=0;i<10000;i++){
        avlTree3.insertIter(randArr[i]);
        bstTreeIter2.insertIter(bstTreeIter2.getRoot(),randArr[i]);
    }
    cout<<"Nodes Gone Down in Random AVL Tree "<<avlTree3.getNumTraverse()<<endl;
    cout<<"Nodes Gone Down in Random BST "<<bstTreeIter2.getNumTraverse()<<endl;

    avl::AvlTree avlTree4;
    Tree bstTreeIter3;
    randArr=getSortedArray(10000);
    for(int i=0;i<10000;i++){
        avlTree4.insertIter(randArr[i]);
        bstTreeIter3.insertIter(bstTreeIter3.getRoot(),randArr[i]);
    }
    cout<<"Nodes Gone Down in Sorted AVL Tree "<<avlTree4.getNumTraverse()<<endl;
    cout<<"Nodes Gone Down in Sorted BST "<<bstTreeIter3.getNumTraverse()<<endl;

    return 0;
}
