#include"Polynomial.h"

/* Implemantaion for Polynomial*/
/* Constructor */
Polynomial::Polynomial():LinkedList(nullptr, 0, 0) {}
Polynomial::Polynomial(Node* head, size_t size):LinkedList(head, 0, size){}
Polynomial::Polynomial(const Polynomial& other):LinkedList(other){}
Polynomial::Polynomial(Polynomial&& other):LinkedList(other){}

/* Basic Operation*/
void Polynomial::insert(int key, int value){
    if(key < 0){
        throw std::runtime_error("Invalid Key:"+std::to_string(key));
    }
    LinkedList::insert(key, value);
}

Polynomial Polynomial::operator+(const Polynomial& other){
    size_t sz;
    Node* result = merge(head, other.head, [](int v1, int v2){return v1+v2;}, sz);
    Polynomial newLink(result, sz);
    newLink.removeVal(0);
    return newLink;
}

Polynomial Polynomial::operator+=(const Polynomial& other){
    size_t sz;
    Node* result = merge(head, other.head, [](int v1, int v2){return v1+v2;}, sz);
    // free origin head
    Node* curr = head;
    head = result;
    size = sz;
    while(curr != nullptr){
        Node* temp = curr;
        curr = curr->next;
        delete temp;
    }
    removeVal(0);
    return *this;
}

Polynomial Polynomial::operator-(const Polynomial& other){
    size_t sz;
    Node* result = merge(head, other.head, [](int v1, int v2){return v1-v2;}, sz);
    Polynomial newLinke(result, sz);
    newLinke.removeVal(0);
    return newLinke;
}

Polynomial Polynomial::operator-=(const Polynomial& other){
    size_t sz;
    Node* result = merge(head, other.head, [](int v1, int v2){return v1-v2;}, sz);
    // free origin head
    Node* curr = head;
    head = result;
    size = sz;
    while(curr != nullptr){
        Node* temp = curr;
        curr = curr->next;
        delete temp;
    }
    removeVal(0);
    return *this;
}

Polynomial Polynomial::operator*(const Polynomial& other){
    Polynomial result;
    Node* curr = other.head;
    while(curr != nullptr){
        // int ok = other.key, ov = other.value;
        auto funcOfKey = [curr](int k, int v){
            return k+curr->key;
        };
        auto funcOfVal = [curr](int k, int v){
            return v*curr->value;
        };
        Polynomial temp(*this);
        temp.applyAll(funcOfKey, funcOfVal);
        result += temp;
        curr = curr->next;
    }
    return result;
}

Polynomial Polynomial::operator*=(const Polynomial& other){
    Polynomial result;
    Node*curr = other.head;
    while(curr != nullptr){
        auto funcOfKey = [curr](int k, int v){
            return k+curr->key;
        };
        auto funcOfVal = [curr](int k, int v){
            return v*curr->value;
        };
        Polynomial temp(*this);
        temp.applyAll(funcOfKey, funcOfVal);
        result += temp;
        curr = curr->next;
    }
    size = result.size;
    curr = head;
    while(curr != nullptr){
        Node* temp = curr;
        curr = curr->next;
        delete temp;
    }
    head = std::exchange(result.head, nullptr);
    return *this;

}

int Polynomial::compute(int x) const{
    Node* curr = head;
    int result = 0;
    while(curr != nullptr){
        result += curr->value * pow(x, curr->key);
        curr = curr->next;
    }
    return result;
}

void Polynomial::derive(){
    auto funcOfKey = [](int k, int v){return k-1;};
    auto funcOfVal = [](int k, int v){return k*v;};
    applyAll(funcOfKey, funcOfVal);
    if(head != nullptr && head->key == -1){
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

void Polynomial::printPoly() const{
    if(head == nullptr){
        std::cout << 0 << std::endl;
        return;
    }
    Node* curr = head;
    bool first = true;
    while(curr != nullptr){
        if(curr->key == 0){
            std::cout << curr->value;
            first = false;
        }
        else{
            if(!first){
               std::cout << " + ";
            }else{
                first = false;
            }
            if(curr->value != 1){
                std::cout << curr->value;
            }
            std::cout << "x^" << curr->key;
        }
        curr = curr->next;
    }
    std::cout << std::endl;
}