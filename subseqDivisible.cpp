#include <algorithm>
#include <cstddef>
#include <iostream>
#include <vector>

struct Item{
   int value;
   int* count;    
};


int get_length_subsequence(std::vector<Item> &numbers) {
  int result = 0;
  
  
  for (size_t i = 0; i < numbers.size(); i++) {
    int first_number = numbers[i].value;
    int current_result;
    if ( *numbers[i].count != -1 ){
        current_result = *numbers[i].count;
    }
    else{

        std::vector<Item> left_numbers;
        std::remove_copy_if( numbers.begin() + i + 1,
                             numbers.end(),
                             std::back_inserter(left_numbers),
                             [first_number] (const Item& item) {
                                 return  item.value % first_number !=0; 
                             });
        current_result = 1  + 
              get_length_subsequence(left_numbers);
        *numbers[i].count = current_result;      
    }
    
    if (current_result > result) {
         result = current_result;         
    }
  }
  
  for (auto x: numbers) std::cout<<  x.value << " ";
  std::cout<< "\n";
  for (auto x: numbers) std::cout<<  *x.count << "|";
  std::cout<< "\n";
  
  return result;
}

int main(void) {
  size_t number_count;
  std::cin >> number_count;
  std::vector<Item> numbers(number_count);
  
  
  std::vector<int> counts(number_count);
  std::fill_n(counts.begin(), number_count, -1);
  
  for (size_t i = 0; i < number_count; i++){
       std::cin >> numbers[i].value;
       numbers[i].count = &counts[i];
  }
 
  std::cout << get_length_subsequence(numbers ) << std::endl;
}