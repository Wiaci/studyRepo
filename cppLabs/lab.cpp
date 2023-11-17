#include <iostream>
#include <random>
#include <ctime>
#include <vector>
#include <string>


// randint - сгенерировать случайное целое число в диапазоне [from; to]
// используется для генерации характеристик оружия
int randint(int from, int to) {
    int num = to - from + 1;
    return std::rand() % num + from;
}

// перечисления редкостей и типов оружия
enum Rarity { COMMON, RARE, EPIC, LEGENDARY };
enum WeaponType { SPEAR, SWORD, BOW };

// редкость и типы оружия на русском языке
std::string weaponNames[] = {"Копье", "Меч", "Лук"};
std::string rarityNames[] = {"Обычное", "Редкое", "Эпическое", "Легендарное"};

void print_weapon_info(int weaponNum, int weaponType, int rarity) {
    std::cout << weaponNum++ << " - " << weaponNames[weaponType] << ", редкость: " << rarityNames[rarity] << std::endl;
}

/*
Разброс характеристик для копья:
                 Обыч.  Редк.   Эпич.   Лег. 
    damage:      1-4    5-10    11-18   19-30
    durability:  3-5    6-9     10-15   16-20
    attackSpeed: 1-3    4-7     8-11    12-15
*/ 
class Spear {

    public:
        int damage, durability, attackSpeed;
        Rarity rarity;

        // Генерируем характеристики оружия в зависимости от редкости r
        Spear(Rarity r) {
            rarity = r;
            switch (r) {
                case COMMON: {
                    damage = randint(1, 4);
                    durability = randint(3, 5);
                    attackSpeed = randint(1, 3);
                    break;
                }
                case RARE: {
                    damage = randint(5, 10);
                    durability = randint(6, 9);
                    attackSpeed = randint(4, 7);
                    break;
                }
                case EPIC: {
                    damage = randint(11, 18);
                    durability = randint(10, 15);
                    attackSpeed = randint(8, 11);
                    break;
                }
                case LEGENDARY: {
                    damage = randint(19, 30);
                    durability = randint(3, 5);
                    attackSpeed = randint(12, 15);
                    break;
                }
            }
        }
};

/*
Разброс характеристик для меча:
                 Обыч.  Редк.   Эпич.   Лег. 
    damage:      3-6    7-13    14-23   24-37
    durability:  1-3    4-7     8-11    12-15
    attackSpeed: 2-4    5-8     9-13    14-17
*/
class Sword {

    public:
        int damage, durability, attackSpeed;
        Rarity rarity;

        // Генерируем характеристики оружия в зависимости от редкости
        Sword(Rarity r) {
            rarity = r;
            switch (r) {
                case COMMON: {
                    damage = randint(3, 6);
                    durability = randint(1, 3);
                    attackSpeed = randint(2, 4);
                    break;
                }
                case RARE: {
                    damage = randint(7, 13);
                    durability = randint(4, 7);
                    attackSpeed = randint(5, 8);
                    break;
                }
                case EPIC: {
                    damage = randint(14, 23);
                    durability = randint(8, 11);
                    attackSpeed = randint(9, 13);
                    break;
                }
                case LEGENDARY: {
                    damage = randint(24, 37);
                    durability = randint(12, 15);
                    attackSpeed = randint(14, 17);
                    break;
                }
            }
        }
};

/*
Разброс характеристик для лука:
                 Обыч.  Редк.   Эпич.   Лег. 
    damage:      2-5    6-11    12-21   22-33
    durability:  2-4    6-8     9-13    14-17
    attackSpeed: 1-3    4-7     8-12    13-16
*/
class Bow {
    public:
        int damage, durability, attackSpeed;
        Rarity rarity;

        // Генерируем характеристики оружия в зависимости от редкости
        Bow(Rarity r) {
            rarity = r;
            switch (r) {
                case COMMON: {
                    damage = randint(2, 5);
                    durability = randint(2, 4);
                    attackSpeed = randint(1, 3);
                    break;
                }
                case RARE: {
                    damage = randint(6, 11);
                    durability = randint(6, 8);
                    attackSpeed = randint(4, 7);
                    break;
                }
                case EPIC: {
                    damage = randint(12, 21);
                    durability = randint(9, 13);
                    attackSpeed = randint(8, 12);
                    break;
                }
                case LEGENDARY: {
                    damage = randint(22, 33);
                    durability = randint(14, 17);
                    attackSpeed = randint(13, 16);
                    break;
                }
            }
        }
};


