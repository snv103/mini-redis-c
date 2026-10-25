import socket
import struct

def recv_exact(sock, n):
    data = b""
    while len(data) < n:
        left = n - len(data);
        res = sock.recv(left)
        if len(res) == 0:
            raise ConnectionError("server closed\n")
        data += res
    return data

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(("127.0.0.1", 1234))
msg = b"hello"
header = struct.pack("<I", len(msg))
s.sendall(header)
s.sendall(msg)
reply_len = struct.unpack("<I", recv_exact(s, 4))[0]
reply_body = recv_exact(s, reply_len)
print(reply_body)
s.close()

