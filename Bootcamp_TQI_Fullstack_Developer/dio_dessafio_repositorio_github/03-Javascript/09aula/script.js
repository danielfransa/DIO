//tipos de função

// declarativas
function funcao1(){
    console.log('Sou uma mensagem de uma função declarativa.');
}

funcao1();


//expressão de função
//com nome.
var funcao = function funcao(){
    console.log('Sou uma mensagem de uma função expressão');
}

funcao();

//sem nome
var funcao2 = function(){
    console.log('Sou uma mensagem de uma função expressão sem nome');
}

funcao2();

//arrow function
var funcao3 = () => {
    console.log('Sou uma mensagem de uma função Arrow function.');
}

funcao3();
