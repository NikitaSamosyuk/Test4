#include <iostream>
#include <conio.h>
#include <algorithm>
#include <windows.h>
#include <string>
#include <fstream>

using namespace std;

struct Node {
    string facultet;
    int auditor;
    int corpus;
    int students;
    int floor;
    string dekan;
    Node* next;
    Node* prev;
};

Node* head = NULL;
Node* tail = NULL;

void MakeSpisok() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(0, "ru");

    cout << endl << "Новый факультет: " << endl;

    Node* newNode = new Node;

    cout << "Введите название факультета: ";
    cin >> newNode->facultet;

    cout << "Введите номер аудитории: ";
    cin >> newNode->auditor;

    cout << "Введите этаж: ";
    cin >> newNode->floor;

    cout << "Введите номер корпуса: ";
    cin >> newNode->corpus;

    cout << "Введите количество студентов: ";
    cin >> newNode->students;

    cout << "Введите ФИО Декана: ";
    cin >> newNode->dekan;

    newNode->next = NULL;
    newNode->prev = tail;

    if (head == NULL) {
        head = newNode;
        tail = newNode;
    }
    else {
        tail->next = newNode;
        tail = newNode;
    }
}

void AddFacultetStart() {
    cout << endl << "Новый факультет: " << endl;
    Node* newNode = new Node;

    cout << "Введите название факультета: ";
    cin >> newNode->facultet;

    cout << "Введите номер аудитории: ";
    cin >> newNode->auditor;

    cout << "Введите этаж: ";
    cin >> newNode->floor;

    cout << "Введите номер корпуса: ";
    cin >> newNode->corpus;

    cout << "Введите количество студентов: ";
    cin >> newNode->students;

    cout << "Введите ФИО Декана: ";
    cin >> newNode->dekan;

    newNode->next = head;
    newNode->prev = NULL;

    if (head != NULL) {
        head->prev = newNode;
    }
    head = newNode;

    if (tail == NULL) {
        tail = newNode;
    }
}

void AddFacultetEnd() {
    Node* newNode = new Node;
    
    cout << endl << "Новый факультет: " << endl;

    cout << "Введите название факультета: ";
    cin >> newNode->facultet;

    cout << "Введите номер аудитории: ";
    cin >> newNode->auditor;

    cout << "Введите этаж: ";
    cin >> newNode->floor;

    cout << "Введите номер корпуса: ";
    cin >> newNode->corpus;

    cout << "Введите количество студентов: ";
    cin >> newNode->students;

    cout << "Введите ФИО Декана: ";
    cin >> newNode->dekan;

    newNode->next = NULL;
    newNode->prev = tail;

    if (tail != NULL) {
        tail->next = newNode;
    }
    tail = newNode;

    if (head == NULL) {
        head = newNode;
    }
}

void AddFacultetAfter() {
    string targetFacultet;
    cout << "Введите название факультета, после которого вы хотите добавить свой факультет: ";
    cin >> targetFacultet;

    Node* targetNode = head;
    while (targetNode != NULL && targetNode->facultet != targetFacultet) {
        targetNode = targetNode->next;
    }

    if (targetNode == NULL) {
        cout << "Факультет: " << targetFacultet << " не найден" << endl;
        return;
    }
    Node* newNode = new Node;

    cout << endl << "Новый факультет: " << endl;

    cout << "Введите название нового факультета: ";
    cin >> newNode->facultet;

    cout << "Введите номер аудитории: ";
    cin >> newNode->auditor;

    cout << "Введите этаж: ";
    cin >> newNode->floor;

    cout << "Введите номер корпуса: ";
    cin >> newNode->corpus;

    cout << "Введите количество студентов: ";
    cin >> newNode->students;

    cout << "Введите ФИО Декана: ";
    cin >> newNode->dekan;

    newNode->next = targetNode->next;
    newNode->prev = targetNode;

    if (targetNode->next != NULL) {
        targetNode->next->prev = newNode;
    }
    targetNode->next = newNode;

    if (tail == targetNode) {
        tail = newNode;
    }
}