// Weapon - класс оружия
// weapon - указатель на оружие
// type - тип оружия
class Weapon {
    public:
        void* weapon;
        WeaponType type;
        
        // заполняем weapon оружием нужного типа и редкости
        Weapon(WeaponType type, Rarity rarity) {
            this->type = type;
            switch (type) {
                case SPEAR: {
                    Spear* s = new Spear(rarity);
                    weapon = s;
                    break;
                }
                case SWORD: {
                    Sword* s = new Sword(rarity);
                    weapon = s;
                    break;
                }
                case BOW: {
                    Bow* s = new Bow(rarity);
                    weapon = s;
                    break;
                }
            }
        }
};

// Класс магазина
// weaponRange - массив всех оружий в магазине
class Store {
    std::vector<Weapon> weaponRange;

    public:
        // генерируем от 1 до 4 оружий каждого типа и редкости
        Store() {
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 4; j++) {
                    for (int k = 0; k < randint(1, 4); k++) {
                        Weapon w(static_cast<WeaponType>(j), static_cast<Rarity>(i));
                        weaponRange.push_back(w);
                    }
                }
            }
        }

        // метод посещения магазина
        void visit() {
            // получаем достаток посетителя
            // посетитель вводит подходящий номер 
            // этому номеру сопоставляется максимально доступная для него редкость оружия
            std::cout << "Выберите ваш достаток:" << std::endl;
            std::cout << "1 - бедный\n2 - средний\n3 - выше среднего\n4 - богатый" << std::endl;
            int wealth;
            std::cin >> wealth;
            Rarity rarity  = static_cast<Rarity>(--wealth);
            
            // получаем тип оружия
            // посетитель вводит подходящий номер 
            std::cout << "Тип оружия:" << std::endl;
            std::cout << "1 - копье\n2 - меч\n3 - лук" << std::endl;
            int weapon;
            std::cin >> weapon;
            WeaponType weaponType = static_cast<WeaponType>(--weapon);
            
            // находим всё оружие, подходящее ему по достатку и с нужным типом
            // выводим тип оружия, его редкость и его номер
            // в вектор fitting собираем характеристики подходящего оружия
            std::cout << "Введите номер оружия, чтобы узнать о нем подробнее. Введите 0, чтобы выйти." << std::endl;
            int num = 1;
            std::string out;
            std::vector<std::vector<int>> fitting;
            for (Weapon w : weaponRange) {
                if (w.type == weaponType) {
                    switch (w.type) {
                        case SPEAR: {
                            Spear* s = static_cast<Spear*>(w.weapon);
                            if (s->rarity <= rarity) {
                                print_weapon_info(num++, weapon, s->rarity);
                                std::vector<int> v{s->damage, s->durability, s->attackSpeed, s->rarity};
                                fitting.push_back(v);
                            }
                            break;
                        }
                        case SWORD: {
                            Sword* s = static_cast<Sword*>(w.weapon);
                            if (s->rarity <= rarity) {
                                print_weapon_info(num++, weapon, s->rarity);
                                std::vector<int> v{s->damage, s->durability, s->attackSpeed, s->rarity};
                                fitting.push_back(v);
                            }
                            break;
                        }
                        case BOW: {
                            Bow* s = static_cast<Bow*>(w.weapon);
                            if (s->rarity <= rarity) {
                                print_weapon_info(num++, weapon, s->rarity);
                                std::vector<int> v{s->damage, s->durability, s->attackSpeed, s->rarity};
                                fitting.push_back(v);
                            }
                            break;
                        }
                    }
                }
            }

            // пользователь вводит номер нужного оружия
            // выводится информация о характеристиках этого оружия
            // пользователь может дальше вводить номера оружия и смотреть информацию о нем
            // чтобы закончить просмотр, пользователь вводит 0
            std::cin >> num;
            while (num != 0) {
                num--;
                std::cout << "У этого оружия урон " << fitting[num][0] << ", прочность " 
                                                    << fitting[num][1] << ", скорость атаки " 
                                                    << fitting[num][2] << ", редкость "
                                                    << rarityNames[fitting[num][3]] << std::endl; 
                std::cin >> num;
            }
        }
};


int main() {
    std::srand(std::time(0));
    Store store;
    store.visit();
}