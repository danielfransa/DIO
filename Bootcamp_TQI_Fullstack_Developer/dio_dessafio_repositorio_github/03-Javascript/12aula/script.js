//Funções sintaxes e outras restrições
// Alunos aprovados ou não.
const alunos = [
	{
		nome: 'João',
		nota: 4,
		turma: '1B',
	},
	{
		nome: 'Sofia',
		nota: 9,
		turma: '1B',
	},
	{
		nome: 'Paulo',
		nota: 6,
		turma: '2C',
	},
];

    function alunosAprovados(nome, media){
        let aprovados = [];

        for (let i = 0; i < alunos.length; i++) {
            let {nota, nome} = alunos[i];

            if (nota >= media) {
                aprovados.push(nome, nota);
            }
        }

        return aprovados;

    }

    console.log(alunosAprovados(alunos, 5));