void AddFacultetBefore() {
    string targetFacultet;
    cout << "Введите название факультета, перед которым вы хотите добавить новый: ";
    cin >> targetFacultet;

    Node* targetNode = head;
    while (targetNode != NULL && targetNode->facultet != targetFacultet) {
        targetNode = targetNode->next;
    }

    if (targetNode == NULL) {
        cout << "Факультет " << targetFacultet << " Не найден" << endl;
        return;
    }

    Node* newNode = new Node;

    cout << endl << "Новый факультет: " << endl;

    cout << "Введите название нового факультета: ";
    cin >> newNode->facultet;

    cout << "Введите номер аудитории: ";
    cin >> newNode->auditor;

    cout << "Введите этаж: ";
    cin >> newNode->floor;

    cout << "Введите номер корпуса: ";
    cin >> newNode->corpus;

    cout << "Введите количество студентов: ";
    cin >> newNode->students;

    cout << "Введите ФИО Декана: ";
    cin >> newNode->dekan;

    newNode->next = targetNode;
    newNode->prev = targetNode->prev;

    if (targetNode->prev != NULL) {
        targetNode->prev->next = newNode;
    }
    targetNode->prev = newNode;

    if (head == targetNode) {
        head = newNode;
    }
}

void DelFacultet() {
    string targetFacultet;
    cout << "Введите название факультета, который вы хотите удалить: ";
    cin >> targetFacultet;

    Node* targetNode = head;
    while (targetNode != NULL && targetNode->facultet != targetFacultet) {
        targetNode = targetNode->next;
    }

    if (targetNode == NULL) {
        cout << "Факультет " << targetFacultet << " Не найден." << endl;
        return;
    }

    if (targetNode->prev != NULL) {
        targetNode->prev->next = targetNode->next;
    }
    else {
        head = targetNode->next;
    }

    if (targetNode->next != NULL) {
        targetNode->next->prev = targetNode->prev;
    }
    else {
        tail = targetNode->prev;
    }

    delete targetNode;
    cout << "Факультет " << targetFacultet << " Удален " << endl;
}

void SaveToFile(const string& filename)
{
    ofstream outFile(filename);

    if (!outFile) {
        cout << "Ошибка при открытии файла для записи " << endl;
        return;
    }

    Node* current = head;
    while (current != NULL) {
        // Записываем данные узла в файл
        outFile << current->facultet << " "
            << current->auditor << " "
            << current->floor << " "
            << current->corpus << " "
            << current->students << " "
            << current->dekan << endl;
        current = current->next;
    }

    outFile.close();
    cout << "Данные успешно сохранены "<< endl;
}

void LoadFromFile(const string& filename) {
    ifstream file(filename);

    if (!file) {
        cout << "Не удалось открыть файл" << endl;
        return;
    }

    Node* newNode = new Node;
    while (file >> newNode->facultet) {
        file >> newNode->auditor;
        file >> newNode->floor;
        file >> newNode->corpus;
        file >> newNode->students;
        file >> newNode->dekan;

        newNode->next = NULL;
        newNode->prev = tail;

        if (head == NULL) {
            head = newNode;
            tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }

        newNode = new Node;
    }

    delete newNode;
    file.close();
    cout << "Данные успешно загружены" << endl;
}


void SearchFacultet() {
    int targetFloor, targetCorpus;
    cout << "Введите номер корпуса: ";
    cin >> targetCorpus;
    cout << "Введите номер этажа: ";
    cin >> targetFloor;

    Node* temp = head;
    bool found = false;
    while (temp != NULL) {
        if (temp->corpus == targetCorpus && temp->floor == targetFloor) {
            cout << "Факультет: " << temp->facultet << ", Аудитория: " << temp->auditor << ", Этаж: " << temp->floor << ", Номер корпуса : " << temp->corpus << ", Количество студентов : " << temp->students << ", ФИО Декана : " << temp->dekan << endl;
            found = true;
        }
        temp = temp->next;
    }

    if (!found) {
        cout << "Не найдено факультетов, расположенных в корпусе: " << targetCorpus << ", на этаже: " << targetFloor << "." << endl;
    }
}

