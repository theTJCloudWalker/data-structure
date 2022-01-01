#pragma once
#include<vector>
#include<string>

class TrieNode {
public:
    friend class Trie;
    TrieNode() {
        word = 1;
    }
    TrieNode(const char data) {
        word = data;
        wordsCount = 0;
    }
    ~TrieNode() {

    }
    int Search(const char data) {
        for (int i = 0; i < next.size(); i++) {
            if (next[i]->word == data) {
                return i;
            }
        }
        return -1;//search failed
    }
    void SetAsEnd() {
        wordsCount++;
        return;
    }
    char word;
    int wordsCount = 0;
    std::vector<TrieNode*>next;
};

class Trie {
public:
    Trie() {
        root = new TrieNode();
        root->word = '#';
        root->wordsCount = 0;
    }
    ~Trie() {
        delete root;
    }
    void Insert(std::string words);
    void Delete(std::string words);
    int Search(std::string words);
   
private:
    TrieNode* root;
};

int Trie::Search(std::string words) {
    TrieNode* current = root;
    if (current->next.size() == 0) {
        return 0;
    }//非空
    int pos = -1;
    for (int i = 0; i < words.length(); i++) {
        pos = current->Search(words[i]);
        if (-1 == pos) {
            return 0;//search failed 
        }
        else if (i != words.length() - 1) {
            current = current->next[pos];
        }
    }
    return current->next[pos]->wordsCount;
};

void Trie::Insert(std::string words) {
    TrieNode* current = root;
    int pos = -1;
    for (int i = 0; i < words.length(); i++) {
        pos = current->Search(words[i]);
        //未找到需要的path节点
        if (-1 == pos) {
            TrieNode* newNode = new TrieNode(words[i]);
            current->next.push_back(newNode);
            pos = current->Search(words[i]);//获取新node的位置
        }
        if (pos != -1) {
            current = current->next[pos];//调整到新的node
        }
    }
    current->wordsCount++;
    return ;
}

void Trie::Delete(std::string words) {

}

