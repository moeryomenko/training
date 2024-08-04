#include "llist.h"

#include <gtest/gtest.h>

auto middle_node(ListNode *head) -> ListNode * {
  auto slow{head};
  for (auto fast{head}; fast != nullptr && fast->next != nullptr;
       slow = slow->next, fast = fast->next->next) {
  }
  return slow;
}

auto reverse_list(ListNode *head) -> ListNode * {
  ListNode *temp{head}, *prev{nullptr}, *next{nullptr};

  while (temp != nullptr) {
    next = temp->next;
    temp->next = prev;
    prev = temp;
    temp = next;
  }
  return prev;
}

auto is_palindrome_list(ListNode *head) -> bool {
  auto reverted_half{reverse_list(middle_node(head))};

  for (auto cur1{head}, cur2{reverted_half};
       cur1 != reverted_half && cur2 != nullptr;
       cur1 = cur1->next, cur2 = cur2->next) {
    if (cur1->val != cur2->val)
      return false;
  }

  return true;
}

TEST(Palindrome, Cases) {
  EXPECT_TRUE(is_palindrome_list(list_from_vector({1, 2, 2, 1})));
  EXPECT_TRUE(is_palindrome_list(list_from_vector({1, 2, 1})));
  EXPECT_FALSE(is_palindrome_list(list_from_vector({1, 2, 3, 1})));
}
