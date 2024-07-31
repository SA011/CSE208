#include <iostream> 
#include <fstream> 
using namespace std;

template <class T>
class AVLTree{
    class Node{
    public:
        Node *l, *r;
        T val;
        int height;
        Node(int v) : val(v){
            l = r = NULL;
            height = 0;
        }
    };
    
    Node *root;
    int getHeight(Node *node){
        if(node == NULL)return -1;
        return node -> height;
    }
    void adjustHeight(Node *node){
        if(node == NULL)return;
        node -> height = max(getHeight(node -> l), getHeight(node -> r)) + 1;
    }
    
    Node* rotateLeft(Node *node){
        if(node == NULL || node -> r == NULL)return node;
        Node *temp = node -> r;
        node -> r = temp -> l;
        temp -> l = node;
        
        adjustHeight(node);
        adjustHeight(temp);
        return temp;
    }
    
    Node* rotateRight(Node *node){
        if(node == NULL || node -> l == NULL)return node;
        Node *temp = node -> l;
        node -> l = temp -> r;
        temp -> r = node;
        
        adjustHeight(node);
        adjustHeight(temp);
        return temp;
    }
    
    Node* handleViolation(Node *node, int &violation){
        adjustHeight(node);
        if(abs(getHeight(node -> l) - getHeight(node -> r)) <= 1)return node; //No violation here;
        
        //violated
        
        if(getHeight(node -> l) > getHeight(node -> r)){
            if(getHeight(node -> l -> l) < getHeight(node -> l -> r))
                node -> l = rotateLeft(node -> l);
            node  = rotateRight(node);
        }else{
            if(getHeight(node -> r -> l) > getHeight(node -> r -> r))
                node -> r = rotateRight(node -> r);
            node  = rotateLeft(node);
        }
        
        
        violation = 1;
        return node;
    }
    
    Node* insertUtil(Node *node, T v, int &violation){
        violation = 0;
        if(node == NULL)return new Node(v);
        if(node -> val == v){
            violation = -1;
            return node;
        }
        if(node -> val > v)node -> l = insertUtil(node -> l, v, violation);
        else node -> r = insertUtil(node -> r, v, violation);
        
        return handleViolation(node, violation);
    }
    
    Node* deleteUtil(Node *node, T v, int &violation){
        violation = 0;
        if(node == NULL){
            violation = -1;
            return NULL;
        }
        if(node -> val == v){
            Node *temp = node;
            if(node -> r == NULL){
                node = node -> l;
                delete temp;
                return node;
            }
            temp = temp -> r;
            while(temp -> l)temp = temp -> l;
            node -> val = temp -> val;
            node -> r = deleteUtil(node -> r, node -> val, violation);
        }
        else if(node -> val > v)node -> l = deleteUtil(node -> l, v, violation);
        else node -> r = deleteUtil(node -> r, v, violation);
        
        return handleViolation(node, violation);
    }
    
    bool findUtil(Node *node, T v){
        if(node == NULL)return false;
        if(node -> val == v)return true;
        if(node -> val > v)return findUtil(node -> l, v);
        return findUtil(node -> r, v);
    }
    void printUtil(ostream& stream, Node *node){
        if(node == NULL)return;
        stream << (node -> val);
        if(node -> l || node -> r){
            stream << "(";
            printUtil(stream, node -> l);
            stream << ")";
            stream << "(";
            printUtil(stream, node -> r);
            stream << ")";
        }
    }
    void clearUtil(Node *node){
        if(node == NULL)return;
        clearUtil(node -> l);
        clearUtil(node -> r);
        delete node;
    }
public:

    AVLTree(){
        root = NULL;
    }
    int insert(T v){
        int violation = 0;
        root = insertUtil(root, v, violation);
        return violation;
    }
    
    
    int erase(T v){
        int violation = 0;
        root = deleteUtil(root, v, violation);
        return violation;
    }
    
    bool find(T v){
        return findUtil(root, v);
    }
    
    friend ostream& operator << (ostream& stream, AVLTree &tree){
        tree.printUtil(stream, tree.root);
        return stream;
    }
    ~AVLTree(){
        clearUtil(root);
    }
};

int main(){
    ifstream fin("in.txt");
    char c;
    int t;
    AVLTree<int> tree;
    while(fin >> c){
        fin >> t;
        if(c == 'F'){
            if(tree.find(t))cout << "True" << endl;
            else cout << "False" << endl;
        }else if(c == 'I'){
            int k = tree.insert(t);
            if(k == -1)cout << "Value already exists." << endl;
            else if(k == 1)cout << "Height invariant violated.\nAfter rebalancing: ";
            cout << tree << endl;
        }else{
            int k = tree.erase(t);
            if(k == -1)cout << "Value doesn't exist." << endl;
            else if(k == 1)cout << "Height invariant violated.\nAfter rebalancing: ";
            cout << tree << endl;
        }
    }
}
