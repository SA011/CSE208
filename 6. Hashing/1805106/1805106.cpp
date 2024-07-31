#include <bits/stdc++.h>
using namespace std;

//hash Functions
int hash1(string &key, int m){
    long long p = 223, h = 0;
    for(char c : key)h = (h * p + c) % m;
    return h;
}

int hash2(string &key, int m){
    long long p = 0x811C9DC5 % m, h = 0;
    for(char c : key)h = ((h * p) ^ c) % m;
    return h;
}
int auxHash(string &key, int m){
    long long h = 0, a = 2, b = 3;
    for(char c : key){
        h = (h * a + c) % m; 
        a = (a + b) % m;
        swap(a, b);
    }
    return h;
}    
//

//Hash Node    
class Node{
    string key;
    int value;
public:
    Node(string ky = "", int vl = 0) : key(ky), value(vl) {}
    string setKey(string k){
        key = k;
    }
    string getKey(){
        return key;
    }
    int setValue(int v){
        value = v;
    }
    int getValue(){
        return value;
    }
};
//

//Separate Chaining
class HashTableSeparateChaining{
    int m;
    vector<list<Node*>> table; 
    function<int(string&, int)> hash;
    
public:
    HashTableSeparateChaining(int _m, function<int(string&, int)> func) : m(_m){
        table.resize(m);
        hash = func;
    }
    
    int insert(string key, int value){
        int a = hash(key, m);
        
        auto it = table[a].begin();
        int cnt = 0;
        while(it != table[a].end() && (*it) -> getKey() != key)it++, cnt++;
        
        if(it != table[a].end())return cnt; //already exists;
        table[a].push_back(new Node(key, value));
        return cnt;
    }
    
    void erase(string key){
        int a = hash(key, m);
        
        auto it = table[a].begin();
        
        while(it != table[a].end() && (*it) -> getKey() != key)it++;
        
        if(it == table[a].end())return; //doesn't exist;
        table[a].erase(it);
        
    }
    
    pair<int, int> search(string key){
        int a = hash(key, m), cnt = 1;
        auto it = table[a].begin();
        
        while(it != table[a].end() && (*it) -> getKey() != key)it++, cnt++;
        
        if(it == table[a].end())return make_pair(-1, cnt); //doesn't exist
        return make_pair((*it) -> getValue(), cnt);
    }
    ~HashTableSeparateChaining(){
        for(auto x : table){
            for(auto y : x)delete y;
        }
    }
};
//

//Double Hashing
class HashTableDoubleHashing{
    int m;
    vector<Node*> table; 
    function<int(string&, int)> hash;
    
public:
    HashTableDoubleHashing(int _m, function<int(string&, int)> func) : m(_m){
        table.assign(m, NULL);
        hash = func;
    }
    
    int insert(string key, int value){
        int a = hash(key, m);
        int b = auxHash(key, m);
        for(int i = a, j = 0; j < m; j++, i = (i + b) % m){
            if(table[i] == NULL){
                table[i] = new Node(key, value);
                return j;
            }
        }
        
        //cout << "CANNOT INTSERT " << key << ' ' << value << endl;
        return m;
    }
    
    void erase(string key){
        int a = hash(key, m);
        int b = auxHash(key, m);
        for(int i = a, j = 0; j < m; j++, i = (i + b) % m){
            if(table[i] == NULL)continue;
            if(table[i] -> getKey() == key){
                delete table[i];
                table[i] = NULL;
            }
        }
        
        //cout << "CANNOT FIND " << key << endl;
    }
    
    pair<int, int> search(string key){
        int a = hash(key, m);
        int b = auxHash(key, m);
        for(int i = a, j = 0; j < m; j++, i = (i + b) % m){
            if(table[i] == NULL)continue;
            if(table[i] -> getKey() == key){
                return make_pair(table[i] -> getValue(), j + 1);
            }
        }
        
        //cout << "CANNOT FIND " << key << endl;
        return pair(-1, m + 1);
    }
    
