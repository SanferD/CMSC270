#ifndef AVL
#define AVL

#include <iostream>

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

    bool isValid() // wrapper.
    {
        return isValid(root);
    }

    bool isBalanced() // wrapper.
    {
        return isBalanced(root);
    }

private:
    AVLNode<T>* root;

    /* For nodes whose left child has a right child.
     */
    void leftRightSwap(AVLNode<T>* &node)
    {
        AVLNode<T> *left = node->left;

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

    /* For nodes whose right child has a left child.
     */
    void rightLeftSwap(AVLNode<T>* &node)
    {
        AVLNode<T>* right = node->right;

        AVLNode<T> *pivot = right->left;
        AVLNode<T> *Q = pivot->left, *R = pivot->right;

        int nb = node->balance, rb = right->balance, pb = pivot->balance;

        pivot->right = right;
        pivot->left = node;
        right->left = R;
        node->right = Q;
        node = pivot;

        int balR = node->right->balance = (pb<=0) ? rb-pb+1 : rb+1;

        if(rb<=0 && pb<=0)
        {
            int balL = node->left->balance = nb-2;
            if(balL>=0 && balR>=0) node->balance = rb+1;
            else if(balL<0 && balR>=0) node->balance = nb+rb-1;
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

    void rightRotation(AVLNode<T>* &node)
    {
        if(node->left->left)
        {
            AVLNode<T> *left = node->left;

            int nb = node->balance, lb = left->balance;

            node->left = left->right;
            left->right = node;
            node = left;

            int bal = node->right->balance = (lb<=0) ? nb-lb+1 : nb+1;
            node->balance = (bal<=0) ? lb+1 : lb+bal+1;
        }
        else if(node->left->right) leftRightSwap(node);

        if(node->balance<-1) leftRightSwap(node);
        else if(node->balance>1) rightLeftSwap(node);
    }

    void leftRotation(AVLNode<T>* &node)
    {
        if(node->right->right)
        {
            AVLNode<T>* right = node->right;

            int nb = node->balance, rb = right->balance;

            node->right = right->left;
            right->left = node;
            node = right;

            int bal = node->left->balance = (rb>=0) ? nb-rb-1 : nb-1;
            node->balance = (bal>=0) ? rb-1 : rb-bal-1;
        }
        else if(node->right->left) rightLeftSwap(node);

        if(node->balance<-1) leftRightSwap(node);
        else if(node->balance>1) rightLeftSwap(node);
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

        // change balance only if max height changes.
        return (abs(oldBalance)<abs(node->balance)) ? 1 : 0;
    }

    /* Modified to print node->key values whenever node->balance <= -2 or
     * node->balance >= 2.
     */
    void snapShot(std::ostream& out,AVLNode<T> *p)
    {
        if(abs(p->balance)>1) std::cout << "out-of-balance" << p->key
                                        << " " << p->balance << std::endl;

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

    /* The below functions are for verification purposes.
     */
    int height(const AVLNode<T> *node) const
    {
        if(!node) return 0;
        return std::max(height(node->left),height(node->right))+1;
    }

    bool isBalanced(const AVLNode<T> *parent) const
    {
        int trueBal  = (parent->right ? height(parent->right) : 0)
                   - (parent->left ? height(parent->left) : 0);
        int diff = trueBal - parent->balance;

        if(diff) // print the error
            std::cout << parent->key << " " << trueBal << " " << parent->balance << std::endl;
        if(parent->left)
            if(diff || !isBalanced(parent->left)) return false;
        if(parent->right)
            if(diff || !isBalanced(parent->right)) return false;
        return true;
    }

    bool isValid(const AVLNode<T> *parent) const
    {
        if(parent->right)
        {
            if(parent->key <= parent->right->key) return isValid(parent->right);
            else return false;
        }
        if(parent->left)
        {
            if(parent->key >= parent->left->key) return isValid(parent->left);
            else return false;
        }
        return true;
    }

};

#endif // AVL

