#include <iostream>
#include <vector>
#include <iterator>     // std::distance
#include <cassert>

typedef  std::vector<int>::iterator It;

It binary_search_lastLess( It begin, It end, int number){
   std::size_t  count = std::distance( begin, end);
   while(begin != end){
      if (*begin > number) return begin; 

      It  middle = begin + (count/2) ;
      if ( *(middle) > number) end = middle;
      else begin = ++middle;
      count = std::distance(begin, end);
   }
   return end;//all less
}

It binary_search_lastLessEq( It begin, It end, int number){
   std::size_t  count = std::distance( begin, end);
   while(begin != end){
      if (*begin >= number) return begin; 
      
      It  middle = begin + (count/2) ;
      if ( *(middle) >= number) end = middle;
      else begin = ++middle;
      count = std::distance(begin, end);
   }
   return end; //all less
}

It partition(It curr, It end ){
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

void partition3(It curr, It end, It& less, It& equal ){
    It base = curr++;
    int x = *base;
    less = base;
    equal = base;
    for (; curr != end; ++curr ){
        if (*curr == x) {           
          ++equal;
          std::swap(*curr, *equal ); 
          //std::cout << "eq=" << *equal << " ";          
        } 
        else if (*curr < x) {
          ++less;
          ++equal;

          std::swap(*curr, *less ); 
          if (less != equal) std::swap(*curr, *equal ); 
          //std::cout << "ls=" << *equal << " ";
          //std::cout << "eq=" << *equal << " ";          
        }
    }
    std::swap(*base, *less );
}

void quicksort(It begin, It end) {
    std::size_t  count = std::distance(begin, end);
    if (count == 0) return;
    
    It rnd_elem = begin + rand() % count;
    std::swap( *begin, *rnd_elem );
    
    It m = partition(begin, end);
        
    quicksort(begin, m);
    quicksort(m + 1, end);
}

void quicksort3(It begin, It end) {
    std::size_t  count = std::distance(begin, end);
    if (count == 0) return;
    
    It rnd_elem = begin + rand() % count;
    std::swap( *begin, *rnd_elem );
    
    It less; 
    It equal;
    
    /*std::cout << "base="<< *begin << " ";
    for (It it = begin; it != end; ++it) {
            std::cout << *it << " ";
    }
    std::cout <<  "\n";*/
    
    partition3(begin, end, less, equal);
            


    quicksort3(begin, less);
    quicksort3(equal+1, end);
}

struct Segments{
   int count;
   std::vector <int> begins; 
   std::vector <int> ends; 

   Segments(std::size_t count_):
       count(count_),begins(count_),ends(count_) {} 
    
   void prepare(){
        quicksort3(ends.begin(),  ends.end());
        quicksort3(begins.begin(),  begins.end());
        
        /*for (auto &x:begins) {
            std::cout << x << " ";
        }
        std::cout <<  "\n";
        
        for (auto &x:ends) {
            std::cout << x << " ";
        }
        std::cout <<  "\n";*/
   }
   
   int getCountTo_LastBegins(int point){
      //assert(std::is_sorted(begins.begin(), begins.end()));
      
      It elem = binary_search_lastLess(begins.begin(), begins.end(),point );
      return elem - begins.begin();        
   }
   
   int getCountTo_LastEnds(int point){
      //assert(std::is_sorted(ends.begin(), ends.end()));
      It elem = binary_search_lastLessEq(ends.begin(), ends.end(),point );
      return elem - ends.begin();       
   }
   
   int get_count_belongs(int point){ 
       return getCountTo_LastBegins(point) - getCountTo_LastEnds(point) ;
   }
};

int main(void) {

  std::size_t segments_count;
  std::cin >> segments_count;
  
  size_t points_count;
  std::cin >> points_count;
  
  Segments segments(segments_count);
    
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