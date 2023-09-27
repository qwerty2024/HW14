#ifndef TRIE_H
#define TRIE_H

#include <string>

#define MAX_LENGHT_WORD 30

using namespace std;

const int ALPHABET_SIZE = 26;

// Структура узела дерева 
struct TrieNode
{
    struct TrieNode* children[ALPHABET_SIZE];
    // isEndOfWord - true, если ключ является концом слова
    bool isEndOfWord;
};

TrieNode* getNewNode(void);
void insert(TrieNode*, string);
TrieNode* search_branch(TrieNode*, string);
void search_word(TrieNode*, const uint32_t, uint32_t *, string *, bool *);
void count_words(TrieNode*, uint32_t&);

#endif