import socket
import struct
import time

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

def read_split_msg(s, msg):
    header = struct.pack("<I", len(msg))
    s.sendall(header + msg[:3])
    time.sleep(1)
    s.sendall(msg[3:])
    reply_len = struct.unpack("<I", recv_exact(s, 4))[0]
    reply_body = recv_exact(s, reply_len)
    return reply_body

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(("127.0.0.1", 1234))
msg = b"hello"
msg2 = b"world"
reply1 = send_and_receive(s, msg)
reply2 = send_and_receive(s, msg2)
print(reply1, reply2)

split_combined = read_split_msg(s, msg)
split_combined2 = read_split_msg(s, msg2)
print(split_combined)
print(split_combined2)
s.close()

