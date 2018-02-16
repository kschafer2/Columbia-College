//
//  BinaryTree.h
//  CISS350 Assignment 6
//
//  Created by Kyle Schafer on 7/31/17.
//  Copyright © 2017 Kyle Schafer. All rights reserved.
//

#include <fstream>
#include <iostream>
#include <string>
#include "Queue.h"
using namespace std;

#ifndef BinaryTree_h
#define BinaryTree_h

//ENUMERATED ORDERTYPE
//used to specify binary tree traversal mode
enum OrderType {PRE_ORDER, IN_ORDER, POST_ORDER};

//TREENODE STRUCTURE TEMPLATE
template<class T>
struct TreeNode
{
    T info; //to hold the node's data
    TreeNode<T>* left; //points to the node's left child
    TreeNode<T>* right; //points to the node's right child
};

//BINARY TREE CLASS TEMPLATE
template<class T>
class BinaryTree
{
private:
    
//PRIVATE MEMBER VARIABLES
    TreeNode<T>* root; //to point to the tree's
    Queue<T> preQue; //queue of tree's nodes in pre order
    Queue<T> inQue; //queue of tree's nodes in order
    Queue<T> postQue; //queue of tree's nodes in post order
    
//PRIVATE RECURSIVE HELPER FUNCTIONS
/* 1.  */     void Destroy(TreeNode<T>*&);
/* 2.  */     void CopyTree(TreeNode<T>*&, const TreeNode<T>*);
/* 3.  */     int CountNodes(TreeNode<T>*) const;
/* 4.  */     void Retrieve(TreeNode<T>*, T&, bool&);
/* 5.  */     void Insert(TreeNode<T>*&, T);
/* 6.  */     void GetPrevious(TreeNode<T>*, T&);
/* 7.  */     void DeleteNode(TreeNode<T>*&);
/* 8.  */     void Delete(TreeNode<T>*&, T);
/* 9.  */     void PreOrder(TreeNode<T>*, Queue<T>&);
/* 10. */     void InOrder(TreeNode<T>*, Queue<T>&);
/* 11. */     void PostOrder(TreeNode<T>*, Queue<T>&);
/* 12. */     ostream& PrintTree(OrderType, ostream&, TreeNode<T>*) const;
    
public:
    
//CONSTRUCTOR, DESTRUCTOR, COPY CONSTRUCTOR
/* 13. */     BinaryTree();
/* 14. */     ~BinaryTree();
/* 15. */     BinaryTree(const BinaryTree<T>&);
    
//OVERLOADED OPERATORS
/* 16. */     void operator = (const BinaryTree<T>&);
    
//PUBLIC MEMBER FUNCTIONS
/* 17. */     void MakeEmpty();
/* 18. */     bool IsEmpty() const;
/* 19. */     bool IsFull() const;
/* 20. */     int GetLength() const;
/* 21. */     T FindItem(T, bool&);
/* 22. */     void PutItem(T);
/* 23. */     void DeleteItem(T);
/* 24. */     void ResetTree(OrderType);
/* 25. */     T GetNextItem (OrderType, bool&);
/* 26. */     ostream& Print(OrderType, ostream&) const;
};

#endif /* BinaryTree_h */

/*--------------------------------------------------------------------------------------------
 1. FUNCTION DESTROY
 ---------------------------------------------------------------------------------------------
 
 -Deletes all nodes from the tree
 
 */

template <class T>
void BinaryTree<T>::Destroy(TreeNode<T>*& tree)
{
    if(tree != nullptr)
    {
        Destroy(tree->left); //destroys left subtree
        Destroy(tree->right); //destroys right subtree
        delete tree; //destroys node
    }
}

/*--------------------------------------------------------------------------------------------
 2. FUNCTION COPY TREE
 ---------------------------------------------------------------------------------------------
 
 -Allocate a copy of the original tree
 
 */

template <class T>
void BinaryTree<T>::CopyTree(TreeNode<T>*& copy, const TreeNode<T>* original)
{
    if(original == nullptr)
        copy = nullptr;
    else
    {
        copy = new TreeNode<T>;
        copy->info = original->info;
        CopyTree(copy->left, original->left);
        CopyTree(copy->right, original->right);
    }
}

