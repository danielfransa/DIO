import 'package:flutter/material.dart';

class AboutPage extends StatelessWidget {
  const AboutPage({super.key});

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Sobre o aplicativo'),
      ),
      body: Container(
        decoration: const BoxDecoration(
          image: DecorationImage(
              image: AssetImage('lib/images/plano_fundo.jpg'),
              fit: BoxFit.cover),
        ),
        child: Column(
          children: [
            const SizedBox(
              height: 20,
            ),
            Row(children: [
              Expanded(child: Container()),
              Expanded(
                  flex: 2,
                  child: Image.network(
                      "https://hermes.dio.me/tracks/235f721b-49df-4a30-a711-7b947ea63410.png")),
              Expanded(child: Container())
            ]),
            const SizedBox(
              height: 30,
            ),
            const Text(
              "Aprimorando a sua Calculadora de IMC com Flutter",
              style: TextStyle(fontSize: 17, fontWeight: FontWeight.w700),
            ),
            const SizedBox(
              height: 20,
            ),
            const Padding(
              padding: EdgeInsets.symmetric(horizontal: 14, vertical: 0),
              child: Text(
                '''
                Este aplicativo é um projeto para o BootCamp Santander Flutter da DIO. Ele calcula o IMC da pessoa conforme peso e medida, e apresenta uma lista dos pesos coletados que é salvo em um banco SQLite.
                
                A calculadora de IMC é uma ferramenta simples e fácil de usar que pode ajudar você a acompanhar sua saúde e fitness. O IMC é uma medida da relação entre peso e altura que pode ser usada para avaliar se você está no peso ideal.

                O aplicativo também apresenta uma lista dos pesos coletados. Essa lista pode ser usada para acompanhar sua evolução ao longo do tempo.

                Os dados do aplicativo são armazenados em um banco de dados SQLite. O banco de dados SQLite é um banco de dados de código aberto que é fácil de usar e pode ser usado em aplicativos móveis e web.
                ''',
                style: TextStyle(fontSize: 13, fontWeight: FontWeight.w500),
              ),
            ),
          ],
        ),
      ),
    );
  }
}
