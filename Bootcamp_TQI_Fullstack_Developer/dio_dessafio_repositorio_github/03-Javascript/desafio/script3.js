// a função gets é implementada dentro do sistema para ler as entradas(inputs) dos dados e a função print para imprimir a saída (output) de dados e já pula uma linha ("\n")
// Abaixo segue um exemplo de código que você pode ou não utilizar

let qtdEntradas = parseInt(gets());
let melhor = 999;

for(let i = 0; i < qtdEntradas; i++){
    let tempo = parseFloat(gets());
    if ( tempo < melhor ) {
      melhor = tempo;
      
    }
    
  }
    
    console.log(melhor);
