//  Casey Hittinger
//  AVLTree.h
//
//  Created by Casey on 10/24/16.
//  AVL-Tree Data Structure. A self-balancing binary search tree where every node is balanced by a height of no more than 1.
//  Based off of https://tfetimes.com/c-avl-tree/ implementation
//


#ifndef AVLTree_h
#define AVLTree_h


#include<iostream>
#include "file.h"
#include "DSVector.hpp"




template <class T>
class AVLNode {
    
    template<class U> friend class AVLTree;
public:
    T data;
    int height;
    
    AVLNode<T>* right;
    AVLNode<T>* left;
    AVLNode<T>* parent;
    
    // destructor for each node
    ~AVLNode()
    {
        delete left;
        delete right;
    }
    
    // Constructor to initialize node(parent) with an element
    AVLNode(const T& initial, AVLNode* p)
    {
        left = nullptr;
        right = nullptr;
        parent = p;
        data = initial;
        height = 0;
        
    }
    
};


template <class T>
class AVLTree {

private:
    AVLNode<T>* root;


    AVLNode<T>* rotateLeft(AVLNode<T>*);
    AVLNode<T>* rotateRight(AVLNode<T>*);
    AVLNode<T>* rotateLeftRight(AVLNode<T>*);
    AVLNode<T>* rotateRightLeft(AVLNode<T>*);
    
    void rebalance(AVLNode<T>*);
    int height(AVLNode<T>*);
    void getBalance(AVLNode<T>*);
    
    void postOrder(AVLNode<T>*);
    
    
public:
    int numElements;
    
    AVLTree(void);
    ~AVLTree(void);
    bool insert(T);
    
    int getNumElements();
    
    void postOrder();
    
    void searchWord(std::string, std::string, std::string, bool, std::string, int, std::ofstream&);
    void search(AVLNode<T>*, std::string ,std::string, std::string, bool, std::string, int, std::ofstream&);
    bool searchword(Vector<std::string>, std::string);

};


// destructor to delete a root which will also delete the children until it is fully deleted
template <class T>
AVLTree<T>::~AVLTree()
{
    delete root;
    numElements = 0;
}


// constructor for initializing a avltree
template <class T>
AVLTree<T>::AVLTree()
{
    root = nullptr;
    numElements = 0;
}


// inserts an element in teh correct placement while keeping the balance
template<class T>
bool AVLTree<T>::insert(T data)
{
    // creates a new tree if is is yet to exist
    if(root == nullptr)
    {
        root = new AVLNode<T>(data, nullptr);
    }
    
    //if its not empty
    else
    {
        AVLNode<T>*n = root;
        
        AVLNode<T>* parent;
        
        while(true)
        {
            // if teh element already exists then return
            if(n->data == data)
            {
                return false;
            }
            
            parent = n;
            
            // sets goLeft as true if the new data is greater than the tree's value
            bool goLeft = n->data > data;
            // based on true or false, n will equal teh left or the right child
            n = goLeft ? n->left : n->right;
            
            // once the node is found where it is going to be placed, it will be inserted based off it is greater or less than
            if(n == nullptr)
            {
                // inserts on the left
                if(goLeft)
                {
                    parent->left = new AVLNode<T>(data, parent);
                }
                
                //inserts on the right
                else
                {
                    parent->right = new AVLNode<T>(data, parent);
                }
                
                // rebalances the tree
                rebalance(parent);
                break;
            }
        }
    }
    
    // adds to teh total number of elements
    numElements++;
    // returns true once the insertion is completed
    return true;
}





// perfroms a left rotation
template<class T>
AVLNode<T>* AVLTree<T>::rotateLeft(AVLNode<T>* rhs)
{
    //gets right child and make it the "root" of the subtree
    AVLNode<T>* temp = rhs->right;
    
    // rearranging teh pointers
    temp->parent = rhs->parent;
    
    rhs->right = temp->left;
    
    if(rhs->right != nullptr)
    {
        rhs->right->parent = rhs;
    }
    
    temp->left = rhs;
    rhs->parent = temp;
    
    if(temp->parent != nullptr)
    {
        if(temp->parent->right == rhs)
        {
            temp->parent->right = temp;
        }
        else
        {
            temp->parent->left = temp;
        }
    }
    
    // gets new balances for the objects
    getBalance(rhs);
    getBalance(temp);
    return temp;
}




