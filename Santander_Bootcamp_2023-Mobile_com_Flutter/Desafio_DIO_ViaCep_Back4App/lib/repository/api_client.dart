import 'dart:convert';

import 'package:appviacep/models/agenda_model.dart';
import 'package:dio/dio.dart';
import 'package:flutter/foundation.dart';
import 'package:flutter/services.dart';

class ApiClient {
  final Dio _dio = Dio();

  Future<Map<String, String>> readKeys() async {
    try {
      String jsonString = await rootBundle.loadString('assets/keys.json');
      Map<String, dynamic> keys = json.decode(jsonString);
      Map<String, String> stringKeys = keys.map((key, value) =>
          MapEntry(key, value.toString())); // Convert all values to strings

      return stringKeys;
    } catch (e) {
      if (kDebugMode) {
        print('Error reading file: $e');
      }
      return <String,
          String>{}; // Return an empty map or handle the error accordingly
    }
  }

  Future<agendaModel> getAgendaData() async {
    // Definir os headers da API
    Map<String, String> headers = await readKeys();

    // Definir a URL da API
    String url = "https://parseapi.back4app.com/classes/agendaData";

    // Realizar a requisição HTTP
    Response response = await _dio.get(url, options: Options(headers: headers));

    // Verificar se a resposta foi bem-sucedida
    if (response.statusCode == 200) {
      // A resposta foi bem-sucedida, retornar os dados
      return agendaModel.fromJson(response.data);
    } else {
      // A resposta não foi bem-sucedida, retornar um erro
      throw Exception(response.statusCode);
    }
  }
}
