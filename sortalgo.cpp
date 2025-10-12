#include "sortalgo.hpp"
#include <cmath>
#include <cstdint>

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
void insertion_sort(std::vector<int> &vec, size_t low, size_t high) {
    for (size_t i = low + 1; i <= high; i++) {
        int key = vec[i];
        size_t j = i - 1;

        while (j >= 0 && vec[j] > key) {
            vec[j + 1] = vec[j];
            j--;
        }
        vec[j + 1] = key;
    }
}

void selection_sort(std::vector<int> &vec) {
    for (size_t i = 0; i < vec.size() - 1; i++) {
        size_t j_min = i;

        for (size_t j = i + 1; j < vec.size(); j++) {
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
    for (size_t i = 0; i < vec.size() - 1; i++) {
        for (size_t j = 0; j < vec.size() - i - 1; j++) {
            if (vec[j] > vec[j + 1]) {
                swap(vec[j], vec[j + 1]);
            }
        }
    }
}

void cocktail_shaker_sort(std::vector<int> &vec) {
    bool swapped;
    size_t size_minus = vec.size() - 1;

    do {
        swapped = false;
        for (size_t i = 0; i < size_minus; i++) {
            if (vec[i] > vec[i + 1]) {
                swap(vec[i], vec[i + 1]);
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
        swapped = false;
        for (size_t i = size_minus; i >= 0 && i <= size_minus; i--) {
            if (vec[i] > vec[i + 1]) {
                swap(vec[i], vec[i + 1]);
                swapped = true;
            }
        }
    } while (swapped);
}

void comb_sort(std::vector<int> &vec) {
    size_t gap = vec.size();
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

        size_t i = 0;
        while (i + gap < vec.size()) {
            if (vec[i] > vec[i + gap]) {
                swap(vec[i], vec[i + gap]);
                sorted = false;
            }
            i++;
        }
    }
}

void merge_helper(std::vector<int> &vec, size_t left, size_t mid, size_t right) {
    size_t nL = mid - left + 1;
    size_t nR = right - mid;

    int arr_l[nL];
    int arr_r[nR];

    for (size_t i = 0; i < nL; i++)
        arr_l[i] = vec[left + i];
    for (size_t i = 0; i < nR; i++)
        arr_r[i] = vec[mid + 1 + i];

    size_t i = 0;
    size_t j = 0;
    size_t k = left;

    while (i < nL && j < nR) {
        if (arr_l[i] <= arr_r[j]) {
            vec[k] = arr_l[i];
            i++;
        } else {
            vec[k] = arr_r[j];
            j++;
        }
        k++;
    }
    while (i < nL) {
        vec[k] = arr_l[i];
        i++;
        k++;
    }
    while (j < nR) {
        vec[k] = arr_r[j];
        j++;
        k++;
    }
}
void merge_sort_helper(std::vector<int> &vec, size_t left, size_t right) {
    if (left >= right)
        return;

    size_t mid = left + (right - left) / 2;

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

size_t median_of_three_helper(std::vector<int> &vec, size_t low, size_t high) {
    size_t mid = (high + low) / 2;

    if (vec[high] < vec[low]) {
        swap(vec[low], vec[high]);
    }
    if (vec[mid] < vec[low]) {
        swap(vec[low], vec[mid]);
    }
    if (vec[high] < vec[mid]) {
        swap(vec[mid], vec[high]);
    }

    return mid;
}
size_t partition_helper(std::vector<int> &vec, size_t low, size_t high) {
    size_t i = low - 1;
    size_t j = high + 1;
    int pivot = vec[median_of_three_helper(vec, low, high)];

    while (true) {
        do {
            i++;
        } while (vec[i] < pivot);
        do {
            j--;
        } while (vec[j] > pivot);
        if (i >= j) {
            return j;
        }
        swap(vec[i], vec[j]);
    }
}
void quick_sort_helper(std::vector<int> &vec, size_t low, size_t high) {
    if (low < high) {
        size_t pi = partition_helper(vec, low, high);

        quick_sort_helper(vec, low, pi);
        quick_sort_helper(vec, pi + 1, high);
    }
}
void quick_sort(std::vector<int> &vec) {
    if (vec.empty()) {
        return;
    }
    quick_sort_helper(vec, 0, vec.size() - 1);
}

void heapify_helper(std::vector<int> &vec, size_t n, size_t i) {
    size_t largest = i;
    size_t l = 2 * i + 1;
    size_t r = 2 * i + 2;

    if (l < n && vec[l] > vec[largest]) {
        largest = l;
    }
    if (r < n && vec[r] > vec[largest]) {
        largest = r;
    }
    if (largest != i) {
        swap(vec[i], vec[largest]);
        heapify_helper(vec, n, largest);
    }
}
void heap_sort(std::vector<int> &vec, size_t low, size_t high) {
    size_t idk = (high + 1) / 2 - 1;

    for (size_t i = idk; i >= low && i <= idk; i--) {
        heapify_helper(vec, high + 1, i);
    }
    idk = vec.size() - 1;
    for (size_t i = idk; i > low; i--) {
        swap(vec[0], vec[i]);
        heapify_helper(vec, i, low);
    }
}
void heap_sort(std::vector<int> &vec) {
    if (vec.empty()) {
        return;
    }
    heap_sort(vec, 0, vec.size() - 1);
}

void intro_sort_helper(std::vector<int> &vec, uint64_t depth, size_t low, size_t high) {
    if (high - low <= 16) {
        insertion_sort(vec, low, high);
        return;
    }
    if (depth == 0) {
        heap_sort(vec, low, high);
        return;
    }
    size_t pi = partition_helper(vec, low, high);
    intro_sort_helper(vec, depth - 1, low, pi);
    intro_sort_helper(vec, depth - 1, pi + 1, high);
}
void intro_sort(std::vector<int> &vec) {
    uint64_t depth = std::floor(std::log2(vec.size())) * 2;
    intro_sort_helper(vec, depth, 0, vec.size() - 1);
}

void gnome_sort(std::vector<int> &vec) {
    size_t pos = 1;
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
        for (size_t i = 1; i < vec.size() - 1; i += 2) {
            if (vec[i] > vec[i + 1]) {
                swap(vec[i], vec[i + 1]);
                sorted = false;
            }
        }
        for (size_t i = 0; i < vec.size() - 1; i += 2) {
            if (vec[i] > vec[i + 1]) {
                swap(vec[i], vec[i + 1]);
                sorted = false;
            }
        }
    }
}
} // namespace sort
