// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib
// stlport
//
// Retail 0x00290520 (426 B): the "AddEmotion" field parser of
// EmotionTrackerUpdateModuleData. The module data's FieldParse table names it
// (row at VA 0x010BE4D0: "AddEmotion" -> ILT 0x0000CBF8 -> this body, store
// offset 0), so `store` is the module data itself and the nugget pointer vector
// sits at +0x30 as in EmotionTrackerUpdateModuleDataCtorThunk.cpp. The token
// grammar is the parser's own error text at VA 0x010BE2F8: "Emotion name or
// 'OVERRIDE <Emotion name>' expected."; an OVERRIDE entry also reads the rest
// of the block into the copied nugget. The C++ name stays address-derived.
//
// Two source facts reproduce retail's frame. INIException is the 8-byte
// class INIExceptionCtor.cpp constructs (message pointer plus argument
// count), so the two thrown temporaries fill the 8-byte slot the new-result
// and entry share. And the module data pointer is copied to a local at the
// top: once `store` is dead, VC7.1 homes STLport's __true_type tag temporary
// in its argument slot, exactly where retail passes it to _M_insert_overflow.

#include <vector>
#include "ascii_string.h"

extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *, const char *);

class INI
{
public:
	const char *getNextToken(const char *separators = 0);
};

class INIException
{
public:
	INIException(int, const char *, ...);
	INIException(const INIException &);

	char *m_failureMessage;
	int m_argCount;
};

// findNugget's parameter type as the ledger spells it; the temporary it gets
// is built and released exactly like an AsciiString.
class BfmeEmotionName : public AsciiString
{
public:
	BfmeEmotionName(const char *text) : AsciiString(text) {}
};

class EmotionNugget
{
public:
	EmotionNugget();

	AsciiString m_name;
	int m_04;
	unsigned char m_08;
	unsigned char m_09;
	unsigned char m_pad0A[2];
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	int m_24;
	int m_28;
	unsigned char m_2C;
	unsigned char m_2D;
	unsigned char m_pad2E[2];
	int m_30;
	int m_34;
	int m_38;
	AsciiString m_3C;
	int m_40;
	unsigned char m_44;
	unsigned char m_pad45[3];
	int m_48;
	int m_4C;
	int m_50;
	unsigned int m_54[20];
	unsigned int m_A4[20];
	AsciiString m_F4;
};

class EmotionSystem
{
public:
	EmotionNugget *findNugget(const BfmeEmotionName &name);
};

extern EmotionSystem *TheEmotionSystem;

class BfmeThingVKC
{
public:
	void bfmeCopyVKC(const BfmeThingVKC &source);
};

class BfmeOtherDCE;

class BfmeThingDCE
{
public:
	void bfmeGoDCE(BfmeOtherDCE *other);
};

class EmotionTrackerUpdateModuleData
{
public:
	unsigned char m_unknown00[0x30];
	std::vector<EmotionNugget *> m_entries;
};

// ?Rva00290520@@YAXPAVINI@@PAX1PBX@Z
void Rva00290520(INI *ini, void *, void *store, const void *)
{
	EmotionTrackerUpdateModuleData *moduleData = (EmotionTrackerUpdateModuleData *)store;
	const char *emotionToken = ini->getNextToken();
	bool hasOverrideBlock = false;

	if (emotionToken != 0)
	{
		if (_strcmpi(emotionToken, "override") == 0)
		{
			hasOverrideBlock = true;
			emotionToken = ini->getNextToken();
		}
	}

	if (emotionToken == 0)
		throw INIException(3, "Emotion name or 'OVERRIDE <Emotion name>' expected.");

	EmotionNugget *sourceNugget = TheEmotionSystem->findNugget(BfmeEmotionName(emotionToken));
	if (sourceNugget == 0)
		throw INIException(3, "Emotion not found");

	EmotionNugget *copiedNugget = new EmotionNugget;
	((BfmeThingVKC *)copiedNugget)->bfmeCopyVKC(*(const BfmeThingVKC *)sourceNugget);
	copiedNugget->m_name.set(AsciiString(emotionToken));

	if (hasOverrideBlock)
		((BfmeThingDCE *)copiedNugget)->bfmeGoDCE((BfmeOtherDCE *)ini);

	moduleData->m_entries.push_back(copiedNugget);
}
