# mini-redis-c

A small redis-like key-value server in C, built to learn sockets, networks, event loops, data structures.
WIP

## Done
- TCP server on port 1234 echoing length-prefixed messages.
- Use core Linux system calls like `socket()`, `bind()`, `listen()`, `accept()`, `read()` and `write()`.
- `read_full` and `write_all` handle partial read and write.

## Next steps
- Including `poll()` so multiple clients can connect at once
- Avoid server from crashing when client gets disconnected
- Implementing a hash table with GET and SET commands

## Build and run
Requires Linux or Windows Subsystem for Linux (WSL) for system calls. I used WSL2 Ubuntu.

```
gcc -Wall -Wextra -g -o server src/server.c
./server
```
The server listens on port 1234. On second terminal, send a message:

```
python3 tests/tests_clients.py
```