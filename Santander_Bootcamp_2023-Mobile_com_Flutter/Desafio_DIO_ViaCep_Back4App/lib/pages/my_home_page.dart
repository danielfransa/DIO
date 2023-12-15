import 'package:appviacep/models/agenda_model.dart';
import 'package:appviacep/pages/agenda_datails_page.dart';
import 'package:appviacep/repository/api_client.dart';
import 'package:flutter/material.dart';

class MyHomePage extends StatefulWidget {
  const MyHomePage({super.key, required this.title});

  final String title;

  @override
  State<MyHomePage> createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  late Future<agendaModel> _agendaData;

  @override
  void initState() {
    super.initState();

    // Obter os dados da API
    ApiClient apiClient = ApiClient();
    _agendaData = apiClient.getAgendaData();
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
        appBar: AppBar(
          backgroundColor: Theme.of(context).colorScheme.inversePrimary,
          title: const Text('Agenda'),
        ),
        body: FutureBuilder<agendaModel>(
          future: _agendaData,
          builder: (context, snapshot) {
            if (snapshot.hasData) {
              return ListView.builder(
                  itemCount: snapshot.data!.results!.length,
                  itemBuilder: (context, index) {
                    var item = snapshot.data!.results![index];
                    return ListTile(
                      title: Text(item.name!),
                      subtitle: Text(item.phoneNumber!),
                      onTap: () {
                        Navigator.push(
                          context,
                          MaterialPageRoute(
                            builder: (context) => AgendaDetailsPage(item: item),
                          ),
                        );
                      },
                    );
                  });
            } else if (snapshot.hasError) {
              // Ocorreu um erro ao obter os dados da API
              return const Center(
                  child: Text('Ocorreu um erro ao carregar os dados'));
            } else {
              // Os dados da API ainda não foram obtidos
              return const Center(child: CircularProgressIndicator());
            }
          },
        ));
  }
}
