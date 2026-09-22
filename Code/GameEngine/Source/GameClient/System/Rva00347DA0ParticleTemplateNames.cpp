// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/stringinline
// stlport
// ?bfmeDumpCG_00347DA0@@YGXPAVBfmeSinkCG@@@Z
// Retail 0x00347DA0, 143 bytes: pass each particle-template key to a callback.
// The matched ParticleSystemManager::newTemplate at 0x005CECB0 establishes
// the AsciiString -> ParticleSystemTemplate* map at manager+0x9C. The upstream
// ParticleSys.h TemplateMap corroborates its native STLport representation.
// begin: ILT0x0001ABD1 ->0x0033CDA0 (78B); bucket index:
// ILT0x00044ADF ->0x0033D320 (41B). Both template bodies independently match.
// Native iterator increment removes the bank's synthetic volatile load and
// barrier and reproduces its final test of the copied node exactly.
// The callback identity is unproven; retain its banked name plus the RVA.
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include "StringInline.h"
namespace rts
{
template<class T> struct hash { unsigned operator()(T value) const; };
template<class T> struct equal_to { bool operator()(const T &, const T &) const; };
}
class ParticleSystemTemplate;
typedef _STL::hash_map<AsciiString, ParticleSystemTemplate *, rts::hash<AsciiString>, rts::equal_to<AsciiString> > BfmeTableCG;
class ParticleSystemManager
{
public:
 unsigned char m_bfmeHeadCG[0x9c];
 BfmeTableCG m_bfme9CCG;
};
extern ParticleSystemManager *TheParticleSystemManager;
class BfmeSinkCG
{
public:
 virtual void bfmeEmitCG(const char *s);
};
void __stdcall bfmeDumpCG_00347DA0(BfmeSinkCG *sink)
{
	BfmeTableCG &table = TheParticleSystemManager->m_bfme9CCG;
	for (BfmeTableCG::iterator it = table.begin(); it != table.end(); ++it)
		sink->bfmeEmitCG(it->first.str());
}
