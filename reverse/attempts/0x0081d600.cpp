// ?d_0081d600@@YAXXZ
// partial score=0.91 date=2026-09-23
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
};

class SubtitleManager
{
public:
	static void parseLineTable(INI *ini, void *instance, void *store,
		const void *userData);

private:
	char m_fieldsThroughState[0x60];
	bool m_enabled;
};

class VideoPlayer
{
public:
	virtual ~VideoPlayer() {}
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

extern VideoPlayer *TheVideoPlayer;
extern const float BfmeZeroRange;
extern const float g_bfmeDefaultBU;
extern const float Rva0112CF08LineTableStep;

void SubtitleManager::parseLineTable(INI *ini, void *, void *store, const void *)
{
	SubtitleManager *manager = TheVideoPlayer->getSubTitleMgrForVideo(ini->getFilename());
	if (manager == 0 || store == 0)
		throw INIException(9, "Could not locate SubTitleManager for %s", ini->getFilename());

	manager->m_enabled = true;
	volatile float lastValue = -FLT_MAX;
	int index = 0;
	float *lineTable = (float *)store;
	while (index < 15)
	{
		float value = INI::scanReal(ini->getNextToken(0));
		if (!(value >= BfmeZeroRange) || !(value <= g_bfmeDefaultBU) ||
			!(value > lastValue + Rva0112CF08LineTableStep))
			throw INIException(8,
				"LineTable values must be in the range (0.0 - 1.0) must increase in value. %s line %d",
				ini->getFilename(), ini->getLineNum());

		lastValue = value;
		lineTable[index] = value;
		++index;
	}
}
