template <typename T>
class Queue
{
public:
    Queue();
    ~Queue();
    Queue(const Queue<T>& other);
    
    void Push(T data);
    void Pop();
    T Front();

private:
    struct Node
    {
        Node* prev;
        T data;
    };
    
    Node* m_Front;
    Node* m_Tail;
};

/************************************************************************************/

template <typename T>
Queue<T>::Queue() : m_Front(nullptr), m_Tail(nullptr) {}

template <typename T>
Queue<T>::~Queue()
{
    while(m_Front)
    {
        Node* temp = m_Front;
        m_Front = m_Front->prev;
        delete temp;
    }
}

template <typename T>
Queue<T>::Queue(const Queue<T>& other)
    : m_Front(nullptr), m_Tail(nullptr)
{
    if(other.m_Tail && other.m_Front)
    {
        Node* otherCurrentNode = other.m_Front;
        Node* thisCurrentNode = m_Front;

        while(otherCurrentNode)
        {
            // create new node
            Node* newNode = new Node;
            newNode->data = otherCurrentNode->data;
            newNode->prev = nullptr;

            // if this front is not set yet
            if(!m_Front)
            {
                m_Front = newNode;
                thisCurrentNode = m_Front;
            }
            else
            {
                thisCurrentNode->prev = newNode;
                thisCurrentNode = newNode;
            }
            
            // if we are at the tail of the other queue
            if(!otherCurrentNode->prev)
            {
                m_Tail = newNode;
            }
            
            otherCurrentNode = otherCurrentNode->prev;
        }
    }
}

template <typename T>
void Queue<T>::Push(T data)
{
    Node* node = new Node;
    node->data = data;
    node->prev = nullptr;
    
    if(m_Tail)
    {
        m_Tail->prev = node;
    }
    
    m_Tail = node;
    
    if(!m_Front)
    {
        m_Front = node;
    }
}

template <typename T>
void Queue<T>::Pop()
{
    Node* temp = m_Front->prev;
    delete m_Front;
    m_Front = temp;
}

template <typename T>
T Queue<T>::Front()
{
    if(m_Front)
    {
        return m_Front->data;
    }
    
    throw std::exception();
}