#include <iostream>
#include <map>
#include <list>
#include <string>
#include <algorithm>

typedef std::pair <char, int> Freqs;

struct SResult{
    std::string zip;
    std::map<char, std::string> codes;
    int countChars() { return codes.size(); }
};

struct Node{
    char letter;
    char code; // 0|1
    int freq;
    Node* left;
    Node* right;
    Node(const Freqs& f):
         letter(f.first),code(0),freq(f.second),
         left(NULL),right(NULL)
         { }         
    Node(Node* left, Node* right):
         letter(0),code(0),freq(left->freq + right->freq ),
         left(left),right(right){
         this->left->code = '0';  
         this->right->code ='1';          
    }
        
    void genCode(std::string prefix, 
                std::map<char, std::string>& codes){
        if (left == NULL && right == NULL ) {
           codes[letter] = prefix + code;
           return  ;         
        }
        left->genCode(prefix + code, codes );
        right->genCode(prefix + code, codes );        
    }
};

struct ArrNodes{
    int len;
    typedef std::list<Node*>::iterator NodeIt;
    std::list <Node*> nodes;
    ArrNodes(std::map<char,int> freqs){
        //:nodes(freqs.begin(), freqs.end());
        len = freqs.size();
                
        for(auto& it: freqs ){
            Node* node = new Node(it);
            nodes.push_back(node);
        }
    }
    NodeIt getNodeWithMinFreq(){
        return std::min_element(nodes.begin(), nodes.end(),
         [](const Node* a, const Node* b ){
              return a->freq < b->freq;
         });
    }
    void CreateTree(){
       while(len>1){
          NodeIt leftIt = getNodeWithMinFreq();
          Node * left = *leftIt;
          nodes.erase(leftIt);
          --len;
          
          NodeIt rightIt = getNodeWithMinFreq();
          Node * right = *rightIt;
          *rightIt = new Node(left,right);          
       } 
    } 

    void CreateCode(std::map<char, std::string>& codes){
        NodeIt rootIt = nodes.begin();
        Node * root = *rootIt;
        root->left->genCode("", codes);
        root->right->genCode("", codes);
    } 
    
};

SResult calc_huffman(std::string s){
    SResult result;
    std::map<char,int> freqs;
    for ( std::size_t i = 0; i < s.size(); i++) {
        auto it = freqs.find(s[i]);
        if (it == freqs.end()) freqs[ s[i] ]=0;
        ++freqs[ s[i] ]; 
    }
    
    if ( freqs.size() == 1){
        char letter = freqs.begin()->first;
        result.codes[letter] = "0";        
    }
    else{
        ArrNodes tree(freqs);
        tree.CreateTree();    
        tree.CreateCode(result.codes);
    }
    
        
    for ( std::size_t i = 0; i < s.size(); i++) {
         result.zip += result.codes[s[i]]; 
    }
    
    return result;
}


int main(void) {
  std::string s;
  std::cin >> s;
    
  SResult huffman = calc_huffman(s);
  std::cout << huffman.countChars() << " " ;
  std::cout << huffman.zip.size() << std::endl;
  for (auto it: huffman.codes) {
    std::cout << it.first << ": " << it.second << std::endl;
  }
  std::cout << huffman.zip << std::endl;
  std::cout << std::endl;
}