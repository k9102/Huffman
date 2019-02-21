// Huffman.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <string>
#include <map>
#include <queue>

using namespace std;


class Node
{
public:
	char val_;
	int freq_;
	shared_ptr<Node> l_ = nullptr;
	shared_ptr<Node> r_ = nullptr;
	Node(char val, int freq, shared_ptr<Node> l=nullptr, shared_ptr<Node> r=nullptr) : val_(val),freq_(freq),l_(l),r_(r) {}
};

string str_ = R"(
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
)";

string str = "aaaaabbbbbbbbbccccccccccccdddddddddddddeeeeeeeeeeeeeeeefffffffffffffffffffffffffffffffffffffffffffff";
map<char, string> code;
void Traverse(shared_ptr<Node> tree,string prefix)
{
	if (tree == nullptr)
	{
		return;
	}
	if (tree->val_ != 0)
	{
		code[tree->val_] = prefix;
		return;
	}

	Traverse(tree->l_, prefix + "0");
	Traverse(tree->r_, prefix + "1");
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

int main()
{
	map<char, int> tbl;

	for (auto c : str)
	{
		tbl[c]++;
	}

	auto cmp = [](shared_ptr<Node> fir, shared_ptr<Node> sec) { return  fir->freq_ > sec->freq_; };
	std::priority_queue<shared_ptr<Node>, vector<shared_ptr<Node>>, decltype(cmp)> que(cmp);
	
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
	Traverse(que.top(),"");

	for (auto[val, word] : code)
	{
		cout << val << ":"+word << endl;
	}
}