void SumStudent() {
    Node* temp = head;
    int totalStudents = 0;
    while (temp != NULL) {
        totalStudents += temp->students;
        temp = temp->next;
    }

    cout << "Общее количество студентов со всех факультетов: " << totalStudents << endl;
}

void MinFacultet() {
    if (head == NULL) {
        cout << "Список факультетов пуст " << endl;
        return;
    }

    Node* temp = head;
    Node* minFacultet = head;
    while (temp != NULL) {
        if (temp->students < minFacultet->students) {
            minFacultet = temp;
        }
        temp = temp->next;
    }

    cout << "Факультет с наименьшим количеством студентов: " << minFacultet->facultet << ", Аудитория: " << minFacultet->auditor << ", Этаж: " << minFacultet->floor << ", Номер корпуса: " << minFacultet->corpus << ", Количество студентов: " << minFacultet->students << ", ФИО Декана: " << minFacultet->dekan << endl;
}

void MaxFacultet() {
    if (head == NULL) {
        cout << "Список факультетов пуст " << endl;
        return;
    }

    Node* temp = head;
    Node* maxFacultet = head;
    while (temp != NULL) {
        if (temp->students > maxFacultet->students) {
            maxFacultet = temp;
        }
        temp = temp->next;
    }

    cout << "Факультет с наибольшим количеством студентов: " << maxFacultet->facultet << ", Аудитория: " << maxFacultet->auditor << ", Этаж: " << maxFacultet->floor << ", Номер корпуса: " << maxFacultet->corpus << ", Количество студентов: " << maxFacultet->students << ", ФИО Декана: " << maxFacultet->dekan << endl;
}


void ViewSpisok() {
    setlocale(0, "ru");
    cout << endl;
    Node* temp = head;
    while (temp != NULL) {
        cout << "Факультет: " << temp->facultet << ", Аудитория: " << temp->auditor << ", Этаж: " << temp->floor << ", Номер корпуса : " << temp->corpus << ", Количество студентов : " << temp->students << ", ФИО Декана : " << temp->dekan << endl;
        temp = temp->next;
    }
    cout << endl << "=======================================================================================================================" << endl;
}

int Spisok() {
    setlocale(0, "ru");
    int numfacultets;
    cout << "Сколько факультетов вы хотите добавить? ";
    cin >> numfacultets;

    for (int i = 0; i < numfacultets; ++i) {
        MakeSpisok();
    }


    return 0;
}

