class Person {
  String _bmiResult = "";
  late String _weight;
  late String _height;

  Person();

  Person.whithWeight(this._weight, this._height, this._bmiResult);

  void setBmiResult(String name) {
    _bmiResult = name;
  }

  String getBmiResult() {
    return _bmiResult;
  }

  void setWeight(String weigth) {
    _weight = weigth;
  }

  String getWeight() {
    return _weight;
  }

  void setSize(String height) {
    _height = height;
  }

  String getHeight() {
    return _height;
  }
}