/*--------------------------------------------------------------------------------------------
 3. FUNCTION COUNT NODES
 ---------------------------------------------------------------------------------------------
 
 -Returns the number of nodes in a tree
 
 */

template <class T>
int BinaryTree<T>::CountNodes(TreeNode<T>* tree) const
{
    if(tree == nullptr)
        return 0;
    else
        return CountNodes(tree->left) + CountNodes(tree->right) + 1;
}

/*--------------------------------------------------------------------------------------------
 4. FUNCTION RETRIEVE
 ---------------------------------------------------------------------------------------------
 
 -Searches for item with key "item"
 -If found, returns changes item and sets found to true
 -Otherwise, item is unchanged and sets found to false
 
 */

template <class T>
void BinaryTree<T>::Retrieve(TreeNode<T>* tree, T& item, bool& found)
{
    if(tree == nullptr)
        found = false;
    
    else if(item < tree->info)
        Retrieve(tree->left, item, found); //searches through left subtree
    
    else if(item > tree->info)
        Retrieve(tree->right, item, found); //searches through right subtree
    
    else
    {
        item = tree->info; //item found when item is not less than or greater than info
        found = true;
    }
}

/*--------------------------------------------------------------------------------------------
 5. FUNCTION INSERT
 ---------------------------------------------------------------------------------------------
 
 -Inserts an item into the tree in its proper place
 
 */

template <class T>
void BinaryTree<T>::Insert(TreeNode<T> *& tree, T item)
{
    if(tree == nullptr)
    {
        tree = new TreeNode<T>; //allocates new node
        tree->right = nullptr;
        tree->left = nullptr;
        tree->info = item; //info set to item
    }
    
    //inserts new node in proper place based on info relation to all other node info
    else if (item < tree->info)
    {
        Insert(tree->left, item); //recursive call to left subtree if item is less than info
    }
    else
        Insert(tree->right, item); //recursive call to right subtree if item is less than info
}

/*--------------------------------------------------------------------------------------------
 6. FUNCTION GET PREVIOUS
 ---------------------------------------------------------------------------------------------
 
 -Data set to info of node with info closest to but lower than node's info
 
 */

template <class T>
void BinaryTree<T>::GetPrevious(TreeNode<T>* tree, T& data)
{
    while (tree->right != nullptr)
        tree = tree->right;
    
    data = tree->info;
}

/*--------------------------------------------------------------------------------------------
 7. FUNCTION DELETE NODE
 ---------------------------------------------------------------------------------------------
 
 -If node to be deleted has only one child, sets node info to child's info
 -Deletes the child
 
 -If node to be deleted has two children, calls function 6. Get Previous
 -Sets node info to previous node's info and deletes the previous node
 
 */

template <class T>
void BinaryTree<T>::DeleteNode(TreeNode<T>*& tree)
{
    T data;
    TreeNode<T>* treePtr;
    
    treePtr = tree;
    if(tree->left == nullptr)
    {
        tree = tree->right;
        delete treePtr;
    }
    else if(tree->right == nullptr)
    {
        tree = tree->left;
        delete treePtr;
    }
    else
    {
        GetPrevious(tree->left, data);
        tree->info = data;
        Delete(tree->left, data);
    }
}

/*--------------------------------------------------------------------------------------------
 8. FUNCTION DELETE
 ---------------------------------------------------------------------------------------------
 
 -Searches the tree for item
 -If the item is found, calls function 7. Delete Node to delete the node
 
 */

template <class T>
void BinaryTree<T>::Delete(TreeNode<T>*& tree, T item)
{
    if(item < tree->info)
        Delete(tree->left, item);
    else if(item > tree->info)
        Delete(tree->right, item);
    else
        DeleteNode(tree);
}

/*--------------------------------------------------------------------------------------------
 9. FUNCTION PRE ORDER
 ---------------------------------------------------------------------------------------------
 
 -Creates queue of tree items in pre order
 
 */

template <class T>
void BinaryTree<T>::PreOrder(TreeNode<T>* tree, Queue<T>& preQue)
{
    if(tree != nullptr)
    {
        //Enqueues node, recursion for left subtree, then recursion for right subtree
        preQue.Enqueue(tree->info);
        PreOrder(tree->left, preQue);
        PreOrder(tree->right, preQue);
    }
}

