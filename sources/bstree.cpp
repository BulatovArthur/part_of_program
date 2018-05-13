#include <iostream>
#include "bstree.hpp"
#include <fstream>

using namespace std;
using namespace BSTree;

Node::Node(int val) : data(val), left(nullptr), right(nullptr) {}

Tree::Tree() : root(nullptr) {}

Tree::Tree(initializer_list<int> list) : root(nullptr) {
	for (auto p = list.begin(); p != list.end(); p++)
                Add(*p);
}

Tree::Tree(const Tree& tree) : root(nullptr) {
	Appropriation(tree.root);
}

void Tree::Appropriation(Node *m_root) {
        Add(m_root->data);
        if (m_root->left != nullptr)
                Appropriation(m_root->left);
        if (m_root->right != nullptr)
                Appropriation(m_root->right);
}

bool Tree::Check() const {
	if (root == nullptr)
		return false;
	else
		return true;
}

void Tree::Add(int m_data, Node *&m_root) {
        if (m_root == nullptr)
                m_root = new Node{m_data};
        if (m_data < m_root->data) {
                if (m_root->left != nullptr)
                        Add(m_data, m_root->left);
                else
                        m_root->left = new Node{m_data};
        }
        if (m_data > m_root->data) {
                if (m_root->right != nullptr)
                        Add(m_data, m_root->right);
                else
                        m_root->right = new Node{m_data};
        }
}

void Tree::Clear(Node *&m_root) {
        if (m_root != nullptr) {
                Clear(m_root->left);
                Clear(m_root->right);
                delete m_root;
                m_root = nullptr;
        }
}

void Tree::Add(int m_data) {
        Add(m_data, root);
}

void Tree::Detour() {
	cout << "Enter order code (0-2)" << endl;
	cout << "0. In" << endl;
	cout << "1. Pre" << endl;
	cout << "2. Post" << endl;
	int code;
	cin >> code;
	switch (code) {
		case in :
			Transversal();
			cout << endl;
			break;
		case pre :
			Straight();
			cout << endl;
			break;
		case post :
			Reverse();
			cout << endl;
			break;
	}

}

void Tree::Print(Node *m_root, int space) const {
        if (m_root == nullptr)
                return;
        int count = 1;
        space += count;
        Print(m_root->right, space);
        cout << endl;
        for (int i = count; i < space; i++)
                cout << "   ";
        cout << "--" << m_root->data << endl;
        Print(m_root->left, space);
}

void Tree::Print() const {
	Print(root, 0);
}

void Tree::Transversal(Node *m_root) const {
	if (m_root->left != nullptr)
		Transversal(m_root->left);
	cout << m_root->data << " ";
	if (m_root->right != nullptr)
		Transversal(m_root->right);
}

void Tree::Transversal() const {
	Transversal(root);
}

void Tree::Straight(Node *m_root) const {
	cout << m_root->data << " ";
	if (m_root->left != nullptr)
		Straight(m_root->left);
	if (m_root->right != nullptr)
		Straight(m_root->right);
}

void Tree::Straight() const {
	Straight(root);
}

void Tree::Reverse(Node *m_root) const {
	if (m_root->left != nullptr)
		Reverse(m_root->left);
  	if (m_root->right != nullptr)
		Reverse(m_root->right);
  	cout << m_root->data << " ";
}

void Tree::Reverse() const {
	Reverse(root);
}

bool Tree::Compare(int m_item, Node *&m_root) const {
	if (m_root == nullptr)
		return false;
	if (m_item == m_root->data)
		return true;
	if (m_item < m_root->data) {
		if (m_root->left != nullptr)
			return Compare(m_item, m_root->left);
		else
			return false;
	} else {
		if (m_root->right != nullptr)
			return Compare(m_item, m_root->right);
		else
			return false;
	}
}

bool Tree::Compare(int m_item) {
	Compare (m_item, root);
}

void Tree::Deleting(int m_item, Node *&m_root) {
    	if (m_item == m_root->data) {
        	Node *tmp;
        	if (m_root->right == nullptr)
            		tmp = m_root->left;
        	else {
            		Node *ptr = m_root->right;
            		if (ptr->left == nullptr) {
                		ptr->left = m_root->left;
                		tmp = ptr;
            		} else {
                		Node *pmin = ptr->left;
                		while (pmin->left != nullptr) {
                    			ptr  = pmin;
                    			pmin = ptr->left;
                		}
                		ptr->left = pmin->right;
                		pmin->left = m_root->left;
                		pmin->right = m_root->right;
                		tmp = pmin;
            		}
        	}
        delete m_root;
	m_root = tmp;
    	} else if (m_item < m_root->data)
        		Deleting(m_item, m_root->left);
    		else
        		Deleting(m_item, m_root->right);
}

void Tree::Deleting(int m_item) {
	Deleting(m_item, root);
}

void Tree::Saving(Node *m_root, int space, string m_address) const {
	ofstream fout(m_address, ios_base::app);
        if (m_root == nullptr)
                return;
        int count = 1;
        space += count;
        Saving(m_root->right, space, m_address);
        fout << endl;
        for (int i = count; i < space; i++)
                fout << "   ";
        fout << "--" << m_root->data << endl;
        Saving(m_root->left, space, m_address);
	fout.close();
}

void Tree::Saving() const {
	string address;
	cout << "Enter the path to the file: ";
	cin >> address;
	ifstream file;
	file.open(address);
	if (!file.is_open())
		cerr << "This file does not exist" << endl;
	else {
		file.seekg(0, ios::end);
		if (file.tellg() == 0) {
			file.close();
                	Saving(root, 0, address);
		}
		else {
			cout << "File already exists, overwrite?:" << endl;
			string exit;
			cin >> exit;
			if ((exit == "y") || (exit == "yes")) {
				file.close();
				ofstream file(address, ios_base::out | ios_base::trunc);
				file.close();
				Saving(root, 0, address);
			}
			else
				return;
		}
	}
}

void Tree::Loading(string address) {
	ifstream fin(address);
    	string stree;
    	getline (fin, stree);
    	int count = 0;
    	for (int i=0; i< stree.length(); i++) {
        	if (stree[i] == ' ')
			count++;
    	}
    	fin.close();
    	fin.open(address);
    	for (int i = 0; i <= count; i++) {
        	fin >> stree;
        	Add(atoi(stree.data()));
    	}
	fin.close();
}

void Tree::Loading() {
        string address;
        cout << "Enter the path to the file: ";
        cin >> address;
        ifstream file;
        file.open(address);
        if (!file.is_open())
                cerr << "This file does not exist" << endl;
        else {
        	file.close();
                Loading(address);
	}
}

void Tree::Auxiliary_fun(ostream& stream, Node *m_root, int space) {
        if (m_root == nullptr)
                return;
        int count = 1;
        space += count;
        Auxiliary_fun(stream, m_root->right, space);
        cout << endl;
        for (int i = count; i < space; i++)
                stream << "   ";
        stream << "--" << m_root->data << endl;
        Auxiliary_fun(stream, m_root->left, space);
}

auto Tree::operator=(const Tree&) -> Tree& {
	Clear(this->root);
    	Appropriation(root);
    	return *this;
}

Tree::~Tree() {
        Clear(root);
}
