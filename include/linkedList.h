#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include<iostream>
#include<functional>

class Node{
    public:
        Node(int key, double value, Node* next=nullptr);
        Node(const Node& other);
        Node(Node&& other);
        void operator=(const Node& other)=delete;
        void operator=(Node&& other)=delete;
        int key;
        double value;
        Node* next;
};
class LinkedList{
    /* A LinkedList sorted in acessening order*/
    public:
        LinkedList(); 
        LinkedList(Node* head, double valToRemove, size_t size=0);
        LinkedList(const LinkedList& other);
        LinkedList(LinkedList&& other);
        LinkedList operator=(const LinkedList& other);
        LinkedList operator=(LinkedList&& other);
        ~LinkedList();
        void insert(int key, double value);
        void removeKey(int key);
        bool isEmpty() const;
        size_t length() const;
        // LinkedList operator=(LinkedList&& other);
        Node* head;
    protected:
        size_t size;
        double valToRemove;
        void removeVal(double val);
        // void merge(LinkedList)
        void applyAll(std::function<int(int, double)>, std::function<double(int, double)>);
};

Node* merge(Node*, Node*, std::function<double(double, double)>, size_t& sz);
#endif