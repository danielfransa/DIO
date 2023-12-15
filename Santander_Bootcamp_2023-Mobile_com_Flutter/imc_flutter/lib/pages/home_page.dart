import 'package:app_imc/pages/about_me_page.dart';
import 'package:app_imc/pages/about_page.dart';
import 'package:app_imc/pages/bmi_calc_page.dart';
import 'package:app_imc/pages/bmi_list_page.dart';
import 'package:flutter/material.dart';

class HomePage extends StatefulWidget {
  const HomePage({super.key});

  @override
  State<HomePage> createState() => _HomePageState();
}

class _HomePageState extends State<HomePage> {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text("Aplicativo Saúde!"),
      ),
      body: SafeArea(
        child: Container(
          decoration: const BoxDecoration(
              image: DecorationImage(
                  image: AssetImage('lib/images/plano_fundo.jpg'),
                  fit: BoxFit.cover)),
          child: Column(
            children: [
              const SizedBox(
                height: 85,
              ),
              Padding(
                padding: const EdgeInsets.symmetric(horizontal: 8, vertical: 0),
                child: Material(
                  color: const Color.fromRGBO(225, 200, 255, 1),
                  elevation: 5,
                  shadowColor: Colors.black54,
                  borderRadius: const BorderRadius.all(Radius.circular(18)),
                  child: Expanded(
                    child: ListTile(
                        leading: const Icon(Icons.info),
                        title: const Text(
                          "Sobre o Aplicativo",
                          style: TextStyle(
                              fontSize: 18, fontWeight: FontWeight.w600),
                        ),
                        onTap: () {
                          Navigator.push(
                              context,
                              MaterialPageRoute(
                                  builder: (context) => const AboutPage()));
                        }),
                  ),
                ),
              ),
              const SizedBox(
                height: 30,
              ),
              Padding(
                padding: const EdgeInsets.symmetric(horizontal: 8, vertical: 0),
                child: Material(
                  color: const Color.fromRGBO(235, 185, 255, 1),
                  elevation: 5,
                  shadowColor: Colors.black54,
                  borderRadius: const BorderRadius.all(Radius.circular(18)),
                  child: ListTile(
                      leading: const Icon(Icons.calculate_rounded),
                      title: const Text(
                        "Calculadora IMC",
                        style: TextStyle(
                            fontSize: 18, fontWeight: FontWeight.w600),
                      ),
                      onTap: () {
                        Navigator.push(
                            context,
                            MaterialPageRoute(
                                builder: (context) => const BmiCalcPage()));
                      }),
                ),
              ),
              const SizedBox(
                height: 30,
              ),
              Padding(
                padding: const EdgeInsets.symmetric(horizontal: 8, vertical: 0),
                child: Material(
                  color: const Color.fromRGBO(200, 255, 255, 1),
                  elevation: 5,
                  shadowColor: Colors.black54,
                  borderRadius: const BorderRadius.all(Radius.circular(18)),
                  child: ListTile(
                      leading: const Icon(Icons.list_alt_outlined),
                      title: const Text(
                        "Histórico de IMC",
                        style: TextStyle(
                            fontSize: 18, fontWeight: FontWeight.w600),
                      ),
                      onTap: () {
                        Navigator.push(
                            context,
                            MaterialPageRoute(
                                builder: (context) => const BmiListPage()));
                      }),
                ),
              ),
              const SizedBox(
                height: 30,
              ),
              Padding(
                padding: const EdgeInsets.symmetric(horizontal: 8, vertical: 0),
                child: Material(
                  color: const Color.fromRGBO(180, 225, 235, 1),
                  elevation: 5,
                  shadowColor: Colors.black54,
                  borderRadius: const BorderRadius.all(Radius.circular(18)),
                  child: ListTile(
                      leading: const Icon(Icons.developer_board),
                      title: const Text(
                        "Sobre o Desenvolvedor",
                        style: TextStyle(
                            fontSize: 18, fontWeight: FontWeight.w600),
                      ),
                      onTap: () {
                        Navigator.push(
                            context,
                            MaterialPageRoute(
                                builder: (context) => const AboutMePage()));
                      }),
                ),
              ),
              const SizedBox(
                height: 20,
              )
            ],
          ),
        ),
      ),
    );
  }
}
