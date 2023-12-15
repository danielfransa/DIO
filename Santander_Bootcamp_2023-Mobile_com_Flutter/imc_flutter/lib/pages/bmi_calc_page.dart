import 'package:app_imc/repository/person_repository.dart';
import 'package:app_imc/service/bmi_calc.dart';
import 'package:app_imc/model/person.dart';
import 'package:flutter/material.dart';

class BmiCalcPage extends StatefulWidget {
  const BmiCalcPage({super.key});

  @override
  State<BmiCalcPage> createState() => _BmiCalcPageState();
}

class _BmiCalcPageState extends State<BmiCalcPage> {
  TextEditingController weightController = TextEditingController();
  TextEditingController heightController = TextEditingController();
  PersonRepository personRepository = PersonRepository();

  final GlobalKey<FormState> _formKey = GlobalKey<FormState>();

  String _infoText = 'Informe seus dados!';

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text("Calculadora IMC"),
      ),
      body: SingleChildScrollView(
        padding: const EdgeInsets.fromLTRB(10.0, 0.0, 10.0, 0.0),
        child: Form(
          key: _formKey,
          child:
              Column(crossAxisAlignment: CrossAxisAlignment.stretch, children: [
            const Icon(
              Icons.person_outline,
              size: 140.0,
              color: Colors.green,
            ),
            TextFormField(
              keyboardType: TextInputType.number,
              decoration: const InputDecoration(
                labelText: 'Peso (Kg)',
                labelStyle: TextStyle(
                  color: Colors.green,
                ),
              ),
              textAlign: TextAlign.center,
              style: const TextStyle(color: Colors.green, fontSize: 28.0),
              controller: weightController,
              validator: (value) {
                if (value == null || value.isEmpty) {
                  return 'Insira seu peso!';
                }
                return null;
              },
            ),
            TextFormField(
              keyboardType: TextInputType.number,
              decoration: const InputDecoration(
                labelText: 'Altura (cm)',
                labelStyle: TextStyle(
                  color: Colors.green,
                ),
              ),
              textAlign: TextAlign.center,
              style: const TextStyle(color: Colors.green, fontSize: 28.0),
              controller: heightController,
              validator: (value) {
                if (value == null || value.isEmpty) {
                  return 'Insira sua altura!';
                }
                return null;
              },
            ),
            Container(
              height: 50.0,
              margin:
                  const EdgeInsets.symmetric(vertical: 8.0, horizontal: 6.0),
              child: ElevatedButton(
                style: ElevatedButton.styleFrom(backgroundColor: Colors.green),
                onPressed: () async {
                  if (_formKey.currentState!.validate()) {
                    Person person = Person();
                    person.setWeight(weightController.text);
                    person.setSize(heightController.text);

                    person.setBmiResult(calculateBMI(person));

                    setState(() {
                      _infoText = person.getBmiResult();
                    });

                    personRepository.salvar(person);
                  }
                },
                child: const Text(
                  'Calcular',
                  style: TextStyle(color: Colors.white, fontSize: 28.0),
                ),
              ),
            ),
            Text(
              _infoText,
              textAlign: TextAlign.center,
              style: const TextStyle(color: Colors.green, fontSize: 28.0),
            )
          ]),
        ),
      ),
    );
  }
}
