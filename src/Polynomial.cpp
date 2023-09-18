#include"Polynomial.h"

/* Implemantaion for Polynomial*/
/* Constructor */
Polynomial::Polynomial():LinkedList(nullptr, 0, 0) {}
Polynomial::Polynomial(Node* head, size_t size):LinkedList(head, 0, size){}
Polynomial::Polynomial(const Polynomial& other):LinkedList(other){}
Polynomial::Polynomial(Polynomial&& other):LinkedList(other){}

Polynomial Polynomial::operator=(const Polynomial& other){
    LinkedList::operator=(other);
    return *this;
}
Polynomial Polynomial::operator=(Polynomial&& other){
    LinkedList::operator=(std::move(other));
    return *this;
}
/* Basic Operation*/
void Polynomial::insert(int key, double value){
    // if(key < 0){
    //     throw std::runtime_error("Invalid Key:"+std::to_string(key));
    // }
    LinkedList::insert(key, value);
}

Polynomial Polynomial::operator+(const Polynomial& other){
    size_t sz;
    Node* result = merge(head, other.head, [](double v1, double v2){return v1+v2;}, sz);
    Polynomial newLink(result, sz);
    newLink.removeVal(0);
    return newLink;
}

Polynomial Polynomial::operator+=(const Polynomial& other){
    size_t sz;
    Node* result = merge(head, other.head, [](double v1, double v2){return v1+v2;}, sz);
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
    Polynomial temp(other);
    temp.applyAll([](int k, double v){return k;}, [](int k, double v){return -v;});
    temp.printPoly(std::cout);
    Node* result = merge(head, temp.head, [](double v1, double v2){return (v1+v2);}, sz);
    Polynomial newLinke(result, sz);
    newLinke.removeVal(0);
    return newLinke;
}

Polynomial Polynomial::operator-=(const Polynomial& other){
    size_t sz;
    Polynomial temp(other);
    temp.applyAll([](int k, double v){return k;}, [](int k, double v){return -v;});
    Node* result = merge(head, temp.head, [](double v1, double v2){return (v1+v2);}, sz);
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
        auto funcOfKey = [curr](int k, double v){
            return k+curr->key;
        };
        auto funcOfVal = [curr](int k, double v){
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
        auto funcOfKey = [curr](int k, double v){
            return k+curr->key;
        };
        auto funcOfVal = [curr](int k, double v){
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

double Polynomial::compute(double x) const{
    Node* curr = head;
    double result = 0;
    while(curr != nullptr){
        result += curr->value * pow(x, curr->key);
        curr = curr->next;
    }
    return result;
}

void Polynomial::derive(){
    auto funcOfKey = [](int k, double v){return k-1;};
    auto funcOfVal = [](int k, double v){return k*v;};
    applyAll(funcOfKey, funcOfVal);
    if(head != nullptr && head->key == -1){
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

void Polynomial::printPoly(std::ostream& os) const{
    if(head == nullptr){
        os << 0 << std::endl;
        return;
    }
    Node* curr = head;
    bool first = true;
    while(curr != nullptr){
        if(curr->key == 0){
            os << curr->value;
            first = false;
        }
        else{
            if(!first){
               os << " + ";
            }else{
                first = false;
            }
            if(curr->value != 1){
                if(curr->value > 0)
                    os << curr->value;
                else
                    os << '(' << curr->value << ')';
            }
            
            os << "x^";
            if(curr->key < 0){
                os << '(' << curr->key << ')';
            }else{
                os << curr->key;
            }
        }
        curr = curr->next;
    }
    os << std::endl;
}