// #include"linkedList.h"
#include"Polynomial.h"
using std::cout; using std::endl;
int main(){
    if(true){
        /* debug part*/
        Polynomial link;
        link.insert(1, 2);
        link.insert(3, 1);
        // Node* n = link.head;
        Polynomial link2;
        link2.insert(1, 1);
        link2.insert(2, 3);
        // size_t sz;
        // Node* l = merge(link.head, link2.head, [](int v1, int v2){return v1+v2;}, sz);
        // while(n != nullptr){
        //     cout << n << ','<< n->key << ',' << n->value<< endl;
        //     cout << n2 << ','<< n2->key << ',' << n2->value << endl;
        //     n = n->next;
        //     n2 = n2->next;
        // }
        link.printPoly();
        // auto n = link.index(3);
        
        // n->value = 4;
        // n->key = 2;
        // if(n == nullptr)
        //     link.printPoly();
        link2.printPoly();
        Polynomial lk = link*link2;

        lk.insert(0, 3);
        lk.printPoly();
        lk.derive();
        lk.printPoly();
        cout << lk.compute(1) << endl;
        for(int i = 0; i < 10; i++){
            lk.derive();
        }
        lk.printPoly();
        link *= link2;
        link.printPoly();
        link *= lk;
        link.printPoly();
        // link.removeVal(0);
        // link.remove(3);
        // cout <<  link.length() << endl;
    }else{
        /* implementation part*/
    }
}