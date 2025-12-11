#include "sortalgo.hpp"
#include <bit>
#include <cmath>
#include <cstdint>
#include <memory>

namespace sort {
inline void swap(int &a, int &b) {
    int t = a;
    a = b;
    b = t;
}

void insertion_sort(std::vector<int> &vec) {
    if (vec.empty()) {
        return;
    }
    insertion_sort(vec, 0, vec.size() - 1);
}
void insertion_sort(std::vector<int> &vec, ssize_t low, ssize_t high) {
    for (ssize_t i = low + 1; i <= high; i++) {
        int key = vec[i];
        ssize_t j = i - 1;

        while (j >= 0 && j <= high && key < vec[j]) {
            vec[j + 1] = vec[j];
            j--;
        }
        vec[j + 1] = key;
    }
}

void selection_sort(std::vector<int> &vec) {
    for (ssize_t i = 0; i < vec.size() - 1; i++) {
        ssize_t j_min = i;

        for (ssize_t j = i + 1; j < vec.size(); j++) {
            if (vec[j] < vec[j_min]) {
                j_min = j;
            }
        }
        if (j_min != i) {
            swap(vec[i], vec[j_min]);
        }
    }
}

void bubble_sort(std::vector<int> &vec) {
    for (ssize_t i = 0; i < vec.size() - 1; i++) {
        for (ssize_t j = 0; j < vec.size() - i - 1; j++) {
            if (vec[j] > vec[j + 1]) {
                swap(vec[j], vec[j + 1]);
            }
        }
    }
}

void cocktail_shaker_sort(std::vector<int> &vec) {
    bool swapped;
    ssize_t size_minus = vec.size() - 1;

    do {
        swapped = false;
        for (ssize_t i = 0; i < size_minus; i++) {
            if (vec[i] > vec[i + 1]) {
                swap(vec[i], vec[i + 1]);
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
        swapped = false;
        for (ssize_t i = size_minus; i >= 0 && i <= size_minus; i--) {
            if (vec[i] > vec[i + 1]) {
                swap(vec[i], vec[i + 1]);
                swapped = true;
            }
        }
    } while (swapped);
}

void comb_sort(std::vector<int> &vec) {
    ssize_t gap = vec.size();
    const double shrink = 1.3f;
    bool sorted = false;

    while (!sorted) {
        gap = std::floor(gap / shrink);
        if (gap <= 1) {
            gap = 1;
            sorted = true;
        } else if (gap == 9 || gap == 10) {
            gap = 11;
        }

        ssize_t i = 0;
        while (i + gap < vec.size()) {
            if (vec[i] > vec[i + gap]) {
                swap(vec[i], vec[i + gap]);
                sorted = false;
            }
            i++;
        }
    }
}

void merge_helper(std::vector<int> &vec, ssize_t left, ssize_t mid, ssize_t right) {
    ssize_t n_l = mid - left + 1;
    ssize_t n_r = right - mid;

    std::unique_ptr<int[]> arr_l = std::make_unique<int[]>(n_l);
    std::unique_ptr<int[]> arr_r = std::make_unique<int[]>(n_r);

    for (ssize_t i = 0; i < n_l; i++)
        arr_l[i] = vec[left + i];
    for (ssize_t i = 0; i < n_r; i++)
        arr_r[i] = vec[mid + 1 + i];

    ssize_t i = 0;
    ssize_t j = 0;
    ssize_t k = left;

    while (i < n_l && j < n_r) {
        if (arr_l[i] <= arr_r[j]) {
            vec[k] = arr_l[i];
            i++;
        } else {
            vec[k] = arr_r[j];
            j++;
        }
        k++;
    }
    while (i < n_l) {
        vec[k] = arr_l[i];
        i++;
        k++;
    }
    while (j < n_r) {
        vec[k] = arr_r[j];
        j++;
        k++;
    }
}
void merge_sort_helper(std::vector<int> &vec, ssize_t left, ssize_t right) {
    if (left >= right)
        return;

    ssize_t mid = (right + left) / 2;

    merge_sort_helper(vec, left, mid);
    merge_sort_helper(vec, mid + 1, right);
    merge_helper(vec, left, mid, right);
}
void merge_sort(std::vector<int> &vec) {
    if (vec.empty()) {
        return;
    }
    merge_sort_helper(vec, 0, vec.size() - 1);
}

ssize_t median_of_3_helper(const std::vector<int> &vec, ssize_t low, ssize_t high) {
    ssize_t mid = (low + high) / 2;
    if (vec[mid] < vec[low]) {
        std::swap(mid, low);
    }
    if (vec[high] < vec[low]) {
        std::swap(high, low);
    }
    if (vec[high] < vec[mid]) {
        std::swap(high, mid);
    }
    return mid;
}
ssize_t partition_helper(std::vector<int> &vec, ssize_t low, ssize_t high) {
    swap(vec[high], vec[median_of_3_helper(vec, low, high)]);
    int pivot = vec[high];
    ssize_t i = low - 1;
    for (ssize_t j = low; j <= high - 1; j++) {
        if (vec[j] < pivot) {
            i++;
            swap(vec[i], vec[j]);
        }
    }
    swap(vec[i + 1], vec[high]);
    return i + 1;
}
void quick_sort_helper(std::vector<int> &vec, ssize_t low, ssize_t high) {
    if (low < high) {
        ssize_t pi = partition_helper(vec, low, high);

        quick_sort_helper(vec, low, pi - 1);
        quick_sort_helper(vec, pi + 1, high);
    }
}
void quick_sort(std::vector<int> &vec) {
    if (vec.empty()) {
        return;
    }
    quick_sort_helper(vec, 0, vec.size() - 1);
}

void perc_down(std::vector<int> &vec, ssize_t root, ssize_t end) {
    while (2 * root + 1 < end) {
        ssize_t child = 2 * root + 1;

        if (child + 1 < end && vec[child] < vec[child + 1]) {
            child++;
        }
        if (vec[root] < vec[child]) {
            swap(vec[root], vec[child]);
            root = child;
            continue;
        }
        return;
    }
}
void heap_sort(std::vector<int> &vec, ssize_t low, ssize_t high) {
    if (high - low <= 1 || low > high) {
        return;
    }

    ssize_t i_max = high / 2;

    for (ssize_t i = i_max; i >= low && i <= i_max; i--) {
        perc_down(vec, i, high);
    }
    for (ssize_t i = high; i > low; i--) {
        swap(vec[low], vec[i]);
        perc_down(vec, low, i);
    }
}
void heap_sort(std::vector<int> &vec) {
    if (vec.empty()) {
        return;
    }
    heap_sort(vec, 0, vec.size() - 1);
}

void intro_sort_helper(std::vector<int> &vec, uint8_t depth, ssize_t low, ssize_t high) {
    if (high - low <= 16) {
        insertion_sort(vec, low, high);
        return;
    }
    if (depth == 0) {
        heap_sort(vec, low, high);
        return;
    }
    ssize_t pi = partition_helper(vec, low, high);
    intro_sort_helper(vec, depth - 1, low, pi - 1);
    intro_sort_helper(vec, depth - 1, pi + 1, high);
}
void intro_sort(std::vector<int> &vec) {
    if (vec.empty()) {
        return;
    }
    uint8_t depth = (std::bit_width(vec.size()) - 1) * 2;
    intro_sort_helper(vec, depth, 0, vec.size() - 1);
}

void gnome_sort(std::vector<int> &vec) {
    ssize_t pos = 1;
    while (pos < vec.size()) {
        if (pos == 0 || vec[pos] >= vec[pos - 1]) {
            pos++;
        } else {
            swap(vec[pos], vec[pos - 1]);
            pos--;
        }
    }
}

void odd_even_sort(std::vector<int> &vec) {
    bool sorted = false;
    while (!sorted) {
        sorted = true;
        for (ssize_t i = 1; i < vec.size() - 1; i += 2) {
            if (vec[i] > vec[i + 1]) {
                swap(vec[i], vec[i + 1]);
                sorted = false;
            }
        }
        for (ssize_t i = 0; i < vec.size() - 1; i += 2) {
            if (vec[i] > vec[i + 1]) {
                swap(vec[i], vec[i + 1]);
                sorted = false;
            }
        }
    }
}
} // namespace sort
