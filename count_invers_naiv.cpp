#include <iostream>
#include <vector>

int get_count_invers(std::vector<int>& numbers){
    std::size_t len = numbers.size();
    int count = 0;
    for(std::size_t i =0; i < len; ++i){
        for(std::size_t j =i+1; j < len; ++j){
            if (numbers[i]> numbers[j] ) ++count;
        }
    }
    return count;
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