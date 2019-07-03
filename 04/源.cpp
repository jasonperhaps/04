#include <iostream>

using namespace std;

typedef struct Node {
	Node(int value);
	Node* lchild;
	Node* rchild;
	int value;
}*pNode, Node;

pNode insert(pNode& root, int value) {
	if (root == NULL) {
		pNode node = new Node(value);
		root = node;
	}
	else if (value < root->value) {
		insert(root->lchild, value);
	}
	else {
		insert(root->rchild, value);
	}
	return root;
}

bool searchBST(Node* pNode, int value) {
	bool solved = false;
	while (pNode && !solved) {
		if (pNode->value == value) {
			solved = true;
		}
		else if (value < pNode->value) {
			pNode = pNode->lchild;
		}
		else {
			pNode = pNode->rchild;
		}
	}
	if (pNode == NULL) {
		cout << "没有找到" << endl;
	}
	return solved;
}

bool delBST(pNode tree, int value) {
	pNode p = tree;
	pNode q = NULL;
	bool find = false;
	while (p && !find) {
		if (p->value == value) {
			find = true;
		}
		else if (value < p->value) {
			q = p;
			p = p->lchild;
		}
		else {
			q = p;
			p = p->rchild;
		}
	}
	if (p == NULL) {
		cout << "没有找到" << endl;
		return find;
	}

	// p为叶子节点
	if (p->lchild == NULL && p->rchild == NULL) {
		if (p == tree) {
			//			delete tree;
			tree = NULL;
		}
		else if (p == q->lchild) {
			//			delete q->lchild;
			q->lchild = NULL;
		}
		else {
			//			delete q->rchild;
			q->rchild = NULL;
		}
		delete p;
		return find;
	}

	//
	if (p->lchild == NULL || p->rchild == NULL) {
		if (p == tree) {
			if (p->lchild != NULL) {
				tree = p->lchild;
				//				delete p;
			}
			else {
				tree = p->rchild;
				//				delete p;
			}
		}
		else {
			if (p == q->lchild && p->lchild != NULL) {
				q->lchild = p->lchild;
			}
			else if (p == q->lchild && p->rchild != NULL) {
				q->lchild = p->rchild;
			}
			else if (p == q->rchild && p->lchild != NULL) {
				q->rchild = p->lchild;
			}
			else {
				q->rchild = p->rchild;
			}
		}
		delete p;
		return find;
	}

	if (p->lchild != NULL && p->rchild != NULL) {
		pNode after = p->lchild;
		q = p;
		while (after->rchild != NULL) {
			q = after;
			after = after->rchild;
		}
		p->value = after->value;
		if (p == q) {
			p->lchild = after->lchild;
		}
		else {
			q->rchild = after->lchild;
		}
		delete after;
		return find;
	}
	return find;
}

void InTraverse(pNode tree) {
	if (tree == NULL) {
		return;
	}
	pNode p = tree;
	InTraverse(p->lchild);
	cout << p->value << " ";
	InTraverse(p->rchild);
}

void PreTraverse(pNode tree) {
	if (tree == NULL) {
		return;
	}
	pNode p = tree;
	cout << p->value << " ";
	PreTraverse(p->lchild);
	PreTraverse(p->rchild);
}

void PostTraverse(pNode tree) {
	if (tree == NULL) {
		return;
	}
	pNode p = tree;
	PreTraverse(p->lchild);
	PreTraverse(p->rchild);
	cout << p->value << " ";
}

void InPre2Post(int* inorder, int* preorder, int length) {
	pNode node = new Node(-1);
	node->value = *preorder;
	int nRoot = 0;
	for (; nRoot < length; nRoot++) {
		if (inorder[nRoot] == *preorder) {
			break;
		}
	}
	InPre2Post(inorder, preorder + 1, nRoot);
	InPre2Post(inorder + nRoot + 1, preorder + nRoot + 1, length - (nRoot + 1));
	cout << node->value << " ";
	return;
}

void InPost2Pre(int* inorder, int* postorder, int length) {
	pNode node = new Node(-1);
	node->value = postorder[length - 1];
	int nRoot = 0;
	for (; nRoot < length; nRoot++) {
		if (inorder[nRoot] == postorder[length - 1]);
		break;
	}
	cout << node->value << " ";
	InPost2Pre(inorder, postorder, nRoot);
	InPost2Pre(inorder + nRoot + 1, postorder + nRoot, length - (nRoot + 1));
	return;
}

int main() {
	Node* tree = new Node(15);
	insert(tree, 5);
	insert(tree, 3);
	insert(tree, 12);
	insert(tree, 16);
	insert(tree, 20);
	insert(tree, 23);
	insert(tree, 13);
	insert(tree, 18);
	insert(tree, 10);
	insert(tree, 6);
	insert(tree, 7);
	InTraverse(tree);
	cout << endl;
	PreTraverse(tree);
	cout << endl;
	PostTraverse(tree);
	cout << endl;
	cout << endl;
	cout << searchBST(tree, 13) << endl;
	cout << delBST(tree, 16) << endl;
	InTraverse(tree);
	cout << endl;
	PreTraverse(tree);
	cout << endl;
	PostTraverse(tree);
	cout << endl;
	return 0;
}

Node::Node(int value) {
	this->value = value;
	this->lchild = NULL;
	this->rchild = NULL;
}