#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Source.h"

struct list {
	int line;
	struct list* next;
};

std::string convertToString(char* a, int size) {
	int i;
	std::string s = "";
	for (i = 0; i < size; i++) {
		s = s + a[i];
	}
	return s;
}

struct Node {
	std::string word;
	struct list* line;
	struct Node* left, * right;

}*root;

bool compare(std::string a, std::string b) {
	if (a < b)
		return true;
	return false;
}

struct Node* createNode(std::string word, int line) {
	struct Node* tempN = new Node();
	struct list* tempL = new list();
	tempN->word = word;
	tempN->left = nullptr;
	tempN->right = nullptr;
	tempL->line = line;
	tempL->next = nullptr;
	tempN->line = tempL;
	return tempN;
}

bool checkNode(Node* node, std::string word) {
	if (node == nullptr) {
		return false;
	}
	else if (node->word == word) {
		return true;
	}
	else if (node->word > word) {
		return checkNode(node->left, word);
	}
	else {
		return checkNode(node->right, word);
	}
}

void addList(struct list* head, int line) {
	struct list* temp = new list();
	temp->line = line;
	temp->next = nullptr;
	struct list* list = head;
	while (list->next != nullptr) {
		list = list->next;
	}
	list->next = temp;
}

void addLine(std::string word, int line) {
	struct Node* temp = root;
	while (temp) {
		if (temp->word == word) {
			addList(temp->line, line);
			break;
		}
		else if (temp->word > word) {
			temp = temp->left;
		}
		else {
			temp = temp->right;
		}
	}
}

struct Node* insertNode(Node* node, std::string word, int line) {
	bool check;
	check = checkNode(root, word);
	if (check) {
		addLine(word, line);
		return node;
	}
	else {
		struct Node* temp = createNode(word, line);
		if (node == nullptr) {
			node = temp;
			return node;
		}
		if (node->word > word) {
			node->left = insertNode(node->left, word, line);
		}
		else {
			node->right = insertNode(node->right, word, line);
		}
		return node;
	}
}

void inOrder(Node* node) {
	if (!node)
		return;
	inOrder(node->left);
	std::cout << node->word<< " ";
	struct list* temp = node->line;
	
	while (temp) {
		std::cout << temp->line << " ";
		temp = temp->next;
	}
	std::cout << std::endl;
	inOrder(node->right);
}
void ReadFile()
{
	std::ifstream input("Text.txt");
	char line[256];
	int i = 0;
	while (input.getline(line, 256)) {
		i++;
		char* pch;
		pch = strtok(line, " ,.-");
		while (pch != NULL)
		{
			std::string s(pch);
			root = insertNode(root, s, i);
			pch = strtok(NULL, " ,.-");

		}
	}
}

int main() {

	ReadFile();
	inOrder(root);
	return 0;
}


