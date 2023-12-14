/* Crie uma função que recebe dois números como parâmetros.
Confira se os números são iguais.
Confira se a soma dos números é maior que 10 ou menor que 20.
Retorne uma string dizendo "Os números num1 e num2 não/são iguais. Sua soma é soma, que é maior/menor que 10 e maior/menor que 20". */



let num1 = Number(prompt('Insira o primeiro valor:'));
let num2 = Number(prompt('Insira o segundo valor:'));
let soma = 0;
var igual;
var comp1;
var comp2;

    soma = num1 + num2;

    if(num1 == num2) {
        igual = 'são iguais';
    }else 
        igual = 'não são iguais';
    
    if(soma > 10) {
        comp1 = 'maior';
    }else
        comp1 = 'menor';
    
    if(soma > 20) {
        comp2 = 'maior';
    }else
        comp2 = 'menor'

        alert(`Os números ${num1} e ${num2} ${igual}. Sua soma é ${soma}, que é ${comp1} que 10 e ${comp2} que 20".`);