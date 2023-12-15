import 'package:app_imc/model/person.dart';
import 'package:app_imc/repository/database_helper.dart';

class PersonRepository {
  Future<List<Person>> obterDados() async {
    List<Person> person = [];
    var db = await DatabaseHelper().obterDatabase();
    var result = await db.rawQuery('SELECT weight, height, bmi FROM person');

    for (var element in result) {
      person.add(Person.whithWeight(
        element["weight"].toString(),
        element["height"].toString(),
        element["bmi"].toString(),
      ));
    }

    return person;
  }

  Future<void> salvar(Person person) async {
    var db = await DatabaseHelper().obterDatabase();
    await db.rawInsert('INSERT INTO person (weight, height, bmi) values(?,?,?)',
        [person.getWeight(), person.getHeight(), person.getBmiResult()]);
  }
}