    ~HashTableDoubleHashing(){
        for(auto x : table){
            delete x;
        }
    }
};
//


//Custom Probing
class HashTableCustomProbing{
    int m;
    long long c1 = 11411, c2 = 10831;
    vector<Node*> table; 
    function<int(string&, int)> hash;
    
public:
    HashTableCustomProbing(int _m, function<int(string&, int)> func) : m(_m){
        table.assign(m, NULL);
        hash = func;
    }
    
    int insert(string key, int value){
        int a = hash(key, m);
        int b = auxHash(key, m);
        for(int i = a, j = 0; j < m; j++, i = (i + c1 * b) % m){
            int u = (i + c2 * j * j) % m;
            if(table[u] == NULL){
                table[u] = new Node(key, value);
                return j;
            }
        }
        
        //cout << "CANNOT INTSERTC " << key << ' ' << value << endl;
        return m;
    }
    
    void erase(string key){
        int a = hash(key, m);
        int b = auxHash(key, m);
        for(int i = a, j = 0; j < m; j++, i = (i + c1 * b) % m){
            int u = (i + c2 * j * j) % m;
            if(table[u] == NULL)continue;
            if(table[u] -> getKey() == key){
                delete table[u];
                table[u] = NULL;
            }
        }
        
        //cout << "CANNOT FIND " << key << endl;
    }
    
    pair<int, int> search(string key){
        int a = hash(key, m);
        int b = auxHash(key, m);
        for(int i = a, j = 0; j < m; j++, i = (i + c1 * b) % m){
            int u = (i + c2 * j * j) % m;
            if(table[u] == NULL)continue;
            if(table[u] -> getKey() == key){
                return make_pair(table[u] -> getValue(), j + 1);
            }
        }
        
        //cout << "CANNOT FIND " << key << endl;
        return pair(-1, m + 1);
    }
    
    ~HashTableCustomProbing(){
        for(auto x : table){
            delete x;
        }
    }
};


vector<string> gen(int n, int len){
    set<string> ret;
    while(ret.size() < n){
        string s;
        while(s.size() < len)
            s.push_back((char)(rand() % 26 + (rand() % 2 ? 'A' : 'a')));
        ret.insert(s);
    }
    
    vector<string> v;
    for(auto x : ret)v.push_back(x);
    return v;
}
int main(){
    int N;
    cin >> N;
    srand(clock());
    HashTableSeparateChaining hsh1(N, hash1);
    HashTableSeparateChaining hsh2(N, hash2);
    HashTableDoubleHashing hsh3(N, hash1);
    HashTableDoubleHashing hsh4(N, hash2);
    HashTableCustomProbing hsh5(N, hash1);
    HashTableCustomProbing hsh6(N, hash2);
    auto strings = gen(10000, 7);
    int col[6] = {0};
    double avg[6] = {0};
    for(int i = 0; i < strings.size(); i++){
        col[0] += hsh1.insert(strings[i], i + 1);
        col[1] += hsh2.insert(strings[i], i + 1);
        col[2] += hsh3.insert(strings[i], i + 1);
        col[3] += hsh4.insert(strings[i], i + 1);
        col[4] += hsh5.insert(strings[i], i + 1);
        col[5] += hsh6.insert(strings[i], i + 1);
    }
    for(int i = 0; i < 1000; i++){
        int l = rand() % strings.size();
        avg[0] += hsh1.search(strings[l]).second;
        avg[1] += hsh2.search(strings[l]).second;
        avg[2] += hsh3.search(strings[l]).second;
        avg[3] += hsh4.search(strings[l]).second;
        avg[4] += hsh5.search(strings[l]).second;
        avg[5] += hsh6.search(strings[l]).second;
    }
    
    for(int i = 0; i < 6; i++)avg[i] /= 1000;
    cout << "Collision   " << "Average Probes" << endl;
    for(int i = 0 ; i < 6; i++){
        cout << ' ' << setw(11) << left << col[i] << ' ' << avg[i] << endl;
    }
}
