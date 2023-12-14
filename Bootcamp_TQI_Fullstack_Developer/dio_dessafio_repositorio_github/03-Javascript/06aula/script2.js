// objeto

let object = { string: 'string', number: 1, Boolean: true, array: ['array'], objectInterno: {objectInterno: 'objeto interno'}};
console.log(object);
console.log(object.objectInterno);

//desestruturação

var string = object.string;
console.log(string);

var array = object.array;
console.log(array);

var {string, Boolean, objectInterno} = object;
console.log(string, Boolean, objectInterno);