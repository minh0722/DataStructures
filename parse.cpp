#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <climits>

using namespace std;

// <дърво> ::= (<корен> (<празен низ>|<списък от наследници>)),
// където
// <корен> ::= <цяло число>
// <списък от наследници> ::= <дърво> | <дърво>,<списък от наследници>

// (5 ((9 ()),(1 ((4 ()),(12 ()),(42 ())))))

struct Node
{
    int data;
    std::vector<Node*> children;
};

// (5 ((9 ()), (1 ((4 ()), (12 ()), (42 ())))))

Node* parse(ifstream& file)
{
    Node* root = nullptr;
    
    while(!file.eof())
    {
        file.ignore();          // ignore '('
        
        Node* newNode = new Node;
        file >> newNode->data;
        file.ignore();          // skip ' '
        
        while(file.peek() != ')')
        {
            file.ignore();      // skip '('
            
            newNode->children.push_back(parse(file));
        
            if(file.peek() == ',')
            {
                file.ignore();      // skip ','
                file.ignore();      // skip ' '
            }
            else
            {

            }
        }
        
        
    }
    
    return root;
}

Node* parseHelper(const char* name)
{
    ifstream file(name, ios::in);
    parse(file);
}

// correct!
int iterate(Node* node)
{
    if(node->children.empty())
        return node->data;
    
    int maxChildSum = node->children[0]->data;
    
    for(int i = 1; i < node->children.size(); ++i)
    {
        Node* child = node->children[i];
        
        maxChildSum = max(maxChildSum, iterate(child));
    }
    
    return node->data + maxChildSum;
}

int main()
{
    Node* root = new Node;
    root->data = 5;
    
    for(int i = 0; i < 2; ++i)
    {
        root->children.push_back(new Node);        
    }
    
    root->children[0]->data = 9;
    root->children[1]->data = 1;
    
    for(int i = 0; i < 3; ++i)
        root->children[1]->children.push_back(new Node);
    
    root->children[1]->children[0]->data = 4;
    root->children[1]->children[1]->data = 12;
    root->children[1]->children[2]->data = 42;
    
    cout << iterate(root) << endl;
    
    return 0;
}