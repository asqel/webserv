import socket

HOST = 'localhost'
PORT = 8000

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect((HOST, PORT))
print( 'Connexion vers ' + HOST + ':' + str(PORT) + ' reussie.')

message = 'Hello, world\r\n'.encode("utf-8")
print('Envoi de :' + message.decode("utf-8"))
n = client.send(message)
if (n != len(message)):
        print('Erreur envoi.')
else:
        print('Envoi ok.')

print('Reception...')
donnees = client.recv(1024)
print('Recu :', donnees)

print('Deconnexion.')
client.close()
