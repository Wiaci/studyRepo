#include <iostream>
#include <string>
#include <random>
#include <ctime>
#include <vector>
#include <fstream>
#include <thread>
#include <chrono>

// количество посетителей при интенсивности 1
const int MAX_VISITORS = 15;

// вспомогательная функция для генерации случайного double от 0 до 1
double rnd() {
    return ((double) std::rand()) / RAND_MAX;
}

// функция для вычисления интенсивности посещения зоопарка
// возьмем функцию гаусса, максимальной интенсивностью посчитаем время 18:00
double gauss(double x) {
    return 0.8*exp(-(x-18)*(x-18)/24.5);
}

// функция вычисляет значение интенсивности посещения в конкретный час с разбросом +-0.1
// для этого в предыдущей фунции экспонента умножается на 0.8
double intensity_by_hour(int hour) {
    return rnd() * 0.2 + gauss((double) hour);
}

// возвращает вектор интенсивностей посещения за каждый час дня
// зоопарк не работает с 00:00 до 8:00, так что оставляем там значение 0
std::vector<double> generateIntensities() {
    std::vector<double> intensities(24);
    for (int i = 8; i < 24; i++) {
        intensities[i] = intensity_by_hour(i);
    }
    return intensities;
}

// перечисление состояний животных
enum State {AWAKE, SLEEPING, EATING, PLAYING};

/* 
основной класс животного

std::string name;               - имя
int age;                        - возраст
int satiety;                    - сытость
int fatigue;                    - усталость
State state;                    - состояние
int energyRestoringPerHour;     - восстановление энергии за час сна
int fatiguePerPlaying;          - усталость от цикла игры с другими животными
double playingProbability;      - вероятность в цикле поиграть с животными
int sleepsForCycles;            - сколько циклов уже спит
int satietyRestoringPerCycle;   - восстановление сытости за цикл кормления
std::string animalName;         - вид животного
int fatigueByCycle;             - пассивное накопление усталости за цикл
int satietyByCycle;             - пассивное уменьшение сытости за цикл

*/
class Animal {
    public:
        std::string name;
        int age;
        int satiety = 100;
        int fatigue = 0;
        State state = AWAKE;

        int energyRestoringPerHour;
        int fatiguePerPlaying;
        double playingProbability;
        int sleepsForCycles;
        int satietyRestoringPerCycle;
        std::string animalName;

        int fatigueByCycle;
        int satietyByCycle;

        Animal(std::string name, int age) {
            this->name = name;
            this->age = age;
        }

        // with_animal - играет с животным или с человеком
        void play(bool with_animal) {
            // с человеком играем всегда, с животным - если сработала вероятность
            if (rnd() > playingProbability && with_animal) return;

            // множитель для расчета усталости
            double mult = with_animal ? 1.0 : 1.5;
            state = PLAYING;
            std::string s = with_animal ? "с животными" : "с посетителем";
            std::cout << animalName << " " << name 
                      << " играет " << s << std::endl;
            
            // с человеком животное устает в 1.5 раза больше
            fatigue += (int) (fatiguePerPlaying * mult);
            if (fatigue > 100) fatigue = 100;
        }

        // только полноценный час сна (6 циклов) уменьшает усталость, поэтому следим за циклами
        void sleep() {
            state = SLEEPING;
            std::cout << animalName << " " << name 
                        << " спит" << std::endl;
            sleepsForCycles++;
            if (sleepsForCycles == 6) {
                fatigue -= energyRestoringPerHour;
                if (fatigue < 0) fatigue = 0;
                sleepsForCycles = 0;
            }
            
        }
        
        // feed_by_visitor - кормит посетитель или работник зоопарка
        void eat(bool feed_by_visitor) {
            state = EATING;

            // множитель для расчета насыщения - посетителю нельзя много кормить животное
            double mult = feed_by_visitor ? 0.2 : 1.0;
            satiety += (int) (satietyRestoringPerCycle * mult);
            if (satiety > 100) satiety = 100;
            std::string s = feed_by_visitor ? "посетителя" : "работника";
            std::cout << animalName << " " << name 
                      << " ест еду " << s << std::endl;
        }

