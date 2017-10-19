#include <cstddef>
#include <iostream>
#include <vector>
#include <iterator>     // для std::distance
#include <cassert>

const size_t no_index = -1;

//за основу взят алгоритм Longest increasing subsequence
//из Википедии со сложностью O(n*logn)
int get_length_subsequence(std::vector<int> &numbers, 
                           size_t& end_index,
                           std::vector<size_t>& prevs) {
 
  size_t count = numbers.size(); 
  
  std::vector<size_t> pos_max;  
  pos_max.reserve(count);
  
  //первый элемент должен существовать по условию задачи
  assert(count > 0 );
  
  //положили индекс первого числа
  pos_max.push_back(0); 
  
  //первый элемент уже обработан,  
  //поэтому начинаем со второго элемента
  for (size_t i = 1; i < count; i++) {
    auto curr = pos_max.begin();
    auto end = pos_max.end();
    // среди чисел  содержащихся(через индексы)  
    //в pos_max ищем верхнюю границу для текущего числа numbers[i]
    while (curr < end){
          auto mid = curr + (std::distance(curr, end)/2) ;
          
          if (numbers[*mid] <= numbers[i]) curr = mid + 1;
          else end = mid;          
    }
    
    //если все числа больше, чем текущее  numbers[i],
    //то данное число становится началом последовательности
    //значит "предыдущего числа" у него нет, ставим: prevs[i] = no_index
    if ( curr == pos_max.begin() ) prevs[i] = no_index; 
    //иначе запоминаем индекс "предыдущего числа"
    else prevs[i] = *(curr-1);
    
    //если все числа меньше, чем текущее numbers[i],
    //значит создаем новую ячейку
    if (curr == pos_max.end())  pos_max.push_back(i); 
    //иначе изменяем индекс, хранящийся в текущей ячейке   
    else *curr = i;
  }
  
  //индекс конца  найденной последовательности 
  //лежит в конце массива pos_max 
  end_index = pos_max.back();
  return pos_max.size();
}

int main(void) {
  size_t number_count;
  std::cin >> number_count;
  std::vector<int> numbers(number_count);
  
  //в связи с особенностью реализации алгоритма
  //необходимо сохранить данные в обратном порядке  
  for (size_t i = number_count; i > 0; ){
       std::cin >> numbers[--i];
  }
  
  std::vector<size_t> indexes(number_count, no_index);
  
  size_t  end_index; //последний элемент последовательности
  std::cout << get_length_subsequence(numbers, end_index, indexes  ) << std::endl;
  
  size_t index = end_index;
  
  //в связи с особенностью реализации алгоритма
  // индексы можем извлекать только в обратном порядке.
  //Чтобы не сохранять индексы в массив, 
  //и избавится от необходимости переворачивать массив с такими результатами,
  // (как было уже ранее сказано) исходный массив был перевернут.
  //Теперь все индексы в ответе, рассчитаны для перевернутого массива,
  // а это значит перед отображением на экран 
  // их необходимо просто пересчитывать по формуле: number_count - index

  
  while(index != no_index ){
     std::cout << number_count - index << " "; 
     index = indexes[index];
  }
}