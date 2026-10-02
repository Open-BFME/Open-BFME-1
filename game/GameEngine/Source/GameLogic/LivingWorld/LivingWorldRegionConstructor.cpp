// RVA 0x0061AF80, 304-byte LivingWorldRegion constructor.
// Evidence: targets/game/reverse/identity_evidence/livingworldregion_ctor_0061af80.md
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#include "ascii_string.h"
#include <vector>
#include <new>
class BfmeBaseVUQ { public: virtual ~BfmeBaseVUQ() {} };
class Rva0061A5F0 { public: Rva0061A5F0(const AsciiString&); ~Rva0061A5F0(); char body[0x98]; };
struct Gen0061A200 { virtual ~Gen0061A200(); char body[0x20]; };
class Rva0076F980Mid { public:
 Rva0076F980Mid():m_begin(0),m_end(0),m_capacity(0) {} ~Rva0076F980Mid();
 AsciiString* erase(AsciiString*,AsciiString*);
 void clear(){erase(m_begin,m_end);}
 AsciiString *m_begin,*m_end,*m_capacity;
};
class Gen_0061A3D0 { public:
 Gen_0061A3D0(const StringBase<char>&); char at00[0x18]; unsigned char at18; char at19[0x2c-0x19];
};
int Rva003C9220(int,int);
struct Rva0061AF80Pair { int a,b; Rva0061AF80Pair():a(0),b(0) {} };
class LivingWorldRegion : public BfmeBaseVUQ { public:
 LivingWorldRegion(const AsciiString&);
 Rva0061A5F0 m_04;
 _STL::vector<Gen0061A200> m_9c;
 unsigned char m_a8;
 int m_ac,m_b0,m_b4;
 AsciiString m_b8;
 Rva0061AF80Pair m_bc; int m_c4,m_c8,m_cc;
 unsigned char m_d0,m_d1;
 Rva0076F980Mid m_d4;
 Rva0061AF80Pair m_e0;
 unsigned char m_e8,m_e9;
 Gen_0061A3D0 *m_ec;
 int m_f0;
};
LivingWorldRegion::LivingWorldRegion(const AsciiString& name)
 :m_04(name),m_a8(0),m_ac(0),m_b4(Rva003C9220(0,0)),m_c4(0),m_c8(0),m_cc(0),m_d0(0),m_d1(0),m_e8(0),m_e9(0),m_f0(0)
{
 m_ec=new Gen_0061A3D0(name);
 m_ec->at18=0;
 m_b8.clear();
 m_d4.clear();
}
