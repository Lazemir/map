#include <chrono>
#include <experimental/random>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "map.hpp"
#include "AVL_tree.hpp"
typedef map_AVL<int, std::string> binTree_t;
// typedef std::map<int, std::string> binTree_t;



class MyTimer
{
    private:
        // почему не работает со static ????????????????
        std::chrono::time_point<std::chrono::steady_clock> start_time, finish_time;
        std::chrono::duration<double, std::milli> time_dif;  // ms
    public:
        void start()
        {
            start_time = std::chrono::steady_clock::now();
        }
        void stop()
        {
            finish_time = std::chrono::steady_clock::now();
            time_dif = finish_time - start_time;
        }
        double time()
        {
            return time_dif.count();
        }

};

void line()
{
    std::cout << "---------------------------------------------------------------------------\n\n";
}


void test_1_0(int& n_fail)
{
    std::cout << "\n\t1.0 test: Insert N random number in empty tree\n\n";

    // Preparation
    MyTimer tic_tuck;
    int is_test_correct = true;
    binTree_t tree;

    int repeat = 20;
    double time = 0;
    for (int n = 1; n < 1000000; n *= 8)
    {
        std::vector<int> rand_vec(n*repeat);
        for (int i = 0; i < rand_vec.size(); ++i) {
            rand_vec[i] = std::experimental::randint(0, 1000*n);
        }


        // Test
        for (int i = 0; i < repeat; ++i)
        {
            tic_tuck.start();
            for (int j = i*n; j < (i+1)*n; ++j)
                tree.insert(std::make_pair(rand_vec[j], "My life is pain :("));
            tic_tuck.stop();
            time += tic_tuck.time();

        // Check
            for (int j = i*n; j < (i+1)*n; ++j)
                if (!(tree.end() != tree.find(rand_vec[j])) && is_test_correct)
                {
                    std::cout << "Your rbtree is messy\nIt can't find or insert elements\n";
                    std::cout << "Not found " << rand_vec[j] << '\n';
                    for (int k = n*i; k < n*(i+1); ++k)
                        std::cout << rand_vec[k] << " ";
                    std::cout << '\n';
                    is_test_correct = false;
                    n_fail++;
                }
            // if ((tree.size() != n) && is_test_correct)
            // {
            //     std::cout << "My tree is cooler than your tree\nYou have problem with function size_t rbTree::size()\n";
            //     std::cout << "expected " << n << " real size is " << tree.size() << '\n';  // TODO: delete this line after debug
            //     is_test_correct = false;
            //     n_fail++;
            // }
            // if (is_test_correct)
            //     std::cout << "1.0 test complete\n";

            tree.clear();
        }
        std::cout << "time to insert " << n << " elements: " << time/repeat << " ms\n";
    }
    line();
}

void test_2_0(int& n_fail)
{
    std::cout << "\t2.0 test: Inserting time of one element for different size\n\n";
    
    // Preparation
    MyTimer tic_tuck;
    int is_test_correct = true;
    binTree_t tree;
    
    std::vector<int> sizes {0, 8, 64, 512, 4096, 32768, 262144, 2097152, 16777216, 134217728};  // размеры
    std::vector<int> rand_vec(*sizes.rbegin());  // TODO: мб использовать reserve
    std::srand('я устал');
    int spec_number = std::rand();  // точно нет в дереве
    for (int i = 0; i < rand_vec.size(); ++i)
    {
        auto tmp = std::experimental::randint(0, 1000 * (*sizes.rbegin()));
        if (tmp == spec_number)
            tmp++;
        rand_vec[i] = tmp;
    }
    int repeat = 1000; // число повторений для усреднения
    std::vector<int> small_rand_vec(repeat);
    for (int i = 0; i < repeat; ++i)
        small_rand_vec[i] = std::rand();
    double insert_time = 0;  // ms время вставки
    double erase_time = 0;  // ms 
    
    for (int i = 0; i < sizes.size(); ++i)
    {
        if (i > 0) {
            for (int j = sizes[i-1]; j < sizes[i]; ++j) {
                tree.insert(std::make_pair(rand_vec[j], "It's a joke. It's all a fucking joke"));
            }
        }
        
    // Test
        for (int j = 0; j < repeat; ++j)
        {
            int tmp = small_rand_vec[j];  // spec_number or small_rand_vec[i]
            tic_tuck.start();
            tree.insert(std::make_pair(tmp, "Hello Hell"));
            tic_tuck.stop();
            insert_time += tic_tuck.time();

            tic_tuck.start();
            tree.erase(tmp);
            tic_tuck.stop();
            erase_time += tic_tuck.time();
        }
        std::cout << "The average insertion time into a tree of " << sizes[i] << "\telements is " << insert_time/repeat << " ms\n";
        std::cout << "The average erase time:" << "\t\t\t\t\t\t " << erase_time/repeat << " ms\n";
    }
    // Check

    line();
}


int main()
{
    // Дебил, не забудь все вернуть на место
    // rbTree_t --> rbTree< , >
    // count --> contains
    // std::pair(a, b) --> a, b
    // std::rand --> randint

    std::cout << "\n\n============================== Start of test ==============================\n\n";
    int number_of_tests = 2;
    int number_of_failed_tests = 0;

    test_1_0(number_of_failed_tests);
    test_2_0(number_of_failed_tests);

    std::cout << "\tResults\n" << number_of_failed_tests << " test(s) is FAILED\n";
    std::cout << number_of_tests - number_of_failed_tests << " test(s) is passed";
    std::cout << "\n\n=============================== End of test ===============================\n\n";

    
    return 0;
}
