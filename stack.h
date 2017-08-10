template <typename T>
class Stack
{
public:
    Stack();
    Stack(const Stack<T>& other);
    ~Stack();
    
    void Push(const T& data);
    void Pop();
    T Top();
    size_t Size();
    
private:
    
    struct Node
    {
        T data;
        Node* next;
    };
    
    Node* m_Top;
    size_t m_Size;
};


/**************************************************************************************/

template <typename T>
Stack<T>::Stack() : m_Top(nullptr), m_Size(0) {}

template <typename T>
Stack<T>::~Stack()
{
    while(m_Top)
    {
        Node* temp = m_Top->next;
        delete m_Top;
        m_Top = temp;        
    }
}

template <typename T>
Stack<T>::Stack(const Stack<T>& other)
    : m_Top(nullptr), m_Size(0)
{
    Node* otherCurrent = other.m_Top;
    Node* thisCurrent;
    
    while(otherCurrent)
    {
        Node* newNode = new Node;
        newNode->data = otherCurrent->data;
        newNode->next = nullptr;
        
        if(!m_Top)
        {
            m_Top = newNode;
            thisCurrent = newNode;
        }
        else
        {
            thisCurrent->next = newNode;
            thisCurrent = newNode;
        }
        
        otherCurrent = otherCurrent->next;
    }
}

template <typename T>
void Stack<T>::Push(const T& data)
{
    Node* newNode = new Node;
    newNode->data = data;
    newNode->next = m_Top;
    
    m_Top = newNode;
    
    ++m_Size;
}

template <typename T>
void Stack<T>::Pop()
{
    Node* temp = m_Top->next;
    delete m_Top;
    m_Top = temp;
    
    --m_Size;
}
    
template <typename T>
T Stack<T>::Top()
{
    if(m_Top)
        return m_Top->data;
    
    throw std::exception();
}

template <typename T>
size_t Stack<T>::Size()
{
    return m_Size;
}
