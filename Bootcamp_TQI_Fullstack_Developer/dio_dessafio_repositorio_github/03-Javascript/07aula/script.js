var jogador1 = 0;
var jogador2 = 0;
var placar;

// if ternário de uma linha só:
jogador1 !== -1 && jogador2 !== -1 ? console.log('Os Jogadores são Válidos') : console.log('Jogadores Inválidos'); 

// estrutura if, else if e else
if(jogador1 > 0 && jogador2 == 0){
    console.log('Jogador 1 Marcou ponto');
    placar = jogador1 > jogador2;
}
// else if
else if(jogador2 > 0 && jogador1 == 0){
    console.log('Jogador 2 Marcou ponto');
    placar = jogador2 > jogador1;
}
// usando else
else{
    console.log('Ninguém marcou ponto');
}
   
switch (placar) {
    case placar = jogador1 > jogador2:
    console.log('Jogador 1 Ganhou');
    break;
    case placar = jogador2 > jogador1:
    console.log('Jogador 2 Ganhou');
    break;
    default:
    console.log('Ninguém ganhou!');
}

// estrutura de repetição

var array = ['array1', 'array2', 'array3', 'array4', 'array5'];

let object = { propriedade1: 'valor1', propriedade2: 'valor2', propriedade3: 'valor3',}

for(let indice = 0; indice < array.length; indice++){
    console.log(indice);
}

for(let i in array){
    console.log(i)
}

for (i in object) {
    console.log(i);
}

//forOf
for (i of array) {
    console.log(i);
}
//forOf objetos não funciona.
for (i of object.propriedade1) {
    console.log(i);    
}

//while

var a = 0; 

while (a < 10) {
    a++;
    console.log(a);
}

//do while

var b = 0;

do{
    b++;
    console.log(b);
}while(b < 10);