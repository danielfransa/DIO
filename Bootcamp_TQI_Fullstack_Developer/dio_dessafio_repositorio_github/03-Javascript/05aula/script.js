// Tipos primitivos

//boolean
var VouF = false;
console.log(typeof(VouF));

//number
var numeroQualquer = 1;
console.log(typeof(numeroQualquer));

// string

var nome = 'diana';
console.log(typeof(nome));

// como declarar variavel.

var variavel = 'diana';
variavel = 'martini'
console.log(variavel)

let variavel2 = 'diana'
variavel2 = 'joão'
console.log(variavel2)

const constante = 'Daniel';
console.log(constante)

var escopoGlobal = 'global';
console.log(escopoGlobal);

function escopoLocal() {
    let escopoLocalInterno = 'Local'
    console.log(escopoLocalInterno);
}

escopoLocal();

// atribuição

var atribuição = 'diana';
console.log(atribuição);

// comparação
var comparação = '0' == 0;
console.log(comparação);

// comparação idêntica
var comparação2 = '0' === 0;
console.log(comparação2);

// adição

var adicao = 1 + 1;
console.log(adicao)

//subtração

var subtracao = 2 - 1; 
console.log(subtracao);

// Multiplicação

var multiplicacao = 2 * 3;
console.log(multiplicacao)

//Divisão

var divisao = 4 / 2;
console.log(divisao)

//Resto da divisão

var restodiv = 5 % 2;
console.log(restodiv);

//potencia

var potencia = 2 ** 10;
console.log(potencia)

// Maior que

var maiorque = 5 > 2;
console.log(maiorque);

// Menor que

var menorque = 5 < 2;
console.log(menorque);

// Maior igual que
var maiorIgualque = 5 >= 2;
console.log(maiorIgualque);

// Menor igual que
var menorIgualque = 5 <= 2;
console.log(menorIgualque);

// e

var e = true && false;
console.log(e);

// ou
var ou = true || false;
console.log(ou);

// não

var nao = !true;
console.log(nao);
