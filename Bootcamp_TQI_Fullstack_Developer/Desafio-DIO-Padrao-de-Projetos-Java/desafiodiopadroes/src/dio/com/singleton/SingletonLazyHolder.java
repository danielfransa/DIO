package dio.com.singleton;

public class SingletonLazyHolder {

    private static class  InstanceHolder {
        public static SingletonLazyHolder instacia = new SingletonLazyHolder();
    }

    private SingletonLazyHolder() {
        super();
    }

    public static SingletonLazyHolder getInstacia() {
        return InstanceHolder.instacia;
    }
}
