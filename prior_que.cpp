#include <iostream>
#include <vector>
#include <algorithm>

class prior_que_max{
    std::vector<int> data;
public:    
    int extractMax(){
        int result = data[0];
        std::size_t last = data.size()-1;
        std::swap(data[0], data[last]);
        data.resize(last);
        sinkDown(0);
        return result;
    }
    void insert(int n){
        data.push_back(n);
        std::size_t i = data.size()-1;
        swimUp(i);
    }

private:    
    bool valid_relation(std::size_t i, std::size_t child){
        std::size_t last = data.size()-1;
        if (child > last ) return true;
        return data[i] >= data[child];
    }
    
    void sinkDown(std::size_t i){
       std::size_t childL = 2*i ;
       std::size_t childR = 2*i+1 ;
       if (valid_relation(i,childL) 
          && valid_relation(i,childR) ) return;
       do{ 
          std::size_t max_child;
          if (!get_max_child(childL, childR, max_child) ) return ;      
          std::swap(data[max_child], data[i]);
          i = max_child;
          childL = 2*i;
          childR = 2*i+1;
       } while ( !valid_relation(i,childL) 
              || !valid_relation(i,childR) );
    }
    
    bool get_max_child(std::size_t childL,
                        std::size_t childR,
                        std::size_t& max_child){
        std::size_t last = data.size()-1;
        if (childL > last && childR > last) return false;
        
        if (childL > last ) {
            max_child = childR;            
        } else if (childR > last ){
            max_child = childL;
        } else 
           max_child =  data[childL] > data[childR] ? childL:childR;
        return true;
    }
    
    void swimUp(std::size_t i){
       std::size_t parent = i / 2;
       if (data[parent] >= data[i] ) return;
       do{          
          std::swap(data[parent], data[i]);
          i = parent;
          parent = i / 2;
       } while ( data[parent] < data[i]  );
        
    }
};


int main(void) {
  int n;
  std::cin >> n;
  prior_que_max que;
  
  for (std::size_t i = 0; i < n; i++) {
    std::string op;  
    std::cin >> op;
   
    if (op == "Insert"){
        int value;
        std::cin >> value;
        que.insert(value);
    }else if (op == "ExtractMax"){
        int max = que.extractMax();
        std::cout << max << std::endl;
    }
  }
  std::cout << std::endl;
  
  return 0;
}