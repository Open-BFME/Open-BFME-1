// cl: /DNDEBUG /MD /EHsc
// readable body of ?getStaticGameLODIndex@GameLODManager@@QAEHVAsciiString@@@Z: Code/GameEngine/Source/Common/GameLOD.cpp

typedef int Int;

extern "C" __declspec(dllimport) int __cdecl _strnicmp(
	const char *left, const char *right, unsigned count);
extern "C" unsigned __cdecl strlen(const char *text);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	~AsciiString();

	Int compareNoCase(const char *other) const
	{
		Int otherLength = other ? strlen(other) : 0;
		Int thisLength;
		const char *thisText;
		if (m_data)
		{
			thisLength = m_data->length;
			thisText = m_data->text;
		}
		else
		{
			thisLength = 0;
			thisText = "";
		}

		Int count = thisLength < otherLength ? thisLength : otherLength;
		Int comparison = _strnicmp(thisText, other, count);
		if (comparison != 0)
			return comparison;
		return thisLength - otherLength;
	}

private:
	struct Data
	{
		Int references;
		unsigned short length;
		unsigned short reserved;
		char text[1];
	};
	Data *m_data;
};

extern const char *StaticGameLODNames[6];

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameLOD.h
class GameLODManager
{
public:
	Int getStaticGameLODIndex(AsciiString name);
};

// ?getStaticGameLODIndex@GameLODManager@@QAEHVAsciiString@@@Z
Int GameLODManager::getStaticGameLODIndex(AsciiString name)
{
	for (Int i = 0; i < 6; ++i)
	{
		if (name.compareNoCase(StaticGameLODNames[i]) == 0)
			return i;
	}
	return -1;
}
