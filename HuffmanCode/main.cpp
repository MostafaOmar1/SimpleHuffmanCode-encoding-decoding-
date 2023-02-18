#include <iostream>
#include <string>
#include <queue>
#include <map>

using namespace std;
struct HuffmanNode{
    char c;
    int freq;
    HuffmanNode* left;
    HuffmanNode* right;
    HuffmanNode() : c{}, freq{0}, left{nullptr}, right{nullptr} {}
};
ostream& operator<<(ostream& os, const HuffmanNode& obj) {
    os << obj.c << "  " << obj.freq;
    return os; 
}
struct comapreFunctor{
    int operator()(const HuffmanNode* l, const HuffmanNode* r) {
        return ((l->freq) > (r->freq));
    }
};

struct Node{
    char c;
    string s;
    };

void preOrderTrav(HuffmanNode* root, string str, vector<Node>& codes) {
    if (!root) {    
        return;
    }
    
    if (root->c != '$') {
        cout << root->c << " : " << str << endl;
        Node n;
        n.c = root->c;
        n.s = str;
        codes.push_back(n);
    }
    
    preOrderTrav(root->left, str + "0", codes);
    preOrderTrav(root->right, str + "1", codes);
}

char travWithCode(const string& str, HuffmanNode* hNode) {
    
    for (const auto& character : str) {
        if (character == '1') 
            hNode = hNode->right;
        else 
            hNode = hNode->left;
    }
    return hNode->c;
}

int main() {
    string str{"a fast runner need never be afraid of the dark"};
    
    map <char, int> map;
    
    for (auto const& c : str) {
        ++map[c];
    }
//    for (auto const& entry : map) {
//        cout << entry.first << "  " << entry.second;
//        cout << endl;
//    }    
//    cout << endl;
    
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, comapreFunctor> pq;
    
    
    for (auto const& item : map) {
        HuffmanNode* hf = new HuffmanNode();
         hf->c = item.first;
         hf->freq = item.second;
         pq.push(hf);
    }
    
//    while (pq.size() > 0) {
//        cout << pq.top()->c << "  " << pq.top()->freq << endl;
//        pq.pop();
//    }
    
    while (pq.size() > 1) {
        HuffmanNode* firstMin = pq.top();
        pq.pop();
        HuffmanNode* secondMin = pq.top();
        pq.pop();
        
        HuffmanNode* newNode = new HuffmanNode();
        newNode->c = '$';
        newNode->freq = firstMin->freq + secondMin->freq;
        newNode->left = firstMin;
        newNode->right = secondMin;
        pq.push(newNode);
    }
    
    //cout << pq.size() << endl;
    
    vector<Node> vec;
    preOrderTrav(pq.top(), " ", vec);
    
    cout << " ======================== " << endl;
    while (true) {
        string s;
        cin >> s;
        cout << s << " ==> " << travWithCode(s, pq.top()) << endl;
    }
    cout << endl;
    return 0;
}
