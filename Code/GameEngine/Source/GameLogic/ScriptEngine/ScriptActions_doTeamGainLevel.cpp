// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
// Open-BFME: TEAM_GAIN_LEVEL handler at retail RVA 0x002F77C0.

#include "StringInline.h"

typedef bool Bool;
class Object;
typedef void (__cdecl *BfmeObjectVisitor)(Object *, void *);

class BfmeInnerIterable
{
public:
	int bfmeVisit(BfmeObjectVisitor visitor, void *userData);
};

extern void __cdecl j_00021355();

class ScriptEngine
{
public:
	virtual void _slot00() = 0;
	virtual void _slot01() = 0;
	virtual void _slot02() = 0;
	virtual void _slot03() = 0;
	virtual void _slot04() = 0;
	virtual void _slot05() = 0;
	virtual void _slot06() = 0;
	virtual void _slot07() = 0;
	virtual void _slot08() = 0;
	virtual void _slot09() = 0;
	virtual void _slot10() = 0;
	virtual void _slot11() = 0;
	virtual void _slot12() = 0;
	virtual void _slot13() = 0;
	virtual void _slot14() = 0;
	virtual void _slot15() = 0;
	virtual void _slot16() = 0;
	virtual BfmeInnerIterable *getTeamNamed(AsciiString name, Bool createIfMissing) = 0;
};

extern ScriptEngine *TheScriptEngine;

class Parameter
{
public:
	unsigned char _pad[0x10];
	AsciiString m_string;
};

class ScriptActions
{
protected:
	void doTeamGainLevel(Parameter *team, Bool showExperienceFX);
};

void ScriptActions::doTeamGainLevel(Parameter *team, Bool showExperienceFX)
{
	BfmeInnerIterable *members = TheScriptEngine->getTeamNamed(team->m_string, false);
	if (members) {
		members->bfmeVisit((BfmeObjectVisitor)j_00021355, (void *)(int)showExperienceFX);
	}
}
