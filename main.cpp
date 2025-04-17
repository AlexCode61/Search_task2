#include <iostream>
#include <random>
#include <vector>
#include <string>
#include <chrono>

int count_srav;
int iter;

// Заполение массива случайными числами
std::vector<int> createMassiv(int count) {
    int start = -100;
    int end = 100;

    std::vector<int> mas;

    for (int i = 0; i < count; i++) {
        int el = rand() % (end - start + 1);
        mas.push_back(el);
    }

    return mas;
}

// Вывод массива
void printMas(const std::vector<int> mas) {
    std::cout << std::endl;
    for (int element : mas) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

int linearSearch(const std::vector<int>& vec, int key) {
    count_srav = 0;
    iter = 0;
    for (size_t i = 0; i < vec.size(); ++i) {
        count_srav++;
        iter++;
        if (vec[i] == key) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

int binarySearch(const std::vector<int>& mas, int key)
{
    iter = 0;
    count_srav = 0;
    int left = 0;
    int right = mas.size() - 1;

    while (left <= right)
    {
        iter++;
        int mid = left + (right - left) / 2;

        count_srav++;
        if (mas[mid] == key) 
        {
            return mid;
        }
        else if (mas[mid] < key)
        {
            left = mid + 1;
        }
        else if(mas[mid] > key)
        {
            right = mid - 1;
        }
    }

    return -1;
}

std::string spacesIndentation(int val, int length) {
    std::string str = std::to_string(val);
    int size = length - str.size();
    for (int i = 0; i < size; i++) {
        str += " ";
    }
    return str;
}

std::string spacesIndentationFloat(float val, int length) {
    std::string str = std::to_string(val);
    int size = length - str.size();
    for (int i = 0; i < size; i++) {
        str += " ";
    }
    return str;
}

void printTableReverse(std::vector<int> mas, int search_el)
{
    std::vector<int> copy_mas = mas;
    std::sort(copy_mas.begin(), copy_mas.end());
    std::reverse(copy_mas.begin(), copy_mas.end());

    std::vector<int> linear_mas = copy_mas;
    std::vector<int> binary_mas = copy_mas;

    // Линейный поиск
    auto start = std::chrono::high_resolution_clock::now();
    linearSearch(linear_mas, search_el);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = end - start;
    float time_linear = duration.count() * 1000;

    std::cout << "| Линейный поиск |" << spacesIndentation(mas.size(), 8) << "|" << " reverse          "  << "|" << spacesIndentation(search_el, 17) << '|' << spacesIndentation(iter, 12) << '|' << spacesIndentation(count_srav, 14) << "|" << spacesIndentationFloat(time_linear, 11) << "|" << std::endl;
    std::cout << "+ ---------------+--------+------------------+-----------------+------------+--------------+-----------+" << std::endl;

    // Бинарный поиск
    start = std::chrono::high_resolution_clock::now();
    binarySearch(binary_mas, search_el);
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    float time_binary = duration.count() * 1000;

    std::cout << "| Бинарный поиск |" << spacesIndentation(mas.size(), 8) << "|" << " reverse          " << "|" << spacesIndentation(search_el, 17) << '|' << spacesIndentation(iter, 12) << '|' << spacesIndentation(count_srav, 14) << "|" << spacesIndentationFloat(time_binary, 11) << "|" << std::endl;
    std::cout << "+ ---------------+--------+------------------+-----------------+------------+--------------+-----------+" << std::endl;

    copy_mas.clear();
}

void printTable(std::vector<int>& mas)
{
    std::vector<float> percent_sortings = { 0, 0.25, 0.5, 0.75, 1 };

    std::cout << "\n+ ---------------+--------+------------------+-----------------+------------+--------------+-----------+" << std::endl;
    std::cout << "| Метод поиска   | Размер |Процент сортировки| Искомый элемент | Повторений | Сравнения    | Время (мс)|" << std::endl;
    std::cout << "+ ---------------+--------+------------------+-----------------+------------+--------------+-----------+" << std::endl;
    int search_el = mas[rand() % (mas.size() - 0 + 1)];
    for (float percent : percent_sortings)
    {
        std::vector<int> copy_mas = mas;
        std::sort(begin(copy_mas), begin(copy_mas) + (copy_mas.size() * percent));

        std::vector<int> linear_mas = copy_mas;
        std::vector<int> binary_mas = copy_mas;

        // Линейный поиск
        auto start = std::chrono::high_resolution_clock::now();
        linearSearch(linear_mas, search_el);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> duration = end - start;
        float time_linear = duration.count() * 1000;

        std::cout << "| Линейный поиск |" << spacesIndentation(mas.size(), 8) << "|" << spacesIndentation(percent * 100, 18) << "|" << spacesIndentation(search_el, 17) << '|'<<spacesIndentation(iter, 12) <<'|' << spacesIndentation(count_srav, 14) << "|" << spacesIndentationFloat(time_linear, 11) << "|" << std::endl;
        std::cout << "+ ---------------+--------+------------------+-----------------+------------+--------------+-----------+" << std::endl;
        
        // Бинарный поиск
        start = std::chrono::high_resolution_clock::now();
        binarySearch(binary_mas, search_el);
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        float time_binary = duration.count() * 1000;

        std::cout << "| Бинарный поиск |" << spacesIndentation(mas.size(), 8) << "|" << spacesIndentation(percent * 100, 18) << "|" << spacesIndentation(search_el, 17) << '|' << spacesIndentation(iter, 12) << '|' << spacesIndentation(count_srav, 14) << "|" << spacesIndentationFloat(time_binary, 11) << "|" << std::endl;
        std::cout << "+ ---------------+--------+------------------+-----------------+------------+--------------+-----------+" << std::endl;
    }
    printTableReverse(mas, search_el);
}

int checkInput(const std::string str) {
    int n;
    while (true) {
        std::cout << str;
        if (std::cin >> n && n >= 0) {
            return n;
        }
        else {
            std::cin.clear();
            std::cin.ignore(2000, '\n');
            std::cout << "Длина массива не может быть отрицательным\n";
        }
    }
}

int main()
{
    srand(time(0));
    setlocale(LC_ALL, "RU");
    
    int length = checkInput("Введите длину массива : ");
    std::vector<int> originalUser = createMassiv(length);
    std::cout << "\nCозданный массив: " << std::endl;
    printMas(originalUser);
    printTable(originalUser);
}