package br.com;

public class Main {

    public static void main(String[] args) {
        Cliente daniel = new Cliente();
        daniel.setNome("Daniel");

        Conta cc = new ContaCorrente(daniel);
        cc.depositar(100);
        
        Conta poupanca = new ContaPoupanca(daniel);

        cc.imprimirExtrato();
        poupanca.imprimirExtrato();

        cc.sacar(10);
        cc.imprimirExtrato();
        poupanca.imprimirExtrato();

        cc.transferir(90, poupanca);
        cc.imprimirExtrato();
        poupanca.imprimirExtrato();

    }
}
