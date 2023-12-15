import 'dart:math';

import 'package:desafio_dio_imc/person.dart';

double calculateBMI(Person person) {
  double bmi = person.getWeight() / pow(person.getHeight(), 2);
  return bmi;
}