        // восстановление бодрствующего состояния 
        void wakeUp() {
            state = AWAKE;
            sleepsForCycles = 0;
        }

        // нужно ли животному есть
        bool needsToEat() {
            return satiety < 20;
        }

        // нужно ли животному спать
        bool needsToSleep() {
            return fatigue > 80;
        }

        // уменьшение показателей каждый цикл работы зоопарка
        void passiveDecline(double intensity) {
            if (state != SLEEPING) {
                fatigue += (int)((1 + intensity) * fatigueByCycle);
                if (state != EATING) {
                    satiety -= (int)((1 + intensity) * satietyByCycle);
                }
            }
        }
};

// класс кошки и ее характеристики
class Cat: public Animal {
    public:
        Cat(std::string name, int age) : Animal(name, age) {
            energyRestoringPerHour = 7;
            fatiguePerPlaying = 10;
            playingProbability = 0.1;
            animalName = "Кошка";
            satietyRestoringPerCycle = 75;
            fatigueByCycle = 5;
            satietyByCycle = 4;
        }
};


// класс собаки и ее характеристики
class Dog: public Animal {
    public:
        Dog(std::string name, int age) : Animal(name, age) {
            energyRestoringPerHour = 9;
            fatiguePerPlaying = 8;
            playingProbability = 0.3;
            animalName = "Собака";
            satietyRestoringPerCycle = 70;
            fatigueByCycle = 6;
            satietyByCycle = 4;
        }
};


// класс вомбата и его характеристики
class Wombat: public Animal {
    public:
        Wombat(std::string name, int age) : Animal(name, age) {
            energyRestoringPerHour = 6;
            fatiguePerPlaying = 13;
            playingProbability = 0.05;
            animalName = "Вомбат";
            satietyRestoringPerCycle = 60;
            fatigueByCycle = 7;
            satietyByCycle = 3;
        }
};

// класс крысы и ее характеристики
class Rat: public Animal {
    public:
        Rat(std::string name, int age) : Animal(name, age) {
            energyRestoringPerHour = 10;
            fatiguePerPlaying = 5;
            playingProbability = 0.5;
            animalName = "Крыса";
            satietyRestoringPerCycle = 100;
            fatigueByCycle = 4;
            satietyByCycle = 6;
        }
};


/*
класс зоопарка

std::vector<Animal*> animals    - животные зоопарка
std::vector<double> intensities - интенсивность посещений текущего дня
int hours = 0                   
int minutes = 0                 - текущее время

*/
class Zoo {
    public:
        std::vector<Animal*> animals;
        std::vector<double> intensities;
        int hours = 0;
        int minutes = 0;
        
        // count - вектор, содержащий количество каждого типа животных в зоопарке
        // создаем зоопарк, наполняем его животными
        Zoo(std::vector<int> count) {
            // читаем из файла names.txt возможные имена животных
            std::fstream names_file;
            names_file.open("names.txt", std::ios::in);
            std::string names_str;
            std::getline(names_file, names_str);
            names_file.close();

            // собираем вектор всех возможных имен
            std::vector<std::string> names;
            int pos = 0;
            while(pos < names_str.size()) {
                pos = names_str.find(", ");
                names.push_back(names_str.substr(0,pos));
                names_str.erase(0,pos+2);
            }

            // наполняем вектор animals нужным количеством животных каждого типа
            // со случайными именами и возрастом
            for (int i = 0; i < count[0]; i++) {
                animals.push_back(new Cat(names[(int)(rnd() * names.size())], 
                                    (int)(rnd() * 18.0) + 1));
            }
            for (int i = 0; i < count[1]; i++) {
                animals.push_back(new Dog(names[(int)(rnd() * names.size())], 
                                    (int)(rnd() * 13.0) + 1));
            }
            for (int i = 0; i < count[2]; i++) {
                animals.push_back(new Wombat(names[(int)(rnd() * names.size())], 
                                    (int)(rnd() * 15.0) + 1));
            }
            for (int i = 0; i < count[3]; i++) {
                animals.push_back(new Rat(names[(int)(rnd() * names.size())], 
                                    (int)(rnd() * 3.0) + 1));
            }
        }

