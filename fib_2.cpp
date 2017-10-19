#include <cassert>
#include <iostream>

class Fibonacci {
 public:
  static int get_last_digit(int num) {
    assert(num >= 1);
    if (num == 1) return 1;
    
    int bbn =0; //0 elem
    int bn = 1; //1 elem
    int n ; 
    for(int i=2;i<=num;++i){        
        n = (bn + bbn) %10;
        
        bbn=bn;
        bn=n;
    }
    return n;
  }
};

int main(void) {
  int n;
  std::cin >> n;
  std::cout << Fibonacci::get_last_digit(n) << std::endl;
  return 0;
}