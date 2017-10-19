#include <algorithm>
#include <cstddef>
#include <iostream>
#include <vector>

size_t end_seq = -1;

struct Item{
   size_t index;
   int value;
   int* count; 
   size_t* next_elem;   
};


int get_length_subsequence(size_t & start_index,
                           std::vector<Item> &numbers) {
  int result = 0;
  
  
  for (size_t i = 0; i < numbers.size(); i++) {
    int first_number = numbers[i].value;
    int current_result;
    
   /*for (auto x: numbers) std::cout<<  x.value << " ";
   std::cout<< "\n";
   for (auto x: numbers) std::cout<<  *x.count << "|";
   std::cout<< "\n";
   for (auto x: numbers) std::cout<<  *x.next_elem << "|";
   std::cout<< "\n";*/
  
    if ( *numbers[i].count != -1 ){
        current_result = *numbers[i].count;
    }
    else{

        std::vector<Item> left_numbers;
        std::remove_copy_if( numbers.begin() + i + 1,
                             numbers.end(),
                             std::back_inserter(left_numbers),
                             [first_number] (const Item& item) {
                                 return  item.value > first_number; 
                             });
        size_t next_elem = end_seq;                     
        current_result = 1  + 
              get_length_subsequence(next_elem,left_numbers);
        *numbers[i].count = current_result;
        *numbers[i].next_elem = next_elem;         
    }
    
    if (current_result > result) {
         result = current_result; 
         start_index = numbers[i].index;         
    }
  }
  
  
  
  return result;
}

int main(void) {
  size_t number_count;
  std::cin >> number_count;
  std::vector<Item> numbers(number_count);
  
  
  std::vector<int> counts(number_count);
  std::fill_n(counts.begin(), number_count, -1);
  
  std::vector<size_t> next_elems(number_count);
  std::fill_n(next_elems.begin(), number_count, end_seq);
  
  for (size_t i = 0; i < number_count; i++){
       numbers[i].index = i ;
       std::cin >> numbers[i].value;
       numbers[i].count = &counts[i];
       numbers[i].next_elem = &next_elems[i];
  }
   
  size_t  start_index; 
  std::cout << get_length_subsequence(start_index, numbers ) << std::endl;
  size_t index = start_index;
  
  while(index !=end_seq ){
     std::cout <<  numbers[index].index + 1 << " ";
     index = *numbers[index].next_elem;
  }
}