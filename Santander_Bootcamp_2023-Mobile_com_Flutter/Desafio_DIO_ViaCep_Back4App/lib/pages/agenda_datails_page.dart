import 'package:appviacep/models/agenda_model.dart';
import 'package:flutter/material.dart';

class AgendaDetailsPage extends StatelessWidget {
  Results item;

  AgendaDetailsPage({required this.item});

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Detalhes'),
      ),
      body: Padding(
        padding: const EdgeInsets.all(16.0),
        child: Column(
          children: [
            Text(item.name!),
            Text(item.phoneNumber!),
            Text(item.cep!),
            Text(item.logradouro!),
            Text(item.complemento!),
            Text(item.bairro!),
            Text(item.localidade!),
            Text(item.uf!),
            Text(item.number!),
          ],
        ),
      ),
    );
  }
}
