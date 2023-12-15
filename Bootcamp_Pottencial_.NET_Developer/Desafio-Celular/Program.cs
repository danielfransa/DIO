using DesafioPOO.Models;

// TODO: Realizar os testes com as classes Nokia e Iphone

Console.WriteLine("Smartphone Nokia");
Smartphone nokia = new Nokia(numero: "19982342134", modelo: "N-22",imei: "228737636273836", memoria: 256 );
nokia.Ligar();
nokia.InstalarAplicativo("Whatsapp");

Console.WriteLine("\n");

Console.WriteLine("Smartphone Iphone");
Smartphone iphone = new Iphone(numero: "19982215674", modelo: "Iphone 14 Pro",imei: "228737636273836", memoria: 512 );
iphone.ReceberLigacao();
iphone.InstalarAplicativo("Telegram");