/*--------------------------------------------------------------------------------------------
 10. FUNCTION IN ORDER
 ---------------------------------------------------------------------------------------------
 
 -Creates queue of tree items in order
 
 */

template <class T>
void BinaryTree<T>::InOrder(TreeNode<T>* tree, Queue<T>& inQue)
{
    if(tree != nullptr)
    {
        //recursion for left subtree, enqueues node, then recursion for right subtree
        InOrder(tree->left, inQue);
        inQue.Enqueue(tree->info);
        InOrder(tree->right, inQue);
    }
}

/*--------------------------------------------------------------------------------------------
 11. FUNCTION POST ORDER
 ---------------------------------------------------------------------------------------------
 
 -Creates queue of tree items in post order
 
 */

template <class T>
void BinaryTree<T>::PostOrder(TreeNode<T>* tree, Queue<T>& postQue)
{
    if(tree != nullptr)
    {
        //recursion for left subtree, recursion for right subtree, then enqueues node
        PostOrder(tree->left, postQue);
        PostOrder(tree->right, postQue);
        postQue.Enqueue(tree->info);
    }
}

/*--------------------------------------------------------------------------------------------
 12. FUNCTION PRINT TREE
 ---------------------------------------------------------------------------------------------
 
 -Sends tree information to stream in designated order
 -Returns stream
 
 */

template <class T>
ostream& BinaryTree<T>::PrintTree(OrderType order, ostream& stream, TreeNode<T>* tree) const
{
    if(tree != nullptr)
    {
        switch(order)
        {
                //sends node info, recursion for left subtree, then recursion for right subtree
            case PRE_ORDER:  stream << tree->info << endl;
                PrintTree(PRE_ORDER, stream, tree->left);
                PrintTree(PRE_ORDER, stream, tree->right);
                break;
                
                //recursion for left subtree, sends node info, then recursion for right subtree
            case IN_ORDER:   PrintTree(IN_ORDER, stream, tree->left);
                stream << tree->info << endl;
                PrintTree(IN_ORDER, stream, tree->right);
                break;
                
                //recursion for left subtree, recursion for right subtree, then sends node info
            case POST_ORDER: PrintTree(POST_ORDER, stream, tree->left);
                PrintTree(POST_ORDER, stream, tree->right);
                stream << tree->info << endl;
                break;
        }
    }
    return stream;
}

/*--------------------------------------------------------------------------------------------
 13. CONSTRUCTOR
 ---------------------------------------------------------------------------------------------
 
 -Sets root to nullptr
 
 */

template <class T>
BinaryTree<T>::BinaryTree()
{
    root = nullptr;
}

/*--------------------------------------------------------------------------------------------
 14. DESTRUCTOR
 ---------------------------------------------------------------------------------------------
 
 -Calls function 1. Destroy to delete all nodes
 
 */

template <class T>
BinaryTree<T>::~BinaryTree()
{
    Destroy(root);
}

/*--------------------------------------------------------------------------------------------
 15. COPY CONSTRUCTOR
 ---------------------------------------------------------------------------------------------
 
 -Calls function 2. Copy Tree to allocate a copy of original tree
 
 */

template <class T>
BinaryTree<T>::BinaryTree(const BinaryTree<T>& original)
{
    CopyTree(root, original.root);
}

/*--------------------------------------------------------------------------------------------
 16. ASSIGNMENT OPERATOR OVERLOAD
 ---------------------------------------------------------------------------------------------
 
 -Destroys current nodes in the tree
 -Calls function 2. Copy Tree to allocate a copy of original tree
 
 */

template <class T>
void BinaryTree<T>::operator = (const BinaryTree<T>& original)
{
    if(&original == this)
        return;
    Destroy(root);
    CopyTree(root, original.root);
}

/*--------------------------------------------------------------------------------------------
 17. FUNCTION MAKE EMPTY
 ---------------------------------------------------------------------------------------------
 
 -Calls function 1. Destroy to deallocate all nodes
 -Sets root to nullptr
 
 */

template <class T>
void BinaryTree<T>::MakeEmpty()
{
    Destroy(root);
    root = nullptr;
}

