#include <iostream>
#include <vector>


int get_optim( std::vector<int>& marks){
    size_t count = marks.size()-1;
    int sum =0;
    //последнюю ступеньку всегда берем
    sum += marks[count];
    //забываем значение, чтобы второй раз не считать
    marks[count] = 0; 
    
    
    for(int i = 0; i < count; i++ ) {
        if (marks[i] > 0){
            sum += marks[i];
            continue;
        } 

        if( marks[i] <0 && marks[i+1] <0 ){
            if (marks[i] > marks[i+1]) sum += marks[i];
            else {
                sum += marks[i+1];
                i++;  
            }
        }
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
  //marks[count] = 0; //stub elem

  std::cout << get_optim(marks) << std::endl;
  
  return 0;
}