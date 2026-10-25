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

def send_and_receive(s, msg):
    header = struct.pack("<I", len(msg))
    s.sendall(header + msg)
    reply_len = struct.unpack("<I", recv_exact(s, 4))[0]
    reply_body = recv_exact(s, reply_len)
    return reply_body


s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(("127.0.0.1", 1234))
msg = b"hello"
msg2 = b"world"
print(send_and_receive(s, msg), send_and_receive(s, msg2))
s.close()

