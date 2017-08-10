template <typename T>
class DoubleLinkedList
{
private:
    struct Node
    {
        Node() : prev(nullptr), next(nullptr) {}
        
        T data;
        Node* prev;
        Node* next;
    };
    
public:
    class Iterator
    {
        friend class DoubleLinkedList<T>;
    public:
        Iterator(Node* node);
        Iterator(const Iterator& other);
        Iterator& operator=(const Iterator& other);
        
        T& operator*();
        T* operator->();
        
        Iterator operator+(int n);
        Iterator operator-(int n);
        
        Iterator& operator++();
        Iterator operator++(int);
        
        Iterator& operator--();
        Iterator operator--(int);
        
        bool operator==(const Iterator& other);
        bool operator!=(const Iterator& other);
                
    private:
        Node* m_Node;
    };
    
public:    
    DoubleLinkedList();
    DoubleLinkedList(const DoubleLinkedList& other);
    ~DoubleLinkedList();
    
    void PushBack(const T& data);                       // O(1)
    void PushFront(const T& data);                      // O(1)
    void PopBack();                                     // O(1)
    void PopFront();                                    // O(1)
    void InsertBefore(Iterator it, const T& value);     // O(1)
    void Erase(const Iterator& it);                     // O(1)
    
    T& Front();
    T& Back();
        
    Iterator Begin();
    Iterator End();
    
    Iterator Begin() const;
    Iterator End() const;
    
    bool IsEmpty() const;
    
private:
    Node* m_Begin;
    Node* m_End;
};


/**************************************************************************************/
/***************************DOUBLE LINKED LIST DEFINITION******************************/
/**************************************************************************************/
template <typename T>
DoubleLinkedList<T>::DoubleLinkedList()
{
    m_End = new Node;
    m_Begin = m_End;
}

template <typename T>
DoubleLinkedList<T>::DoubleLinkedList(const DoubleLinkedList<T>& other)
{
    m_End = new Node;
    m_Begin = m_End;
    
    if(!other.IsEmpty())
    {
        for(DoubleLinkedList<T>::Iterator it = other.Begin(); it != other.End(); ++it)
        {
            PushFront(*it);
        }
    }
}

template <typename T>
DoubleLinkedList<T>::~DoubleLinkedList()
{
    while(m_Begin)
    {
        Node* temp = m_Begin;
        
        m_Begin = m_Begin->next;
        delete temp;
    }
}

template <typename T>
void DoubleLinkedList<T>::PushBack(const T& data)
{
    if(m_Begin == m_End)
    {
        PushFront(data);
    }
    else
    {
        Node* newNode = new Node;
        newNode->data = data;
        
        newNode->next = m_End;
        newNode->prev = m_End->prev;
        
        m_End->prev->next = newNode;
        m_End->prev = newNode;
    }
    
//     Node* newNode = new Node;
//     newNode->data = data;
    
//     // connect the tail and new node
//     newNode->next = m_Begin;
//     m_Begin->prev = newNode;

//     // set the new tail
//     m_Begin = newNode;
}

template <typename T>
void DoubleLinkedList<T>::PushFront(const T& data)
{
    Node* newNode = new Node;
    newNode->data = data;
    newNode->next = m_Begin;
    m_Begin->prev = newNode;
    
    m_Begin = newNode;

//     if(m_Begin == m_End)
//     {
//         PushBack(data);
//     }
//     else
//     {
//         Node* newNode = new Node;
//         newNode->data = data;

//         // connect new node with head and its prev node
//         newNode->prev = m_End->prev;
//         newNode->next = m_End;

//         m_End->prev->next = newNode;
//         m_End->prev = newNode;
//     }
}

template <typename T>
void DoubleLinkedList<T>::PopBack()
{
    if(m_Begin == m_End)
    {
        return;
    }
    
//     Node* temp = m_Begin;
//     m_Begin = m_Begin->next;
//     m_Begin->prev = nullptr;

    Node* temp = m_End;
    m_End = m_End->prev;
    m_End->next = nullptr;
    
    delete temp;
}

// FIX THIS! We flip back and end
template <typename T>
void DoubleLinkedList<T>::PopFront()
{
    if(m_Begin == m_End)
    {
        return;
    }
    
    // has 1 element
    if(m_Begin->next == m_End)
    {
        PopBack();
    }
    else
    {
        Node* lastNode = m_End->prev;
        Node* beforeLastNode = lastNode->prev;
        
        // connect the head with the before the last node
        beforeLastNode->next = lastNode->next;
        m_End->prev = beforeLastNode;
        
        delete lastNode;
    }
}

