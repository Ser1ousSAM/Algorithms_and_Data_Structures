#include "PrefixTree.h"

PrefixTree::PrefixTree()
{
	root = std::make_shared<Node>();
}

void PrefixTree::insert(std::string value)
{
	std::shared_ptr<Node> node = root;
	for (int i=0; i<value.length();i++) {
		if(node->m.find(value[i]) == node->m.end()){
			node->m[value[i]] = std::make_shared<Node>(value[i]);
		}
		node = node->m[value[i]];
	}
	if (node->count == 0) {
		count++;
	}
	node->count++;

}

int PrefixTree::find(std::string value)
{
	std::shared_ptr<Node> node = root;
	for (int i = 0; i < value.length(); i++) {
		if (node->m.find(value[i]) == node->m.end()) {
			return 0;
		}
		node = node->m[value[i]];
	}
	return node->count;
}
