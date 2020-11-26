#include <chrono>
#include <experimental/random>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "map.hpp"
#include "AVL_tree.hpp"

#include <fstream>
typedef map_AVL<int, int> SearchTree;

unsigned long long get_time() {
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
}




void Insert()
{
    std::ofstream fout;
    fout.open("C:\\Users\\alexb\\CLionProjects\\untitled3\\3_sem\\tree\\AVLT_insert_data.txt");

    std::cout << "Insert N random numbers in empty tree"<< std::endl;

    SearchTree tree;
    unsigned long long e = 0;


    for (int i = 0; i < 1000; i++) {//расчет погрешности ввода
        unsigned long long a =  get_time();
        unsigned long long b =  get_time();
        e += b - a;
    }
    e = (int) (1.0 * e / 1000 + 0.5);//расчет погрешности ввода

    int flag = true;
    int repeat = 10;
    int time = 0;
    for (int n = 1; n < 50000; n += 1000)
    {



        for (int i = 0; i < repeat; ++i)
        {
            std::vector<int> vec_insert(n);
            for (int i = 0; i < n; ++i) {
                vec_insert[i] = std::experimental::randint(0, 1000*n);
            }

            unsigned long long start =  get_time();
            for (int j = 0; j < n; ++j)
                tree.insert(std::make_pair(vec_insert[j], 1));
            unsigned long long finish =  get_time();
            time += ( finish >= start + e ? finish - start - e : 0);

            for (int j = 0; j < n; ++j)
                if (!(tree.end() != tree.find(vec_insert[j])) && flag)
                {
                    std::cout << "It can't insert elements"<< std::endl;
                    std::cout << "There is a problem with" << vec_insert[j] <<  std::endl;

                    for (int k = n; k < n; ++k)
                        std::cout << vec_insert[k] << " ";
                    flag = false;

                }
            vec_insert.clear();

            tree.clear();
        }
        std::cout << n << "                 " << time/repeat <<  std::endl;
        fout  << n << " " << time/repeat << std::endl;
    }
    fout.close();

}

void Insert_for_baby()
{
    std::ofstream fout;

    fout.open("C:\\Users\\alexb\\CLionProjects\\untitled3\\3_sem\\tree\\AVLT_insert_for_baby_data.txt");
    std::cout <<" Inserting time of one element "<< std::endl;

    SearchTree tree;

    unsigned long long e = 0;

    for (int i = 0; i < 1000; i++) {//расчет погрешности ввода
        unsigned long long a =  get_time();
        unsigned long long b =  get_time();
        e += b - a;
    }
    e = (int) (1.0 * e / 1000 + 0.5);//расчет погрешности ввода

    int p = 22;
    int a = 1;
    std::vector<int> sizes {p};  // размеры
    for (int i = 0; i < p; ++i){

        sizes.push_back(a);
        a*=2;
    }

    std::vector<int> rand_vec(sizes.back());
    std::srand(get_time());
    for (int i = 0; i < sizes.back(); ++i) {
        auto tmp = std::rand();
        rand_vec[i] = tmp;

    }
    int repeat = 1000; // число повторений для усреднения
    std::vector<int> small_rand_vec(repeat);
    for (int i = 0; i < repeat; ++i)
        small_rand_vec[i] = std::rand();
    double insert_time = 0;  // ms время вставки

    for (int i = 0; i < sizes.size(); ++i) {
        if (i > 0) {
            for (int j = sizes[i - 1]; j < sizes[i]; ++j) {
                tree.insert(std::make_pair(rand_vec[j], 1));
            }
        }

        for (int j = 0; j < repeat; ++j) {
            int tmp = small_rand_vec[j];
            unsigned long long start = get_time();
            tree.insert(std::make_pair(tmp, 1));
            unsigned long long finish = get_time();

            insert_time += (finish >= start + e ? finish - start - e : 0);

        }
        std::cout <<  sizes[i] << "                       " << insert_time / repeat << std::endl;
        fout   << sizes[i] << " " << insert_time / repeat <<  std::endl;


    }
    rand_vec.clear();
    small_rand_vec.clear();
    tree.clear();
    fout.close();

}




void Erase()
{
    std::ofstream fout;

    fout.open("C:\\Users\\alexb\\CLionProjects\\untitled3\\3_sem\\tree\\AVLT_erase_data.txt");
    std::cout << " Erasing time of one element for different size"<< std::endl;

    SearchTree tree;

    unsigned long long e = 0;

    for (int i = 0; i < 1000; i++) {//расчет погрешности ввода
        unsigned long long a =  get_time();
        unsigned long long b =  get_time();
        e += b - a;
    }
    e = (int) (1.0 * e / 1000 + 0.5);//расчет погрешности ввода

    int p =21;
    int a = 1;
    std::vector<int> sizes {p};  // размеры

    for (int i = 0; i < p; ++i){

        sizes.push_back(a);
        a*=2;
    }

    std::vector<int> rand_vec(sizes.back());
    std::srand(get_time());
    for (int i = 0; i < sizes.back(); ++i) {
        auto tmp = std::rand();
        rand_vec[i] = tmp;

    }
    int repeat = 1000; // число повторений для усреднения
    std::vector<int> small_rand_vec(repeat);
    for (int i = 0; i < repeat; ++i)
        small_rand_vec[i] = std::rand();
    double erase_time = 0;  // ms время удаления

    for (int i = 0; i < sizes.size(); ++i) {
        if (i > 0) {
            for (int j = sizes[i - 1]; j < sizes[i]; ++j) {
                tree.insert(std::make_pair(rand_vec[j], 1));
            }
        }

        for (int j = 0; j < repeat; ++j) {
            int tmp = small_rand_vec[j];

            tree.insert(std::make_pair(tmp, 1));
            unsigned long long start = get_time();
            tree.erase(tmp);
            unsigned long long finish = get_time();

            erase_time += (finish >= start + e ? finish - start - e : 0);

        }

        std::cout << sizes[i] << "                 " << erase_time/repeat << std::endl;
        fout  << sizes[i] << " "  <<  erase_time/repeat << std::endl;

    }
    rand_vec.clear();
    small_rand_vec.clear();
    tree.clear();
    fout.close();


}
// Check


int main()
{

    Insert();
    Insert_for_baby();
    Erase();


    return 0;
}
//
// Created by alexb on 26.11.2020.
//
