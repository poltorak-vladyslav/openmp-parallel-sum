#include <iostream>
#include <omp.h>
#include <vector>
#include <numeric>

int main()
{
    int n = 500000;
    std::vector<int> array(n, 1);

    int total_sum = 0;
    int num_threads = 8;
    int chunk_size = n / num_threads;

    #pragma omp parallel num_threads (num_threads)
    {
        int thread_id = omp_get_thread_num();
        int start_index = thread_id * chunk_size;
        int end_index = (thread_id == num_threads - 1) ? n : start_index + chunk_size;

        int local_sum = std::accumulate(array.begin() + start_index, array.begin() + end_index, 0);

        #pragma omp critical
        {
            total_sum += local_sum;
        }
    }

    std::cout << "Total sum: " << total_sum << std::endl;
}
