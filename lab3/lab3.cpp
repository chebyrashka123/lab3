#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

// Базовый класс
class Publication {
protected:
    string title;
    string publisher;
    int year;

public:
    Publication(const string& t = "", const string& p = "", int y = 0)
        : title(t), publisher(p), year(y) {
    }

    virtual ~Publication() {}

    virtual void show() const = 0;   // чистый виртуальный метод
};

// Производный класс Book
class Book : public Publication {
private:
    string author;
    int pages;

public:
    Book(const string& a, const string& t, const string& p, int y, int pg)
        : Publication(t, p, y), author(a), pages(pg) {
    }

    int getAge() const {
        time_t now = time(nullptr);
        return (localtime(&now)->tm_year + 1900) - year;
    }

    void show() const override {
        cout << "Книга: \"" << title << "\", автор " << author
            << ", изд. " << publisher << ", " << year << " г., "
            << pages << " стр., возраст " << getAge() << " лет\n";
    }
};

// Второй производный класс Newspaper
class Newspaper : public Publication {
private:
    int issueNumber;     // номер выпуска
    string editor;       // редактор

public:
    Newspaper(const string& t, const string& p, int y, int issue, const string& ed)
        : Publication(t, p, y), issueNumber(issue), editor(ed) {
    }

    void show() const override {
        cout << "Газета: \"" << title << "\", " << publisher << ", " << year
            << ", выпуск №" << issueNumber << ", редактор: " << editor << endl;
    }
};

int main() {
    system("chcp 1251 > nul");
    // Массив указателей на базовый класс
    const int SIZE = 6;
    Publication* arr[SIZE];

    // Заполняем объектами Book и Newspaper
    arr[0] = new Book("Оруэлл", "1984", "Секкер", 1949, 328);
    arr[1] = new Book("Толкин", "Хоббит", "Аллен", 1937, 310);
    arr[2] = new Book("Роулинг", "Гарри Поттер", "Блумсбери", 1997, 223);

    arr[3] = new Newspaper("Правда", "Изд. Правда", 1985, 120, "Иванов");
    arr[4] = new Newspaper("Известия", "Известия", 1990, 45, "Петрова");
    arr[5] = new Newspaper("Коммерсантъ", "Коммерсант", 2000, 78, "Сидоров");

    // Вызов show() для каждого – полиморфизм
    cout << "=== Содержимое массива Publication ===\n";
    for (int i = 0; i < SIZE; ++i) {
        arr[i]->show();
    }

    // Освобождение памяти
    for (int i = 0; i < SIZE; ++i) {
        delete arr[i];
    }

    return 0;
}