// Huffman.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h> 

#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <string>
#include <map>
#include <queue>

using namespace std;

class Node;
using NodePtr = shared_ptr<Node>;

class Node
{
public:
	char val_;
	int freq_;
	NodePtr l_;
	NodePtr r_;
	Node(char val, int freq, NodePtr l = nullptr, NodePtr r = nullptr) : val_(val), freq_(freq), l_(l), r_(r) {}
};


string str = R"(aaaaabbbbbbbbbccccccccccccdddddddddddddeeeeeeeeeeeeeeeefffffffffffffffffffffffffffffffffffffffffffff)";
map<char, string> code_map;
void Traverse(NodePtr tree, string prefix)
{
	if (nullptr == tree)
	{
		return;
	}
	if (0 != tree->val_)
	{
		code_map[tree->val_] = prefix;
	}
	else
	{
		Traverse(tree->l_, prefix + "0");
		Traverse(tree->r_, prefix + "1");
	}
}

/*
https://www.geeksforgeeks.org/huffman-coding-greedy-algo-3/
There are mainly two major parts in Huffman Coding
1) Build a Huffman Tree from input characters.
2) Traverse the Huffman Tree and assign codes to characters.

Steps to build Huffman Tree
Input is array of unique characters along with their frequency of occurrences and output is Huffman Tree.

1. Create a leaf node for each unique character and build a min heap of all leaf nodes(Min Heap is used as a priority queue.The value of frequency field is used to compare two nodes in min heap.Initially, the least frequent character is at root)

2. Extract two nodes with the minimum frequency from the min heap.

3. Create a new internal node with frequency equal to the sum of the two nodes frequencies.Make the first extracted node as its left child and the other extracted node as its right child.Add this node to the min heap.

4. Repeat steps#2 and #3 until the heap contains only one node.The remaining node is the root node and the tree is complete.
*/

void GenerateHuffCode()
{
	map<char, int> tbl;

	for (auto c : str)
	{
		tbl[c]++;
	}

	auto cmp = [](NodePtr fir, NodePtr sec) { return  fir->freq_ > sec->freq_; };
	std::priority_queue<NodePtr, vector<NodePtr>, decltype(cmp)> que(cmp);

	/*
	1) Build a Huffman Tree from input characters
	*/
	for (auto[val, freq] : tbl)
	{
		//1. Create a leaf node for each unique character and build a min heap of all leaf nodes(Min Heap is used as a priority queue.The value of frequency field is used to compare two nodes in min heap.Initially, the least frequent character is at root)
		que.push(make_shared<Node>(val, freq));
	}

	//4. Repeat steps#2 and #3 until the heap contains only one node.The remaining node is the root node and the tree is complete.
	while (que.size() >= 2)
	{
		//2. Extract two nodes with the minimum frequency from the min heap.
		auto l = que.top(); que.pop();
		auto r = que.top(); que.pop();

		int t_freq = l->freq_ + r->freq_;
		//3. Create a new internal node with frequency equal to the sum of the two nodes frequencies.Make the first extracted node as its left child and the other extracted node as its right child.Add this node to the min heap.
		que.push(make_shared<Node>(0, t_freq, l, r));

	}

	/*
	2) Traverse the Huffman Tree and assign codes to characters
	*/
	Traverse(que.top(), "");

	for (auto[val, bits] : code_map)
	{
		cout << val << ":" + bits << endl;
	}

	code_map.clear();
}

int main()
{

#if 0
	_CrtSetBreakAlloc(188);
#endif

	_CrtMemState s1, s2,s3;

	_CrtMemCheckpoint(&s1);
	GenerateHuffCode();
	_CrtMemCheckpoint(&s2);

	if (_CrtMemDifference(&s3, &s1, &s2))
	{
		_CrtMemDumpStatistics(&s3);
		_CrtDumpMemoryLeaks();
	}

}

