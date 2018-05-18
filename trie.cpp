#include "trie.h"

trie::trie()
{
	root = new trienode();
}

void trie::insert(std::string word)
{
	if (word.size() == 0)
	{ 
		return;
	}

	trienode* current = root;

	for (int i = 0; i < word.size(); ++i)
	{
		char c = word[i];
		trienode* node = current->children[c];

		if (node == NULL)
		{
			node = new trienode();
			std::pair<char, trienode*> p(c, node);
			current->children.insert(p);
		}

		current = node;
	}

	current->endOfWord = true;
}

void trie::insertRecursive(std::string word)
{
	return insertRecursive(root, word, 0);
}

void trie::insertRecursive(trienode* current, std::string word, int index)
{
	if (index == word.size())
	{
		current->endOfWord = true;
		return;
	}

	char c = word[index];
	trienode* node = current->children[c];

	if (node == NULL)
	{
		node = new trienode();
		current->children.insert(std::make_pair(c, node));
	}

	insertRecursive(node, word, index + 1);
}

bool trie::search(std::string word)
{
	if (word.size() == 0)
	{
		return false;
	}

	trienode* current = root;

	for (int i = 0; i < word.size(); ++i)
	{
		char c = word[i];
		trienode* node = current->children[c];
		if (node == NULL)
		{
			return false;
		}

		current = node;
	}

	return current->endOfWord;
}

bool trie::searchRecursive(std::string word)
{
	return searchRecursive(root, word, 0);
}

bool trie::searchRecursive(trienode* current, std::string word, int index)
{
	if (index == word.size())
	{
		return current->endOfWord;
	}

	char c = word[index];
	trienode* node = current->children.find(c)->second;
	if (node == NULL)
	{
		return false;
	}

	return searchRecursive(node, word, index + 1);
}

void trie::deleteNode(std::string word)
{
	delNode(root, word, 0);
}

bool trie::delNode(trienode* current, std::string word, int index)
{
	if (index == word.size())
	{
		if (!current->endOfWord)
		{
			return false;
		}

		current->endOfWord = false;
		return current->children.size() == 0;
	}

	char c = word[index];
	trienode* node = current->children.find(c)->second;
	if (node == NULL)
	{
		return false;
	}

	bool deleteCurrentNode = delNode(node, word, index + 1);

	if (deleteCurrentNode)
	{
		current->endOfWord = false;
		return current->children.size() == 0;
	}

	return false;
}
