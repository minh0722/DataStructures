// ordered binary tree

#include "util.h"

template <typename T>
class BinarySearchTree
{
public:
    BinarySearchTree();
    ~BinarySearchTree();
    
    void Add(const T& value);
    void Remove(const T& value);
    
    bool IsEmpty();
    
private:
    struct Node
    {
        Node() : left(nullptr), right(nullptr) {}
        Node(const T& d) : left(nullptr), right(nullptr), data(d) {}
        
        Node* left;
        Node* right;
        T data;
    };
    
    void AddInternal(const T& value, Node*& node);
    void RemoveInternal(const T& value, Node* node);
    void Destroy(Node*& node);
    Node** GetRightMostNode(Node** parent);
    Node** GetLeftMostNode(Node** parent);
    
    Node* m_Root;
};


/*******************************************************************************************/
/*******************************************************************************************/
/*******************************************************************************************/

template <typename T>
BinarySearchTree<T>::BinarySearchTree() : m_Root(nullptr) {}

template <typename T>
BinarySearchTree<T>::~BinarySearchTree()
{
    Destroy(m_Root);
}

template <typename T>
void BinarySearchTree<T>::Add(const T& value)
{
    AddInternal(value, m_Root);
}

template <typename T>
void BinarySearchTree<T>::Remove(const T& value)
{
    RemoveInternal(value, m_Root);
}

template <typename T>
bool BinarySearchTree<T>::IsEmpty() 
{
    return m_Root == nullptr;
}

template <typename T>
void BinarySearchTree<T>::AddInternal(const T& value, BinarySearchTree<T>::Node*& node)
{
    if(!node)
    {
        node = new Node(value);
    }
    else if(value <= node->data)
    {
        AddInternal(value, node->left);
    }
    else
    {
        AddInternal(value, node->right);
    }    
}

template <typename T>
void BinarySearchTree<T>::RemoveInternal(const T& value, BinarySearchTree<T>::Node* node)
{
    if(!node)
    {
        return;
    }

    if(value == node->data)
    {
        if(node->left)
        {
            Node** rightMostNodeOfLeftTree = GetRightMostNode(&(node->left));
            Util::Swap(node->data, (*rightMostNodeOfLeftTree)->data);
            Destroy(*rightMostNodeOfLeftTree);
        }
        else if(node->right)
        {
            Node** leftMostNodeOfRightTree = GetLeftMostNode(&(node->right));
            Util::Swap(node->data, (*leftMostNodeOfRightTree)->data);
            Destroy(*leftMostNodeOfRightTree);
        }
        else
        {
            delete node;
        }
    }
    else if(value <= node->data)
    {
        RemoveInternal(value, node->left);
    }
    else
    {
        RemoveInternal(value, node->right);
    }
}

template <typename T>
void BinarySearchTree<T>::Destroy(BinarySearchTree<T>::Node*& node)
{
    if(!node)
    {
        return;
    }
    
    if(node->left)
    {
        Destroy(node->left);
    }
    
    if(node->right)
    {
        Destroy(node->right);
    }
    
    delete node;
    node = nullptr;
}

template <typename T>
typename BinarySearchTree<T>::Node** BinarySearchTree<T>::GetRightMostNode(BinarySearchTree<T>::Node** parent)
{
    Node** current = parent;
    
    while( (*current)->right)
    {
        current = &((*current)->right);
    }
    
    return current;
}

template <typename T>
typename BinarySearchTree<T>::Node** BinarySearchTree<T>::GetLeftMostNode(BinarySearchTree<T>::Node** parent)
{
    Node** current = parent;
    
    while( (*current)->left)
    {
        current = &((*current)->left);
    }
    
    return current;
}