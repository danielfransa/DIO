import os
import pyaes

# Abrir o arquivo e ser descriptografado
file_name = 'teste.txt.ransomwaretroll'
file = open(file_name, 'rb')
file_data = file.read()
file.close()

# Definir chave encriptação
key = b"testeransomwares"
aes = pyaes.AESModeOfOperationCTR(key)

# Descriptografar arquivo
decrypt_data = aes.decrypt(file_data)

# Removendo arquivo original
os.remove(file_name)

# Salvar o arquivo criptografado
new_file = 'teste.txt'
new_file = open(f'{new_file}', 'wb')
new_file.write(decrypt_data)
new_file.close()