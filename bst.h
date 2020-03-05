#include <iostream>

struct Node{
private:
    int value;
    Node *left=NULL;
    Node *right=NULL;
    Node *parent=NULL;
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

};

struct Tree{
private:
    Node *root=NULL;
    int numTraverse=0;
public:
    void insertRec(Node *node,int val){
        if (root==NULL){
            root=new Node();
            root->setVal(val);
            return;
        }
        if (val>node->getVal()){
            if(node->getRight()==NULL){
                node->setRight(new Node());
                node->getRight()->setVal(val);
                return;
            }
            else{
                insertRec(node->getRight(),val);
                updateTraverse();
            }
        }
        else{
            if(node->getLeft()==NULL){
                node->setLeft(new Node());
                node->getLeft()->setVal(val);
                return;
            }
            else{
                insertRec(node->getLeft(),val);
                updateTraverse();
            }
        }
    }

    void insertIter(Node *node,int val){
        if (root==NULL){
            root=new Node();
            root->setVal(val);
            return;
        }

        Node * curr=node;
        while (curr!=NULL){
            if(val<curr->getVal()){
                if(curr->getLeft()==NULL){
                    curr->setLeft(new Node());
                    curr->getLeft()->setVal(val);
                    return;
                }
                else{
                    curr=curr->getLeft();
                    updateTraverse();
                }
            }
            else{
                if(curr->getRight()==NULL){
                    curr->setRight(new Node());
                    curr->getRight()->setVal(val);
                    return;
                }
                else{
                    curr=curr->getRight();
                    updateTraverse();
                }
            }
        }
    }

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

    Node * getRoot(){
        return this->root;
    }

    Node * findMinRec(Node * node){
        if(node->getLeft()!=NULL){
            findMinRec(node->getLeft());
            updateTraverse();
        }
        else{
           return node;
        }
    }
    Node * findMinIter(Node * node){
        Node*curr=node;
        while(curr->getLeft()!=NULL){
            curr=curr->getLeft();
            updateTraverse();
        }
        return curr;
    }
    Node * findMaxRec(Node * node){
        if(node->getRight()!=NULL){
            findMaxRec(node->getRight());
            updateTraverse();
        }
        else{
           return node;
        }
    }
    Node * findMaxIter(Node * node){
        Node*curr=node;
        while(curr->getRight()!=NULL){
            curr=curr->getRight();
            updateTraverse();
        }
        return curr;
    }
    Node * findNextRec(Node*node){
        if (node->isLeaf()){
            if(node->getRight()->getVal()>node->getParent()->getVal()){
                if(node->getVal()<getRoot()->getVal()){
                    return root;
                }
                else
                    return NULL;
            }
            else{
                return node->getParent();
            }
        }
        else{
            Node * curr=node->getRight();
            updateTraverse();
            if(curr!=NULL){
                return findMinRec(curr);
            }
            else{
                return curr->getParent();
            }
        }

    }
    Node * findNextIter(Node *node){
        Node * curr;
        if (node->getRight()!=NULL){
            curr=node->getRight();
            updateTraverse();
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
    Node * findPrevRec(Node*node){
        if (node->isLeaf()){
            if(node->getLeft()->getVal()<node->getParent()->getVal()){
                if(node->getVal()>getRoot()->getVal()){
                    return root;
                }
                else
                    return NULL;
            }
            else{
                return node->getParent();
            }
        }
        else{
            Node * curr=node->getLeft();
            updateTraverse();
            if(curr!=NULL){
                return findMaxRec(curr);
            }
            else{
                return curr->getParent();
            }
        }
    }
    Node * findPrevIter(Node *node){
        Node * curr;
        if (node->getLeft()!=NULL){
            curr=node->getLeft();
            updateTraverse();
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
    void deleteRec(Node *node,int val){
        if (node->getVal()==val){
            if (node->isLeaf()){
                if(node==node->getParent()->getLeft()){
                    node->getParent()->setLeft(NULL);
                }
                else{
                    node->getParent()->setRight(NULL);
                }
                delete(node);
            }

            else if(node->hasChildren()==1){
                Node * par=node->getParent();
                if (node->getLeft()!=NULL){
                    Node * leftNode=node->getLeft();

                    if (par->getLeft()==node){
                        par->setLeft(leftNode);
                    }
                    else{
                        par->setRight(leftNode);
                    }
                }
                else{
                    Node * rightNode=node->getRight();
                    if (par->getLeft()==node){
                        par->setLeft(rightNode);
                    }
                    else{
                        par->setRight(rightNode);
                    }
                }
                delete(node);
            }

            else if(node->hasChildren()==2){
                Node * next=findNextRec(node);
                Node * par=next->getParent();

                node->setVal(next->getVal());
                if(node->getVal()==par->getLeft()->getVal()){
                    if(!next->isLeaf()){
                        par->setLeft(next->getLeft());
                    }
                    else{
                       par->setLeft(NULL);
                    }
                }
                else{
                    if(!next->isLeaf()){
                        par->setRight(next->getRight());
                    }
                    else{
                       par->setRight(NULL);
                    }
                }
                delete(next);


            }
        }
        else if(node->getVal()>val){
            deleteRec(node->getLeft(),val);
            updateTraverse();
        }
        else if(node->getVal()<val){
            deleteRec(node->getRight(),val);
            updateTraverse();
        }
    }

    void deleteIter(Node * node, int val){
        Node * curr=node;
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
            delete(curr);
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
            }
            else{
                Node * rightNode=curr->getRight();
                if (par->getLeft()==curr){
                    par->setLeft(rightNode);
                }
                else{
                    par->setRight(rightNode);
                }
            }
            delete(curr);
        }

        else if(curr->hasChildren()==2){
            Node * next=findNextIter(curr);
            Node * par=next->getParent();

            curr->setVal(next->getVal());
            if(curr->getVal()==par->getLeft()->getVal()){
                if(!next->isLeaf()){
                    par->setLeft(next->getLeft());
                }
                else{
                    par->setLeft(NULL);
                }
            }
            else{
                if(!next->isLeaf()){
                    par->setRight(next->getRight());
                }
                else{
                   par->setRight(NULL);
                }
            }

            delete(next);
        }

        return;
    }
    void updateTraverse(){
        numTraverse+=1;
    }
    int getNumTraverse(){
        return numTraverse;
    }

};

void sort(Node *node){
    if (node==NULL){
        return;
    }
    else if (node->isLeaf()){
        cout<<node->getVal()<<" ";
    }
    else{
        sort(node->getLeft());
        cout<<node->getVal()<<" ";
        sort(node->getRight());
    }
}


