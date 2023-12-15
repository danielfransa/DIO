import 'dart:math';

import 'package:app_imc/model/person.dart';

String calculateBMI(Person person) {
  double height = double.parse(person.getHeight());
  double heightMeter = height / 100;
  double weight = double.parse(person.getWeight());

  double bmi = weight / pow(heightMeter, 2);
  return classification(bmi);
}

String classification(double bmi) {
  late String result;

  if (bmi < 16) {
    result = "Magreza grave (${bmi.toStringAsPrecision(4)})";
  } else if (bmi >= 16 && bmi < 17) {
    result = "Magreza Moderada (${bmi.toStringAsPrecision(4)})";
  } else if (bmi >= 17 && bmi < 18.5) {
    result = "Magreza leve (${bmi.toStringAsPrecision(4)})";
  } else if (bmi >= 18.5 && bmi < 25) {
    result = "Saudável (${bmi.toStringAsPrecision(4)})";
  } else if (bmi >= 25 && bmi < 30) {
    result = "Sobrepeso (${bmi.toStringAsPrecision(4)})";
  } else if (bmi >= 30 && bmi < 35) {
    result = "Obesidade Grau I (${bmi.toStringAsPrecision(4)})";
  } else if (bmi >= 35 && bmi < 40) {
    result = "Obesidade Grau II (severa) (${bmi.toStringAsPrecision(4)})";
  } else if (bmi >= 40) {
    result = "Obesidade Grau III (mórbida) (${bmi.toStringAsPrecision(4)})";
  } else {
    result = "Restultado não cadastrado na classificação";
  }

  return result;
}
