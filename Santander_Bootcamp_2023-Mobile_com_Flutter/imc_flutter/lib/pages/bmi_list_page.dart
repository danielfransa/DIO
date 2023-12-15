import 'package:app_imc/model/person.dart';
import 'package:app_imc/repository/person_repository.dart';
import 'package:flutter/material.dart';

class BmiListPage extends StatefulWidget {
  const BmiListPage({super.key});

  @override
  State<BmiListPage> createState() => _BmiListPageState();
}

class _BmiListPageState extends State<BmiListPage> {
  List<Person> list = [];
  PersonRepository personRepository = PersonRepository();

  @override
  initState() {
    super.initState();

    _loadList();
  }

  Future<void> _loadList() async {
    list = await personRepository.obterDados();

    setState(() {});
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text("Lista Medições"),
      ),
      body: Container(
        decoration: const BoxDecoration(
          image: DecorationImage(
              image: AssetImage('lib/images/plano_fundo.jpg'),
              fit: BoxFit.cover),
        ),
        child: ListView.builder(
            itemCount: list.length,
            itemBuilder: (context, index) {
              return ListTile(
                title: Text("Meu IMC é: ${list[index].getBmiResult()}"),
                subtitle: Text(
                    "Para o Peso: ${list[index].getWeight()} e a Altura de: ${list[index].getHeight()}"),
              );
            }),
      ),
    );
  }
}
