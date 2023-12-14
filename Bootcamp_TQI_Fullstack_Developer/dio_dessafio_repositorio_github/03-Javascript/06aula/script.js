// o que são vetores ou arrays

// como declarar um Array
let array = ['string', 1, true];
console.log(array);

//pode gravar varios tipos de dados inclusive arrays.
let array2 = ['string', 1, true, ['array1'], ['array2'], ['array3'], ['array4']];
console.log(array2);

// forEach
array2.forEach(function(item, index){console.log(item, index)});

// push

array2.push('novo item');
console.log(array2);

// pop

array2.pop();
console.log(array2);

//shift

array2.shift();
console.log(array2);

//unshift

array2.unshift('string');
console.log(array2);

//indexOf

console.log(array2.indexOf(true));

//splice
array2.splice(0, 3);
console.log(array2);

//slice

let novoArray = array2.slice(0, 3);
console.log(novoArray);