// FIX THIS! We flip back and end
template <typename T>
T& DoubleLinkedList<T>::Front()
{
    return m_End->prev->data;
}

// FIX THIS! We flip back and end
template <typename T>
T& DoubleLinkedList<T>::Back()
{
    return m_Begin->data;
}

template <typename T>
void DoubleLinkedList<T>::InsertBefore(Iterator it, const T& value)
{
    // get the node at iterator
    Node* itNode = it.m_Node;
    
    if(itNode == m_Begin)
    {
        PushBack(value);
    }
    else if(itNode == m_End)
    {
        PushFront(value);
    }
    else
    {
        Node* newNode = new Node;
        newNode->data = value;
        
        newNode->next = itNode;
        newNode->prev = itNode->prev;
        
        itNode->prev->next = newNode;
        itNode->prev = newNode;
    }
}

template <typename T>
void DoubleLinkedList<T>::Erase(const Iterator& it)
{
    Node* itNode = it.m_Node;
    
    if(itNode == m_Begin)
    {
        PopBack();
    }
    else if(IsEmpty())
    {
        return;
    }
    else if(itNode == m_End->prev)
    {
        PopFront();
    }
    else
    {
        Node* itPrevNode = itNode->prev;
        Node* itNextNode = itNode->next;
        
        itPrevNode->next = itNextNode;
        itNextNode->prev = itPrevNode;
        delete itNode;
    }
}

template <typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::Begin()
{
    return Iterator(m_Begin);
}

template <typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::End()
{
    return Iterator(m_End);
}

template <typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::Begin() const
{
    return Iterator(m_Begin);
}

template <typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::End() const
{
    return Iterator(m_End);
}

template <typename T>
bool DoubleLinkedList<T>::IsEmpty() const
{
    return m_Begin == m_End;
}

/**************************************************************************************/
/*******************************ITERATOR DEFINITION************************************/
/**************************************************************************************/

template <typename T>
DoubleLinkedList<T>::Iterator::Iterator(Node* node) : m_Node(node) {}

template <typename T>
DoubleLinkedList<T>::Iterator::Iterator(const Iterator& other) : m_Node(other.m_Node) {}

template <typename T>
typename DoubleLinkedList<T>::Iterator& DoubleLinkedList<T>::Iterator::operator=(const Iterator& other)
{
    if(this != &other)
    {
        m_Node = other.m_Node;
    }
    
    return *this;
}

template <typename T>
T& DoubleLinkedList<T>::Iterator::operator*()
{
    return m_Node->data;
}

template <typename T>
T* DoubleLinkedList<T>::Iterator::operator->()
{
    return &m_Node->data;
}

template <typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::Iterator::operator+(int n)
{
    Node* itNode = m_Node;
    for(int i = 0; i < n; ++i)
    {
        if(itNode->next)
        {
            itNode = itNode->next;
        }
        else
        {
            break;
        }
    }
    
    return Iterator(itNode);
}

template <typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::Iterator::operator-(int n)
{
    Node* itNode = m_Node;
    for(int i = 0; i < n; ++i)
    {
        if(itNode->prev)
        {
            itNode = itNode->prev;
        }
        else
        {
            break;
        }
    }
    
    return Iterator(itNode);
}


template <typename T>
typename DoubleLinkedList<T>::Iterator& DoubleLinkedList<T>::Iterator::operator++()
{
    m_Node = m_Node->next;
    return *this;
}

template <typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::Iterator::operator++(int)
{
    Node n(m_Node);
    m_Node = m_Node->next;
    
    return n;
}

template <typename T>
typename DoubleLinkedList<T>::Iterator& DoubleLinkedList<T>::Iterator::operator--()
{
    m_Node = m_Node->prev;
    return *this;
}

template <typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::Iterator::operator--(int)
{
    Node n(m_Node);
    m_Node = m_Node->prev;
    
    return n;
}

template <typename T>
bool DoubleLinkedList<T>::Iterator::operator==(const Iterator& other)
{
    return m_Node == other.m_Node;
}

template <typename T>
bool DoubleLinkedList<T>::Iterator::operator!=(const Iterator& other)
{
    return m_Node != other.m_Node;
}













