import socket
import struct

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(("127.0.0.1", 1234))
msg = b"hello"
header = struct.pack("<I", len(msg))
s.sendall(header)
s.sendall(msg)
full_amount = len(header) + len(msg)
reply = s.recv(full_amount)
print(reply)
s.close()

