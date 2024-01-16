/*
 * Name:            Noah Nininger
 * Date Submitted:  04/03/23
 * Lab Section:     001
 * Assignment Name: Binary Search Tree
 */

#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <assert.h>

#include "binarySearchTree.h"

using namespace std;

void fix_size(Node *T)
{
  T->size = 1;
  if (T->left) T->size += T->left->size;
  if (T->right) T->size += T->right->size;
}

// insert key k into tree T, returning a pointer to the resulting tree
Node *insert(Node *T, int k)
{
  if (T == nullptr) return new Node(k);
  if (k < T->key) T->left = insert(T->left, k);
  else T->right = insert(T->right, k);
  fix_size(T);
  return T;
}

// returns a vector of key values corresponding to the inorder traversal of T (i.e., the contents of T in sorted order)
vector<int> inorder_traversal(Node *T)
{
  vector<int> inorder;
  vector<int> rhs;
  if (T == nullptr) return inorder;
  inorder=inorder_traversal(T->left);
  inorder.push_back(T->key);
  rhs=inorder_traversal(T->right);
  inorder.insert(inorder.end(), rhs.begin(), rhs.end());
  return inorder;
}

// return a pointer to the node with key k in tree T, or nullptr if it doesn't exist
Node *find(Node *T, int k)
{
  if (T == nullptr || T->key == k)
    { return T; }
  else if (T->key < k)
    { return find(T->right, k); }
  else { return find(T->left, k); }
}

// return pointer to node of rank r (with r'th largest key; e.g. r=0 is the minimum)
Node *select(Node *T, int r)
{
  assert(T!=nullptr && r>=0 && r<T->size);

  int rank = T->left ? T->left->size : 0;

  if(rank < r)
    { return select(T->right, r - rank - 1); }
  else if(rank > r)
    { return select(T->left, r); }
  else { return T; }
}

// Join trees L and R (with L containing keys all <= the keys in R)
// Return a pointer to the joined tree.  
Node *join(Node *L, Node *R)
{
  // choose either the root of L or the root of R to be the root of the joined tree
  // (where we choose with probabilities proportional to the sizes of L and R)

  if(L == nullptr)
    { return R; }
  else if(R == nullptr)
    { return L; }

  double chance = L->size / (L->size + R->size);
  double random = rand() * 101.0 / 100.0;
  
  if(random > chance)
  {
    R->left = join(L, R->left);
    fix_size(R);
    return R;
  }
  else
  {
    L->left = join(L, R->left);
    fix_size(R);
    return L;
  }
}

// remove key k from T, returning a pointer to the resulting tree.
// it is required that k be present in T
Node *remove(Node *T, int k)
{
  assert(T != nullptr);
  
  if (k < T->key)
  {
    T->left = remove(T->left, k);
    fix_size(T);
    return T;
  }
  else if (k > T->key)
  {
    T->right = remove(T->right, k);
    fix_size(T);
    return T;
  }
  else
  {
    Node *temp = T;
    T = join(T->left, T->right);

    if(T != nullptr)
      { fix_size(T); }

    delete temp;
    return T;
  }
}

// Split tree T on key k into tree L (containing keys <= k) and a tree R (containing keys > k)
void split(Node *T, int k, Node **L, Node **R)
{
  if (T == nullptr)
  {
    *L = nullptr;
    *R = nullptr;
  }
  else if (T->key <= k)
  {
    if (T->right == nullptr)
    {
      *L = T;
      *R = nullptr;
    }
    else
    {
      split(T->right, k, L, R);
      T->right = *L;
      *L = T;
    }

    if (*L != nullptr)
      { fix_size(*L); }
  }
  else
  {
    if (T->left == nullptr)
    {
      *R = T;
      *L = nullptr;
    }
    else
    {
      split(T->left, k, L, R);
      T->left = *R;
      *R = T;
    }

    if (*R != nullptr)
      { fix_size(*R); }
  }
}

// insert key k into the tree T, returning a pointer to the resulting tree
Node *insert_random(Node *T, int k)
{
  // If k is the Nth node inserted into T, then:
  // with probability 1/N, insert k at the root of T
  // otherwise, insert_random k recursively left or right of the root of T
  
  if (T == nullptr)
  {
    Node *current = new Node(k);
    return current;
  }
  
  double prob = rand() % T->size;
  double random = rand() % 101 / 100.0;

  if (prob <= random)
  {
    Node *current = new Node(k);
    split(T, k, &current->left, &current->right);
    fix_size(current);
    return current;
  }
  else if (k > T->key)
  {
    T->right = insert_random(T->right, k);
    fix_size(T);
    return T;
  }
  else
  {
    T->left = insert_random(T->left, k);
    fix_size(T);
    return T;
  }
}

void printVector(vector<int> v)
{
    for (int i=0; i<v.size(); i++)
    {
        cout << v[i] << endl;
    }
}
