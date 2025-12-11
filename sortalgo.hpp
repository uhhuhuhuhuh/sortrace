#include <cstdint>
#include <sys/types.h>
#include <vector>

namespace sort {
void insertion_sort(std::vector<int> &vec);
void insertion_sort(std::vector<int> &vec, ssize_t low, ssize_t high);

void selection_sort(std::vector<int> &vec);

void bubble_sort(std::vector<int> &vec);

void cocktail_shaker_sort(std::vector<int> &vec);

void comb_sort(std::vector<int> &vec);

void merge_helper(std::vector<int> &vec, ssize_t left, ssize_t mid, ssize_t right);
void merge_sort_helper(std::vector<int> &vec);
void merge_sort(std::vector<int> &vec);

ssize_t partition_helper(std::vector<int> &vec, ssize_t low, ssize_t high);
void quick_sort_helper(std::vector<int> &vec, ssize_t low, ssize_t high);
void quick_sort(std::vector<int> &vec);

void perc_down(std::vector<int> &vec, ssize_t root, ssize_t end);
void heap_sort(std::vector<int> &vec);

void intro_sort_helper(std::vector<int> &vec, uint8_t depth, ssize_t low, ssize_t high);
void intro_sort(std::vector<int> &vec);

void gnome_sort(std::vector<int> &vec);

void odd_even_sort(std::vector<int> &vec);
} // namespace sort
