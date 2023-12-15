import 'dart:io';

String getNameInput() {
  late String name;
  do {
    stdout.write("Digite seu nome: ");
    name = stdin.readLineSync()!;
    if (name.isEmpty) {
      print("Nome não pode estar vazio. Tente novamente.");
    }
  } while (name.isEmpty);
  return name;
}

double getHeightInput() {
  stdout.write(
      "Digite sua altura em metros: (Ex: 1.80 - use ponto \".\" ao invéz de vígula\" , \") ");
  late double height;
  do {
    String? input = stdin.readLineSync();
    if (input != null && input.isNotEmpty) {
      try {
        height = double.parse(input);
        break; // Saia do loop se a conversão for bem-sucedida
      } catch (e) {
        print("Altura inválida. Digite um número válido.");
      }
    } else {
      print("Altura não pode estar vazia. Tente novamente.");
    }
  } while (true);
  return height;
}

double getWeightInput() {
  stdout.write(
      "Digite seu peso em quilos: (Ex: 85.800 - use ponto \".\" ao invéz de vígula\" , \") ");
  double weight;
  do {
    String? input = stdin.readLineSync();
    if (input != null && input.isNotEmpty) {
      try {
        weight = double.parse(input);
        break; // Saia do loop se a conversão for bem-sucedida
      } catch (e) {
        print("Peso inválido. Digite um número válido.");
      }
    } else {
      print("Peso não pode estar vazio. Tente novamente.");
    }
  } while (true);
  return weight;
}
