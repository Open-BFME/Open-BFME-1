// cl: /DNDEBUG /MD /EHsc
// Fuzzy twin (tools/fuzzy_twin_scan.py) of Rva0007F560Ctor.cpp: build a temporary
// AsciiString from the literal, look it up through a singleton, and hand the
// pointer back. Retail 0x003392B0 keeps the result in esi and returns it (ret 4,
// no this), so it is a __stdcall free function over TheParticleSystemManager
// (0x012F64BC) and its lookup thunk at 0x00015267. Identity of the lookup is not
// otherwise recovered; address-derived names.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString( const char *text );
	~AsciiString();

private:
	void *m_data;
};

class Rva003392B0TemplateStore
{
public:
	void *findTemplate( const AsciiString &name );
};

extern Rva003392B0TemplateStore *TheParticleSystemManager;

void *__stdcall Rva003392B0FindParticleTemplate( const char *name )
{
	AsciiString tmp( name );
	return TheParticleSystemManager->findTemplate( tmp );
}
