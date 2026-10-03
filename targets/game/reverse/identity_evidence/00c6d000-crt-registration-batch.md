# Five opaque CRT callback-registration entries

Retail startup009F72C4 passes begin VA012A5000 and end VA012A617C to
_initterm at009F73EE (pushes009F73E9/009F73E4 respectively). That callee
routes through009F7F92 to the MSVCR71 import. The following native table
cells lie in that half-open range and directly hold these entry VAs:

| Entry RVA | CRT cell VA | Callback RVA | Existing callback name |
| --- | --- | --- | --- |
| 00C6D000 | 012A5BE8 | 00C70C40 | Rva00C70C40SetGlobal |
| 00C6D3B0 | 012A5C60 | 00C70C50 | Rva00C70C50SetGlobal |
| 00C6D820 | 012A5CF0 | 00C70C60 | Rva00C70C60SetGlobal |
| 00C6E030 | 012A5DC0 | 00C71320 | Rva00C71320SetGlobal |
| 00C6E040 | 012A5DC4 | 00C71330 | Rva00C71330SetGlobal |

Each body is exactly12B PUSH callback-VA; CALL009F6E26; POP ECX; RET,
then four INT3 bytes. Ghidra memory and independent PE decoding agree.
These are positively referenced complete functions, not fragments carved
from surrounding compiler output. Each existing callback is a complete
11B absolute dword-store followed by RET in SmallLeafBodies2.cpp, with no
incoming register/stack argument. The emitted free void-cdecl declaration
therefore preserves its established ABI and symbol; no callback alias or
new pin is introduced.

callees.py names the existing _atexit binding at009F6E26 for all five
entries. Independently decoded18B009F6E26 forwards its one callback stack
argument to009F6E00 and converts the returned pointer to0/-1 before RET.
Use the toolchain's stdlib.h atexit(void (__cdecl *)(void)) declaration.
The _initterm entries ignore that result, consistent with void startup
callback ABI. The new function names retain their own addresses and make
no claim about original compiler-generated symbol spelling.

Every complete native entry is verified with both callback DIR32 and atexit
REL32 references resolved, not merely relocation-masked probe equality.
