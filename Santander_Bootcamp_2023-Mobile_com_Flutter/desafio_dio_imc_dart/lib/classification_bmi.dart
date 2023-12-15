String classification(double bmi) {
  late String result;

  if (bmi < 16) {
    result = "Magreza grave";
  } else if (bmi >= 16 && bmi < 17) {
    result = "Magreza Moderada";
  } else if (bmi >= 17 && bmi < 18.5) {
    result = "Magreza leve";
  } else if (bmi >= 18.5 && bmi < 25) {
    result = "Saudável";
  } else if (bmi >= 25 && bmi < 30) {
    result = "Sobrepeso";
  } else if (bmi >= 30 && bmi < 35) {
    result = "Obesidade Grau I";
  } else if (bmi >= 35 && bmi < 40) {
    result = "Obesidade Grau II (severa)";
  } else if (bmi >= 40) {
    result = "Obesidade Grau III (mórbida)";
  } else {
    result = "Restultado não cadastrado na classificação";
  }

  return result;
}
