// ?d_00c6dd80@@YAXXZ
// partial score=0.99 date=2026-09-26
// cl: /O2 /MD
// The Vector2 vector's out-of-line constructor is reached through retail ILT 0x00049341.
#include <new>
class Vector2;

class Rva0013B6A0Vector2
{
public:
    Rva0013B6A0Vector2(unsigned size, const Vector2 *array) throw();
private:
    void *m_words[6];
};

extern Rva0013B6A0Vector2 g_bfmeRva01341130Static;
void bfmeForward_00C71020();
extern "C" int __cdecl atexit(void (__cdecl *callback)());

void bfmeRva00C6DD80Initialize()
{
    new (&g_bfmeRva01341130Static) Rva0013B6A0Vector2(0, 0);
    atexit(bfmeForward_00C71020);
}
