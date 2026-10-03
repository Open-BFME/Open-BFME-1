// cl: /O2 /Ob2 /DNDEBUG /MD
#include <stdlib.h>
void Rva00C70C40SetGlobal();
void Rva00C70C50SetGlobal();
void Rva00C70C60SetGlobal();
void Rva00C71320SetGlobal();
void Rva00C71330SetGlobal();
void rva00C6D000() { atexit(Rva00C70C40SetGlobal); }
void rva00C6D3B0() { atexit(Rva00C70C50SetGlobal); }
void rva00C6D820() { atexit(Rva00C70C60SetGlobal); }
void rva00C6E030() { atexit(Rva00C71320SetGlobal); }
void rva00C6E040() { atexit(Rva00C71330SetGlobal); }
