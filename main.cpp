#include "sortalgo.hpp"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <sstream>
#include <stdexcept>
#include <vector>

class Timer {
  public:
    void start() { start_timepoint = std::chrono::high_resolution_clock::now(); }

    long double stop() {
        using namespace std::chrono;
        auto end_timepoint = high_resolution_clock::now();

        auto start = time_point_cast<microseconds>(start_timepoint).time_since_epoch().count();
        auto end = time_point_cast<microseconds>(end_timepoint).time_since_epoch().count();

        auto duration = end - start;
        return duration * 1;
    }

  private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_timepoint;
};

std::string time_format(double ms);
void test_sort(void (*sort_func)(std::vector<int> &), const std::vector<int> &vec,
               const std::string &sort_name);
void test_std_sort(const std::vector<int> &vec, const std::string &sort_name);

int main() {
    size_t test_bach;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 999999999);

    while (!(std::cin >> test_bach)) {
        std::cin.clear();
        std::cin.ignore(123, '\n');
    }

    std::vector<int> random_nums;
    random_nums.reserve(test_bach);

    for (size_t i = 0; i < test_bach; i++) {
        random_nums.push_back(dis(gen));
    }
    std::cout << "Done making batch...\n";
    std::cout << "NOTE: Sort time does not include check of validity of sort, and copying of vector(the sorting algorithims sort "
                 "in place)\n\n";

    test_std_sort(random_nums, "STD Sort");
    test_sort(sort::intro_sort, random_nums, "Intro Sort");
    test_sort(sort::quick_sort, random_nums, "Quick Sort");
    test_sort(sort::merge_sort, random_nums, "Merge Sort");
    test_sort(sort::comb_sort, random_nums, "Comb Sort");
    test_sort(sort::heap_sort, random_nums, "Heap Sort");
    test_sort(sort::insertion_sort, random_nums, "Insertion Sort");
    test_sort(sort::selection_sort, random_nums, "Selection Sort");
    test_sort(sort::odd_even_sort, random_nums, "Odd Even Sort");
    test_sort(sort::gnome_sort, random_nums, "Gnome Sort");
    test_sort(sort::cocktail_shaker_sort, random_nums, "C.S. Sort");
    test_sort(sort::bubble_sort, random_nums, "Bubble Sort");
}

void test_sort(void (*sort_func)(std::vector<int> &), const std::vector<int> &vec,
               const std::string &sort_name) {
    std::vector<int> vec_copy;
    vec_copy.reserve(vec.size());
    for (int i : vec) {
        vec_copy.push_back(i);
    }

    double time;
    Timer timer;

    timer.start();
    sort_func(vec_copy);
    time = timer.stop();

    if (!std::is_sorted(vec_copy.begin(), vec_copy.end())) {
        throw std::invalid_argument("sort_func: \"" + sort_name + "\" does not sort properly");
    }
    std::cout << sort_name << ":\t" << time_format(time) << '\n';
}
void test_std_sort(const std::vector<int> &vec, const std::string &sort_name) {
    std::vector<int> vec_copy;
    vec_copy.reserve(vec.size());
    for (int i : vec) {
        vec_copy.push_back(i);
    }

    long double time;
    Timer timer;

    timer.start();
    std::sort(vec_copy.begin(), vec_copy.end());
    time = timer.stop();
    std::cout << sort_name << ":\t" << time_format(time) << '\n';
}

std::string time_format(double microsecs) {
    long double time = microsecs;
    std::string return_val;
    std::stringstream strs;

    // bubble sort exists...
    if (microsecs >= 3600000000) {
        time = microsecs / 3600000000;
        strs << time;
        return_val = strs.str();
        return_val.append(" hours");
    }
    if (microsecs >= 60000000) {
        time = microsecs / 60000000;
        strs << time;
        return_val = strs.str();
        return_val.append(" minutes");

        return return_val;
    }
    if (microsecs >= 1000000) {
        time = microsecs / 1000000;
        strs << time;
        return_val = strs.str();
        return_val.append(" seconds");

        return return_val;
    }
    if (microsecs >= 1000) {
        time = microsecs / 1000;
        strs << time;
        return_val = strs.str();
        return_val.append(" milliseconds");

        return return_val;
    }

    strs << time;
    return_val = strs.str();
    return_val.append(" microseconds");

    return return_val;
}
