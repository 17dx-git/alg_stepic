#include <iostream>
#include <vector>
#include <cstring>

void merge(int * left, int * end_left,
           int * right, int * end_right,
           int * result, long& count_invers){

    while (left < end_left and right < end_right){
        if( *left <= *right){
            *result++ = *left++;
        }
        else{
            // ведем подсчет через какое количесвто цифр в левой части
            // я переношу цифру из правой части
            count_invers += (end_left-left) ;
            *result++ = *right++;
        }
    }
        
    while (left < end_left)
        *result++ =  *left++;
        
    while (right < end_right)  
        *result++ =  *right++;
}

void mergeSort(int * origin, int * result,
               std::size_t size, long& count_invers){
    if (size ==0 ) return ;
    
    if (size ==1 ) {
        *result =  *origin;
        return ;
    } 
    std::size_t const left_size = size / 2;
    std::size_t const right_size = size - left_size;

    mergeSort(origin, result, left_size,count_invers);
    mergeSort(&origin[left_size], &result[left_size], right_size,count_invers);
    
    memcpy(origin, result, size*sizeof(*origin));
    merge(origin, &origin[left_size], 
          &origin[left_size], &origin[size],
          result, count_invers);
    return ;      
}

long get_count_invers(std::vector<int>& numbers){
    std::size_t len = numbers.size();
    long count_invers = 0;
    
    std::vector<int> ordered;
    ordered.resize(numbers.size());
    
    mergeSort( &numbers[0], &ordered[0], numbers.size(), count_invers );
    return count_invers;
}

int main(void) {
  size_t number_count;
  std::cin >> number_count;
  std::vector<int> numbers(number_count);
  for (auto &number:numbers) {
    std::cin >> number;
  }
  
  std::cout << get_count_invers(numbers) << std::endl;
  return 0;
}