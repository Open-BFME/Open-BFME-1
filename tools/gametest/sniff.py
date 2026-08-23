#!/usr/bin/env python3
"""sniff.py <iface> <out.log> — log UDP headers seen on one interface.

tcpdump is not installed and this only needs five fields, so it reads frames
straight off an AF_PACKET socket. It runs inside a network namespace, where
CAP_NET_RAW comes from the user namespace rather than from real privilege.
"""
import socket
import struct
import sys
import time

iface, out = sys.argv[1], sys.argv[2]
s = socket.socket(socket.AF_PACKET, socket.SOCK_RAW, socket.ntohs(0x0003))
s.bind((iface, 0))
with open(out, "w", buffering=1) as f:
    while True:
        try:
            frame = s.recv(65535)
        except OSError as e:
            # the interface goes down when the namespace is torn down; anything
            # else is worth seeing rather than losing the rest of the capture
            f.write(f"# recv error: {e}\n")
            time.sleep(0.5)
            continue
        if len(frame) < 34 or frame[12:14] != b"\x08\x00":
            continue                                  # IPv4 ethertype only
        ip = frame[14:]
        ihl = (ip[0] & 0x0F) * 4
        if ip[9] != 17:                               # UDP only
            continue
        src = socket.inet_ntoa(ip[12:16])
        dst = socket.inet_ntoa(ip[16:20])
        sport, dport, ulen = struct.unpack_from(">HHH", ip, ihl)
        f.write(f"{time.time():.2f} {src}:{sport} -> {dst}:{dport} len={ulen-8}\n")
