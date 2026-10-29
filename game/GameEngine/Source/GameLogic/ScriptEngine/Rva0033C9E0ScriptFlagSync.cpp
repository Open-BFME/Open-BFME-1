// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// Open-BFME: retail 0x0033C9E0, 82 bytes. Nothing calls it directly (its only
// reference is ILT 0x00012E36), so the owner and method keep address-derived
// names. The receiver's fields sit in the ScriptEngine range: it pushes the
// byte at +0x1762C to TheScriptActions' slot 11, then walks the STLport
// map<AsciiString, byte> at +0x16068 (node key at +0x10, value at +0x14,
// _Rb_global<bool>::_M_increment at 0x0082B870) and hands each pair to slot
// 12. Zero Hour's ScriptEngine::loadPostProcess opens the same way
// (doEnableOrDisableObjectDifficultyBonuses), which is a lead, not identity.
//
// Both byte arguments are widened as `xor edx,edx; mov dl,[m]`: that is
// what VC7.1 emits for an unsigned char parameter; a bool parameter gives a
// different body (96 bytes).

#include <map>

#include "ascii_string.h"

typedef _STL::map<AsciiString, unsigned char> Rva0033C9E0FlagMap;

class ScriptActionsInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11(unsigned char enable);
	virtual void slot12(const AsciiString &name, unsigned char enable);
};

extern ScriptActionsInterface *TheScriptActions;

class Rva0033C9E0Owner
{
public:
	void sync();

private:
	unsigned char m_pad00[0x16068];
	Rva0033C9E0FlagMap m_flags;				// +0x16068
	unsigned char m_pad16074[0x1762C - 0x16074];
	unsigned char m_flag;					// +0x1762C
};

void Rva0033C9E0Owner::sync()
{
	TheScriptActions->slot11(m_flag);
	for (Rva0033C9E0FlagMap::iterator it = m_flags.begin(); it != m_flags.end(); ++it)
		TheScriptActions->slot12((*it).first, (*it).second);
}
