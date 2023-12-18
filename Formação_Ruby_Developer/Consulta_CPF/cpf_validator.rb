require "cpf_cnpj"

puts 'Digite apenas os números do seu CPF:'
cpf_number = gets.chomp.to_i

def check(cpf_number)
  if CPF.valid?(cpf_number)
    return "O CPF informado é válido"
  else
    return 'O CPF Informado é inválido'
  end
end

puts "#{check(cpf_number)}"
