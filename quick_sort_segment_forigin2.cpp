//Сложность O((n+m)*log(n+m))
#include <iostream>
#include <vector>
#include <functional>
#include <iterator>
#include <unordered_map>
#include <algorithm>

using std::cout;
using std::cin;
using std::endl;


enum point_type {
	line_begin,
	line_point,
	line_end
};

struct point {
	point_type type;
	int x;

	bool operator < (const point &p) const {
		return x < p.x || x == p.x && type < p.type;
	}
};

int main() {
	size_t n, m;
	cin >> n >> m;
	std::vector<point> v;
	v.reserve(2 * n + m);
	std::vector<int> line_points(m);
	std::unordered_map<int, size_t> points_counter;

	for (size_t i = 0; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		v.emplace_back(point{ line_begin, a });
		v.emplace_back(point{ line_end, b });
	}

	for (size_t i = 0; i < m; ++i) {
		int x;
		cin >> x;
		v.emplace_back(point{ line_point, x});
		line_points[i] = x;
	}

	std::sort(v.begin(), v.end());

	size_t line_count = 0;
	for (auto &it : v) {
		switch(it.type) {
		case line_begin: 
			line_count += 1;
			break;
		case line_end: 
			line_count -= 1;
			break;
		case line_point: 
			points_counter[it.x] = line_count;
			break;
		default: ;
		}
	}

	for (auto &it : line_points) {
		cout << points_counter[it] << ' ';
	}
	cout << endl;
}