// rotates a right rotation
template<class T>
AVLNode<T>* AVLTree<T>::rotateRight(AVLNode<T>* rhs)
{
    // gets left child and makes it the root
    AVLNode<T> *temp2 = rhs->left;
    
    // rotates new value to teh top
    temp2->parent = rhs->parent;
    
    rhs->left = temp2->right;
    
    if(rhs->left != nullptr)
    {
        rhs->left->parent = rhs;
    }
    
    temp2->right = rhs;
    rhs->parent = temp2;
    
    if(temp2->parent != nullptr)
    {
        if(temp2->parent->right == rhs)
        {
            temp2->parent->right = temp2;
        }
        else
        {
            temp2->parent->left = temp2;
        }
    }
    
    // gets the balance/heights of these trees
    getBalance(rhs);
    getBalance(temp2);
    return temp2;
}



//performs double rotation
template<class T>
AVLNode<T>* AVLTree<T>::rotateLeftRight(AVLNode<T>* rhs)
{
    rhs->left = rotateLeft(rhs->left);
    return rotateRight(rhs);
}



// performs a double rotation
template<class T>
AVLNode<T>* AVLTree<T>::rotateRightLeft(AVLNode<T>* rhs)
{
    rhs->right = rotateRight(rhs->right);
    return rotateLeft(rhs);
}



// finds height of a subtree/tree
template <class T>
int AVLTree<T>::height(AVLNode<T>* rhs)
{
    // if has no element and it returns -1 for teh case of no seg faults
    if (rhs == nullptr)
    {
        return -1;
    }
    
    return 1 + std::max(height(rhs->left), height(rhs->right));
}



template <class T>
void AVLTree<T>::rebalance(AVLNode<T>* rhs)
{
    // gets the balance for the first location
    getBalance(rhs);
    
    // this is for the left side
    if (rhs->height == -2)
    {
        if(height(rhs->left->left) >= height(rhs->left->right))
        {
            rhs = rotateRight(rhs);
        }
        else
        {
            rhs = rotateLeftRight(rhs);
        }
    }
    
    // for the right side
    else if (rhs->height == 2)
    {
        if(height(rhs->right->right) >= height(rhs->right->left))
        {
            rhs = rotateLeft(rhs);
        }
        else
        {
            rhs = rotateRightLeft(rhs);
        }
    }
    
    // recursively call this function until balanced
    if (rhs->parent != nullptr)
    {
        rebalance(rhs->parent);
    }
    
    else
    {
        root = rhs;
    }
}



// finds the balance by mesuring the heights of the inputed subtress
template<class T>
void AVLTree<T>::getBalance(AVLNode<T>* rhs)
{
    // sets overall height to the substitution of the two subtrees
    rhs->height = height(rhs->right) - height(rhs->left);
}

// return the number of elements in the avl tree
template<class T>
int AVLTree<T>::getNumElements()
{
    return numElements;
}

// mmakes call to the recursive function
template<class T>
void AVLTree<T>::postOrder()
{
    postOrder(root);
}


// postorder iterator mainly for testing
template<class T>
void AVLTree<T>::postOrder(AVLNode<T>* rhs)
{
    // if node is valid
    if(rhs == nullptr)
    {
        return;
    }
    
    postOrder(rhs->left);
    postOrder(rhs->right);
    
    // visits the node and gets infromation
    // testing case, just output the int/string/char or whatever is the data
    //std::cout << rhs->data << std::endl;
    //One used when item is just simple vairables
    std::cout << rhs->data.ID << std::endl;
    
}

//Inorder search that is recursive
template<class T>
void AVLTree<T>::searchWord(std::string andOr, std::string one, std::string two, bool nOT, std::string three, int notword, std::ofstream &outputs)
{
    search(root, andOr, one, two, nOT, three, notword, outputs);
    
}

