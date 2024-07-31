#include <bits/stdc++.h>
using namespace std;


class BinomialHeap{    
    class Node{
        int value, degree;
        Node *parent;
        list<Node*> child;
    public:
        Node(int _v = 0) : value(_v){
            degree = 0;
            parent = NULL;
        }
        void addChild(Node *c){
            c -> parent = this;
            child.push_front(c);
            degree++;
        }
        
        int getDegree(){
            return degree;
        }
        
        int getValue(){
            return value;
        }
        void setValue(int x){
            value = x;
        }
        
        Node* getParent(){
            return parent;
        }
        
        void setParent(Node* par){
            parent = par;
        }
        
        list<Node*> getChild(){
            return child;
        }
        
        
        Node* find(int val){
            if(value == val)return this;
            if(value < val)return NULL;
            for(auto node : child){
                auto x = node -> find(val);
                if(x != NULL)return x;
            }
            
            return NULL;
        }
        
        void clear(){
            for(auto node : child){
                node -> clear();
                delete node;
            }
        }
        
    };
    
    list<Node*> root;
    size_t sz;
    
    
    Node* merge(Node *h1, Node *h2){                //merging binomial tree with same degree
        if(h1 -> getDegree() != h2 -> getDegree()){
            //merge failed
            return NULL;
        }
            
        if(h1 -> getValue() > h2 -> getValue())swap(h1, h2);
        h2 -> addChild(h1);
        return h2;
    }
    void Union(BinomialHeap h){
        sz += h.sz;
        auto it1 = root.begin();
        auto it2 = h.root.begin();
        while(it2 != h.root.end()){         // merging two list
            if(it1 == root.end() || (*it1) -> getDegree() <= (*it2) -> getDegree())root.insert(it1, *(it2++));
            else it1++;
        }
        if(root.size() <= 1){
            return;
        }
        root.reverse();
        it1 = root.begin();
        it2 = it1;
        it2++;
        auto it3 = it2;
        it3++;
        while(it1 != root.end()){
            if(it2 == root.end() || (*it1) -> getDegree() < (*it2) -> getDegree()){
                it1++;
                if(it2 != root.end())it2++;
                if(it3 != root.end())it3++;
                continue;
            }
            
            if(it3 == root.end() || (*it2) -> getDegree() < (*it3) -> getDegree()){
                (*it1) = merge(*it1, *it2);
                root.erase(it2++);
                if(it3 != root.end())it3++;
                continue;
            }
            it1++;
            it2++;
            it3++;
        }
        root.reverse();
    }
    
    BinomialHeap(list<Node*> node){
        sz = 0;
        root = node;
        for(auto x : node)sz |= 1 << x -> getDegree();
    }
    
    list<Node*>::iterator findMaxUtil(){
        list<Node*>::iterator ret = root.begin();
        for(auto it = root.begin(); it != root.end(); it++){
            if((*ret) -> getValue() < (*it) -> getValue())ret = it;
        }
        return ret;
    }
    
    Node* find(int val){
        for(auto node : root){
            auto x = node -> find(val);
            if(x != NULL)return x;
        }
        return NULL;
    }
public:
    BinomialHeap(){
        sz = 0;
    }
    
    
    int findMax(){
        auto it = findMaxUtil();
        int ret = (it == root.end() ? -1 : (*it) -> getValue());
        return ret;
    }
    
    int extractMax(){
        auto it = findMaxUtil();
        int ret = (it == root.end() ? -1 : (*it) -> getValue());
        
        if(it != root.end()){
            list<Node*> nw = (*it) -> getChild();
            sz -= (1 << ((*it) -> getDegree()));
            delete *it;
            root.erase(it);
            for(auto x : nw) x -> setParent(NULL);
            Union(BinomialHeap(nw));
        }
        return ret;
    } 
    
    void insert(int node){
        Union(BinomialHeap(list<Node*>(1, new Node(node))));
        cout << "Inserted " << node << endl;
    }
    
    void increaseKey(int prevKey, int newKey){
        if(prevKey >= newKey)return;
        auto node = find(prevKey);
        if(node == NULL)return;
        
        node -> setValue(newKey);
        
        while(node -> getParent() != NULL && node -> getValue() > node -> getParent() -> getValue()){
            int x = node -> getValue();
            node -> setValue(node -> getParent() -> getValue());
            node -> getParent() -> setValue(x);
            node = node -> getParent();
        }
        
        cout << "Increased " << prevKey << ". The updated value is " << newKey << "." << endl;
    }
    
    void erase(int node){
        increaseKey(node, INT_MAX);
        extractMax();
    }
    
    void print(){
        cout << "Printing Binomial Heap..." << endl;
        cout << "--------------------------" << endl;
        for(auto it = root.rbegin(); it != root.rend(); it++){
            cout << "Binomial Tree, B" << (*it) -> getDegree() << endl;
            list<Node*> l1, l2;
            l1.push_back(*it);
            int l = 0;
            while(!l1.empty()){
                cout << "Level " << l << " :";
                for(auto y : l1){
                    cout << " " << y -> getValue();
                    for(auto z : y -> getChild())l2.push_back(z);
                }
                cout << endl;
                l1 = l2;
                l2.clear();
                l++;
            }
        }
        cout << "--------------------------" << endl;
    }
    
    void clear(){
        for(auto x : root){
            x -> clear();
            delete x;
        }
    }
};


int main(){
    ifstream fin("in.txt");
    
    string s;
    BinomialHeap b;
    while(fin >> s){
        if(s == "INS"){
            int x;
            fin >> x;
            b.insert(x);
        }else if(s == "INC"){
            int x, y;
            fin >> x >> y;
            b.increaseKey(x, y);
        }
        else if(s == "FIN")
            cout << "FindMax returned " << b.findMax() << endl;
        else if(s == "EXT")
            cout << "ExtractMax returned " << b.extractMax() << endl;
        else b.print();
    }
    b.clear();
}

