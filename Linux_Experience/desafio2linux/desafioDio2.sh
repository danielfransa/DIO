#!/bin/bash

echo 'Inicando o Script...'

##Atualizando a máquina
apt-get update
apt-get upgrade -y

## Instalando Servidor HTML Apache
apt-get install apache2 -y

## Instalando Unzip
apt-get install unzip -y

## Baixar Aplicalção do Git
cd /tmp
wget https://github.com/denilsonbonatti/linux-site-dio/archive/refs/heads/main.zip

## Descompactar arquivo baixado
unzip main.zip
cd linux-site-dio-main

## Copiar arquivos para pasta padrão Apache
cp -R * /var/www/html/


echo 'Finalizando o Script!!!'



