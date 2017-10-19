#include <iostream>
#include <map>
#include <string>


typedef std::pair <char, int> Freqs;

struct Node{
    char letter;
    Node* left;
    Node* right;        
    Node():
         letter(0),
         left(NULL),right(NULL){         
    }
        
    void parse(std::string& code, std::size_t index, char letter_){
        
        if (code.size() <= index ){
            letter = letter_;
            return;
            /*left=NULL;
            right=NULL;*/
        }
        if (code[index] == '0'){
            if (left == NULL) left = new Node();
            left->parse(code, index+1, letter_);
            return;
        }
        
        if (right == NULL) right = new Node();
        right->parse(code, index+1, letter_);
        return;
    }
    
    Node* putNext(char code){
        if (code == '0'){
            if (left == NULL) return this;
            return left;
        }    
        if (right == NULL) return this;
        return right;        
    }
    bool decoded(){
        return (right == NULL && left == NULL); 
    }
};


Node* CreateTree(std::map<char, std::string>& codes){
       Node* root = new Node();
       for (auto &code:codes) {
           root->parse(code.second, 0, code.first);
       }
       return root;
} 


std::string decode_huffman(std::map<char, std::string>& codes,
                           std::string& zip){

    Node* root = CreateTree(codes);    
    
    std::string result;  
    Node * node = root;
    for ( std::size_t i = 0; i < zip.size(); i++) {
        
        node = node->putNext(zip[i]);
        //std::cout << zip[i] <<" "<< node->letter <<" ";
        if (node->decoded()) {
            result+= node->letter;
            node = root;
        } 
    }
    
    return result;
}


int main(void) {
  int count_chars;
  std::cin >> count_chars;
  
  int len_zip;
  std::cin >> len_zip;
  
  std::map<char, std::string> codes;
  
  for (int i = 0; i < count_chars; i++) {
    char letter;
    std::string s;
    
    std::cin >> letter;
    std::cin.ignore(); //ignore ":"    
    std::cin >> s;
    
    codes[letter] = std::move(s);
  }
  std::string zip;
  std::cin >> zip;
    
  std::string msg = decode_huffman(codes, zip);
  std::cout << msg;
  std::cout << std::endl;
}