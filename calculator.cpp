#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include  <climits>
struct Item{
    int before;
    int cost;
};

const int end_value = -1;

int get_optim( int number, std::vector< Item >& D){  
    
 
    D[0].cost = INT_MAX;
    D[1].cost = 0;
    D[1].before = end_value;
    
    for( int curr = 2; curr <= number; curr++ ){
        std::vector<int> befores(3);
        
        // number / 3 тоже может быть 0
        befores[0] = ( curr % 3 == 0)?    curr / 3 : 0;         
        befores[1] = ( curr % 2 == 0)?    curr / 2 : 0;
        befores[2] = curr -1; 
        
        std::vector<int> costs(3);
        costs[0] = D[ befores[0] ].cost;
        costs[1] = D[ befores[1] ].cost;
        costs[2] = D[ befores[2] ].cost;
                         
        auto cost = std::min_element(costs.begin(), costs.end());
        
        size_t min_before = cost-costs.begin();
        D[curr].before = befores[min_before];
        D[curr].cost = 1 + *cost;
    }  

    return D[number].cost ;                      
}

int main(void) {
  int number;
  std::cin >> number;
  std::vector< Item > D(number+1);  
  int k = get_optim(number, D);
  std::cout << k << std::endl;
  
  std::vector< int > intermediats;
  intermediats.reserve(k);
  int before  = number; 
  while (before != 1 ){  
     intermediats.push_back(before);
     before = D[before].before;
  }
  intermediats.push_back(1);
  
  for (auto it = intermediats.rbegin(); 
           it != intermediats.rend(); ++it ){
     std::cout << *it  << " ";          
  }
  
  std::cout << std::endl;
  return 0;
}