#include <iostream>
#include <algorithm>

int main() {
  int segment_count, point_count;
  std::cin >> segment_count >> point_count;
  std::vector<int> segments_begins(segment_count);
  std::vector<int> segments_ends(segment_count);
  for(auto begin = segments_begins.begin(), end = segments_ends.begin();
      segment_count; --segment_count, ++begin, ++end)
    std::cin >> *begin >> *end;

  std::sort(segments_begins.begin(), segments_begins.end());
  std::sort(segments_ends.begin(), segments_ends.end());

  while(point_count--) {
    int point;
    std::cin >> point;
    auto less = std::lower_bound(segments_ends.begin(), segments_ends.end(), point)
      - segments_ends.begin();
    auto greater = std::upper_bound(segments_begins.begin(), segments_begins.end(), point)
      - segments_begins.begin();
    std::cout << greater - less << " ";
  }
  std::cout << std::endl;
  return 0;
}