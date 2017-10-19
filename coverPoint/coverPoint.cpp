/*
По данным n

отрезкам необходимо найти множество точек минимального размера, для которого каждый из отрезков содержит хотя бы одну из точек.

В первой строке дано число 1≤n≤100
отрезков. Каждая из последующих n строк содержит по два числа 0≤l≤r≤109, задающих начало и конец отрезка. Выведите оптимальное число m точек и сами m точек. Если таких множеств точек несколько, выведите любое из них

 Sample Input 1:

3
1 3
2 5
3 6

Sample Output 1:

1
3 

Sample Input 2:

4
4 7
1 3
2 5
5 6

Sample Output 2:

2
3 6 
*/

#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>


typedef std::pair <int, int> Segment;

int getFirst (const Segment& sg){
    return sg.first;
};


int getSecond (const Segment& sg){
    return sg.second;
};

typedef int (* fGetPoint )(const Segment& sg);

void setFirst ( Segment& sg, int value){
     sg.first = value;
};


void setSecond ( Segment& sg, int value){
     sg.second =value;
};

typedef void (* fSetPoint )( Segment& sg, int value);


struct SPoints{
    std::vector <Segment>&  points;
    fGetPoint getPoint;
    fSetPoint setPoint;
    SPoints(std::vector <Segment>& segments,
           fGetPoint getPoint,
           fSetPoint setPoint); 

    void setNewValue(std::size_t i, std::size_t i_end, int next_point);
    bool can_setNewValue(std::size_t i,
                             std::size_t i_end,
                             int new_value);
    bool getNextPoint(int i_curr, int& i, int& value);
    void shiftPoints();
};

SPoints::SPoints(std::vector <Segment>& segments,
                      fGetPoint getPoint,
                      fSetPoint setPoint
               ): points(segments),getPoint(getPoint), setPoint(setPoint) {  
}


bool SPoints::can_setNewValue(std::size_t i,
                             std::size_t i_end,
                             int new_value){
    
    
    for (; i < i_end; i++) {
        //если новое значение попадает в диапазон;
        if  (  points[i].first <= new_value &&
               points[i].second >= new_value) continue;
        
        return false;
    }
    return true;
}

void SPoints::setNewValue(std::size_t i, std::size_t i_end, int next_point){    
    for (; i < i_end; i++) {      
        setPoint(points[i], next_point);        
    }

}

bool SPoints::getNextPoint(int i_curr, int& i, int& value){
    int curr_point = getPoint(points[i_curr]);
    i = i_curr;
    for (; i < points.size(); i++) {
       if  (getPoint(points[i]) == curr_point) continue;
       value=getPoint(points[i]);       
       return true;       
    } 
    return false;    
}

void SPoints::shiftPoints(){
   std::size_t count = points.size();
       
   for (std::size_t i = 0; i < count; ) {
       int new_value;
       int i_next;
       if (!getNextPoint(i, i_next, new_value )) break;

       while( can_setNewValue(i, i_next, new_value) ){
           setNewValue(i, i_next, new_value) ;
           if (!getNextPoint(i_next, i_next, new_value )) break;
       }
       i=i_next;   
   } 
}

  
std::vector <int> get_covering_set(std::vector <Segment> segments) {
  std::vector <int> result;
  
  
  /*struct {
    bool operator()(const Segment& a, 
                    const Segment& b) const
    {   
        return a.first < b.first;
    }   
  } SortFirst;

  std::sort (segments.begin(), segments.end(), SortFirst );
  SPoints startPoint(segments, getFirst, shiftFirstToRight);  
  startPoint.shiftPoints();*/
  
  struct {
    bool operator()(const Segment& a,
                    const Segment& b) const
    {   
        return a.second > b.second;
    }   
  } SortSecond;
  std::sort(segments.begin(), segments.end(), SortSecond );
  SPoints endPoint(segments, getSecond, setSecond);  
  endPoint.shiftPoints();
  
  if (segments.size() ==0 ) return result;
  result.push_back(segments[0].second);
  int last = segments[0].second ;
  
  for (std::size_t i = 1; i < segments.size(); i++) {
      if (last == segments[i].second) continue;
      result.push_back(segments[i].second);
      last = segments[i].second ;
  }

  return result;
}

int main(void) {
  int segments_count;
  std::cin >> segments_count;
  std::vector <Segment> segments(segments_count);
  for (int i = 0; i < segments_count; i++) {
    std::cin >> segments[i].first >> segments[i].second;
  }

  std::vector <int> points = get_covering_set(segments);
  std::cout << points.size() << std::endl;
  for (std::size_t i = 0; i < points.size(); i++) {
    std::cout << points[i] << " ";
  }
  std::cout << std::endl;
}