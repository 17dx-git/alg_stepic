#include <iostream>
#include <vector>


int main(void) {
  int number_count;
  std::cin >> number_count;
  std::vector<int> counting(11);
  
  for (int i = 0; i < 11; i++)  counting[i] = 0;
  
  for (int i = 0; i < number_count; i++) {
    int number;
    std::cin >> number;
    ++counting[number];
  }
  
  for (int i = 0; i < 11; i++) {
    while(counting[i] >0){
        std::cout<< i << " ";
        --counting[i];
    }
  }
  
  std::cout << std::endl;
 
  return 0;
}