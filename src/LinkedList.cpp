#include"LinkedList.h"

/* Implementation for class Node */
Node::Node(int key, double value, Node*next):key(key), value(value), next(next){}
Node::Node(const Node& other):key(other.key), value(other.value){}
Node::Node(Node&& other):key(other.key), value(other.value){}

/* Implementation for class LinkedList */
// default constructor
LinkedList::LinkedList():head(nullptr), size(0){}
LinkedList::LinkedList(Node* head, double valToRemove, size_t size):head(head), size(size), valToRemove(valToRemove){
    if(size == 0){
        Node* curr = head;
        while(curr != nullptr){
            curr = curr->next;
            size++;
        }
    }
}
// copy constructor and copy assignment
LinkedList::LinkedList(const LinkedList& other){
    size = 0;
    head = nullptr;
    valToRemove = other.valToRemove;

    if(other.head != nullptr){
        Node* curr = other.head;
        while(curr != nullptr){
            insert(curr->key, curr->value);
            curr = curr->next;
        }
    }
}

LinkedList LinkedList::operator=(const LinkedList& other){
    std::cout << "here" << std::endl;
    Node* curr = head;
    size = other.size;
    valToRemove = other.valToRemove;
    while(curr != nullptr){
        Node* tmp = curr;
        curr = curr->next;
        delete tmp;
    }
    head = nullptr;
    if(other.head != nullptr){
        curr = other.head;
        while(curr != nullptr){
            insert(curr->key, curr->value);
            curr = curr->next;
        }
    }
    return *this;
}

// move constructor and move assignment 
LinkedList::LinkedList(LinkedList&& other){
    size = other.size;
    head = std::exchange(other.head, nullptr);
    valToRemove = other.valToRemove;
}
LinkedList LinkedList::operator=(LinkedList&& other){
    // std::cout << "here" << std::endl;
    size = other.size;
    Node*curr = head;
    while(curr != nullptr){
        Node* temp = curr;
        curr = curr->next;
        delete temp;
    }
    head = std::exchange(other.head, nullptr);
    return *this;
}
/** to be written */
// Destructor
LinkedList::~LinkedList(){
    if(head != nullptr){
        while(head != nullptr){
            Node* temp = head;
            head = head -> next;
            delete temp;
        }
    }
}

bool LinkedList::isEmpty() const{
    return size == 0;
}

size_t LinkedList::length() const{
    return size;
}

// LinkedList Operation
void LinkedList::insert(int key, double value){
    if(value == valToRemove){
        return;
    }
    size++;
    if(head == nullptr){
        head = new Node(key, value);
    }else{
        if(key < head->key){
            Node* newNode = new Node(key, value, head);
            head = newNode;
        }else if(key == head->key){
                head->value = value + head->value;
                size--;
                if(head->value == valToRemove){
                    Node* temp = head;
                    head = head->next;
                    delete(temp);
                    size--;
            }
        }
        else{
            Node* curr = head;
            while(curr-> next && curr->next->key<key){
                curr = curr->next;
            }
            if(curr->next && curr->next->key == key){
                    curr->next->value = curr->next->value + value;
                    size--;
                    if(curr->next->value == valToRemove){
                        Node* temp = curr->next;
                        curr->next = temp->next;
                        delete(temp);
                        size--;
                    }
            }else{
                Node* newNode = new Node(key, value, curr->next);
                curr -> next = newNode; 
            }
        }
    }
}

void LinkedList::removeVal(double val){
    Node* prev = nullptr; Node* curr = head;
    while(curr != nullptr){
        if(curr->value == val){
            size--;
            if(prev == nullptr){
                Node* tmp = curr;
                curr = curr->next;
                head = curr;
                delete tmp;
            }else{
                Node* tmp = curr;
                curr = curr->next;
                prev->next = curr;
                delete tmp;
            }
        }else{
            prev = curr;
            curr = curr->next;
        }
    }
}

void LinkedList::removeKey(int key){
    Node* prev = nullptr; Node* curr = head;
    while(curr != nullptr){
        if(curr->key == key){
            size--;
            if(prev == nullptr){
                Node* tmp = curr;
                curr = curr->next;
                head = curr;
                delete tmp;
            }else{
                Node* tmp = curr;
                curr = curr->next;
                prev->next = curr;
                delete tmp;
            }
            break;
        }else{
            prev = curr;
            curr = curr->next;
        }
    }
}

void LinkedList::applyAll(std::function<int(int, double)> funcOfKey, std::function<double(int, double)> funcOfVal){
    Node* curr = head;
    while(curr != nullptr){
        int k = curr->key; double v = curr->value;
        curr->key = funcOfKey(k, v); curr->value = funcOfVal(k, v);
        curr = curr->next;
    }
}
// Operator Overloading
Node* merge(Node* head1, Node* head2, std::function<double(double, double)>funcOfVal, size_t& sz){
    Node* head = nullptr; Node* tail=head;
    sz = 0;
    while(head1 != nullptr || head2 != nullptr){
        Node* tmp = nullptr;
        if(head1 == nullptr || (head2 != nullptr && head1->key > head2->key)){
            tmp = head2;
            head2 = head2->next;
        }else{
            tmp = head1;
            head1 = head1->next;
        }
        if(head == nullptr){
            head =new Node(tmp->key, tmp->value);
            tail = head;
            sz++;
        }
        else{
            if(tail->key != tmp->key){
                tail->next = new Node(tmp->key, tmp->value);
                tail = tail->next;
                sz++;
            }else{
                tail->value = funcOfVal(tail->value, tmp->value);
            }
        }
    }
    return head;
}