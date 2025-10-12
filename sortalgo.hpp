#include <cstdint>
#include <vector>

namespace sort {
void insertion_sort(std::vector<int> &vec);
void insertion_sort(std::vector<int> &vec, size_t low, size_t high);

void selection_sort(std::vector<int> &vec);

void bubble_sort(std::vector<int> &vec);

void cocktail_shaker_sort(std::vector<int> &vec);

void comb_sort(std::vector<int> &vec);

void merge_helper(std::vector<int> &vec, size_t left, size_t mid, size_t right);
void merge_sort_helper(std::vector<int> &vec);
void merge_sort(std::vector<int> &vec);

size_t partition_helper(std::vector<int> &vec, size_t low, size_t high);
void quick_sort_helper(std::vector<int> &vec, size_t low, size_t high);
void quick_sort(std::vector<int> &vec);

void heapify_helper(std::vector<int> &vec, size_t n, size_t i);
void heap_sort(std::vector<int> &vec);

void intro_sort_helper(std::vector<int> &vec, uint64_t depth, size_t low, size_t high);
void intro_sort(std::vector<int> &vec);

void gnome_sort(std::vector<int> &vec);

void odd_even_sort(std::vector<int> &vec);
} // namespace sort
