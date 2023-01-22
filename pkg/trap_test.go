package pkg

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func trap(height []int) int {
	max := 0
	index := 0
	for i, v := range height {
		if v > max {
			max = v
			index = i
		}
	}

	init := height[0]
	sum := 0
	for _, v := range height[1:index] {
		if init < v {
			init = v
		}
		sum += init - v
	}

	init = height[len(height) - 1]
	for i := len(height)-2; i > index; i-- {
		if init < height[i] {
			init = height[i]
		}
		sum += init - height[i]
	}

	return sum
}

func Test_trap(t *testing.T) {
	assert.Equal(t, 6, trap([]int{0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1}))
	assert.Equal(t, 9, trap([]int{4, 2, 0, 3, 2, 5}))
}
