// ?Rva0081D600ParseLineTable@@YAXPAVINI@@PAX1PBX@Z
// partial score=0.95 date=2026-09-25
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /FAsc /Fabuild/subtitle_line_table.cod

#include "../../Code/GameEngine/Include/GameClient/Video.h"
#include <float.h>

class INI
{
public:
	AsciiString getFilename() const;
	int getLineNum() const;
	const char *getNextToken(const char *separators);
	static float scanReal(const char *token);
};

class INIException
{
public:
	INIException(int argumentCount, const char *format, ...);
	INIException(const INIException &other);
	~INIException();

	char *mFailureMessage;
	int m_argumentCount;
};

class SubtitleManager
{
public:
	friend void Rva0081D600ParseLineTable(INI *ini, void *instance, void *store,
		const void *userData);

private:
	char m_fieldsThroughState[0x60];
	bool m_enabled;
};

class VideoPlayerInterface
{
public:
	virtual ~VideoPlayerInterface() {}
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual SubtitleManager *getSubTitleMgrForVideo(const AsciiString &title) = 0;
};

extern VideoPlayerInterface *TheVideoPlayer;
extern const float BfmeZeroRange;
extern const float g_bfmeDefaultBU;

// The retail field table names LineTable at +0x24; the callback's C++ owner is unproven.
void Rva0081D600ParseLineTable(INI *ini, void *, void *store, const void *)
{
	SubtitleManager *manager = TheVideoPlayer->getSubTitleMgrForVideo(ini->getFilename());
	if (manager != 0 && store != 0)
	{
	manager->m_enabled = true;
	float lastValue = -FLT_MAX;
	int index = 0;
	float *lineTable = (float *)store;
	while (index < 15)
	{
		float value = INI::scanReal(ini->getNextToken(0));
		if (!(value >= BfmeZeroRange) || !(value <= g_bfmeDefaultBU) ||
			!(value > lastValue + 0.01875f))
			throw INIException(8,
				"LineTable values must be in the range (0.0 - 1.0) must increase in value. %s line %d",
				ini->getFilename(), ini->getLineNum());

		lastValue = value;
		lineTable[index] = value;
		++index;
	}
	}
	else
	{
		throw INIException(9, "Could not locate SubTitleManager for %s", ini->getFilename());
	}
}
