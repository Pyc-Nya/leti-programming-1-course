let value, ttop, bottom, left, right, col, row, i, j;
let arr = new Array(9).fill(0).map(() => new Array(9).fill(0));

value = 1;
ttop = 0;
bottom = 8;
left = 0;
right = 8;

while (ttop <= bottom && left <= right) {

    for (col = left; col <= right; col++) {
        arr[ttop][col] = value++;
    }
    ttop++;

    for (row = ttop; row <= bottom; row++) {
        arr[row][right] = value++;
    }
    right--;

    if (ttop <= bottom) {
        for (col = right; col >= left; col--) {
            arr[bottom][col] = value++;
        }
        bottom--;
    }

    if (left <= right) {
        for (row = bottom; row >= ttop; row--) {
            arr[row][left] = value++;
        }
        left++;
    }
}

console.log(arr);

