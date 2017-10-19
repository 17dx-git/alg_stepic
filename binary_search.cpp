#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
#include <iterator>     // std::distance

typedef  std::vector<int>::const_iterator It;

It binary_search( It begin, It end, int number){
   std::size_t  count = std::distance( begin, end);
   It fail = end;
   while(begin != end){
      if (count == 1 ) {
          if (*begin != number) return fail; 
          return begin ;      
      }
      It  middle = begin + (count/2) ;
      if ( *(middle) == number) return middle;
      if ( *(middle) < number) begin = ++middle;
      else end = middle;
      count = std::distance(begin, end);
   }
   return fail;
}

int get_pos(const std::vector<int> &numbers, int number) {
 
  It it = binary_search(numbers.begin(), numbers.end(), number);
  if (it == numbers.end()) {
    return -1;
  }
  return static_cast<int>(it - numbers.begin()) + 1;
}

int main(void) {
  size_t number_count;
  std::cin >> number_count;
  std::vector<int> numbers(number_count);
  for (auto &number:numbers) {
    std::cin >> number;
  }
  assert(std::is_sorted(numbers.begin(), numbers.end()));

  size_t query_count;
  std::cin >> query_count;
  while (query_count-- > 0) {
    int number;
    std::cin >> number;
    std::cout << get_pos(numbers, number) << " ";
  }
  std::cout << std::endl;
}