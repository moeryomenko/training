package pkg

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

type Stack struct {
	items [][2]int
}

func (s *Stack) Push(index, height int) {
	s.items = append(s.items, [2]int{index, height})
}

func (s Stack) Empty() bool {
	return len(s.items) == 0
}

func (s Stack) Top() [2]int {
	return s.items[len(s.items)-1]
}

func (s *Stack) Pop() [2]int {
	ret := s.Top()
	s.items = s.items[:len(s.items)-1]
	return ret
}

func largestRectangle(heights []int) int {
	stack := Stack{
		items: make([][2]int, 0, len(heights)),
	}
	maxArea := 0

	heights = append(heights, 0)
	for i, height := range heights {
		start := i
		for !stack.Empty() && stack.Top()[1] > height {
			prev := stack.Pop()

			prevArea := prev[1] * (i - prev[0])

			if maxArea < prevArea {
				maxArea = prevArea
			}
			start = prev[0]
		}
		stack.Push(start, height)
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

		if temp := largestRectangle(row); temp > maxArea {
			maxArea = temp
		}
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
}
