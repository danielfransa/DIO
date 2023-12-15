import 'package:desafio_dio_imc/calculator_bmi.dart';
import 'package:desafio_dio_imc/classification_bmi.dart';
import 'package:desafio_dio_imc/data_inputs.dart';
import 'package:desafio_dio_imc/person.dart';

void main(List<String> arguments) {
  print("Calculadora de IMC");
  print("----------------------------------");

  String name = getNameInput();
  double height = getHeightInput();
  double weight = getWeightInput();

  Person person = Person();
  person.setName(name);
  person.setSize(height);
  person.setWeight(weight);

  double bmi = calculateBMI(person);

  String result = classification(bmi);

  String formattedBMI = bmi.toStringAsFixed(2);

  print("----------------------------------");
  print("Resultados:");
  print("Olá: ${person.getName()}");
  print("Sua altura sendo: ${person.getHeight()} metros");
  print("E seu peso sendo: ${person.getWeight()} quilos");
  print("Seu IMC é: $formattedBMI");
  print("Sua Classificação é: $result");
  print("----------------------------------");
}
