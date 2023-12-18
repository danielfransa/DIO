numeros = []
i = 1

3.times do |i|
  print "Digite o #{i + 1}º número: "
  numeros.push(gets.chomp.to_i)
end

puts "Números Digitados: #{numeros}"

numeros.map! { |num| num ** 3 }

puts "Números elevados ao cubo: #{numeros}"
