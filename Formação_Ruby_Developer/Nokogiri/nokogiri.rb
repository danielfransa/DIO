require 'nokogiri'
require 'net/http'

https = Net::HTTP.new('exemplo.com', 443)
https.use_ssl = true

response = https.get("/")

doc = Nokogiri::HTML(response.body)

desafio = doc.at('p')

if desafio
  puts desafio.content
else
  puts "Não foi encontrado nenhum parágrafo <p>."
end