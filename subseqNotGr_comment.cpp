#include <algorithm>
#include <cstddef>
#include <iostream>
#include <vector>

size_t no_index = -1;


int get_length_subsequence(std::vector<int> &numbers, 
                           size_t& index_result,
                           std::vector<size_t>& prevs) {
  size_t count = numbers.size();  
  std::vector<size_t> pos_max(count+1, no_index);  
    
  int len_max = 0;
  //pos_max[len_max] = 0;

  //for (auto& x: numbers)   std::cout<<  x << " ";

  for (size_t i = 0; i < count; i++) {
    size_t curr = 0;
    size_t end = len_max;
   /* std::cout<< " c" << numbers[i] << " ";
    std::cout<< "ci=" << curr << " ";           
    std::cout<< "ei=" << end << " "; */
    while (curr < end){
          size_t mid = (curr + end) / 2;
        /*  std::cout<< "mi=" << pos_max[mid] << " "; 
          std::cout<< "m" << numbers[pos_max[mid]] << " ";*/
          
          if (numbers[pos_max[mid]] <= numbers[i]) curr = mid + 1;
          else end = mid; 
          /*std::cout<< "ci=" << curr << " ";           
          std::cout<< "ei=" << end << " "; */ 
    }
    
    /*std::cout<< curr << " ";
    std::cout<< "\n";*/
    
    if (curr == 0) prevs[i] = no_index; 
    else prevs[i] = pos_max[curr-1];
    
    pos_max[curr] = i;
    
    int newLen = curr+1;
    if (newLen > len_max) len_max = newLen;
    
    /*std::cout<< "\n";
    for (auto x: pos_max) 
        std::cout<<  x << " ";
    std::cout<< "\n";*/
  }

 /* for (auto x: prevs) std::cout<<  x << " ";
  std::cout<< "\n";   */
  index_result = pos_max[len_max-1];
  return len_max;
}

int main(void) {
  size_t number_count;
  std::cin >> number_count;
  std::vector<int> numbers(number_count);
  
  //reverse save
  for (size_t i = number_count; i > 0; ){
       std::cin >> numbers[--i];
  }
  
  std::vector<size_t> prevs(number_count, no_index);
  
  size_t  start_index; 
  std::cout << get_length_subsequence(numbers, start_index, prevs  ) << std::endl;
  size_t index = start_index;
  
  while(index != no_index ){
     std::cout << number_count - index << " "; //
     index = prevs[index];
  }
}