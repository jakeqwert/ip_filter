// cat ip_filter.tsv | ip_filter
// Вывод совпадет с ip_filter.tst

// cat ip_filter.tsv | cmake-build-debug/ip_filter
// Вывод совпадет с ip_filter.tst

//WIN
// cat ip_filter.tsv | cmake-build-debug/filter.exe

// $ ip_filter < ip_filter.tsv


//Совет: можно избавиться от ручного создания build каталога:
//$ cmake -H. -Bbuild -DBUILD_TESTING=ON -DCMAKE_BUILD_TYPE=Release
//где:
//-H указывает путь до CMake проекта;
//-B задаёт путь для каталога сборки (создаёт его, если нет его);
//-D задаёт переменные в CMake, что может добавить гибкости.
//
//Далее:
//$ cmake --build build
//$ cmake --build build --target test
//$ cmake --build build --target package
//в результате будет deb-пакет в каталоге build.


// по руководству https://docs.conan.io/en/latest/getting_started.html
//'conanfile.txt'
//[requires]
//gtest/cci.20210126
//
//[generators]
//cmake

/*
   $ source ~/PackageManagerCPP_conan/venv/bin/activate
   $ conan install . --install-folder cmake-build-debug --build=missing      // cmake-build-release
     //лучше, т.к. указывается папка для build (иначе для subdirectory будет внутри их build делать и тек. папке)
   $ cmake -G "Unix Makefiles" -S . -B ./cmake-build-debug -DCMAKE_BUILD_TYPE=debug
   $ cmake --build ./cmake-build-debug                        --config Release

     target calculations
     target MyProject
     target tests

// запуск программы
   $ ./cmake-build-debug/bin/ip_filter

// запуск тестов
   $ ./cmake-build-debug/bin/ip_filter_tests

*/


//ниже вывожу отладочные сообщения
#define NDEBUG

#include "ip_filter.h"

int main()
{
    ip_vector ip_pool;

    try
    {
        for(std::string line; std::getline(std::cin, line);)
        {
            line.resize(line.find_first_of('\t')); //укоротили до первой таб

            ip_pool.emplace_back(parse_ip(line));
        }

        // TODO reverse lexicographically sort
        // 1 Сортировка без написания своих лямбд и операторов сравнения.
        std::sort(ip_pool.begin(), ip_pool.end(), std::greater<>());

#ifdef NDEBUG
        std::cout << "######## reverse lexicographically sort" << std::endl;
#endif // NDEBUG
        print_ip_pool(ip_pool); // вывод на экран результата
        /*
         222.173.235.246
         222.130.177.64
         222.82.198.61
         ...
         1.70.44.170
         1.29.168.152
         1.1.234.8
         */


        // TODO filter by first byte and output
#ifdef NDEBUG
        std::cout << "######## filter(1)" << std::endl;
#endif
        print_ip_pool(filter(ip_pool, 1));
        /*
         1.231.69.33
         1.87.203.225
         1.70.44.170
         1.29.168.152
         1.1.234.8
         */

        // TODO filter by first and second bytes and output
#ifdef NDEBUG
        std::cout << "######## filter(46, 70)" << std::endl;
#endif
        print_ip_pool(filter(ip_pool, 46, 70));
        /*
        46.70.225.39
        46.70.147.26
        46.70.113.73
        46.70.29.76
        */

        // TODO filter by any byte and output
#ifdef NDEBUG
        std::cout << "######## filter_any(46)" << std::endl;
#endif
        print_ip_pool(filter_any(ip_pool, 46));
        /*
         186.204.34.46
         186.46.222.194
         185.46.87.231
         185.46.86.132
         185.46.86.131
         185.46.86.131
         185.46.86.22
         185.46.85.204
         185.46.85.78
         68.46.218.208
         46.251.197.23
         46.223.254.56
         46.223.254.56
         46.182.19.219
         46.161.63.66
         46.161.61.51
         46.161.60.92
         46.161.60.35
         46.161.58.202
         46.161.56.241
         46.161.56.203
         46.161.56.174
         46.161.56.106
         46.161.56.106
         46.101.163.119
         46.101.127.145
         46.70.225.39
         46.70.147.26
         46.70.113.73
         46.70.29.76
         46.55.46.98
         46.49.43.85
         39.46.86.85
         5.189.203.46
         */
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
