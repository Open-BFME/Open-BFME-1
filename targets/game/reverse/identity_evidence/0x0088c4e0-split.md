# 0x0088C4E0 is an initializer lookup, not the purecall reporter

Decode 92 bytes from the retail image with
`python3 tools/dis_retail.py 0x0088C4E0 92`.

The first body calls `GetModuleHandleA(0)` and `GetProcAddress` for
`?PostStaticInit@Debug@@CAXXZ`. Its `jne` at 0x0088C4F6 selects the resolved
address in EAX; the other arm loads `Debug::PostStaticInit` at 0x00C8AF60.
Both arms end at `jmp eax` at 0x0088C4FD. The next byte, 0x0088C4FF, is
`int3`. No path from this body reaches 0x0088C500.

The distinct body at 0x0088C500 calls the debug recorder and reporter. It
passes the retail string at 0x011334F4, "Pure virtual function called.", and
ends with `ret` at 0x0088C53B. The old 92-byte dump claim and its banked
source crossed the `int3` and combined both bodies under `purecallHandler`.
That name therefore cannot identify the first 31-byte body. The replacement
keeps its address token while the second body is converted separately.
