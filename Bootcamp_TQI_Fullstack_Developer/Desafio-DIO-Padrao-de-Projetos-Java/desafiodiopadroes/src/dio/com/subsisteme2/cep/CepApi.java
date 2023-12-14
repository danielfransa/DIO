package dio.com.subsisteme2.cep;

import dio.com.singleton.SingletonEager;

public class CepApi {

    private static CepApi instacia = new CepApi();

    private CepApi() {
        super();
    }

    public static CepApi getInstacia() {
        return instacia;
    }

    public String recuperarCidade(String cep) {
        return "Araras";
    }

    public String recuperarEstado(String cep) {
        return "SP";
    }
}
