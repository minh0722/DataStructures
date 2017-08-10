template <typename T>
class LinkedList
{
private:
    struct Node
    {
        Node() : next(nullptr) {}
        
        T data;
        Node* next;
    };
    
public:       
    class Iterator
    {
        friend class LinkedList<T>;

    public:
        Iterator(Node* node);
        Iterator(const Iterator& other);
        Iterator& operator=(const Iterator& other);
        
        T& operator*();
        T* operator->();
        
        Iterator& operator++();
        Iterator operator++(int);
        
        bool operator==(const Iterator& other);
        bool operator!=(const Iterator& other);
                
    private:
        Node* m_Node;
    };
    
    LinkedList();
    ~LinkedList();
    
    void PushBack(const T& data);       // O(1)
    void PushFront(const T& data);      // O(1)
    void PopBack();                     // O(1)
    void PopFront();                    // O(n)
    
    T& Front();
    T& Back();
    
    void InsertAfter(Iterator it, T value);
//     void Erase(const Iterator& it);  // O(n) so will not implement it
    
    Iterator Begin();
    Iterator End();
    
private:   
    Node* m_Head;
    Node* m_Tail;
};


/**************************************************************************************/
/******************************LINKED LIST DEFINITION**********************************/
/**************************************************************************************/

template <typename T>
LinkedList<T>::LinkedList()
{
    m_Head = new Node;
    
    m_Tail = m_Head;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
    while(m_Tail)
    {
        Node* temp = m_Tail;
        m_Tail = m_Tail->next;
        
        delete temp;
    }
}

template <typename T>
void LinkedList<T>::PushBack(const T& data)
{
    Node* newNode = new Node;
    newNode->data = data;    
    newNode->next = m_Tail;
    
    m_Tail = newNode;
}

template <typename T>
void LinkedList<T>::PushFront(const T& data)
{
    // assign the data to the pivot node
    m_Head->data = data;
    
    //create a new pivot node
    m_Head->next = new Node;
    m_Head = m_Head->next;
}

template <typename T>
void LinkedList<T>::PopBack()
{
    if(m_Tail != m_Head)
    {
        Node* temp = m_Tail;
        m_Tail = m_Tail->next;
        delete temp;
    }
}

template <typename T>
void LinkedList<T>::PopFront()
{
    // find the last node, free the old pivot 
    // and make the last node the new pivot
    
    Node* currentNode = m_Tail;
    while(currentNode->next)
    {
        // find the node before the head (pivot) node
        if(currentNode->next == m_Head)
        {
            Node* temp = currentNode->next;
            
            // the last node now becomes the pivot node
            m_Head = currentNode;
            
            // free the old pivot node
            delete temp;
        }
        
        currentNode = currentNode->next;
    }
}

template <typename T>
T& LinkedList<T>::Front()
{
    if(m_Tail == m_Head)
        throw std::exception();
    
    Node* currentNode = m_Tail;
    while(currentNode->next != m_Head)
    {
        currentNode = currentNode->next;
    }
    
    return currentNode->data;
}

template <typename T>
T& LinkedList<T>::Back()
{
    if(m_Tail == m_Head)
    {
        throw std::exception();
    }
    
    return m_Tail->data;
}

template <typename T>
void LinkedList<T>::InsertAfter(Iterator it, T value)
{
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = nullptr;
    
    // get node at iterator
    Node* itNode = it.m_Node;
    
    // if node at iterator is pivot then insert before it
    if(itNode == m_Head)
    {
        newNode->next = itNode;
        m_Tail = newNode;
    }
    else
    {    
        // get node after iterator
        Node* itNext = itNode->next;

        itNode->next = newNode;
        newNode->next = itNext;
    }
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::Begin()
{
    return Iterator(m_Tail);
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::End()
{
    return Iterator(m_Head);
}


/**************************************************************************************/
/*******************************ITERATOR DEFINITION************************************/
/**************************************************************************************/

template <typename T>
LinkedList<T>::Iterator::Iterator(Node* node) : m_Node(node) {}

template <typename T>
LinkedList<T>::Iterator::Iterator(const Iterator& other) : m_Node(other.m_Node) {}

template <typename T>
typename LinkedList<T>::Iterator& LinkedList<T>::Iterator::operator=(const Iterator& other)
{
    if(this != &other)
    {
        m_Node = other.m_Node;
    }
    
    return *this;
}

template <typename T>
T& LinkedList<T>::Iterator::operator*()
{
    return m_Node->data;
}

template <typename T>
T* LinkedList<T>::Iterator::operator->()
{
    return &m_Node->data;
}

template <typename T>
typename LinkedList<T>::Iterator& LinkedList<T>::Iterator::operator++()
{    
    m_Node = m_Node->next;
    return *this;
}

template <typename T>
typename LinkedList<T>::Iterator LinkedList<T>::Iterator::operator++(int)
{
    Node n(m_Node);
    m_Node = m_Node->next;
    
    return n;
}

template <typename T>
bool LinkedList<T>::Iterator::operator==(const Iterator& other)
{
    return m_Node == other.m_Node;
}

template <typename T>
bool LinkedList<T>::Iterator::operator!=(const Iterator& other)
{
    return m_Node != other.m_Node;
}
