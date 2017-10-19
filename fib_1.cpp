#include <cassert>
#include <iostream>

class Fibonacci {
 public:
  static int get(int n) {
    assert(n >= 0);
    if (n == 0) return 0;
    if (n == 1) return 1;
    /*int bn = get(n-1);
    int bbn = get(n-2);*/
    return get(n-1) + get(n-2);
  }
};

int main(void) {
  int n;
  std::cin >> n;
  std::cout << Fibonacci::get(n) << std::endl;
  return 0;
}