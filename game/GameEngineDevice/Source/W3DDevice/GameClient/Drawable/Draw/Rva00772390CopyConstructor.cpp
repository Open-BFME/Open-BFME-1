// ??0Rva00772390Owner@@QAE@ABU0@@Z
// partial score=0.9173 date=2026-10-03
// cl: /DNDEBUG /MD /EHsc /D_STLP_NO_EXCEPTIONS /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Open-BFME: address-qualified 992-byte copy constructor at retail RVA 0x00772390.
// Its 14-state FuncInfo records member cleanup through +0xBC. Call sites do not
// prove a semantic owner, so the type name retains the retail address.
#include "ascii_string.h"
#include <new>
#include <vector>
#include <bitset>
namespace _STL {
template<> vector<AsciiString>::vector(const vector<AsciiString>&);
template<> vector<AsciiString>::~vector();
}
// These member layouts use the existing copy-constructor signatures pinned at their ILTs.
struct Gen_uw_000096b5 { char body[4]; ~Gen_uw_000096b5(); };
struct Rva00776240List50 : Gen_uw_000096b5 {
 Rva00776240List50(const Rva00776240List50&);
};
#pragma comment(linker, "/alternatename:??0Rva00776240List50@@QAE@ABU0@@Z=?j_000296e5@@YAXXZ")
struct Open2Elem7716A0 {
 int m_word00; int m_word04; int m_word08; AsciiString m_room0C; int m_word10;
 ~Open2Elem7716A0();
};
namespace _STL { template<> vector<Open2Elem7716A0>::~vector(); }
struct Rva00776240Vector54 : _STL::vector<Open2Elem7716A0> {
 Rva00776240Vector54(const Rva00776240Vector54&);
};
#pragma comment(linker, "/alternatename:??0Rva00776240Vector54@@QAE@ABU0@@Z=?j_00046141@@YAXXZ")
struct Gen_uwm_0003ffd0 { void *start, *finish, *end; ~Gen_uwm_0003ffd0(); };
struct Rva00776240Vector60 : Gen_uwm_0003ffd0 {
 Rva00776240Vector60(const Rva00776240Vector60&);
};
#pragma comment(linker, "/alternatename:??0Rva00776240Vector60@@QAE@ABU0@@Z=?j_000027f2@@YAXXZ")
struct Rva00772390Turret {unsigned w00,w04,w08,w0C,w10,w14;};
struct Rva00772390Owner {
 _STL::bitset<320> at00;
 _STL::vector<AsciiString> at28;
 AsciiString at34;unsigned char byte38;char pad39[3];
 AsciiString at3C;
 _STL::vector<AsciiString> at40;
 AsciiString at4C[4],at5C[4],at6C[4],at7C[4],at8C[4];
 Rva00776240List50 at9C;Rva00776240Vector54 atA0;Rva00776240Vector60 atAC;
 unsigned short wordB8;char padBA[2];AsciiString atBC;
 unsigned wordC0,wordC4,wordC8,wordCC,wordD0,wordD4,wordD8,wordDC,wordE0,wordE4;
 float wordE8;unsigned char byteEC,byteED,byteEE,byteEF;
 Rva00772390Turret atF0[2];unsigned word120;unsigned char byte124;char pad125[3];
 Rva00772390Owner(const Rva00772390Owner&);
};
Rva00772390Owner::Rva00772390Owner(const Rva00772390Owner& v):at00(v.at00),at34(v.at34),byte38(v.byte38),at3C(v.at3C),at40(v.at40),at9C(v.at9C),atA0(v.atA0),atAC(v.atAC),wordB8(v.wordB8),atBC(v.atBC),wordC0(v.wordC0),wordC4(v.wordC4),wordC8(v.wordC8),wordCC(v.wordCC),wordD0(v.wordD0),wordD4(v.wordD4),wordD8(v.wordD8),wordDC(v.wordDC),wordE0(v.wordE0),wordE4(v.wordE4),wordE8(v.wordE8),byteEC(v.byteEC),byteED(v.byteED),byteEE(v.byteEE) {
 for(int i=0;i<4;++i){at4C[i]=v.at4C[i];at5C[i]=v.at5C[i];at6C[i]=v.at6C[i];at7C[i]=v.at7C[i];at8C[i]=v.at8C[i];}
 for(int j=0;j<2;++j){atF0[j].w00=v.atF0[j].w00;atF0[j].w04=v.atF0[j].w04;atF0[j].w08=v.atF0[j].w08;atF0[j].w0C=v.atF0[j].w0C;atF0[j].w10=v.atF0[j].w10;atF0[j].w14=v.atF0[j].w14;}
 byte124=v.byte124;
 at28.clear();
 for(int k=0;k<(int)v.at28.size();++k)at28.push_back(v.at28[k]);
}
