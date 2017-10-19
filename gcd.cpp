#include <cassert>
#include <iostream>

template <class Int>
Int gcd(Int a, Int b) {
  assert(a > 0 && b > 0);

  /*Int current_gcd = 1;
  for (Int d = 2; d <= a && d <= b; d++) {
    if (a % d == 0 && b % d == 0) {
        current_gcd = d;
    }
  }*/
  for(;;){
      if (a==0) return b;
      if (b==0) return a;
      if (a >= b)  a = a % b;
      else  b = b % a;
  }
  return 1;
}

int main(void) {
  int a, b;
  std::cin >> a >> b;
  std::cout << gcd(a, b) << std::endl;
  return 0;
}