/*--------------------------------------------------------------------------------------------
 18. FUNCTION IS EMPTY
 ---------------------------------------------------------------------------------------------
 
 -Returns true if tree is empty
 -Otherwise returns false
 
 */

template <class T>
bool BinaryTree<T>::IsEmpty() const
{
    if(root == nullptr)
        return true;
    else
        return false;
}

/*--------------------------------------------------------------------------------------------
 19. FUNCTION IS FULL
 ---------------------------------------------------------------------------------------------
 
 -Returns true if there's no space to store another node
 -Otherwise returns false
 
 */

template <class T>
bool BinaryTree<T>::IsFull() const
{
    TreeNode<T>* newNode;
    
    //try to create a new node
    try
    {
        newNode = new TreeNode<T>;
        delete newNode;
        return false;
    }
    catch(bad_alloc exception)
    {
        return true;
    }
}

/*--------------------------------------------------------------------------------------------
 20. FUNCTION GET LENGTH
 ---------------------------------------------------------------------------------------------
 
 -Calls function 3. Count Nodes to find number of nodes in the whole tree
 
 */

template <class T>
int BinaryTree<T>::GetLength() const
{
    return CountNodes(root);
}

/*--------------------------------------------------------------------------------------------
 21. FUNCTION FIND ITEM
 ---------------------------------------------------------------------------------------------
 
 -Calls function 4. Retieve to find key matching item
 -Returns item
 
 */

template <class T>
T BinaryTree<T>::FindItem(T item, bool& found)
{
    Retrieve(root, item, found);
    
    return item;
}

/*--------------------------------------------------------------------------------------------
 22. FUNCTION PUT ITEM
 ---------------------------------------------------------------------------------------------
 
 -Calls function 5. Insert to insert an item into the tree
 
 */

template <class T>
void BinaryTree<T>::PutItem(T item)
{
    Insert(root, item);
}

/*--------------------------------------------------------------------------------------------
 23. FUNCTION DELETE ITEM
 ---------------------------------------------------------------------------------------------
 
 -Calls function 8. Delete to delete item
 
 */

template <class T>
void BinaryTree<T>::DeleteItem(T item)
{
    Delete(root, item);
}

/*--------------------------------------------------------------------------------------------
 24. FUNCTION RESET TREE
 ---------------------------------------------------------------------------------------------
 
 -Creates order function corresponding to traversal order type
 
 */

template <class T>
void BinaryTree<T>::ResetTree(OrderType order)
{
    switch(order)
    {
        case PRE_ORDER:  PreOrder(root, preQue);
                         break;
        
        case IN_ORDER:   InOrder(root, inQue);
                         break;
        
        case POST_ORDER: PostOrder(root, postQue);
                         break;
    }
}

/*--------------------------------------------------------------------------------------------
 25. FUNCTION GET NEXT ITEM
 ---------------------------------------------------------------------------------------------
 
 -Dequeues queue corresponding to traversal order
 -Finished = true if the last item in the queue was dequeued
 -Returns dequeued item
 
 */

template <class T>
T BinaryTree<T>::GetNextItem (OrderType order, bool& finished)
{
    T item;
    finished = false;
    switch(order)
    {
        case PRE_ORDER:  preQue.Dequeue(item);
            
                         if(preQue.IsEmpty())
                            finished = true;
                         break;
            
        case IN_ORDER:   inQue.Dequeue(item);
            
                         if(inQue.IsEmpty())
                             finished = true;
                         break;
            
        case POST_ORDER: postQue.Dequeue(item);
            
                         if(postQue.IsEmpty())
                             finished = true;
                         break;
    }
    return item;
}

/*--------------------------------------------------------------------------------------------
 26. FUNCTION PRINT
 ---------------------------------------------------------------------------------------------
 
 -Calls function 12. Print Tree to output tree information in designated order
 
 */

template <class T>
ostream& BinaryTree<T>::Print(OrderType order, ostream& stream) const
{
    switch(order)
    {
        case PRE_ORDER:  return PrintTree(PRE_ORDER, stream, root);
                         break;
            
        case IN_ORDER:   return PrintTree(IN_ORDER, stream, root);
                         break;
            
        case POST_ORDER: return PrintTree(POST_ORDER, stream, root);
                         break;
    }
}
