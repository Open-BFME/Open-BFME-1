// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
// Clean C++ recovery of ScriptActions::doTeamDecreasePriority.
// Retail RVA 0x002F3A60 (196 bytes), executeAction TEAM_DECREASE_PRIORITY arm.

#include "StringInline.h"

typedef bool Bool;
typedef int Int;

class Team;
class TeamPrototype;
class ScriptEngine;

// Retail passes the BFME one-word string through an out-of-line copy
// constructor when the ScriptEngine vcall takes it by value.
class BfmeStringArgBase
{
	friend class BfmeAsciiStringArg;

private:
	BfmeStringArgBase(const BfmeStringArgBase &other);
};

class BfmeAsciiStringArg
{
public:
	BfmeAsciiStringArg(const AsciiString &that)
	{
		((BfmeStringArgBase *)this)->BfmeStringArgBase::BfmeStringArgBase(
			*(const BfmeStringArgBase *)&that);
	}
	~BfmeAsciiStringArg();

private:
	char *m_text;
};

// The BFME string data header is eight bytes; its text starts at data+8.
struct BfmeAsciiStringData
{
	unsigned short m_refCount;
	unsigned short m_numCharsAllocated;
	unsigned short m_numChars;
	unsigned short m_unreconstructed_06;
};

static const char *bfmeStringChars(const AsciiString &str)
{
	const BfmeAsciiStringData *data =
		*(const BfmeAsciiStringData * const *)&str;
	return data ? (const char *)(data + 1) : "";
}

// This local spelling carries the out-of-line BFME constructor, formatter and
// release ABI without changing the shared AsciiString header.
class BfmeStringLiteralBase
{
	friend class BFMERetailAsciiString;

private:
	BfmeStringLiteralBase(const char *string);
	~BfmeStringLiteralBase();
};

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString() : m_data(0) {}
	BFMERetailAsciiString(const char *string)
	{
		((BfmeStringLiteralBase *)this)->BfmeStringLiteralBase::BfmeStringLiteralBase(string);
	}
	~BFMERetailAsciiString() { releaseBuffer(); }

	void __cdecl format(BFMERetailAsciiString fmt, ...);

private:
	void releaseBuffer();
	char *m_data;
};

class BfmeTeamProtoField
{
public:
	const TeamPrototype *getPrototype() const { return m_proto; }

	unsigned char m_unreconstructed_00[4];
	const TeamPrototype *m_proto;
};

struct BfmeTeamPrototypeFields
{
	unsigned char m_unreconstructed_00[0x1c8];
	Int m_productionPriority;
};

// The named action's decrease call lands on the existing incremental-link
// thunk at 0x0003DDBB, whose body is the BFME TeamPrototype implementation at
// 0x000EC8C0.
class TeamPrototype
{
public:
	void decreaseAIPriorityForFailure() const;
};

class BfmeScriptEngineVtbl_44
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0;
	virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0;
	virtual void slot08() = 0; virtual void slot09() = 0;
	virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0;
	virtual void slot14() = 0; virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual Team *getTeamNamed(BfmeAsciiStringArg name, Bool exact = false) = 0;
};

class ScriptEngine
{
public:
	void AppendDebugMessage(const AsciiString &message, Bool printToConsole);
};

extern ScriptEngine *TheScriptEngine;

class ScriptActions
{
protected:
	void doTeamDecreasePriority(const AsciiString &);
};

// ?doTeamDecreasePriority@ScriptActions@@IAEXABVAsciiString@@@Z
void ScriptActions::doTeamDecreasePriority(const AsciiString &teamName)
{
	Team *team =
		((BfmeScriptEngineVtbl_44 *)TheScriptEngine)->getTeamNamed(teamName);
	if (!team)
		return;

	const TeamPrototype *theTeamProto =
		((const BfmeTeamProtoField *)team)->getPrototype();
	if (!theTeamProto)
		return;

	theTeamProto->decreaseAIPriorityForFailure();

	BFMERetailAsciiString msg;
	msg.format("Team '%s' priority decreased to %d for failure.",
		bfmeStringChars(teamName),
		((const BfmeTeamPrototypeFields *)theTeamProto)->m_productionPriority);
	TheScriptEngine->AppendDebugMessage(*(const AsciiString *)&msg, false);
}
