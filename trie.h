#pragma once
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

struct trienode
{
	std::unordered_map<char, trienode*> children;
	bool endOfWord;
};

class trie
{
private:
	trienode* root;

	void insertRecursive(trienode*, std::string, int);
	bool searchRecursive(trienode*, std::string, int);
	bool delNode(trienode*, std::string, int);

public:
	trie();
	void insert(std::string);
	void insertRecursive(std::string);
	bool search(std::string);
	bool searchRecursive(std::string);
	void deleteNode(std::string);
};
