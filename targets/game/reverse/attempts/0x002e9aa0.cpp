// ?rva002E9AA0@LuaScriptEngine@@QAEXPAVBfmeLexEAN@@@Z
// partial score=0.29 date=2026-09-23
// cl: /O2 /Oy- /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport

#include <string.h>
#include <vector>
#include "../../Code/Libraries/Source/WWVegas/WWLib/ascii_string.h"

extern const char Rva006A16B0Empty[];

class Rva002E9AA0ParserAccess
{
public:
	int count();
	void *fieldName(int index);
	void *fieldValue(int index);
	void *currentTail();
	int finish();
};

#pragma comment(linker, "/alternatename:?count@Rva002E9AA0ParserAccess@@QAEHXZ=?j_00038fc8@@YAXXZ")
#pragma comment(linker, "/alternatename:?fieldName@Rva002E9AA0ParserAccess@@QAEPAXH@Z=?j_0003a5fd@@YAXXZ")
#pragma comment(linker, "/alternatename:?fieldValue@Rva002E9AA0ParserAccess@@QAEPAXH@Z=?j_00027a7a@@YAXXZ")
#pragma comment(linker, "/alternatename:?currentTail@Rva002E9AA0ParserAccess@@QAEPAXXZ=?j_000262ba@@YAXXZ")
#pragma comment(linker, "/alternatename:?finish@Rva002E9AA0ParserAccess@@QAEHXZ=?j_00049ae4@@YAXXZ")

class Rva002E9AA0KeyField
{
public:
	void initialize();
	void setFromName(const char *name);

private:
	unsigned int m_value;
};

#pragma comment(linker, "/alternatename:?initialize@Rva002E9AA0KeyField@@QAEXXZ=?j_00025e1e@@YAXXZ")
#pragma comment(linker, "/alternatename:?setFromName@Rva002E9AA0KeyField@@QAEXPBD@Z=?j_00022bf6@@YAXXZ")

class Rva002E7C50Element
{
private:
	unsigned char m_data[28];
};

class DeathStatusFlags
{
public:
	void initialize(int init, int bit1, int bit2, int bit3, int bit4, int bit5);
	void parse(AsciiString description);
	void operator&=(const DeathStatusFlags &other)
	{
		m_words[0] &= other.m_words[0];
		m_words[1] &= other.m_words[1];
		m_words[2] &= other.m_words[2];
	}

private:
	unsigned int m_words[3];
};

#pragma comment(linker, "/alternatename:?parse@DeathStatusFlags@@QAEXVAsciiString@@@Z=?j_0001b04f@@YAXXZ")

class LuaScriptEngine
{
public:
	void rva002E9AA0(class BfmeLexEAN *parser);

private:
	char m_beforeFunctionFields[0xa4];
	_STL::vector<Rva002E7C50Element> m_functionFields;
};

void LuaScriptEngine::rva002E9AA0(BfmeLexEAN *parser)
{
	Rva002E9AA0ParserAccess *xml = (Rva002E9AA0ParserAccess *)parser;
	AsciiString name;

	for (int index = 0; index < xml->count(); ++index)
	{
		const char *field = (const char *)xml->fieldName(index);
		if (memcmp(field, "Name", 5) == 0)
		{
			const char *value = (const char *)xml->fieldValue(index);
			if (value != 0)
			{
				int length = (int)strlen(value);
				((StringBase<char> *)&name)->set(value, length);
			}
		}
	}

	if (xml->finish() != 1)
		return;
	if (memcmp((const char *)xml->currentTail(), "Conditions", 11) != 0)
		return;
	if (xml->finish() != 3)
		return;

	{
		AsciiString conditions((const char *)xml->currentTail());
		DeathStatusFlags first;
		DeathStatusFlags second;
		unsigned int *firstWords = (unsigned int *)&first;
		unsigned int *secondWords = (unsigned int *)&second;

		for (int index = 0; index < 3; ++index)
		{
			firstWords[index] = 0;
			secondWords[index] = 0;
		}
		for (int index = 0; index < 3; ++index)
			secondWords[index] = ~secondWords[index];
		secondWords[2] &= 0x3fffff;

		first.parse(conditions);
		second.parse(conditions);

		for (int index = 0; index < 3; ++index)
			secondWords[index] = ~secondWords[index];
		secondWords[2] &= 0x3fffff;

		{
			unsigned int words[7];
			Rva002E9AA0KeyField *key = (Rva002E9AA0KeyField *)words;
			key->initialize();
			words[1] = firstWords[0];
			words[2] = firstWords[1];
			words[3] = firstWords[2];
			words[4] = secondWords[0];
			words[5] = secondWords[1];
			words[6] = secondWords[2];

			void *nameData = *(void **)&name;
			const char *nameText = nameData != 0
				? (const char *)nameData + 8
				: Rva006A16B0Empty;
			key->setFromName(nameText);

			for (_STL::vector<Rva002E7C50Element>::iterator current =
				m_functionFields.begin(); current != m_functionFields.end(); ++current)
			{
				const unsigned int *existing = (const unsigned int *)&*current;
				if (existing[0] == words[0])
				{
					int index = 0;
					while (index < 3 && existing[index + 1] == words[index + 1])
						++index;
					if (index == 3)
					{
						index = 0;
						while (index < 3 && existing[index + 4] == words[index + 4])
							++index;
						if (index == 3)
							return;
					}
				}
			}

			m_functionFields.push_back(*(Rva002E7C50Element *)words);
		}
	}

	if (xml->finish() == 2)
		xml->finish();
}
