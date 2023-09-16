#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include<iostream>
#include<functional>

class Node{
    public:
        Node(int key, int value, Node* next=nullptr);
        Node(const Node& other);
        Node(Node&& other);
        void operator=(const Node& other)=delete;
        void operator=(Node&& other)=delete;
        int key;
        int value;
        Node* next;
};
class LinkedList{
    /* A LinkedList sorted in acessening order*/
    public:
        LinkedList(); 
        LinkedList(Node* head, size_t size=0);
        LinkedList(const LinkedList& other);
        LinkedList(LinkedList&& other);
        ~LinkedList();
        void insert(int key, int value, int valToRemove,
                    bool autoDealWithConfict=false);
        void removeKey(int key);
        bool isEmpty() const;
        size_t length() const;
        // LinkedList operator=(const LinkedList& other);
        LinkedList operator=(LinkedList&& other);
        Node* head;
    protected:
        size_t size;
        void removeVal(int val);
        // void merge(LinkedList)
        void applyAll(std::function<int(int, int)>, std::function<int(int, int)>);
};

Node* merge(Node*, Node*, std::function<int(int, int)>, size_t& sz);
#endif