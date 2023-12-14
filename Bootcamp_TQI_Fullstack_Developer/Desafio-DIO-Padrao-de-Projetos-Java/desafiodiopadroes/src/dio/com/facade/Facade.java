package dio.com.facade;

import dio.com.subsistema1.crm.CrmServices;
import dio.com.subsisteme2.cep.CepApi;

public class Facade {

    public void migrarCliente(String nome, String cep){
        String cidade = CepApi.getInstacia().recuperarCidade(cep);
        String estado = CepApi.getInstacia().recuperarEstado(cep);

        CrmServices.gravarCliente(nome, cep, cidade, estado);
    }
}
