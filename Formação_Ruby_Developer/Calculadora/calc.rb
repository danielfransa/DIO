def soma (num1, num2)
  num1 + num2
end

def subtracao (num1, num2)
  num1 - num2
end

def multiplicacao (num1, num2)
  num1 * num2
end

def divisao (num1, num2)
  num1 / num2
end
resultato = ''
loop do
  puts resultato
  puts '**Selecione uma opção:**'
  puts '1- Soma.'
  puts '2- Subtração.'
  puts '3- Multiplicação.'
  puts '4- Divisão.'
  puts '0- Sair.'
  print 'Digite sua escolha: '
  
  opcao = gets.chomp.to_i

  case opcao
  when opcao = 1
    print "Digite o primeiro número: "
    num1 = gets.chomp.to_i
    print "Digite o segundo número: "
    num2 = gets.chomp.to_i
    puts resultato
    puts "O resutado da sua Soma é: #{soma(num1, num2)}"
    puts resultato
    
  when opcao = 2
    print "Digite o primeiro número: "
    num1 = gets.chomp.to_i
    print "Digite o segundo número: "
    num2 = gets.chomp.to_i
    puts resultato
    puts "O resutado da sua Subtração é: #{subtracao(num1, num2)}"
    puts resultato

  when opcao = 3
    print "Digite o primeiro número: "
    num1 = gets.chomp.to_i
    print "Digite o segundo número: "
    num2 = gets.chomp.to_i
    puts resultato
    puts "O resutado da sua Multiplicação é: #{multiplicacao(num1, num2)}"
    puts resultato

  when opcao = 4
    print "Digite o primeiro número: "
    num1 = gets.chomp.to_i
    print "Digite o segundo número: "
    num2 = gets.chomp.to_i
    puts resultato
    puts "O resutado da sua Divisão é: #{divisao(num1, num2)}"
    puts resultato

  when opcao = 0
    puts "Obrigarado por utilizar meu programa, Volte logo!"
    break
    
  else 
    puts resultato
    puts "Opção invalida!"
  end
end

