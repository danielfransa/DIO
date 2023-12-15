import br.com.dio.desafio.dominio.Bootcamp;
import br.com.dio.desafio.dominio.Curso;
import br.com.dio.desafio.dominio.Dev;
import br.com.dio.desafio.dominio.Mentoria;

import java.time.LocalDate;

public class Main {
    public static void main(String[] args) {
        Curso curso1 = new Curso();
        curso1.setTitulo("HTML");
        curso1.setDescricao("Curso de HTML do básico ao Avançado");
        curso1.setCargaHoraria(5);

        Curso curso2 = new Curso();
        curso2.setTitulo("CSS");
        curso2.setDescricao("Curso de CSS do básico ao Avançado");
        curso2.setCargaHoraria(7);

        Curso curso3 = new Curso();
        curso3.setTitulo("JavaScript");
        curso3.setDescricao("Curso de JS do básico ao Avançado");
        curso3.setCargaHoraria(10);

        Mentoria mentoria1 = new Mentoria();
        mentoria1.setTitulo("Mentoria Front-End");
        mentoria1.setDescricao("Explicando o que é um Desenvolvedor Front-End");
        mentoria1.setData(LocalDate.now());

        Bootcamp bcFrontEnd  = new Bootcamp();
        bcFrontEnd.setNome("Bootcamp Front-End");
        bcFrontEnd.setDescricao("Descrição Bootcamp Front-End");
        bcFrontEnd.getConteudos().add(curso1);
        bcFrontEnd.getConteudos().add(curso2);
        bcFrontEnd.getConteudos().add(curso3);
        bcFrontEnd.getConteudos().add(mentoria1);

        Curso curso4 = new Curso();
        curso4.setTitulo("Banco de dados com My SQL");
        curso4.setDescricao("Curso de Banco de Dados do básico ao Avançado com MySQL");
        curso4.setCargaHoraria(10);

        Curso curso5 = new Curso();
        curso5.setTitulo("Curso Java Completo");
        curso5.setDescricao("Curso de Java do básico ao Avançado");
        curso5.setCargaHoraria(40);

        Curso curso6 = new Curso();
        curso6.setTitulo("Curso Java Spring-Boot");
        curso6.setDescricao("Potencialize o Java com Spring Boot");
        curso6.setCargaHoraria(25);

        Mentoria mentoria2 = new Mentoria();
        mentoria2.setTitulo("Mentoria Back-End");
        mentoria2.setDescricao("Explicando o que é um Desenvolvedor Back-End");
        mentoria2.setData(LocalDate.now());

        Bootcamp bcBackEnd = new Bootcamp();
        bcBackEnd.setNome("Bootcamp Back-End");
        bcBackEnd.setDescricao("Descrição Bootcamp Back-End");
        bcBackEnd.getConteudos().add(curso4);
        bcBackEnd.getConteudos().add(curso5);
        bcBackEnd.getConteudos().add(curso6);
        bcBackEnd.getConteudos().add(mentoria2);

        Bootcamp bcFullStack = new Bootcamp();
        bcFullStack.setNome("Bootcamp Full Stack");
        bcFullStack.setDescricao("Descrição Bootcamp Full Stack");
        bcFullStack.getConteudos().add(curso1);
        bcFullStack.getConteudos().add(curso2);
        bcFullStack.getConteudos().add(curso3);
        bcFullStack.getConteudos().add(mentoria1);
        bcFullStack.getConteudos().add(curso4);
        bcFullStack.getConteudos().add(curso5);
        bcFullStack.getConteudos().add(curso6);
        bcFullStack.getConteudos().add(mentoria2);


        Dev devMaria = new Dev();
        devMaria.setNome("Maria");
        devMaria.inscreverBootcamp(bcFrontEnd);
        System.out.println("Conteúdos Inscritos Maria:" + devMaria.getConteudosInscritos());
        devMaria.progredir();
        devMaria.progredir();
        System.out.println("-");
        System.out.println("Conteúdos Inscritos Maria:" + devMaria.getConteudosInscritos());
        System.out.println("Conteúdos Concluídos Maria:" + devMaria.getConteudosConcluidos());
        System.out.println("XP:" + devMaria.calcularTotalXp());

        System.out.println("-------");

        Dev devJoao = new Dev();
        devJoao.setNome("João");
        devJoao.inscreverBootcamp(bcBackEnd);
        System.out.println("Conteúdos Inscritos João:" + devJoao.getConteudosInscritos());
        devJoao.progredir();
        devJoao.progredir();
        System.out.println("-");
        System.out.println("Conteúdos Inscritos João:" + devJoao.getConteudosInscritos());
        System.out.println("Conteúdos Concluídos João:" + devJoao.getConteudosConcluidos());
        System.out.println("XP:" + devJoao.calcularTotalXp());


        System.out.println("-------");

        Dev devDaniel = new Dev();
        devDaniel.setNome("Daniel");
        devDaniel.inscreverBootcamp(bcFullStack);
        System.out.println("Conteúdos Inscritos Daniel:" + devDaniel.getConteudosInscritos());
        devDaniel.progredir();
        devDaniel.progredir();
        devDaniel.progredir();
        devDaniel.progredir();
        devDaniel.progredir();
        devDaniel.progredir();
        devDaniel.progredir();
        System.out.println("-");
        System.out.println("Conteúdos Inscritos Daniel:" + devDaniel.getConteudosInscritos());
        System.out.println("Conteúdos Concluídos Daniel:" + devDaniel.getConteudosConcluidos());
        System.out.println("XP:" + devDaniel.calcularTotalXp());




    }
}