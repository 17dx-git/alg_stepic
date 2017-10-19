#include <algorithm>
#include <cstddef>
#include <iostream>
#include <string>
#include <iterator>     // для std::distance

const int none = -1;
typedef std::string::const_iterator It;

struct Levenshtein{
    const std::string &str1;
    const std::string &str2;
    int **cache;
    Levenshtein(const std::string &str1_,
                const std::string &str2_)
             :str1(str1_), str2(str2_){
         cache = new int * [size1];
         for(int i = 0; i <size1; i++ ){
             cache[i] = new int  [size2];
             for(int j = 0; j <size2; j++ ) cache[i][j] = none;
         }
    }
    int get_distance(size_t i, size_t j );
    int get_distance( );       
};

int Levenshtein::get_distance(size_t i, size_t j ) {
  size_t size1 = str1.size() - i;
  size_t size2 = str2.size() - j;
  if (size1 == 0 || size2==0) {
    return size1 + size2;
  }
  
  if (cache[i][j] != none) return cache[i][j];
  
  int insert_distance = get_distance(i,  j+1) + 1;
  int delete_distance = get_distance(i+1, j) + 1;
  int match_distance = get_distance(i+1, j+1) + (str1[i] != str2[j]);
  int result =  std::min({insert_distance, delete_distance, match_distance});
  cache[i][j] = result;
  return result;
}


int Levenshtein::get_distance() {
  return get_distance(0,0);
}

int main(void) {
  std::string str1;
  std::string str2;

  std::cin >> str1 >> str2;  
  Levenshtein levenshtein(str1, str2);
  std::cout << levenshtein.get_distance() << std::endl;
}