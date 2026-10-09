// cl: /EHs-c- /Ob2
class Rva007F02F0 {
public:
    Rva007F02F0();
    virtual void slot();
};
class Gen_007f0300 {
public:
    void m();
};
extern Gen_007f0300 g_bfme912B;
extern void *g_bfme912A;
extern char g_bfme912Str[];
extern "C" __declspec(dllimport) void *__stdcall CreateMutexA(void *, int, const char *);
extern "C" int __cdecl atexit(void (__cdecl *)());
void bfmeGo912B();
inline void *operator new(unsigned int, void *p) { return p; }
// ?Rva00C6CA80Init@@YAXXZ
// Open BFME 2 donor Code/GameEngine/Source/Common/Rva00CE12FCMutex.cpp.
void Rva00C6CA80Init() {
    new (&g_bfme912B) Rva007F02F0;
    *reinterpret_cast<char **>(&g_bfme912B) = g_bfme912Str;
    g_bfme912A = CreateMutexA(0, 0, 0);
    atexit(bfmeGo912B);
}
