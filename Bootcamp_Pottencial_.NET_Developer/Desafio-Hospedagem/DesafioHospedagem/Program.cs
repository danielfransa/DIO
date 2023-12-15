using System.Text;
using DesafioProjetoHospedagem.Models;

Console.OutputEncoding = Encoding.UTF8;

// Cria os modelos de hóspedes e cadastra na lista de hóspedes
List<Pessoa> hospedes = new List<Pessoa>();
List<Pessoa> hospedes1 = new List<Pessoa>();
List<Pessoa> hospedes2 = new List<Pessoa>();

Pessoa p1 = new Pessoa(nome: "Hóspede 1");
Pessoa p2 = new Pessoa(nome: "Hóspede 2");
Pessoa p3 = new Pessoa(nome: "Hóspede 3");
Pessoa p4 = new Pessoa(nome: "Hóspede 4");
Pessoa p5 = new Pessoa(nome: "Hóspede 5");
Pessoa p6 = new Pessoa(nome: "Hóspede 6");
Pessoa p7 = new Pessoa(nome: "Hóspede 7");
Pessoa p8 = new Pessoa(nome: "Hóspede 8");
Pessoa p9 = new Pessoa(nome: "Hóspede 9");
Pessoa p10 = new Pessoa(nome: "Hóspede 10");

hospedes.Add(p1);
hospedes.Add(p2);
hospedes1.Add(p3);
hospedes1.Add(p4);
hospedes1.Add(p5);
hospedes2.Add(p6);
hospedes2.Add(p7);
hospedes2.Add(p8);
hospedes2.Add(p9);
hospedes2.Add(p10);


// Cria a suíte
Suite suite = new Suite(tipoSuite: "Premium", capacidade: 2, valorDiaria: 70);
Suite suite1 = new Suite(tipoSuite: "Basic", capacidade: 3, valorDiaria: 30);
Suite suite2 = new Suite(tipoSuite: "Luxo", capacidade: 6, valorDiaria: 99);

// Cria uma nova reserva, passando a suíte e os hóspedes
Reserva reserva = new Reserva(diasReservados: 5);
reserva.CadastrarSuite(suite);
reserva.CadastrarHospedes(hospedes);

Reserva reserva1 = new Reserva(diasReservados: 7);
reserva1.CadastrarSuite(suite1);
reserva1.CadastrarHospedes(hospedes1);

Reserva reserva2 = new Reserva(diasReservados: 15);
reserva2.CadastrarSuite(suite2);
reserva2.CadastrarHospedes(hospedes2);

// Exibe a quantidade de hóspedes e o valor da diária
Console.WriteLine($"Hóspedes: {reserva.ObterQuantidadeHospedes()}");
Console.WriteLine($"Valor diária: {reserva.CalcularValorDiaria()}");

Console.WriteLine($"Hóspedes: {reserva1.ObterQuantidadeHospedes()}");
Console.WriteLine($"Valor diária: {reserva1.CalcularValorDiaria()}");

Console.WriteLine($"Hóspedes: {reserva2.ObterQuantidadeHospedes()}");
Console.WriteLine($"Valor diária: {reserva2.CalcularValorDiaria()}");