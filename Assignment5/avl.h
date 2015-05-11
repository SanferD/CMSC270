#ifndef AVL
#define AVL

#include<iostream>
using namespace std;
/* AVLNode */
template<class T>
class AVLNode
{
public:
    AVLNode()
    {
        left = right = 0;
        balance = 0;
    }
    AVLNode(const T& el, AVLNode *l = 0, AVLNode *r = 0)
    {
        key = el; left = l; right = r;
        balance = 0;
    }
    T key;
    AVLNode *left, *right;
    int balance;
};

/* AVLTree */
template<class T>
class AVLTree
{
public:
    AVLTree() { root = NULL; }

    void insert(const T& key)
    {
        insert(root,key);
    }

    void snapShot(std::ostream& out)
    {
        out << "TreeForm[";
        snapShot(out,root);
        out << "]" << std::endl;
    }
private:
    AVLNode<T>* root;

//    void rightRotation(AVLNode<T>* &node) {
//        AVLNode<T>* left = node->left;

//        if(left)
//        {
//            node->left = left->right;
//            left->right = node;
//            node = left;
//        }
//        else
//        {
//            node->balance--;
//            node->right->left = new AVLNode<T>(node->key);
//            node = node->right;
//        }
//    }

    void rightRotation(AVLNode<T>* &node)
    {
        cout << "rightRot: " << node->key << endl;
        AVLNode<T> *left = node->left;

        if(node->left->left)
        {

            int nb = node->balance, lb = left->balance;

            node->left = left->right;
            left->right = node;
            node = left;

            int bal = node->right->balance = (lb<=0) ? nb-lb+1 : nb+1;
            node->balance = (bal<=0) ? lb+1 : lb+bal+1;
        }
        else
        {
            AVLNode<T> *pivot = left->right;
            AVLNode<T> *Q = pivot->left, *R = pivot->right;

            int nb = node->balance, lb = left->balance, pb = pivot->balance;

            pivot->left = left;
            pivot->right = node;
            left->right = Q;
            node->left = R;
            node = pivot;

            int balL = node->left->balance = (pb>=0) ? lb-pb-1 : lb-1;

            if(lb>=0 && pb>=0)
            {
                int balR = node->right->balance = nb+2;
                if(balL<=0 && balR<=0) node->balance = lb-1;
                else if(balL<=0 && balR>0) node->balance = nb+lb+1;
                else if(balL>0 && balR<=0) node->balance = pb;
                else node->balance = nb+pb+2;
            }
            else if(lb<0 && pb>=0)
            {
                int balR = node->right->balance = nb-lb+2;
                if(balL<=0 && balR<=0) node->balance = lb-1;
                else if (balL<=0 && balR>0) node->balance = nb+1;
                else if(balL>0 && balR<=0) node->balance = pb;
                else node->balance = nb-lb+pb+2;
            }
            else if(lb>=0 && pb<0)
            {
                int balR = node->right->balance = nb-pb+2;
                if(balL<=0 && balR<=0) node->balance = lb+pb-1;
                else if(balL<=0 && balR>0) node->balance = nb+lb+1;
                else if(balL>0 && balR<=0) node->balance = pb;
                else node->balance = nb+2;
            }
            else // lb<0 && pb<0
            {
                int balR = node->right->balance = nb-lb-pb+2;
                if(balL<=0 && balR<=0) node->balance = lb+pb-1;
                else if (balL<=0 && balR>0) node->balance = nb+1;
                else if(balL>0 && balR<=0) node->balance = pb;
                else node->balance = nb-lb+2;
            }

        }

        if(node->balance<-1) rightRotation(node->right);
        else if(node->balance>1) leftRotation(node->right);
    }

    void leftRotation(AVLNode<T>* &node)
    {
        cout << "leftRot: " << node->key << endl;
        AVLNode<T>* right = node->right;

        if(node->right->right)
        {
            int nb = node->balance, rb = right->balance;

            node->right = right->left;
            right->left = node;
            node = right;

            int bal = node->left->balance = (rb>=0) ? nb-rb-1 : nb-1;
            node->balance = (bal>=0) ? rb-1 : rb-bal-1;
        }
        else
        {
            AVLNode<T> *pivot = right->left;
            AVLNode<T> *Q = pivot->left, *R = pivot->right;

            int nb = node->balance, rb = right->balance, pb = pivot->balance;

            pivot->right = right;
            pivot->left = node;
            right->left = R;
            node->right = Q;
            node = pivot;

            int balR = node->right->balance = (pb<=0) ? rb-pb+1 : lb+1;

            if(rb<=0 && pb<=0)
            {
                int balL = node->left->balance = nb-2;
                if(balL>=0 && balR>=0) node->balance = rb+1;
                else if(balL<0 && balR>=0) node->balance = nb+lb-1;
                else if(balL>=0 && balR<0) node->balance = pb;
                else node->balance = nb+pb-2;
            }
            else if(rb>0 && pb<=0)
            {
                int balL = node->left->balance = nb+rb-2;
                if(balL>=0 && balR>=0) node->balance = rb+1;
                else if(balL<0 && balR>=0) node->balance = nb-1;
                else if(balL>=0 && balR<0) node->balance = pb;
                else node->balance = nb-rb+pb-2;
            }
            else if(rb<=0 && pb>0)
            {
                int balL = node->left->balance = nb-pb-2;
                if(balL>=0 && balR>=0) node->balance = rb+pb+1;
                else if(balL<0 && balR>=0) node->balance = nb+rb-1;
                else if(balL>=0 && balR<0) node->balance = pb;
                else node->balance = nb-2;
            }
            else // rb>0 && pb>0
            {
                int balL = node->left->balance = nb-rb-pb-2;
                if(balL>=0 && balR>=0) node->balance = rb+pb+1;
                else if (balL<0 && balR>=0) node->balance = nb-1;
                else if(balL>=0 && balR<0) node->balance = pb;
                else node->balance = nb-rb-2;
            }
        }

        if(node->balance<-1) rightRotation(node->right);
        else if(node->balance>1) leftRotation(node->right);
    }


    int insert(AVLNode<T>* &node,const T& key)
    {
        int oldBalance = node ? node->balance : 0;

        if(node == NULL) return (node=new AVLNode<T>(key))->balance+1;
        else if(key > node->key)
        {
            node->balance += insert(node->right,key);
            if(node->balance>1) leftRotation(node);
        }
        else
        {
            node->balance -= insert(node->left,key);
            if(node->balance<-1) rightRotation(node);
        }

        return (abs(oldBalance)<abs(node->balance)) ? 1 : 0;
    }

    void snapShot(std::ostream& out,AVLNode<T> *p)
    {
        std::cout << p->key << " " << p->balance << std::endl;
        out << '\"' << p->key << '\"';
        if(p->left != 0 || p->right != 0)
        {
            out << '[';
            if(p->left==0)
                out << "\"\"";
            else
                snapShot(out,p->left);
            out << ',';
            if(p->right==0)
                out << "\"\"";
            else
                snapShot(out,p->right);
            out << ']';
        }
    }

};

#endif // AVL

