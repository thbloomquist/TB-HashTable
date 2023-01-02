//
//  Node.h
//

#ifndef _NODE_H_
#define _NODE_H_

// Hash Table node
class Node
{
public:
    // Constructor (private, only for friends)
    Node(std::string str, Node * nxt = nullptr)
    : data(str), next(nxt) {}
    
    std::string data;
    Node *next;
};

#endif
