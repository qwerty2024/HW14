#include "TrieNode.h"

#include <iostream>

using namespace std;

// Возвращет новый узел с пустыми детьми
TrieNode* getNewNode(void)
{
    // Выделяем память по новый узел
    struct TrieNode* pNode = new TrieNode;

    // устанавливаем флаг конца слова в false
    pNode->isEndOfWord = false;

    // инициализируем детей нулевым уазателем
    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = nullptr;

    return pNode;
}


// Вставляет ключ в дерево, если его нет, 
// иначе если ключ явлется префксом узла дерева 
// помечает в качестве лиcтового, т.е. конец слова
void insert(TrieNode* root, string key)
{
    TrieNode* node = root;

    for (int i = 0; i < key.length(); i++)
    {
        // вычисляем индекс в алфавите через смещение относительно первой буквы
        int index = key[i] - 'a';

        // если указатель пустой, т.е. детей с таким префиксом нет
        // создаем новый узел
        if (!node->children[index])
            node->children[index] = getNewNode();

        node = node->children[index];
    }

    // помечаем последний узел как лист, т.е. конец слова
    node->isEndOfWord = true;
}

// поиск узла, которым заканчивается введенноее слово
TrieNode* search_branch(struct TrieNode* root, string key)
{
    struct TrieNode* node = root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!node->children[index])
            return nullptr;

        node = node->children[index];
    }

    return node;
}

// поиск и вывод окончаний слов
void search_word(TrieNode* node, const uint32_t count, uint32_t *count_current, string *res, bool* nawli)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (node->children[i] != nullptr)
        {
            if (*nawli) break; 
            *res += (char)(97 + i);
            
            if (node->children[i]->isEndOfWord)
            {
                if (count == *count_current) // нашли нужное слово по количеству нажатий стреок вправо\влево
                {
                    for (size_t j = 0; j < MAX_LENGHT_WORD; ++j) cout << " "; // зачищаем старый хвост
                    for (size_t j = 0; j < MAX_LENGHT_WORD; ++j) cout << "\b"; // перевод каретки назад на начало перед зачистки
                    
                    cout << *res; 
                    
                    for (size_t j = 0; j < res->size(); ++j) cout << "\b"; // перевод каретки под новое слово
                    
                    // сигнал в рекурсию, что нашли нужный конец
                    *nawli = true;
                    return;
                }

                *count_current += 1;
                search_word(node->children[i], count, count_current, res, nawli);
                res->pop_back(); // подчищаем хвост ветки, если зашли нетуда
            }
            else
            {
                search_word(node->children[i], count, count_current, res, nawli);
                res->pop_back(); // подчищаем хвост ветки, если зашли нетуда
            }
        }
    }
}

// подсчет слов в поддереве по количеству окончаний
void count_words(TrieNode *node, uint32_t &count)
{
    if (!node) return;

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (node->children[i] != nullptr)
        {
            if (node->children[i]->isEndOfWord) count++;

            count_words(node->children[i], count);
        }
    }
}


