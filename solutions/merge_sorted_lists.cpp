#include "gmock/gmock.h"
#include <cstdlib>
#include <numeric>
#include <utility>
#include <vector>

#include "llist.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

auto merge_sorted_lists(ListNode *list1, ListNode *list2) -> ListNode * {
  if (!list1)
    return list2;
  if (!list2)
    return list1;

  if (list1->val > list2->val)
    std::swap(list1, list2);

  if (!list1->next) {
    list1->next = list2;
    return list1;
  }

  auto __cur1 = list1, __next1 = list1->next;
  auto __cur2 = list2, __next2 = list2->next;

  while (__next1 && __cur2) {
    if (__cur1->val <= __cur2->val && __next1->val >= __cur2->val) {
      __next2 = __cur2->next;
      __cur1->next = __cur2;
      __cur2->next = __next1;

      __cur1 = __cur2;
      __cur2 = __next2;
    } else {
      if (__next1->next) {
        __next1 = __next1->next;
        __cur1 = __cur1->next;
      } else {
        __next1->next = __cur2;
        return list1;
      }
    }
  }

  return list1;
}

auto merge_k_sorted_lits(std::vector<ListNode *> lists) -> ListNode * {
  if (lists.empty())
    return nullptr;
  ListNode *res = lists.front();
  return std::accumulate(lists.cbegin() + 1, lists.cend(), res,
                         [](ListNode *list, ListNode *nextList) {
                           return merge_sorted_lists(list, nextList);
                         });
}

TEST(MergeTwoSortedLists, Cases) {
  ASSERT_THAT(vector_from_list(merge_sorted_lists(list_from_vector({1, 2, 4}),
                                                  list_from_vector({1, 3, 4}))),
              testing::ElementsAre(1, 1, 2, 3, 4, 4));
  ASSERT_THAT(vector_from_list(merge_sorted_lists(list_from_vector({1}),
                                                  list_from_vector({2}))),
              testing::ElementsAre(1, 2));
}

TEST(MergeKSortedLists, Cases) {
  ASSERT_THAT(vector_from_list(merge_k_sorted_lits({list_from_vector({1, 4, 5}),
                                                    list_from_vector({1, 3, 4}),
                                                    list_from_vector({2, 6})})),
              testing::ElementsAre(1, 1, 2, 3, 4, 4, 5, 6));
}
