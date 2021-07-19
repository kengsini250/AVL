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
};

#endif // NODE_H

class AVL
{
public:
    AVL(){}

    int getSize(){return size;}
    bool getBalance(Node* n){
        if(n == nullptr) return 0;
        else return n->left->height - n->right->height;
    }

    bool isBalance(){
        return isBalance(root);
    }

    void add();
private:
    int size = 0;
    Node* root = nullptr;

    bool isBalance(Node* n)
    {
        if(n == nullptr) return true;
        int b = n->left->height - n->right->height;
        if(b<0) b = -b;
        if(b > 1) return false;
        return isBalance(n->left) && isBalance(n->right);
    }

    Node* add(Node* n)
    {
        if(n == nullptr){
            size++;
            return n;
        }
    }

    Node* LL(Node* parent)
    {
        Node* self = parent->left;
        Node* self_right = self->right;
        self->right = parent;
        parent->left = self_right;

        parent->height = MAX(parent->left->height,parent->right->height)+1;
        self->height = MAX(self->left->height,self->right->height)+1;
        return self;
    }

    Node* RR(Node* parent)
    {
        Node* self = parent->right;
        Node* self_left = self->left;
        self->left = parent;
        parent->right = self_left;

        parent->height = MAX(parent->left->height,parent->right->height)+1;
        self->height = MAX(self->left->height,self->right->height)+1;
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
        Node* new_self = LL(sonR);

        parent->height = MAX(parent->left->height,parent->right->height)+1;
        new_self->height = MAX(new_self->left->height,new_self->right->height)+1;
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
        Node* new_self = RR(sonL);

        parent->height = MAX(parent->left->height,parent->right->height)+1;
        new_self->height = MAX(new_self->left->height,new_self->right->height)+1;
        return new_self;
    }
};
