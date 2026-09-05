// ?validateParticleSystems@Rva005C5100Owner@@QAEXXZ
// partial score=0.85 date=2026-09-05
// cl: /DNDEBUG /MD /O2 /EHs-c-
// Open-BFME5: convert d_005c5100 (dump Code/gen_asm/d_005b3e30.asm) to standalone C++.
//
// Address-derived identity: the owning class is unidentified. `this` holds two
// identical 16-byte slots at +0x160 and +0x170, each a 12-byte particle-system
// handle (Rva0060FD30Base, already matched at 0x0060FD30/Code/GameEngine/Source/
// Common/Rva0060FD30Copy.cpp) followed by a 4-byte ParticleSystemID. For each
// slot with a nonzero ID: resolve it via TheParticleSystemManager::
// findParticleSystemByID (0x0002A216), copy the resolved handle over the slot,
// destroy the temporary, then assert the resolved ParticleSystem's byte at
// +0x1A8 == 1 (a "loaded" flag), throwing a formatted (tag 5, no message)
// exception via a not-yet-named ThrowInfo (pinned as g_rva005c5100ThrowInfo,
// reverse/symbols.csv) if the slot's handle is null or the flag mismatches.
// Landed under an address-derived class/method name per identity policy.

#include <new>

struct BfmeFormattedText
{
    void *text;
    int tag;
};

extern "C" BfmeFormattedText *__cdecl bfmeFormatText(BfmeFormattedText *result, int tag, const char *format, ...);
__declspec(noreturn) void __stdcall _CxxThrowException(void *object, void *throwInfo);
extern int g_rva005c5100ThrowInfo;

enum ParticleSystemID { PARTICLE_SYSTEM_ID_NONE = 0 };

class ParticleSystem
{
public:
    unsigned char m_pad[0x1A8];
    unsigned char m_loaded;
};

extern "C" ParticleSystem *__cdecl Make00001B18();

class BfmeParticleSystemHandle
{
public:
    ~BfmeParticleSystemHandle();

protected:
    ParticleSystem *m_ptr;
    unsigned char m_pad[0x08];
};

class Rva0060FD30Base
{
public:
    Rva0060FD30Base(const Rva0060FD30Base &other);

    ParticleSystem *m_ptr;
    unsigned char m_pad[0x08];
};

class ParticleSystemManager
{
public:
    BfmeParticleSystemHandle findParticleSystemByID(ParticleSystemID id);
};

extern ParticleSystemManager *TheParticleSystemManager;

class Rva005C5100Owner
{
public:
    void validateParticleSystems();

private:
    unsigned char m_pad0[0x160];
    Rva0060FD30Base m_slotA;
    ParticleSystemID m_slotAId;
    Rva0060FD30Base m_slotB;
    ParticleSystemID m_slotBId;
};

void Rva005C5100Owner::validateParticleSystems()
{
    if (m_slotAId)
    {
        if (m_slotA.m_ptr != 0)
        {
            BfmeFormattedText error;
            bfmeFormatText(&error, 5, 0);
            _CxxThrowException(&error, &g_rva005c5100ThrowInfo);
        }
        BfmeParticleSystemHandle found = TheParticleSystemManager->findParticleSystemByID(m_slotAId);
        new (&m_slotA) Rva0060FD30Base(*(Rva0060FD30Base *)&found);

        if (m_slotA.m_ptr == 0)
            m_slotA.m_ptr = Make00001B18();
        if (m_slotA.m_ptr->m_loaded != 1)
        {
            BfmeFormattedText error;
            bfmeFormatText(&error, 5, 0);
            _CxxThrowException(&error, &g_rva005c5100ThrowInfo);
        }
    }

    if (m_slotBId)
    {
        if (m_slotB.m_ptr != 0)
        {
            BfmeFormattedText error;
            bfmeFormatText(&error, 5, 0);
            _CxxThrowException(&error, &g_rva005c5100ThrowInfo);
        }
        BfmeParticleSystemHandle found = TheParticleSystemManager->findParticleSystemByID(m_slotBId);
        new (&m_slotB) Rva0060FD30Base(*(Rva0060FD30Base *)&found);

        if (m_slotB.m_ptr == 0)
            m_slotB.m_ptr = Make00001B18();
        if (m_slotB.m_ptr->m_loaded != 1)
        {
            BfmeFormattedText error;
            bfmeFormatText(&error, 5, 0);
            _CxxThrowException(&error, &g_rva005c5100ThrowInfo);
        }
    }
}
