#include <iostream>

template <typename T>
class Vector {
private:
    T* data; // массив для хранения элементов вектора
    int size; // текущий размер вектора
    int capacity = 16; // текущая емкость массива

public:
    // Если n не указан, создаем пустой вектор
    // Если указан, создаем вектор соответствующего размера и заполняем нулями
    Vector(int n = 0) {
        size = n;
        if (n > capacity) {
            capacity = n;
        }
        for (int i = 0; i < n; i++) {
            data[i] = 0;
        }
        data = new T[capacity];
    }

    // Деструктор, освобождаем выделенную под массив память
    ~Vector() {
        delete[] data;
    }

    // Пуст ли вектор
    bool isEmpty() {
        return size == 0;
    }

    // Размер вектора
    int getSize() {
        return size;
    }

    // Доступ к элементам вектора
    T& operator[](int index) {
        if (index < 0 || index >= size) {
            std::cerr << "Индекс больше размера вектора" << std::endl;
        }
        return data[index];
    }

    // Изменение емкости массива
    void resize(int newCapacity) {
        if (newCapacity < size) {
            std::cerr << "В новый размер не помещаются элементы вектора" << std::endl;
            return;
        }
        
        // Создаем новый массив и копируем в него элементы предыдущего массива
        T* newData = new T[newCapacity];
        for (int i = 0; i < size; i++) {
            newData[i] = data[i];
        }

        // Удаляем старый массив
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }


    // Вставка элемента в конец вектора
    void push(const T& value) {
        if (size == capacity) {
            resize(capacity * 2); // Удваиваем текущую ёмкость, если она кончилась
        }
        data[size] = value;
        size++;
    }

    // Удаление элемента из конца вектора
    void pop() {
        if (size > 0) {
            size--;
        }
    }

    // Итератор для обхода контейнера
    class Iterator {
    private:
        T* ptr;

    public:
        Iterator(T* p) : ptr(p) {}

        // Переопределяем операторы для обхода контейнера
        T& operator*() {
            return *ptr;
        }

        Iterator& operator++() {
            ptr++;
            return *this;
        }

        bool operator!=(const Iterator& other) {
            return ptr != other.ptr;
        }
    };
        // Реализуем методы получения начала и конца вектора
        Iterator begin() {
            return Iterator(data);
        }

        Iterator end() {
            return Iterator(data + size);
        }
};

// Тестируем вектор
int main() {
    Vector<int> myVector;

    std::cout << "Вектор пуст: " << myVector.isEmpty() << std::endl;

    for (int i = 1; i <= 10; i++) {
        myVector.push(i);
    }

    std::cout << "Вектор пуст: " << myVector.isEmpty() << std::endl;

    for (auto element : myVector) {
        std::cout << element << " ";
    }

    std::cout << std::endl;

    for (int i = 0; i < 5; i++) {
        myVector.pop();
    }

    for (auto element : myVector) {
        std::cout << element << " ";
    }

    std::cout << std::endl;

    std::cout << "Размер вектора: " << myVector.getSize() << std::endl;

    std::cout << myVector[4] << std::endl;
    std::cout << myVector[10] << std::endl;
    

    

    return 0;
}