package dio.com;

import dio.com.facade.Facade;
import dio.com.singleton.SingletonEager;
import dio.com.singleton.SingletonLazy;
import dio.com.singleton.SingletonLazyHolder;
import dio.com.strategy.*;

public class Test {

    public static void main(String [] args) {
        // teste Singleton

        SingletonLazy lazy = SingletonLazy.getInstacia();
        System.out.println(lazy);
        lazy = SingletonLazy.getInstacia();
        System.out.println(lazy);

        SingletonEager Eager = SingletonEager.getInstacia();
        System.out.println(Eager);
        Eager = SingletonEager.getInstacia();
        System.out.println(Eager);

        SingletonLazyHolder LazyHolder = SingletonLazyHolder.getInstacia();
        System.out.println(LazyHolder);
        LazyHolder = SingletonLazyHolder.getInstacia();
        System.out.println(LazyHolder);

        // Teste Strategy

        Comportamento normal = new ComportamentoNormal();
        Comportamento defensivo = new ComportamentoDefensivo();
        Comportamento agressivo = new ComportamentoAgressivo();

        Robo robo = new Robo();
        robo.setComportamento(normal);
        robo.mover();
        robo.mover();
        robo.setComportamento(defensivo);
        robo.mover();
        robo.setComportamento(agressivo);
        robo.mover();
        robo.mover();
        robo.mover();

        // Facade

        Facade facade = new Facade();
        facade.migrarCliente("Daniel", "13.606-020");
    }
}
