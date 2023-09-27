#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <sstream>
#include <conio.h>

#include <TrieNode.h>

#define DICTIONARY "qwerty qwe qwertyu qwertyuiop milk milkiway four fortuna formula formulirovka give given gigabyte"

using namespace std;

int main()
{
    string dictionary = DICTIONARY;
    istringstream iss(dictionary);
    TrieNode* tree = getNewNode(); // дерево в котором будем хранить все ключи

    cout << "Hello! (This dictionary only supports lowercase letters)\n"
        << "Interface:\n"
        << "Press ESC - to quit\n"
        << "Press UP - enter new word\n"
        << "Press DOWN - insert word in tree\n"
        << "Press RIGHT - next word\n"
        << "Press LEFT - prev word\n\n";

    cout << "Current dictionary:\n" << DICTIONARY << endl;

    while (iss) // заполнили дерево ключами
    {
        string tmp;
        iss >> tmp;
        insert(tree, tmp);
    }

    bool go_exit = false; // флаг для эскейпа
    while (1) // повтор нового слова
    {
        string key = ""; // строка ввода символов
        TrieNode* node = nullptr; // рабочий узел
        uint32_t count = 0; // счетчик нажатий стрелки влево\вправо
        uint16_t flag = 666; // если сменили направление, то нужно сделать дополнительное вычитание\сложение

        cout << "\nEnter word or part: ";
        while (1) // введение слова или функциональной кнопки
        {
            int sym = _getch();
            string res = "";
            
            if (sym == 75) //cout << "LEFT\n";
            {
                if (flag == 1) count--;
                flag = 0;

                node = search_branch(tree, key); // нашли корень ветки
                if (node != nullptr)
                {
                    uint32_t current_count = 0;
                    bool nawli = false;// флаг, если нашли слово, то закрываем рекурсию
                    
                    if (count == 0) count = 1; // не выходем влево
                    count--;
                    search_word(node, count, &current_count, &res, &nawli);
                }
                else cout << "No words!";
            }

            if (sym == 77) //cout << "RIGHT\n";
            {
                if (flag == 0) count++;
                flag = 1;

                node = search_branch(tree, key); // нашли корень ветки

                uint32_t max_words = 0; // для ограничения нажатий вправо
                count_words(node, max_words);

                if (node != nullptr)
                {
                    uint32_t current_count = 0;
                    bool nawli = false; // флаг, если нашли слово, то закрываем рекурсию
                    search_word(node, count, &current_count, &res, &nawli);

                    // счетчик ++
                    count++;
                    if (count > max_words) count = max_words; // не уходим вправо
                }
                else cout << "No words!";  
            }

            if (sym == 72) //cout << "UP\n"; 
            { 
                // начать вводить новое слово
                break;   
            }

            if (sym == 80) //cout << "DOWN\n";
            {
                // добавить слово в дерево (не сохраняет от запуска к запуску)
                insert(tree, key);
                cout << " <- Added!";
                break;   
            }
            
            if (sym == 27) //cout << "ESC\n";
            {
                go_exit = true;
                break;
            }

            if (sym > 96  && sym < 123)
            {
                key += (char)sym;
                cout << (char)sym;
            }
        }

        if (go_exit)
        {
            break;
        }
    }

    return 0;
}

