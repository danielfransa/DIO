package one.digitalinnovation.spring.service.impl;

import one.digitalinnovation.spring.model.Cliente;
import one.digitalinnovation.spring.model.ClienteRepository;
import one.digitalinnovation.spring.model.Endereco;
import one.digitalinnovation.spring.model.EnderecoRepository;
import one.digitalinnovation.spring.service.ClienteService;
import one.digitalinnovation.spring.service.ViaCepService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.beans.factory.annotation.Autowire;

import java.security.PrivateKey;
import java.util.Optional;

/**
 * Implementação da <b>Strategy</b> {@link ClienteService} , a qual pode ser
 * injetada no Spring (via {@link Autowire}). Com isso, como essa classe é um
 * {@link Service}, ela será tratada como um <b>Singleton</b>.
 *
 *
 */
@Service
public class ClienteServiceImpl implements ClienteService {

    //Singleton: Injetar os componentes do Spring com @Autowired.
    @Autowired
    private ClienteRepository clienteRepository;
    @Autowired
    private EnderecoRepository enderecoRepository;
    @Autowired
    private ViaCepService viaCepService;
    //Strategy: Implementar os métodos definidos na interface.
    //Facade: Abstrair integrações com subsistemas, provendo uma interface simples.

    @Override
    public Iterable<Cliente> buscarTodos() {
        return clienteRepository.findAll();
    }

    @Override
    public Cliente buscarPorId(Long id) {
        Optional<Cliente> cliente = clienteRepository.findById(id);
        return cliente.get();
    }

    @Override
    public void inserir(Cliente cliente) {
        salvarClienteComCep(cliente);

    }

    @Override
    public void atualizar(Long id, Cliente cliente) {
        // Buscar Clientes por ID, caso exista.
        Optional<Cliente> clienteBd = clienteRepository.findById(id);
        if (clienteBd.isPresent()){
            salvarClienteComCep(cliente);
        }
    }
    @Override
    public void deletar(Long id) {
        //Deletar Cliente por ID.
        clienteRepository.deleteById(id);
    }

    private void salvarClienteComCep(Cliente cliente) {
        //Verificar se o endereço do Cliente já existe (pelo CEP).
        String cep = cliente.getEndereco().getCep();
        Endereco endereco = enderecoRepository.findById(cep).orElseGet(() -> {
            // Caso não exista, integrar com o ViaCEP e persistir o retorno.
            Endereco novoEndereco = viaCepService.consultarCep(cep);
            enderecoRepository.save(novoEndereco);
            return novoEndereco;
        });
        cliente.setEndereco(endereco);
        // Inserir Cliente, vinculando o Endereço (novo ou existente).
        clienteRepository.save(cliente);
    }


}
