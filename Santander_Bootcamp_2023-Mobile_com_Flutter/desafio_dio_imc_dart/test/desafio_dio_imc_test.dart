import 'dart:io';

import 'package:desafio_dio_imc/calculator_bmi.dart';
import 'package:desafio_dio_imc/classification_bmi.dart';
import 'package:desafio_dio_imc/person.dart';
import 'package:mockito/mockito.dart';

import 'package:test/test.dart';

void main() {
  test('Teste de cálculo de IMC', () {
    Person person = Person();
    person.setName("Alice");
    person.setSize(1.70);
    person.setWeight(65.0);

    double bmi = calculateBMI(person);

    expect(bmi, closeTo(22.49, 0.01));
  });

  test('Teste de classificação de IMC', () {
    expect(classification(15), equals("Magreza grave"));
    expect(classification(16.5), equals("Magreza Moderada"));
    expect(classification(17.5), equals("Magreza leve"));
    expect(classification(20.0), equals("Saudável"));
    expect(classification(27.0), equals("Sobrepeso"));
    expect(classification(33.0), equals("Obesidade Grau I"));
    expect(classification(37.0), equals("Obesidade Grau II (severa)"));
    expect(classification(41.0), equals("Obesidade Grau III (mórbida)"));
  });
}
