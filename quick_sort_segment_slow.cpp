#include <iostream>
#include <vector>
#include <iterator>     // std::distance
#include <cassert>

//typedef std::pair <int, int> Segment;

typedef  std::vector<int>::iterator It;

It partition(It curr, It end){
    It base = curr++;
    int x = *base;
    It less = base; 
    for (; curr != end; ++curr ){
        if (*curr <= x) {
          ++less;
          std::swap(*curr, *less );                
        }
    }
    std::swap(*base, *less );
    return less;
}

void quicksort(It begin, It end) {
    std::size_t  count = std::distance(begin, end);
    if (count == 0) return;
    It m = partition(begin, end);
    quicksort(begin, m);
    quicksort(m + 1, end);
}

struct Segments{
   int count;
   //std::vector <Segment> data; 
   std::vector <int> begins; 
   std::vector <int> ends; 

   Segments(std::size_t count_):
       count(count_)/*, data(count_)*/,begins(count_),ends(count_) {} 
    
   void prepare(){
        quicksort(begins.begin(),  begins.end());
        quicksort(ends.begin(),  ends.end());
   }
   
   int getCountTo_LastBegins(int point){
      //assert(std::is_sorted(begins.begin(), begins.end()));
      
      for (int i = 0; i < count; i++) {
          //уже не выполняется
          // в ответе i это количество удовлетворяющих элементов, а не индекс
          if ( begins[i] > point) return i; 
      }  
      return count;        
   }
   
   int getCountTo_LastEnds(int point){
      //assert(std::is_sorted(ends.begin(), ends.end()));
      for (int i = 0; i < count; i++) {
          //уже не выполняется
          // в ответе i это количество удовлетворяющих элементов, а не индекс
          if ( ends[i] >= point) return i;
          
      }  
      return count;        
   }
   
   int get_count_belongs(int point){
       //std::cout << getCountTo_LastBegins(point) << " ";
       //std::cout << getCountTo_LastEnds(point) << "\n"; 
       return getCountTo_LastBegins(point) - getCountTo_LastEnds(point) ;
   }
};

int main(void) {
    
  std::size_t segments_count;
  std::cin >> segments_count;
  
  size_t points_count;
  std::cin >> points_count;
  
  Segments segments(segments_count);
    
  /*for (auto &segment:segments.data) {
    std::cin >> segment.first >> segment.second;
  }*/
  for (int i = 0; i < segments_count; i++) {
    std::cin >> segments.begins[i];
    std::cin >> segments.ends[i];    
  }
  
  segments.prepare();
  
  for (int i = 0; i < points_count; i++) {
    int point;
    std::cin >> point;
    std::cout << segments.get_count_belongs(point) << " " ;
  }
   
  std::cout << std::endl;
  return 0;
}