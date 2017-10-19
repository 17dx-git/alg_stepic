#include <iostream>
#include <vector>

std::vector <int> get_addendum(int n){
    std::vector <int> result;
    int remain=n;
    int i;
    for (i = 1; i <= remain; i++) {
        result.push_back(i);
        remain -=i; 
    }
    if (remain == 0) return result;
    
    result.push_back(i);
    i -=  remain;
    result.erase(result.begin()+i-1);   
    return result;
}


int main(void) {
  int n;
  std::cin >> n;
    
  std::vector <int> addendum = get_addendum(n);
  std::cout << addendum.size() << std::endl;
  for (std::size_t i = 0; i < addendum.size(); i++) {
    std::cout << addendum[i] << " ";
  }
  std::cout << std::endl;
}