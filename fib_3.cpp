#include <cassert>
#include <iostream>
#include <vector>

class Fibonacci {
 public:
  //true if exist two cycle
  static int isRepeated(std::vector<int>& remains){ 
       
     if (remains.size() % 2 == 1) return false;
     
     //may devide on two part
     int half_count = remains.size() / 2 ;

     //split on to part 
     //and check eq both part
    
     for(int i=0; i < half_count ;++i){  
        if (remains[i] != remains[i+half_count] ) return false;
     } 
     
    return true;
  }
  static void getSeqRemains(std::vector<int>& remains,
                            long long num, int m){
    int bbn =0; //0 elem
    remains.push_back(bbn % m);
    
    int bn = 1; //1 elem
    remains.push_back(bn % m);
    
    int n ; 
    for(long long i=2; i<=num ;++i){        
        n = (bn + bbn) % m;        
        remains.push_back(n);
        if (isRepeated(remains)) {
            
            int cycle_length = remains.size() / 2 ;
            remains.resize(cycle_length);
            break;
        }
            
        bbn=bn;
        bn=n;
    }
    //для некоторых num длина периода Пизано так и не будет обнаружена
    //например num = 49, при m=14,
    //длина цикла составляет 48, чтобы это узнать нужно вычислить 
    //94 члена фибоначи, 
    // но если мы уже получили остаток для числа num,
    //то и определять период нам уже нет смысла
  }
  static int get_remainder(long long num, int m) {
    assert(num >= 1);
    assert(m >= 2);
    
    if (num == 1) return 1; //== 1 % m
    if (num == 2) return 1; //== 1 % m
    
    std::vector<int> remains;
    getSeqRemains(remains,num,m);
    
    /*for(int x: remains){
        std::cout << x << " " ;
    }*/
    int cycle_length = remains.size() ;
    
    //std::cout << "cycle_length=" << cycle_length << "\n" ;
    
    int index_num = num % cycle_length;
    return remains[index_num];
  }
};

int main(void) {
  long long n;
  int m;
  std::cin >> n >> m;
  std::cout << Fibonacci::get_remainder(n, m) << std::endl;
  return 0;
}