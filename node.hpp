#ifndef NODE_HPP
#define NODE_HPP

#define MAX(l,r) (l>r?l:r)

class Node
{
public:
    int data;
    int height = 1;
    Node *left = nullptr,*right = nullptr;

    Node(){}
    Node(int i){data = i;}
};

#endif // NODE_H

class AVL
{
public:
    AVL(){}

    int getSize(){return size;}

    bool isBalance(){
        return isBalance(root);
    }

    void add(Node*n){
        if(root == nullptr)
            root = n;
        else
            root = add(root,n);
    }
private:
    int size = 0;
    Node* root = nullptr;

    Node* add(Node* parent,Node* n)
    {
        if(parent == nullptr){
            size++;
            return n;
        }

        if(n->data < parent->data)
            parent->left  = add(parent->left ,n);
        if(n->data > parent->data)
            parent->right = add(parent->right,n);

        parent->height = 1 + MAX(getHeight(parent->left),getHeight(parent->right));

        int balance = getBalance(parent);

        //LL
        if( balance>1 && getBalance(parent->left)>0 ) return LL(parent);
        //LR
        if( balance>1 && getBalance(parent->left)<0 ) return LR(parent);

        //RR
        if( balance<-1 && getBalance(parent->right)<0 ) return RR(parent);
        //RL
        if( balance<-1 && getBalance(parent->right)>0 ) return RL(parent);

        return parent;
    }

    Node* LL(Node* parent)
    {
        Node* self = parent->left;
        if(self->right != nullptr){
            Node* self_right = self->right;
            self->right = parent;
            parent->left = self_right;
        }else{
            self->right = parent;
            parent->left = nullptr;
        }

        parent->height = MAX(getHeight(parent->left),getHeight(parent->right))+1;
        self->height = MAX(getHeight(self->left),getHeight(self->right))+1;
        return self;
    }

    Node* RR(Node* parent)
    {
        Node* self = parent->right;
        if(self->left != nullptr){
            Node* self_left = self->left;
            self->left = parent;
            parent->right = self_left;
        }else{
            self->left = parent;
            parent->right = nullptr;
        }

        parent->height = MAX(getHeight(parent->left),getHeight(parent->right))+1;
        self->height = MAX(getHeight(self->left),getHeight(self->right))+1;
        return self;
    }

    Node* LR(Node* parent)
    {
        Node* self = parent->left;
        Node* sonR = self->right;
        Node* sonR_right = sonR->right;
        parent->left = sonR;
        sonR->left = self;
        self->right = sonR_right;
        Node* new_self = LL(parent);

        parent->height = MAX(getHeight(parent->left),getHeight(parent->right))+1;
        new_self->height = MAX(getHeight(new_self->left),getHeight(new_self->right))+1;
        return new_self;
    }

    Node* RL(Node* parent)
    {
        Node* self = parent->right;
        Node* sonL = self->left;
        Node* sonL_right = sonL->right;
        parent->right = sonL;
        sonL->right = self;
        self->left = sonL_right;
        Node* new_self = RR(parent);

        parent->height = MAX(getHeight(parent->left),getHeight(parent->right))+1;
        new_self->height = MAX(getHeight(new_self->left),getHeight(new_self->right))+1;
        return new_self;
    }

    bool isBalance(Node* n)
    {
        if(n == nullptr) return true;
        int b = n->left->height - n->right->height;
        if(b<0) b = -b;
        if(b > 1) return false;
        return isBalance(n->left) && isBalance(n->right);
    }

    int getBalance(Node* n){
        if(n == nullptr) return 0;
        else return getHeight(n->left) - getHeight(n->right);
    }

    int getHeight(Node*n)
    {
        if(n == nullptr) return 0;
        else return n->height;
    }
};
