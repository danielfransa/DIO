require_relative 'produto'
require_relative 'mercado'
 
produto = Produto.new
produto.nome = 'Banana'
produto.preco = 5.50
 
Mercado.new(produto.nome, produto.preco).comprar