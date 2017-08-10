#include "util.h"

template <typename T>
class AVLTree
{
public:
    AVLTree();
    ~AVLTree();
    
    void Add(const T& data);
    void Remove(const T& data);
    
private:
    struct Node
    {
        Node* left;
        Node* right;
        T data;
    };
    
    void Destroy(Node*& node);
    void AddInternal(const T& data, Node*& node);
    void RemoveInternal(const T& value, Node* node);
    
    Node* m_Root;
};

template <typename T>
AVLTree<T>::AVLTree() : m_Root(nullptr) {}


template <typename T>
AVLTree<T>::~AVLTree()
{
    Destroy(m_Root);
}

template <typename T>
void AVLTree<T>::Add(const T& data)
{
    AddInternal(data, m_Root);
}

template <typename T>
void AVLTree<T>::Remove(const T& data)
{
    RemoveInternal(data, m_Root);
}

template <typename T>
void AVLTree<T>::Destroy(AVLTree<T>::Node*& node)
{
    if(!node)
        return;
    
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
void AVLTree<T>::AddInternal(const T& value, AVLTree<T>::Node*& node)
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
void AVLTree<T>::RemoveInternal(const T& value, AVLTree<T>::Node* node)
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
            Swap(node->data, (*rightMostNodeOfLeftTree)->data);
            Destroy(*rightMostNodeOfLeftTree);
        }
        else if(node->right)
        {
            Node** leftMostNodeOfRightTree = GetLeftMostNode(&(node->right));
            Swap(node->data, (*leftMostNodeOfRightTree)->data);
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
