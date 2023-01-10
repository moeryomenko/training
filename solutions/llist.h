#include <cstdlib>
#include <vector>

struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};

void freeList(ListNode *root) {
  auto current = root;

  while (current->next != nullptr) {
    auto to_free = current;
    current = current->next;
    free(to_free);
  }

  free(current);
}

auto list_from_vector(std::vector<int> vec) -> ListNode * {
  ListNode *l = nullptr;
  ListNode *head;
  for (auto v : vec) {
    if (l == nullptr) {
      l = new ListNode(v);
      head = l;
      continue;
    }

    l->next = new ListNode(v);
    l = l->next;
  }

  return head;
}

auto vector_from_list(ListNode *l) -> std::vector<int> {
  std::vector<int> vec;
  for (auto it = l; it != nullptr; it = it->next) {
    vec.push_back(it->val);
  }

  return vec;
}