        // функция симуляции работы зоопарка
        // days - количество дней
        void simulateForDays(int days) {
            // cycles - оставшееся количество циклов. Цикл составляет 10 минут
            for (int cycles = days * 24 * 6; cycles > 0; cycles--) {
                printTime();
                // если время ночное и зоопарк не работает, всех животных отправляем спать
                // и проматываем циклы до утра
                if (hours >= 0 and hours < 8) {
                    forceToSleep();
                    nextNCycles(48);
                    cycles -= 47;

                    continue;
                } 
                // в 8 утра генерируем интенсивность посещения в этот день и будим всех животных
                if (hours == 8 && minutes == 0) {
                    intensities = generateIntensities();
                    forceToWakeUp();
                }
                // все, кто играл - перестают играть
                stopPlaying();
                // проверяем, нужно ли кому-то спать или есть
                inspect();
                // кто хочет, идет играть с другими животными
                playWithAnimals();
                // к кому-то подходят играть посетители
                playWithVisitors();
                // к кому-то подходят играть посетители чтобы покормить
                feedByVisitors();
                // в конце цикла у всех уменьшаются показатели
                passiveDecline();

                // переходим к следующему циклу
                nextNCycles(1);
                std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            }
        }

        // функция печати текущего времени
        void printTime() {
            std::cout << "\n";
            if (hours < 10) std::cout << "0";
            std::cout << hours << ":";
            if (minutes == 0) std::cout << "0";
            std::cout << minutes << std::endl;
        }

        // проверяем состояние животных
        void inspect() {
            for (Animal* a: animals) {
                if (a->state == SLEEPING) {
                    if (a->sleepsForCycles == 0) {
                        if (a->needsToSleep()) a->sleep();
                        else a->wakeUp();
                    } else a->sleep();
                } else if (a->state == EATING) {
                    if (a->needsToEat()) a->eat(false);
                    else a->wakeUp();
                } else {
                    if (a->needsToSleep()) a->sleep();
                    else if (a->needsToEat()) a->eat(false);
                }
            }
        }

        // животные перестают играть
        void stopPlaying() {
            for (Animal* a: animals) {
                if (a->state == PLAYING) a->wakeUp();
            }
        }

        // животные играют с другими животными
        void playWithAnimals() {
            for (Animal* a: animals) {
                if (a->state == AWAKE) a->play(true);
            }
        }

        // текущая интенсивность делится на три потока - одни играют, другие кормят, третьи просто гуляют
        void playWithVisitors() {
            for (Animal* a: animals) {
                if (a->state == AWAKE && 
                    rnd() < MAX_VISITORS * intensities[hours] / 3 / animals.size()) a->play(false);
            }
        }

        void feedByVisitors() {
            for (Animal* a: animals) {
                if (a->state == AWAKE && 
                    rnd() < MAX_VISITORS * intensities[hours] / 3 / animals.size()) a->eat(true);
            }
        }

        // отправляем животных спать на ночь, их усталость уходит, но сильно теряют в сытости
        void forceToSleep() {
            for (Animal* a: animals) {
                a->sleep();
                a->fatigue = 0;
                a->satiety -= 50;
            }
        }

        // будим животных
        void forceToWakeUp() {
            for (Animal* a: animals) {
                a->wakeUp();
            }
        }

        // уменьшаем показатели в конце цикла
        void passiveDecline() {
            for (Animal* a: animals) {
                a->passiveDecline(intensities[hours]);
            }
        }

        // проматываем N циклов
        void nextNCycles(int n) {
            for (int i = 0; i < n; i++) {
                minutes += 10;
                if (minutes == 60) {
                    minutes = 0;
                    hours++;
                    if (hours == 24) hours = 0;
                }
            }
        }
};


int main() {
    std::srand(time(0));
    std::vector<int> animal_counts = {3, 2, 4, 3};
    Zoo zoo(animal_counts);
    zoo.simulateForDays(30);
}