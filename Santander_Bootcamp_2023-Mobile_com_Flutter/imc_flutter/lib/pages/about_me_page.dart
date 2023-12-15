import 'package:flutter/material.dart';

class AboutMePage extends StatelessWidget {
  const AboutMePage({super.key});

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Sobre o Desenvolvedor'),
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
                  flex: 3,
                  child: ClipRRect(
                      borderRadius: BorderRadius.circular(100.0),
                      child: Image.asset('lib/images/foto.jpg'))),
              Expanded(child: Container())
            ]),
            const SizedBox(
              height: 30,
            ),
            const Text(
              "Quem Sou eu:",
              style: TextStyle(fontSize: 17, fontWeight: FontWeight.w700),
            ),
            const SizedBox(
              height: 20,
            ),
            const Padding(
              padding: EdgeInsets.symmetric(horizontal: 14, vertical: 0),
              child: Text(
                '''
                Eu sou Daniel, um profissional com mais de 15 de experiência na indústria, sou formando em administração e engenharia de produção e atualemte estou estudando desenvolvimento de softwares.
                
                Com mais de 15 anos de experiência no setor alimentício, desenvolvi um perfil analítico, capaz de identificar oportunidades de melhoria e implementá-las de forma eficaz.

                Em 2022, decidi realizar uma transição de carreira para o setor de tecnologia, onde estou aprimorando meus conhecimentos como estudante da FATEC - Araras e estagiando na área de desenvolvimento de sistemas.

                Na minha experiência de estágio obtive valiosa experiência na programação com Ruby on Rails, contribuindo ativamente para o desenvolvimento de novas funcionalidades em um sistema voltado para o setor de transportadoras, atualmente estou participando do Bootcamp Santander Mobile com Flutter da Dio e tenho aprendido muito.
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
