#include <boost/ut.hpp>

#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <numeric>
#include <queue>
#include <stack>
#include <vector>

struct TreeNode {
  int val;
  struct TreeNode *left, *right;
};

struct Node {
  int val;
  std::vector<Node *> children;
};

auto preorder(Node *root) -> std::vector<int> {
  if (root == nullptr) {
    return {};
  }

  std::stack<Node *, std::vector<Node *>> stack;

  stack.push(root);

  std::vector<int> res;
  while (!stack.empty()) {
    auto temp = stack.top();
    stack.pop();

    res.push_back(temp->val);

    for (auto it = temp->children.rbegin(); it != temp->children.rend(); ++it)
      stack.push(*it);
  }

  return res;
}

auto levelOrder(TreeNode *root) -> std::vector<std::vector<int>> {
  if (root == nullptr)
    return {};

  std::queue<TreeNode *> level_queue;
  std::vector<std::vector<int>> res;

  level_queue.push(root);

  for (std::vector<int> current_level; !level_queue.empty();
       current_level.clear()) {
    for (size_t level_size = level_queue.size(); level_size > 0; --level_size) {
      auto node = level_queue.front();
      level_queue.pop();
      current_level.push_back(node->val);
      if (node->left)
        level_queue.push(node->left);
      if (node->right)
        level_queue.push(node->right);
    }
    res.push_back(current_level);
  }

  return res;
}

auto levelOrderBottom(TreeNode *root) -> std::vector<std::vector<int>> {
  if (root == nullptr)
    return {};

  std::queue<TreeNode *> level_queue;
  std::vector<std::vector<int>> res;

  level_queue.push(root);

  for (std::vector<int> current_level; !level_queue.empty();
       current_level.clear()) {
    for (size_t level_size = level_queue.size(); level_size > 0; --level_size) {
      auto node = level_queue.front();
      level_queue.pop();
      current_level.push_back(node->val);
      if (node->left)
        level_queue.push(node->left);
      if (node->right)
        level_queue.push(node->right);
    }
    res.push_back(current_level);
  }

  std::reverse(res.begin(), res.end());

  return res;
}

auto averageOfLevels(TreeNode *root) -> std::vector<double> {
  if (root == nullptr)
    return {};

  std::queue<TreeNode *> level_queue;
  std::vector<double> res;

  level_queue.push(root);

  for (std::vector<int> current_level; !level_queue.empty();
       current_level.clear()) {
    for (size_t level_size = level_queue.size(); level_size > 0; --level_size) {
      auto node = level_queue.front();
      level_queue.pop();
      current_level.push_back(node->val);
      if (node->left)
        level_queue.push(node->left);
      if (node->right)
        level_queue.push(node->right);
    }

    res.push_back(static_cast<double>(std::accumulate(
                      current_level.cbegin(), current_level.cend(), 0ll)) /
                  current_level.size());
  }

  return res;
}

auto preorderTraversal(TreeNode *root) -> std::vector<int> {
  if (root == nullptr) {
    return {};
  }

  std::stack<TreeNode *, std::vector<TreeNode *>> stack;

  stack.push(root);

  std::vector<int> res;
  while (!stack.empty()) {
    auto temp = stack.top();
    stack.pop();

    res.push_back(temp->val);

    if (temp->right)
      stack.push(temp->right);
    if (temp->left)
      stack.push(temp->left);
  }

  return res;
}

auto postorderTraversal(TreeNode *root) -> std::vector<int> {
  if (root == nullptr) {
    return {};
  }

  std::stack<TreeNode *, std::vector<TreeNode *>> stack{{root}};

  std::vector<int> res;
  while (!stack.empty()) {
    auto temp = stack.top();
    stack.pop();

    res.push_back(temp->val);

    if (temp->left)
      stack.push(temp->left);
    if (temp->right)
      stack.push(temp->right);
  }

  std::reverse(res.begin(), res.end());
  return res;
}

auto postorder(Node *root) -> std::vector<int> {
  if (root == nullptr) {
    return {};
  }

  std::stack<Node *, std::vector<Node *>> stack;

  stack.push(root);

  std::vector<int> res;
  while (!stack.empty()) {
    auto temp = stack.top();
    stack.pop();

    res.push_back(temp->val);

    for (auto it = temp->children.begin(); it != temp->children.end(); ++it)
      stack.push(*it);
  }

  std::reverse(res.begin(), res.end());
  return res;
}

auto levelOrder(Node *root) -> std::vector<std::vector<int>> {
  if (root == nullptr)
    return {};

  std::queue<Node *> level_queue{{root}};
  std::vector<std::vector<int>> res;

  for (std::vector<int> current_level; !level_queue.empty();
       current_level.clear()) {
    for (size_t level_size = level_queue.size(); level_size > 0; --level_size) {
      auto node = level_queue.front();
      level_queue.pop();
      current_level.push_back(node->val);
      for (auto it = node->children.begin(); it != node->children.end(); ++it)
        level_queue.push(*it);
    }
    res.push_back(current_level);
  }

  return res;
}
