#include <iostream>
#include <vector>
#include <deque>
#include <chrono>
#include <random>
#include <iterator>

template <typename RandomAccessIterator, typename Compare>
void sift_down(RandomAccessIterator begin,
               std::size_t start_pos,
               std::size_t heap_len,
               Compare cmp) {
    std::size_t node = start_pos;

    while (true) {
        std::size_t left_child = node * 2 + 1;
        if (left_child >= heap_len) break;

        std::size_t chosen = node;
        std::size_t right_child = left_child + 1;

        if (cmp(begin[chosen], begin[left_child])) {
            chosen = left_child;
        }
        if (right_child < heap_len && cmp(begin[chosen], begin[right_child])) {
            chosen = right_child;
        }

        if (chosen == node) break;

        std::swap(begin[node], begin[chosen]);
        node = chosen;
    }
}

template <typename RandomAccessIterator, typename Compare>
void sort(RandomAccessIterator begin, RandomAccessIterator end, Compare cmp) {
    std::size_t n = static_cast<std::size_t>(end - begin);
    if (n < 2) return;

    // Build heap
    for (std::size_t i = n / 2; i > 0; --i) {
        sift_down(begin, i - 1, n, cmp);
    }

    // Extract elements
    for (std::size_t sz = n; sz > 1; --sz) {
        std::swap(begin[0], begin[sz - 1]);
        sift_down(begin, 0, sz - 1, cmp);
    }
}

bool less_int(int x, int y) {
    return x < y;
}

struct GreaterInt {
    bool operator()(int x, int y) const {
        return x > y;
    }
};

template <typename Container>
void print_container(const Container& cont) {
    for (const auto& val : cont) {
        std::cout << val << ' ';
    }
    std::cout << '\n';
}

void demo_sort() {
    std::vector<int> vec1 = {5, 2, 9, 1, 3};
    ::sort(vec1.begin(), vec1.end(), less_int);
    std::cout << "vector function: ";
    print_container(vec1);

    std::deque<int> deq1 = {5, 2, 9, 1, 3};
    ::sort(deq1.begin(), deq1.end(), [](int a, int b) {
        return a < b;
    });
    std::cout << "deque lambda: ";
    print_container(deq1);

    std::vector<int> vec2 = {5, 2, 9, 1, 3};
    ::sort(vec2.begin(), vec2.end(), GreaterInt{});
    std::cout << "vector functor: ";
    print_container(vec2);
}

template <typename Container>
long long benchmark(Container cont) {
    auto start = std::chrono::steady_clock::now();
    ::sort(cont.begin(), cont.end(), [](int a, int b) {
        return a < b;
    });
    auto end = std::chrono::steady_clock::now();

    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

void benchmark_test() {
    const int SIZE = 500000;

    std::vector<int> source;
    source.reserve(SIZE);

    std::mt19937 rng(42);
    std::uniform_int_distribution<int> dist(-1000000, 1000000);

    for (int i = 0; i < SIZE; ++i) {
        source.push_back(dist(rng));
    }

    std::vector<int> vec_copy(source.begin(), source.end());
    std::deque<int> deq_copy(source.begin(), source.end());

    long long time_vec = benchmark(vec_copy);
    long long time_deq = benchmark(deq_copy);

    std::cout << "vector ms: " << time_vec << '\n';
    std::cout << "deque ms: " << time_deq << '\n';

    if (time_vec < time_deq) {
        std::cout << "faster: vector\n";
    } else {
        std::cout << "faster: deque\n";
    }
}

int main() {
    demo_sort();
    benchmark_test();
    return 0;
}
