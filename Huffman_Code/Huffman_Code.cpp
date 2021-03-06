// Huffman_Code.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>

using namespace std;

struct Item final
{
	char value;
	int count;
};

map<char, string> codeMap;

struct Node
{
	char data;
	unsigned freq;

	Node *left, *right;

	Node(char data, unsigned freq)
	{

		left = right = NULL;
		this->data = data;
		this->freq = freq;
	}
};

void printCodes(struct Node* root, string str)
{

	if (!root)
		return;

	if (root->data != '$')
	{
		if (str == "")
			str = "0";
		codeMap.insert(make_pair(root->data, str));
	}

	printCodes(root->left, str + "0");
	printCodes(root->right, str + "1");
}

struct compare 
{
	bool operator()(Node* l, Node* r)
	{
		return (l->freq > r->freq);
	}
};

void Huffman(std::string text)
{
	std::vector<Item> charList;
	for (int i = 0; i < text.size(); i++)
	{
		bool newOne = true;
		for (int j = 0; j < charList.size() && newOne == true; j++)
		{
			if (charList.at(j).value == text[i])
			{
				charList.at(j).count++;
				newOne = false;
			}
		}
		if (newOne)
		{
			Item newItem;
			newItem.value = text[i];
			newItem.count = 1;
			charList.push_back(newItem);
		}
	}

	struct Node *left, *right, *top;

	priority_queue<Node*, vector<Node*>, compare> minHeap;

	for (auto item : charList)
		minHeap.push(new Node(item.value, item.count));

	while (minHeap.size() != 1) 
	{
		left = minHeap.top();
		minHeap.pop();

		right = minHeap.top();
		minHeap.pop();

		top = new Node('$', left->freq + right->freq);

		top->left = left;
		top->right = right;

		minHeap.push(top);
	}

	printCodes(minHeap.top(), "");

	std::cout << codeMap.size() << " ";
	string codeText = "";
	for (int i = 0; i < text.size(); i++)
	{
		auto item = codeMap.find(text[i]);
		codeText += item->second;
	}
	std::cout << codeText.size() << endl;
	for (auto item: codeMap)
	{
		std::cout << item.first << ": " << item.second << endl;
	}
	std::cout << codeText;
}

int main()
{
	std::string n;
	std::cin >> n;	
	Huffman(n);

	system("pause");
	return 0;
}

