# Phishing para captura de senhas do Facebook

### Ferramentas
 - setoolkit
 - Foi clonado a ferramnta do endereço: [social-engineer-toolkit](https://github.com/trustedsec/social-engineer-toolkit) 


### Configurando o Phishing no Kali Linux
 - Acesso root: Como foi instalado com venv no meu ambiente Arch linux utilizei o comando: sudo 
 - Iniciando o setoolkit: sudo ./.venv/bin/python setoolkit

 - Tipo de ataque: Social-Engineering Attacks
    ![Primeira-Tela](imagens/Img_01.png)
 - Vetor de ataque: Web Site Attack Vectors
    ![Segunda-Tela](imagens/Img_02.png)
 - Método de ataque: Credential Harvester Attack Method
    ![Terceira-Tela](imagens/Img_03.png)
 - Método de ataque: Site Cloner
    ![Quarta-Tela](imagens/Img_04.png)
 - Obtendo o endereço da máquina: A propria ferramenta já encontra o IP da máquina e ajusta o mesmo, porem pode utilizar (ip a) no Arch se precisar:
    ![Quinta-Tela](imagens/Img_05.png)
 - URL para clone: http://www.facebook.com
    ![Sexta-Tela](imagens/Img_06.png)
 - Apos o servidor começa a rodar na porta 80 do nosso endereço IP:
    ![Sétima-Tela](imagens/Img_07.png)
 - Vítima acessa a página fake e tem seus daos capturados:
    ![Oitava-Tela](imagens/Img_08.png)
    