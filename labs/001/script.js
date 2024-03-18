let n, digit, last, counter, maxS, globalCounter;
maxS = globalCounter = 0;
n = +prompt("Введите количество чисел");
counter = Math.min(n, 1);
last = +prompt(`Введите число (осталось ${n--})`);

let arr = []
arr.push(last);

for (let i = 0; i < n; i++) {
    digit = +prompt(`Введите число (осталось ${n - i}) \n${arr}`);
    arr.push(digit);
    if (digit < last) {
        if (counter > 1) {
            maxS = Math.max(counter, maxS);
            globalCounter++;
        }
        counter = 1;
    } else {
        counter++;
    }
    last = digit;
}

if (counter > 1) {
    maxS = Math.max(counter, maxS);
    globalCounter++;
}

alert(`Количество подпоследовательностей: ${globalCounter}`);
alert(`Длина наибольшей подпоследовательности: ${maxS}`);
