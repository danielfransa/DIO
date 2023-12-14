function calculadora() {
    const operacao = Number(prompt('Escolha uma operação: \n 1 - Soma (+)\n 2 - Subtração (-)\n 3 - Multiplicação (*)\n 4 - Divisão Real (/)\n 5 - Resto da Divisão (%)\n 6 - Potenciação (**)\n'));

    if (!operacao || operacao >= 7) {
        alert('Erro - operação inválida!');
        calculadora()
    } else {

        let n1 = Number(prompt('Insira o primeiro valor:'));
        let n2 = Number(prompt('Insira o segundo valor:'));
        let resultado = 0;

        if (!n1 || !n2) {
            alert('Parametro incorreto (Utilize apenas números!):');
            calculadora();
        } else {

            function soma() {
                resultado = n1 + n2;
                alert(`${n1} + ${n2} = ${resultado} `)
                novaOperacao();
            }
            function subtracao() {
                resultado = n1 - n2;
                alert(`${n1} - ${n2} = ${resultado} `)
                novaOperacao();
            }
            function multiplicacao() {
                resultado = n1 * n2;
                alert(`${n1} x ${n2} = ${resultado} `)
                novaOperacao();
            }
            function divisaoReal() {
                resultado = n1 / n2;
                alert(`${n1} / ${n2} = ${resultado} `)
                novaOperacao();
            }
            function restoDiv() {
                resultado = n1 % n2;
                alert(`${n1} % ${n2} = ${resultado} `)
                novaOperacao();
            }
            function potencia() {
                resultado = n1 ** n2;
                alert(`${n1} ^ ${n2} = ${resultado} `)
                novaOperacao();
            }

            function novaOperacao() {
                let opcao = prompt('Deseja realizar uma nova operação?\n Digite:\n 1 - SIM\n 2 - NÃO\n');

                if (opcao == 1) {
                    calculadora();
                } else if (opcao == 2) {
                    alert('Obrigado por utilizar nossa calculadora, até mais!');
                } else {
                    alert('Digite uma opção válida');
                    novaOperacao();
                }
            }
        }
        /*if (operacao == 1) {
            soma();
        } else if (operacao == 2) {
            subtracao();
        } else if (operacao == 3) {
            multiplicacao();
        } else if (operacao == 4) {
            divisaoReal();
        } else if (operacao == 5) {
            restoDiv();
        } else if (operacao == 6) {
            potencia();
        } */

        switch (operacao){
            case 1:
                soma();
                break;
            case 2:
                subtracao();
                break;
            case 3:
                multiplicacao();
                break;
            case 4:
                divisaoReal();
                break;
            case 5:
                restoDiv();
                break;
            case 6:
                potencia();
                break;
        }
    }
}
calculadora();
