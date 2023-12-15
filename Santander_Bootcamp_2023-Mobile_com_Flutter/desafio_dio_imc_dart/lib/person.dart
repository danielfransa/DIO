class Person {
  String _name = "";
  late double _weight;
  late double _height;

  void setName(String name) {
    _name = name;
  }

  String getName() {
    return _name;
  }

  void setWeight(double weigth) {
    _weight = weigth;
  }

  double getWeight() {
    return _weight;
  }

  void setSize(double height) {
    _height = height;
  }

  double getHeight() {
    return _height;
  }
}
