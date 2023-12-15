enum class Nivel { BASICO, INTERMEDIARIO, AVANÇADO }

data class Usuario(val nome: String, )

data class ConteudoEducacional(var nome: String, val duracao: Int = 60, val nivel: Nivel)

val disciplinas = mutableListOf<ConteudoEducacional>()

data class Formacao(val nome: String, var conteudos: List<ConteudoEducacional>) {

    val inscritos = mutableListOf<Usuario>()
            
    fun matricular(usuario: Usuario) {
        inscritos.add(usuario)
    }
}

fun main() {
    
	val html = ConteudoEducacional("HTML", 40, Nivel.BASICO)
    val css = ConteudoEducacional("CSS", 60, Nivel.INTERMEDIARIO)
    val javaScript = ConteudoEducacional("Java Script", 120, Nivel.AVANÇADO)
    
    disciplinas.add(html)
    disciplinas.add(css)
    disciplinas.add(javaScript)
    
    val frontEnd = Formacao("Front End", disciplinas)
    
    val daniel = Usuario("Daniel")
    val joao = Usuario("João")
    
    frontEnd.matricular(daniel)
    frontEnd.matricular(joao)
    
    val nome = frontEnd.nome
    val cont = frontEnd.conteudos 
    val insc = frontEnd.inscritos
    
    println("Nome do Curso: $nome")
    cont.forEach {
        i -> println(i)
    }
    println("Inscritos para o Curso: $insc")
    
    disciplinas.clear()
    
    println("---------------------------------------------------------------")
    
    val oop = ConteudoEducacional("Orientação a Objeto", 40, Nivel.BASICO)
    val ux = ConteudoEducacional("User Experience", 60, Nivel.INTERMEDIARIO)
    val kotlin = ConteudoEducacional("Kotlin", 120, Nivel.AVANÇADO)
    
    disciplinas.add(oop)
    disciplinas.add(ux)
    disciplinas.add(kotlin)
    
    val mobile = Formacao("Curso Mobile", disciplinas)
    
    val pedro = Usuario("Pedro")
    val maria = Usuario("Maria")
    
    mobile.matricular(pedro)
    mobile.matricular(maria)
    mobile.matricular(daniel)
    
    val nome2 = mobile.nome
    val cont2 = mobile.conteudos 
    val insc2 = mobile.inscritos
    
    println("Nome do Curso: $nome2")
    cont2.forEach {
        i -> println(i)
    }
    println("Inscritos para o Curso: $insc2")
    
}
