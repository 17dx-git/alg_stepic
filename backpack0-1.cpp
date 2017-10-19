#include <algorithm>
#include <cstddef>
#include <iostream>
#include <vector>


int get_optim(int max_weight, std::vector<int>& weights){
    size_t n = weights.size();
    int **D = new int * [max_weight+1];
    for(int i = 0; i <=max_weight; i++ ){
        D[i] = new int  [n];
        D[i][0] = 0;        
    }
    for(int i = 0; i <n; i++ ) D[0][i] = 0;
    
    // i = 0 is stub elem
    // чтобы не приходилось писать везде weights[i-1]
    for(int i = 1; i <n; i++ ) {
        for(int w = 1; w <= max_weight; w++ ){
            if( weights[i] > w) D[w][i] = D[w][i-1];
            else D[w][i] =  std::max(D[w][i-1], D[w - weights[i] ][i-1] + weights[i] ) ;
        }
    }
    
    /*for(int i = 0; i <n; i++ ) {
        for(int w = 0; w <= max_weight; w++ ){
           std::cout << D[w][i]   << " ";
        }
        std::cout << std::endl;
    }*/
    
    return D[max_weight][n-1];
}

int main(void) {
  size_t max_weight;
  std::cin >> max_weight;
  
  size_t count;
  std::cin >> count;
  std::vector<int> weights(count+1);
  
  weights[0]=0; //stub elem
  for (size_t i = 1; i <= count; i++){
       std::cin >> weights[i];
  }

  std::cout << get_optim(max_weight, weights) << std::endl;
  
  return 0;
}