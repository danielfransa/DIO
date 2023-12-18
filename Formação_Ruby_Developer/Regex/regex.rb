texto1 = 'Olá, tudo bem? Meu whats app é:'
texto = '(99) 9 9999-9999'

match = /\(\d{2}\) \d \d{4}-\d{4}/.match(texto)

if match
  puts "#{texto1} #{match[0]}"
else
  puts "Número de telefone inválido pelo padrão regex."
end