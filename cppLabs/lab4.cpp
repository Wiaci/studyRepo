#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <iterator> 
#include <numeric>
#include <random>

class Divisors {
private:
    const int number;
    std::vector<int> divisors;

public:
    // Конструктор класса, вычисляющий все делители переданного числа
    Divisors(int num) : number(num) {
        for (int i = 1; i <= num; i++) {
            if (num % i == 0) {
                divisors.push_back(i);
            }
        }
    }

    // Метод, определяющий, есть ли делитель у числа
    bool containsDevisor(int devisor) const {
        return std::find(this->divisors.begin(), this->divisors.end(), devisor) != this->divisors.end();
    }

    // Метод для вычисления среднего арифметического делителей числа
    double averageDivisors() const {
        if (divisors.empty()) {
            return 0.0;
        }

        int sum = std::accumulate(divisors.begin(), divisors.end(), 0);
        return static_cast<double>(sum) / divisors.size();
    }

    // Перегрузка оператора вывода для вывода объекта в поток
    friend std::ostream& operator<<(std::ostream& os, const Divisors& divisorsObj) {
        os << divisorsObj.number;
        return os;
    }

    // Статический метод, создающий копию объекта класса
    static Divisors copy(const Divisors& other) {
        return Divisors(other.number);
    }

    // Дружественная функция для нахождения НОД с использованием std::bind
    friend int findNODUsingBind(const Divisors& a, const Divisors& b);
    
    // Дружественная функция для нахождения НОД с использованием лямбда-выражения
    friend int findNODUsingLambda(const Divisors& a, const Divisors& b);
};

// Функция для нахождения НОД с использованием std::bind
int findNODUsingBind(const Divisors& a, const Divisors& b) {
    auto it = a.divisors.begin();
    int val = 0;
    while (it != a.divisors.end()) {
        val = *it;
        it = std::find_if(it + 1, a.divisors.end(), std::bind(&Divisors::containsDevisor, b, std::placeholders::_1));
    }
    return val;
}

// Дружественная функция для нахождения НОД с использованием лямбда-выражения
int findNODUsingLambda(const Divisors& a, const Divisors& b) {
    auto it = a.divisors.begin();
    int val = 0;
    while (it != a.divisors.end()) {
        val = *it;
        it = std::find_if(it + 1, a.divisors.end(), [b](int x) { return b.containsDevisor(x); });
    }
    return val;
}

int main() {
    const int N = 10; // Количество объектов класса

    // Создание контейнера и заполнение случайными числами
    std::vector<Divisors> divisorsContainer;
    for (int i = 1; i <= N; ++i) {
        divisorsContainer.push_back(Divisors(std::rand() % 1000));
    }

    // Вывод объектов из контейнера
    std::cout << "Объекты из контейнера: ";
    std::copy(divisorsContainer.begin(), divisorsContainer.end(), std::ostream_iterator<Divisors>(std::cout, " "));
    std::cout << std::endl;

    // Запрос делителя от пользователя
    int userDivisor;
    std::cout << "Введите делитель: ";
    std::cin >> userDivisor;

    // Подсчет чисел с указанным делителем
    int count = std::count_if(divisorsContainer.begin(), divisorsContainer.end(), [userDivisor](const Divisors& obj) {
        return obj.containsDevisor(userDivisor);
    });

    std::cout << "Количество объектов с делителем " << userDivisor << ": " << count << std::endl;

    // Вывод среднего арифметического делителей для всех чисел в контейнере
    std::cout << "Среднее делителей всех чисел в контейнере:" << std::endl;
    for (const auto& obj : divisorsContainer) {
        std::cout << obj << ": " << obj.averageDivisors() << std::endl;
    }

    // Поиск НОД двух чисел в контейнере с использованием std::bind
    int gcdUsingBind = findNODUsingBind(divisorsContainer[2], divisorsContainer[3]);
    std::cout << "НОД " << divisorsContainer[2] << " и " << divisorsContainer[3] << " с использованием std::bind: " << gcdUsingBind << std::endl;

    // Поиск НОД двух чисел в контейнере с использованием лямбда-выражения
    int gcdUsingLambda = findNODUsingLambda(divisorsContainer[2], divisorsContainer[3]);
    std::cout << "НОД " << divisorsContainer[2] << " и " << divisorsContainer[3] << " с использованием лямбда-выражения: " << gcdUsingLambda << std::endl;

    return 0;
}
