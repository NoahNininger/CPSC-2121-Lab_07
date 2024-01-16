#pragma once

#include <iostream>
#include <vector>

using namespace std;

struct Node {
  int key;
  int size;
  Node *left;
  Node *right;
  Node (int k) { key = k; size = 1; left = right = nullptr; }
};

void fix_size(Node *T);
Node *insert(Node *T, int k);
vector<int> inorder_traversal(Node *T);
Node *find(Node *T, int k);
Node *select(Node *T, int r);
Node *join(Node *L, Node *R);
Node *remove(Node *T, int k);
void split(Node *T, int k, Node **L, Node **R);
Node *insert_random(Node *T, int k);
void printVector(vector<int> v);