// gets individual document through Inorder then sees if word is present or not
template<class T>
void AVLTree<T>::search(AVLNode<T>* rhs, std::string andOr, std::string one, std::string two, bool nOT, std::string three, int notword, std::ofstream &outputs)
{
    if(rhs == nullptr)
    {
        return ;
    }
    // goes left on avltree
    search(rhs->left, andOr, one, two, nOT, three, notword, outputs);
    
    
    //std::cout << rhs->data.ID << std::endl;
    
    //if there is a not
    if(nOT == true)
    {
        // if it is not and has and and
       if(andOr == "AND")
       {
           // depending on the number of wrods in the query
           if(three != "")
           {
                if(searchword(rhs->data.words, one) == true && searchword(rhs->data.words, two) == true && searchword(rhs->data.words, three) == false)
                {
                    //std::cout << rhs->data.ID << "|" << rhs->data.docName << "|" << rhs->data.url <<std::endl;
                    outputs << rhs->data.ID << "|" << rhs->data.docName << "|" << rhs->data.url <<std::endl;
                }
           }
           if(three == "")
           {
               if(searchword(rhs->data.words, one) == true && searchword(rhs->data.words, two) == false)
               {
                   //std::cout << rhs->data.ID << "|" << rhs->data.docName << "|" << rhs->data.url <<std::endl;
                   outputs << rhs->data.ID << "|" << rhs->data.docName << "|" << rhs->data.url <<std::endl;
               }
           }
       }
        // if the quert is not and or
       else if(andOr == "OR")
       {
           // depneding on number of queries
           if(three != "")
           {
               if(searchword(rhs->data.words, one) == true || searchword(rhs->data.words, two) == true)
               {
                   if(searchword(rhs->data.words, three) == false)
                   {
                       //std::cout << rhs->data.ID << "|" << rhs->data.docName << "|" << rhs->data.url <<std::endl;
                       outputs << rhs->data.ID << "|" << rhs->data.docName << "|" << rhs->data.url <<std::endl;
                   }
               }
           }
           if(three == "")
           {
               if(searchword(rhs->data.words, one) == true && searchword(rhs->data.words, two) == false)
               {
                   //std::cout << rhs->data.ID << "|" << rhs->data.docName << "|" << rhs->data.url <<std::endl;
                   outputs << rhs->data.ID << "|" << rhs->data.docName << "|" << rhs->data.url <<std::endl;
               }
           }
       }
        
    }
    
    // if there is no nor
    else
    {
        // query begins with an AND
        if(andOr == "AND")
        {
            // depneding on the number one wrods in the query
            if(three != "")
            {
                if(searchword(rhs->data.words, one) == true && searchword(rhs->data.words, two) == true && searchword(rhs->data.words, three) == true)
                {
                    //std::cout << rhs->data.ID << "|" << rhs->data.docName << "|" << rhs->data.url <<std::endl;
                    outputs << rhs->data.ID << "|" << rhs->data.docName << "|" << rhs->data.url <<std::endl;
                }
            }
            // two words
            else if(two != "" && three == "")
            {
                if(searchword(rhs->data.words, one) == true && searchword(rhs->data.words, two) == true)
                {
                    //std::cout << rhs->data.ID << "|" << rhs->data.docName << "|" << rhs->data.url <<std::endl;
                    outputs << rhs->data.ID << "|" << rhs->data.docName << "|" << rhs->data.url <<std::endl;
                }
            }
            
            // one word
            else if(two == "")
            {
                if(searchword(rhs->data.words, one) == true)
                {
                    //std::cout << rhs->data.ID << "|" << rhs->data.docName << "|" << rhs->data.url <<std::endl;
                    outputs << rhs->data.ID << "|" << rhs->data.docName << "|" << rhs->data.url <<std::endl;
                }
            }
        }
        
        // or query with no NOT
        else if(andOr == "OR")
        {
            if(searchword(rhs->data.words, one) == true || searchword(rhs->data.words, two) == true || searchword(rhs->data.words, three) == true)
            {
                //std::cout << rhs->data.ID << "|" << rhs->data.docName << "|" << rhs->data.url <<std::endl;
                outputs << rhs->data.ID << "|" << rhs->data.docName << "|" << rhs->data.url <<std::endl;
            }
        }
    }
 
    // goes right on avltree
    search(rhs->right, andOr, one, two, nOT, three, notword, outputs);
}

//searches for the word in the document and returns true if present
template<class T>
bool AVLTree<T>::searchword(Vector<std::string> words, std::string w)
{
    for(int i = 0; i < words.size(); i++)
    {
        if(w == words[i])
        {
            return true;
        }
    }
    return false;
}


#endif /* AVLTree_h */
