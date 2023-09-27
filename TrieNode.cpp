#include "TrieNode.h"

#include <iostream>

using namespace std;

// ��������� ����� ���� � ������� ������
TrieNode* getNewNode(void)
{
    // �������� ������ �� ����� ����
    struct TrieNode* pNode = new TrieNode;

    // ������������� ���� ����� ����� � false
    pNode->isEndOfWord = false;

    // �������������� ����� ������� ���������
    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = nullptr;

    return pNode;
}


// ��������� ���� � ������, ���� ��� ���, 
// ����� ���� ���� ������� �������� ���� ������ 
// �������� � �������� ��c������, �.�. ����� �����
void insert(TrieNode* root, string key)
{
    TrieNode* node = root;

    for (int i = 0; i < key.length(); i++)
    {
        // ��������� ������ � �������� ����� �������� ������������ ������ �����
        int index = key[i] - 'a';

        // ���� ��������� ������, �.�. ����� � ����� ��������� ���
        // ������� ����� ����
        if (!node->children[index])
            node->children[index] = getNewNode();

        node = node->children[index];
    }

    // �������� ��������� ���� ��� ����, �.�. ����� �����
    node->isEndOfWord = true;
}

// ����� ����, ������� ������������� ���������� �����
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

// ����� � ����� ��������� ����
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
                if (count == *count_current) // ����� ������ ����� �� ���������� ������� ������ ������\�����
                {
                    for (size_t j = 0; j < MAX_LENGHT_WORD; ++j) cout << " "; // �������� ������ �����
                    for (size_t j = 0; j < MAX_LENGHT_WORD; ++j) cout << "\b"; // ������� ������� ����� �� ������ ����� ��������
                    
                    cout << *res; 
                    
                    for (size_t j = 0; j < res->size(); ++j) cout << "\b"; // ������� ������� ��� ����� �����
                    
                    // ������ � ��������, ��� ����� ������ �����
                    *nawli = true;
                    return;
                }

                *count_current += 1;
                search_word(node->children[i], count, count_current, res, nawli);
                res->pop_back(); // ��������� ����� �����, ���� ����� ������
            }
            else
            {
                search_word(node->children[i], count, count_current, res, nawli);
                res->pop_back(); // ��������� ����� �����, ���� ����� ������
            }
        }
    }
}

// ������� ���� � ��������� �� ���������� ���������
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