int main()
{
    setlocale(0, "ru");
    goto menu;

menu:
    while (true) {
        cout << endl << "                                  ============================================" << endl;
        cout << "                                  |                                          |" << endl;
        cout << "                                  |                   МЕНЮ                   |" << endl;
        cout << "                                  |                                          |" << endl;
        cout << "                                  ============================================" << endl << endl;

        cout << "=======================================================================================================================" << endl << endl;
        cout << " вид операции:       1 - создать список                                                                     " << endl;
        cout << "                     2 - выбор действия над факультетами                                                " << endl;
        cout << "                     3 - работа с файлами                                                                   " << endl;
        cout << "                     4 - виды запросов                                                                      " << endl;
        cout << "                     5 - просмотр списка                                                                    " << endl;
        cout << "                     6 - выход                                                                              " << endl;
        cout << "                                                                                                            " << endl << endl;
        cout << "=======================================================================================================================" << endl;

        while (1)
        {
            switch (_getch())
            {
            case '1':
            {
                Spisok();
                goto menu;
                break;
            }
            case '2':
            {
                goto menu1;
                goto menu;
                break;
               
            }
            case '3': 
            {
                goto menu2;
                goto menu;
                break;
            }
            case '4':
            {
                goto menu3;
                goto menu;
                break;
            }
            case '5': ViewSpisok(); break;
            case '6': return 0;
            default: printf("Ошибка, повторите \n");
            }  
          }
        }
menu1:
    while (1)
    {
            cout << "=======================================================================================================================" << endl << endl;
            cout << "выбор действия:           1 - добавить факультет в начало списка" << endl;
            cout << "                          2 - добавить факультет в конец списка " << endl;
            cout << "                          3 - добавление факультета после определенного факультета" << endl;
            cout << "                          4 - добавление факультета перед определенным факультетом" << endl;
            cout << "                          5 - удаление выбранного факультета" << endl;
            cout << "                          6 - назад" << endl << endl;
            cout << "=======================================================================================================================" << endl;

            switch (_getch())
            {
            case '1':
            {
                AddFacultetStart();
                goto menu1;
                break;
            }
            case '2':
            {
                AddFacultetEnd();
                goto menu1;
                break;

            }
            case '3':
            {
                AddFacultetAfter();
                goto menu1;
                break;
            }
            case '4':
            {
                AddFacultetBefore();
                goto menu1;
                break;
            }
            case '5':
            {
                DelFacultet();
                goto menu1;
                break;
            }
            case '6': 
            {
                goto menu;
                break;
            }
            default: printf("Ошибка, повторите \n");
            }
            
            return 0;
        }
menu2:
    while (1)
    {
        cout << "=======================================================================================================================" << endl << endl;
        cout << " выбор действиий:       7 - сохранение данных списка факультетов в бинарный файл" << endl;
        cout << "                        8 - извлечение данных из бинарного файла и помещение новых факультетов в список" << endl;
        cout << "                        9 - назад" << endl << endl;
        cout << "=======================================================================================================================" << endl;
        switch (_getch())
        {
        case '7':
        {
            SaveToFile("spisok.bin");
            goto menu2;
            break;
        }
        case '8':
        {
            LoadFromFile("spisok.bin");
            goto menu2;
            break;
        }
        case '9':
        {
            goto menu;
            break;
        }
        default: printf("Ошибка, повторите \n");
        }
    }
podmenu3:
    while (1)
    {
        cout << "=======================================================================================================================" << endl << endl;
        cout << " выбор действиий:       1 - Сведения о факультете с наименьшим количеством студентов " << endl;
        cout << "                        2 - Сведения о факультете с наибольшим количеством студентов " << endl;
        cout << "                        3 - Сведения о факультах с наименьшим и наибольшим количеством студентов " << endl;
        cout << "                        4 - Назад " << endl;
        cout << "                        5 - Вернуться в главное меню " << endl << endl;
        cout << "=======================================================================================================================" << endl;
        switch (_getch())
        {
        case '1':
        {
            MinFacultet();
            goto podmenu3;
            break;
        }
        {
        case '2':
        {
            MaxFacultet();
            goto podmenu3;
            break;
        }
        case '3':
        {
            MinFacultet();
            MaxFacultet();
            goto podmenu3;
            break;
        }
        case '4':
        {
            goto menu3;
            break;
        }
        case '5':
        {
            goto menu;
            break;
        }
        default: printf("Ошибка, повторите \n");
        }
        }
    }
menu3:
    while (1)
    {
        cout << "=======================================================================================================================" << endl << endl;
        cout << " выбор действиий:       1 - выдаются сведения о факультетах, расположенных в N-ном корпусе на N-ном этаже " << endl;
        cout << "                        2 - рассчитывается общее количество студентов со всех факультетов " << endl;
        cout << "                        3 - выдаются сведения о факультете с наименьшим и наибольшим количеством студентов " << endl;
        cout << "                        4 - назад" << endl << endl;
        cout << "=======================================================================================================================" << endl; 
        switch (_getch())
        {
        case '1':
        {
            SearchFacultet();
            goto menu3;
            break;
        }
        case '2':
        {
            SumStudent();
            goto menu3;
            break;
        }
        case '3':
        {
            goto podmenu3;
            goto menu3;
            break;
        }
        case '4':
        {
            goto menu;
            break;
        }
        default: printf("Ошибка, повторите \n");
        }
    }

}





