package pkg

import (
	"sort"
	"testing"

	"github.com/stretchr/testify/assert"
)

func countNegatives(matrix [][]int) int {
	count := 0
	size := len(matrix[0])
	end := size
	for _, nums := range matrix {
		end = sort.Search(end, func(i int) bool { return nums[i] < 0 })
		count += size - end
	}

	return count
}

func Test_countNegInMatrix(t *testing.T) {
	assert.Equal(t, 8, countNegatives([][]int{{4, 3, 2, -1}, {3, 2, 1, -1}, {1, 1, -1, -2}, {-1, -1, -2, -3}}))
	assert.Equal(t, 3, countNegatives([][]int{{5, 1, 0}, {-5, -5, -5}}))
	assert.Equal(t, 16, countNegatives([][]int{{3, -1, -3, -3, -3}, {2, -2, -3, -3, -3}, {1, -2, -3, -3, -3}, {0, -3, -3, -3, -3}}))
}
