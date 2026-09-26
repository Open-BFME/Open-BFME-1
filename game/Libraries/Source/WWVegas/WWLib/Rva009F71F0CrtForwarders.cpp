// cl: /O2 /MD
extern "C" __declspec(dllimport) int __cdecl _close(int);
extern "C" __declspec(dllimport) int __cdecl _open(const char *, int, ...);
extern "C" __declspec(dllimport) int __cdecl remove(const char *);
extern "C" __declspec(dllimport) const unsigned short *__cdecl wcschr(const unsigned short *, unsigned short);
int Rva009F71F0_close(int fd) { return _close(fd); }
int Rva009F71F6_open(const char *name, int mode, int perms) { return _open(name, mode, perms); }
int Rva009F71FC_remove(const char *name) { return remove(name); }
const unsigned short *Rva009F7202_wcschr(const unsigned short *s, unsigned short c) { return wcschr(s, c); }
