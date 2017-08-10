#include <iostream>
#include <stack>

#include "stack.h"
#include "queue.h"
#include "linkedlist.h"
#include "doublelinkedlist.h"
#include "binarysearchtree.h"
#include "avltree.h"

using namespace std;

class Foo
{
public:
    friend ostream& operator<<(ostream& os, const Foo& f);
    
    virtual void f() {cout << "foo" << endl;}
    void g() {f();}
    
    int data;
};

ostream& operator<<(ostream& os, const Foo& f)
{
    os << f.data;
    return os;
}

class Bar : public Foo
{
public:
    void f() override {cout << "bar" << endl;}
};

int main()
{
    Bar b;
    Foo* f1 = &b;
    f1->g();
    
//     Stack<int> s;
//    
//     for(int i = 0; i < 5; ++i)
//         s.Push(i);
//    
//     Stack<int> s1(s);
//    
//     for(int i = 0; i < 5; ++i)
//     {
//         cout << s.Top() << endl;
//         s.Pop();
//     }
//    
//     for(int i = 0; i < 5; ++i)
//     {
//         cout << s1.Top() << endl;
//         s1.Pop();
//     }
   
//////////////////////////////////////////////////////////////////////////////
    
//     Queue<int> s;
//    
//     for(int i = 0; i < 5; ++i)
//         s.Push(i);
//    
//     Queue<int> s1(s);
//    
//     for(int i = 0; i < 5; ++i)
//     {
//         cout << s.Front() << endl;
//         s.Pop();
//     }
//    
//     for(int i = 0; i < 5; ++i)
//     {
//         cout << s1.Front() << endl;
//         s1.Pop();
//     }
    
//////////////////////////////////////////////////////////////////////////////
    
//     LinkedList<Foo> l;
//     l.PushFront({2});
//     l.PushBack({3});
//     l.PushBack({1});
//    
//     l.InsertAfter(l.Begin(), {7});
//    
//     for(LinkedList<Foo>::Iterator it = l.Begin(); it != l.End(); ++it)
//     {
//         cout << it->data << endl;
//     }
  
//////////////////////////////////////////////////////////////////////////////

//     DoubleLinkedList<Foo> l;
//     l.PushFront({2});
//     l.PushBack({3});
//     l.PushBack({1});
//    
//     l.InsertBefore(l.Begin(), {7});
//    
//     l.Erase(l.Begin() + 1);
//    
//     DoubleLinkedList<Foo> l1(l);
//    
//     for(DoubleLinkedList<Foo>::Iterator it = l.Begin(); it != l.End(); ++it)
//     {
//         cout << it->data << endl;
//     }
//    
//     for(DoubleLinkedList<Foo>::Iterator it = l1.Begin(); it != l1.End(); ++it)
//     {
//         cout << it->data << endl;
//     }
    
////////////////////////////////////////////////////////////////////////
    
    BinarySearchTree<int> t;
    t.Add(20);
    t.Add(10);
    t.Add(15);
    t.Add(5);
    t.Remove(20);

    return 0;
}