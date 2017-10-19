#include <iostream>
#include <vector>
#include <algorithm>


int get_optim( std::vector<int>& marks){
    size_t count = marks.size();
    int sum = 0;
    int bsum = 0;
    
    for(int i = 0; i < count; i++ ) {           
            int curr = std::max(bsum , sum ) + marks[i];
            bsum = sum;
            sum = curr;
    }
    return sum;
}

int main(void) {
  size_t count;
  std::cin >> count;
  
  std::vector<int> marks(count);
  
  for (size_t i = 0; i < count; i++){
       std::cin >> marks[i];
  }

  std::cout << get_optim(marks) << std::endl;
  
  return 0;
}