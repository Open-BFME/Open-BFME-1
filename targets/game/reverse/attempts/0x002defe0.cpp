// ?testOne@Rva002DF100@@QAEEPAX@Z
// partial score=0.909 date=2026-09-28
// cl: /DNDEBUG /DWIN32 /MD /EHs-c- /D_STLP_USE_STATIC_LIB
// stlport
#include <bitset>
template <unsigned N> class BitFlags {
public:
 unsigned m_bits[N/32];
 bool testSetAndClear(const BitFlags&, const BitFlags&) const;
 bool any() const { for(unsigned i=0;i<N/32;++i) if(m_bits[i]) return true; return false; }
 void set(const BitFlags& x) { for(unsigned i=0;i<N/32;++i) m_bits[i] |= x.m_bits[i]; }

};
class Player;
class Object { public: Player* getControllingPlayer() const; __forceinline BitFlags<192> getCombinedFlags() const { BitFlags<192> f=*(BitFlags<192>*)((char*)this+0x224); f.set(*(BitFlags<192>*)((char*)getControllingPlayer()+0x8c)); return f; } };
class GameLogic { public: Object* findObjectByID(int); };
extern GameLogic* TheGameLogic;
class Rva002DF100 { public: unsigned char testOne(void*); unsigned m_00; BitFlags<192> m_04, m_1c; };
unsigned char Rva002DF100::testOne(void* value) {
 if (!value) return 0;
 Object* obj=TheGameLogic->findObjectByID(*(int*)((char*)value+8));
 if (!obj) { if(m_04.any()) return 0; return 1; }
 { BitFlags<192> flags=obj->getCombinedFlags(); if(flags.testSetAndClear(m_04,m_1c)) return 1; } return 0;
}
