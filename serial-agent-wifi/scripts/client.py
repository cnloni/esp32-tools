#! /usr/bin/env python3
import sys
import os
import fcntl
import socket
import json


def set_nonblocking(fd):
    orig_fl = fcntl.fcntl(fd, fcntl.F_GETFL)
    fcntl.fcntl(fd, fcntl.F_SETFL, orig_fl | os.O_NONBLOCK)


def main(jsonfile):
    with open(jsonfile) as fp:
        conf = json.load(fp)
    ip = conf['ip']
    port = conf['port'] if 'port' in conf else 80
    server = (ip, port)

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
        set_nonblocking(sys.stdin)
        sock.settimeout(1)
        sock.connect(server)
        sock.setblocking(False)
        while True:
            conin = sys.stdin.readline()
            if conin != "":
                sock.sendall(bytes((conin).encode("utf-8")))
                if conin.startswith('cnl:quit'):
                    break
            try:
                sockin = sock.recv(4096).decode()
                if sockin != "":
                    print(sockin, end="")
            except BlockingIOError:
                continue


if len(sys.argv) > 1:
    conf = sys.argv[1]
else:
    conf = 'config.json'
main(conf)
