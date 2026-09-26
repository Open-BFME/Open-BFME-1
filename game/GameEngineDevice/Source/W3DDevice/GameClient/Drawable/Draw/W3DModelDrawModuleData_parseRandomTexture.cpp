// ?parseRandomTexture@W3DModelDrawModuleData@@SAXPAVINI@@PAX1PBX@Z
// Retail field-table owner: W3DModelDrawModuleData::RandomTexture, table 0x00D24F90; reached through ILT 0x000133FE.
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/GameEngine/Include /Igame/Libraries/Source/WWVegas/WWLib
// stlport

#include "Common/INI/INI.h"
#include <vector>
#include <string.h>

struct Rva007701C0Element
{
	AsciiString m_name;
	_STL::vector<AsciiString> m_vector04;
	int m_word10;
};

class Rva0077BC20Owner
{
public:
	Rva007701C0Element *findOrCreateRecord(const AsciiString &name);
};

class W3DModelDrawModuleData
{
public:
	static void __cdecl parseRandomTexture(INI *ini, void *instance,
		void *store, const void *userData);
};

void W3DModelDrawModuleData::parseRandomTexture(
	INI *ini, void *instance, void *, const void *)
{
	if (instance == 0)
		return;

	{
		AsciiString groupName;
		AsciiString textureName;
		const char *token = ini->getNextTokenOrNull();
		if (token != 0)
		{
			((StringBase<char> *)&textureName)->set(token, strlen(token));
		}
		else
		{
			((StringBase<char> *)&textureName)->set("", 0);
		}

		token = ini->getNextTokenOrNull();
		int value = token != 0 ? INI::scanInt(token) : 0;

		token = ini->getNextTokenOrNull();
		if (token != 0)
		{
			((StringBase<char> *)&groupName)->set(token, strlen(token));
		}
		else
		{
			((StringBase<char> *)&groupName)->set(token, 0);
		}

		Rva007701C0Element *record =
			((Rva0077BC20Owner *)instance)->findOrCreateRecord(groupName);
		record->m_vector04.push_back(textureName);
		record->m_word10 = value;
	}
}
