#pragma once
#include <map>
#include <memory>
#include <string>

class PrefixTree
{
public:
	PrefixTree();

	void insert(std::string value);

	int find(std::string value);

	size_t size() { return count; };
private:
	class Node {
	public:
		Node() {}
		Node(char value) {
			val = value;
		}
		std::map <char, std::shared_ptr<Node>> m;
		char val;
		int count = 0;
	};

	std::shared_ptr<Node> root;

	size_t count;
};

