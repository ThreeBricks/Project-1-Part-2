#include <iostream>
#include <algorithm>

using namespace std;
namespace avl{
struct Node{
private:
    int value;
    Node *left=NULL;
    Node *right=NULL;
    Node *parent=NULL;
    int height=-1;
public:
    bool isLeaf(){
        return (this->left==NULL && this->right==NULL);
    }
    void setVal(int val){
        this->value=val;
    }
    int getVal(){
        return this->value;
    }
    void setLeft(Node *node){
        if(node!=NULL){
            node->setParent(this);
        }
        this->left=node;

    }
    Node * getLeft(){
        return this->left;
    }
    void setRight(Node *node){
        if(node!=NULL){
            node->setParent(this);
        }
        this->right=node;
    }
    Node * getRight(){
        return this->right;
    }
    void setParent(Node *node){
        this->parent=node;
    }
    Node * getParent(){
        return this->parent;
    }
    int hasChildren(){
        if (!(this->left==NULL) != !(this->right==NULL)){
            return 1;
        }
        else if (this->left!=NULL && this->right!=NULL){
            return 2;
        }
        else{
            return 0;
        }
    }
    void setHeight(){
        if(getLeft()==NULL && getRight()==NULL){
            height=0;
        }
        else if (getLeft()==NULL){
            height=getRight()->getHeight()+1;
        }
        else if (getRight()==NULL){
            height=getLeft()->getHeight()+1;
        }
        else{
            height=max(getLeft()->getHeight(),getRight()->getHeight())+1;
        }
        return;
    }
    int getHeight(){
        if(this==0){
            return -1;
        }
        return height;
    }

};

struct AvlTree{
private:
    Node *root=NULL;
    int numTraverse=0;
public:
    void insertIter(int val){
     Node * curr=root;
     Node *node=new Node();
     node->setVal(val);
     node->setHeight();
        if (curr==NULL){
            root=node;
        }
        else if (val>curr->getVal()){
            node->setParent(curr);
            curr=curr->getRight();
            updateTraverse();
            while(curr!=NULL){
                if(val < curr->getVal()){
                    node->setParent(curr);
                    curr=curr->getLeft();
                    updateTraverse();
                }
                else{
                    node->setParent(curr);
                    curr=curr->getRight();
                    updateTraverse();
                }
            }
            if(val>node->getParent()->getVal()){
                node->getParent()->setRight(node);
            }
            else{
                node->getParent()->setLeft(node);
            }
            curr=node;
            rebalance(curr);
            return;
        }
        else{
            if(val==curr->getVal()){
                return;
            }
            node->setParent(curr);
            curr=curr->getLeft();
            updateTraverse();
            while(curr!=NULL){
                if(val < curr->getVal()){
                    node->setParent(curr);
                    curr=curr->getLeft();
                    updateTraverse();
                }
                else{
                    node->setParent(curr);
                    curr=curr->getRight();
                    updateTraverse();
                }
            }
            if(val>node->getParent()->getVal()){
                node->getParent()->setRight(node);
            }
            else{
                node->getParent()->setLeft(node);
            }
            curr=node;
            rebalance(curr);
            return;
        }
    }

    void rightRotate(Node * node){
        Node * left=node->getLeft();
        Node * curr=node;

        left->setParent(curr->getParent());
        if(left->getParent()==NULL){
            root=left;
        }
        else if (left->getVal()>left->getParent()->getVal()){
            left->getParent()->setRight(left);
        }
        else {
            left->getParent()->setLeft(left);
        }
        curr->setLeft(left->getRight());
        curr->setParent(left);
        if(left->getRight()!=NULL){
            left->getRight()->setParent(curr);
        }
        left->setRight(curr);

        left->setHeight();
        curr->setHeight();
        return;
    }
    void leftRotate(Node * node){
        Node * right=node->getRight();
        Node * curr=node;

        right->setParent(curr->getParent());
        if(right->getParent()==NULL){
            root=right;
        }
        else if (right->getVal()>right->getParent()->getVal()){
            right->getParent()->setRight(right);
        }
        else {
            right->getParent()->setLeft(right);
        }
        curr->setRight(right->getLeft());
        curr->setParent(right);
        if(right->getLeft()!=NULL){
            right->getLeft()->setParent(curr);
        }
        right->setLeft(curr);
        right->setHeight();
        curr->setHeight();
        return;
    }

    int getBF(Node *node){
        return (node->getLeft()->getHeight())-(node->getRight()->getHeight());
    }

    Node * getRoot(){
        return this->root;
    }

