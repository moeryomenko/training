#include "llist.h"

#include "gmock/gmock.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

int take_value(ListNode *it) { return it != nullptr ? it->val : 0; }

ListNode *next(ListNode *it) { return it != nullptr ? it->next : nullptr; }

auto add_two_numbers(ListNode *l1, ListNode *l2) -> ListNode * {
  if (l1 == nullptr && l2 == nullptr)
    return nullptr;

  auto it1 = l1, it2 = l2;

  ListNode *result = new ListNode();
  ListNode *it = result;

  int acc = 0;
  while (it1 != nullptr || it2 != nullptr) {
    auto v1 = take_value(it1);
    auto v2 = take_value(it2);

    auto v = v1 + v2 + acc;
    acc = v / 10;
    v %= 10;

    it->val = v;

    if (it1 = next(it1), it2 = next(it2); it1 != nullptr || it2 != nullptr) {
      it->next = new ListNode();
      it = it->next;
    }
  }

  if (acc != 0) {
    it->next = new ListNode(acc);
  }

  return result;
}

TEST(List, Converstion) {
  ASSERT_THAT(vector_from_list(list_from_vector({1, 2, 3})),
              testing::ElementsAre(1, 2, 3));
  ASSERT_THAT(
      vector_from_list(list_from_vector(std::vector{8, 9, 9, 9, 0, 0, 0, 1})),
      testing::ElementsAre(8, 9, 9, 9, 0, 0, 0, 1));
}

TEST(AddTwoNumbersList, Cases) {
  ASSERT_THAT(
      vector_from_list(add_two_numbers(list_from_vector(std::vector{2, 4, 3}),
                                       list_from_vector(std::vector{5, 6, 4}))),
      testing::ElementsAre(7, 0, 8));
  ASSERT_THAT(
      vector_from_list(add_two_numbers(list_from_vector(std::vector{0}),
                                       list_from_vector(std::vector{0}))),
      testing::ElementsAre(0));
  ASSERT_THAT(vector_from_list(add_two_numbers(
                  list_from_vector(std::vector{9, 9, 9, 9, 9, 9, 9}),
                  list_from_vector(std::vector{9, 9, 9, 9}))),
              testing::ElementsAre(8, 9, 9, 9, 0, 0, 0, 1));
}
