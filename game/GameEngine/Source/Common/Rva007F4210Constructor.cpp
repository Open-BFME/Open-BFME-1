// cl: /DNDEBUG /MD /O2
extern void *g_bfmeRva01129744Vt;
extern void *g_bfmeRva01118E58Vt;
extern void *g_bfmeRva0112B2B8Vt;
extern void *g_bfme5VtD;
extern void *g_bfme5VtE;

class Rva007F4210Object
{
public:
    Rva007F4210Object(void *payload);

    void *m_vptr;
    void *m_secondaryVptr;
    void *m_payload;
    void *m_trailingVptr;
};

// ??0Rva007F4210Object@@QAE@PAX@Z
// Open BFME 2: Code/GameEngine/Source/Common/BfmeMakeBZA.cpp.
Rva007F4210Object::Rva007F4210Object(void *payload)
{
    *(void *volatile *)&m_secondaryVptr = &g_bfmeRva01129744Vt;
    *(void *volatile *)&m_payload = payload;
    *(void *volatile *)&m_trailingVptr = &g_bfmeRva01118E58Vt;
    *(void *volatile *)&m_vptr = &g_bfmeRva0112B2B8Vt;
    *(void *volatile *)&m_secondaryVptr = &g_bfme5VtD;
    *(void *volatile *)&m_trailingVptr = &g_bfme5VtE;
}
