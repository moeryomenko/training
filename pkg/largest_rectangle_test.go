package pkg

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

type Stack[T any] struct {
	items []T
}

func NewStack[T any](capacity int) *Stack[T] {
	return &Stack[T]{
		items: make([]T, 0, capacity),
	}
}

func (s *Stack[T]) Push(elem T) {
	s.items = append(s.items, elem)
}

func (s Stack[T]) Empty() bool {
	return len(s.items) == 0
}

func (s Stack[T]) Top() T {
	return s.items[len(s.items)-1]
}

func (s *Stack[T]) Pop() T {
	ret := s.Top()
	s.items = s.items[:len(s.items)-1]
	return ret
}

func largestRectangle(heights []int) int {
	stack := NewStack[[2]int](len(heights))
	maxArea := 0

	heights = append(heights, 0)
	for i, height := range heights {
		start := i
		for !stack.Empty() && stack.Top()[1] > height {
			prev := stack.Pop()
			maxArea = max(prev[1]*(i-prev[0]), maxArea)
			start = prev[0]
		}
		stack.Push([2]int{start, height})
	}

	return maxArea
}

func maximalRectangle(matrix [][]byte) int {
	row := make([]int, len(matrix[0]))

	maxArea := 0
	for _, chars := range matrix {
		for i, ch := range chars {
			if ch == '1' {
				row[i] += 1
			} else {
				row[i] = 0
			}
		}

		maxArea = max(largestRectangle(row), maxArea)
	}

	return maxArea
}

func Test_largestRectangle(t *testing.T) {
	assert.Equal(t, 10, largestRectangle([]int{2, 1, 5, 6, 2, 3}))
}

func Test_maximalRectangle(t *testing.T) {
	assert.Equal(t, 6, maximalRectangle([][]byte{
		{'1', '0', '1', '0', '0'},
		{'1', '0', '1', '1', '1'},
		{'1', '1', '1', '1', '1'},
		{'1', '0', '0', '1', '0'},
	}))
	assert.Equal(t, 12, maximalRectangle([][]byte{
		{'1', '1', '1', '1', '1'},
		{'1', '1', '1', '1', '1'},
		{'1', '0', '1', '1', '1'},
		{'1', '0', '1', '1', '1'},
	}))
}