    Node * findMinIter(Node * node){
        Node*curr=node;
        while(curr->getLeft()!=NULL){
            curr=curr->getLeft();
            updateTraverse();
        }
        return curr;
    }
    Node * findMaxIter(Node * node){
        Node*curr=node;
        while(curr->getRight()!=NULL){
            curr=curr->getRight();
            updateTraverse();
        }
        return curr;
    }
    Node * findNextIter(Node *node){
        Node * curr;
        if (node->getRight()!=NULL){
            curr=node->getRight();
            while(curr->getLeft()!=NULL){
                curr=curr->getLeft();
                updateTraverse();
            }
            return curr;
        }
        else if(node->getVal()<node->getParent()->getVal()){
            return node->getParent();
        }
        else if(node->getVal()<getRoot()->getVal()){
            return getRoot();
        }
        else{
            return NULL;
        }
    }
    Node * findPrevIter(Node *node){
        Node * curr;
        if (node->getLeft()!=NULL){
            curr=node->getLeft();
            while(curr->getRight()!=NULL){
                curr=curr->getRight();
                updateTraverse();
            }
            return curr;
        }
        else if(node->getVal()>node->getParent()->getVal()){
            return node->getParent();
        }
        else if(node->getVal()>getRoot()->getVal()){
            return getRoot();
        }
        else{
            return NULL;
        }
    }
    void deleteIter(int val){
        Node * curr=root;
        while(curr->getVal()!=val){
            if(val>curr->getVal()){
                curr=curr->getRight();
                updateTraverse();
            }
            else{
                curr=curr->getLeft();
                updateTraverse();
            }
        }
        if (curr->isLeaf()){
            if(curr==curr->getParent()->getLeft()){
                curr->getParent()->setLeft(NULL);
            }
            else{
                curr->getParent()->setRight(NULL);
            }
            curr=curr->getParent();
            updateTraverse();
            rebalance(curr);
        }
        else if(curr->hasChildren()==1){
            Node * par=curr->getParent();
            if (curr->getLeft()!=NULL){
                Node * leftNode=curr->getLeft();
                if (par->getLeft()==curr){
                    par->setLeft(leftNode);
                }
                else{
                    par->setRight(leftNode);
                }
                leftNode->setParent(par);
                rebalance(leftNode);
            }
            else{
                Node * rightNode=curr->getRight();
                if (par->getLeft()==curr){
                    par->setLeft(rightNode);
                }
                else{
                    par->setRight(rightNode);
                }
                rightNode->setParent(par);
                rebalance(rightNode);
            }
            curr->setLeft(NULL);
            curr->setRight(NULL);
            curr->setParent(NULL);
            delete(curr);
        }

        else if(curr->hasChildren()==2){
            Node * next=findNextIter(curr);
            Node * par=next->getParent();

            curr->setVal(next->getVal());
            if(curr==par->getLeft()){
                if(!next->isLeaf()){
                    par->setLeft(next->getLeft());
                }
                else{
                    par->setLeft(NULL);
                }
                rebalance(par);
            }
            else{
                if(!next->isLeaf()){
                    par->setRight(next->getRight());
                }
                else{
                   par->setRight(NULL);
                }
                rebalance(par);
            }

            delete(next);
        }
        return;
    }

    void rebalance(Node *curr){
        while(curr!=NULL){
            int bf;
            curr->setHeight();
            bf=getBF(curr);
            if(bf==2){
                Node * left=curr->getLeft();
                bf=getBF(left);
                if(bf==1){
                    rightRotate(curr);
                }
                else if(bf==-1){
                    leftRotate(curr->getLeft());
                    rightRotate(curr);
                }
            }
            else if (bf==-2){
                Node * right=curr->getRight();
                bf=getBF(right);
                if(bf==-1){
                    leftRotate(curr);
                }
                else if(bf==1){
                    rightRotate(curr->getRight());
                    leftRotate(curr);
                }
            }
            curr=curr->getParent();
            }
        return;
    }

    Node * findNode(int val){
        Node * curr=root;
        if (val==curr->getVal()){
            return root;
        }
        else if (val>curr->getVal()){
            curr=curr->getRight();
            while(curr!=NULL && val != curr->getVal() ){
                if(val < curr->getVal()){
                    curr=curr->getLeft();
                }
                else{
                    curr=curr->getRight();
                }
            }
            if(curr==NULL){
                cout<<"Node not found with value "<<val<<endl;
                return NULL;
            }
            else{
                return curr;
            }

        }
        else{
            curr=curr->getLeft();
            while(curr!=NULL && val != curr->getVal()){
                if(val < curr->getVal()){
                    curr=curr->getLeft();
                }
                else{
                    curr=curr->getRight();
                }
            }
            if(curr==NULL){
                cout<<"Node not found"<<endl;
                return NULL;
            }
            else{
                return curr;
            }

        }
    }
    void updateTraverse(){
        numTraverse+=1;
    }
    int getNumTraverse(){
        return numTraverse;
    }
};
void preOrder(Node * node){
    if(node!=NULL){
     cout<<node->getVal()<<" ";
    }
    else{
        return;
    }
    preOrder(node->getLeft());
    preOrder(node->getRight());
}

}
