// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
#include <math.h>
#include <string.h>

typedef int Int;
typedef float Real;

class INI
{
public:
	const char *getNextTokenOrNull(const char *seps);
	const char *getNextToken(const char *seps);
	static Int scanInt(const char *token);
	const char *getSepsColon(void) const { return m_sepsColon; }

private:
	char m_pad[0x41C];
	const char *m_sepsColon;
};

// Retail .rdata VA 0x010A0528 (RVA 0x00CA0528) is 0.005f, not ZH's 0.03f
// (LOGICFRAMES_PER_SECOND/1000 with 30 Hz). DIR32 masking hid the 6x error.
static const Real kRetailMsecToFrames = 0.005f;

static Real ConvertDurationFromMsecsToFrames(Real msec)
{
	return msec * kRetailMsecToFrames;
}

void parseMinMaxDuration(INI *ini, void *instance, void * /*store*/, const void * /*userData*/)
{
	static const char *MIN_LABEL = "Min";
	static const char *MAX_LABEL = "Max";

	const char *token = ini->getNextTokenOrNull(ini->getSepsColon());

	if (stricmp(token, MIN_LABEL) == 0)
	{
		*reinterpret_cast<Int *>(reinterpret_cast<char *>(instance) + 0x4B8) = INI::scanInt(ini->getNextToken(ini->getSepsColon()));
		token = ini->getNextTokenOrNull(ini->getSepsColon());
		if (stricmp(token, MAX_LABEL) != 0)
		{
			*reinterpret_cast<Int *>(reinterpret_cast<char *>(instance) + 0x4BC) = *reinterpret_cast<Int *>(reinterpret_cast<char *>(instance) + 0x4B8);
		}
		else
			*reinterpret_cast<Int *>(reinterpret_cast<char *>(instance) + 0x4BC) = INI::scanInt(ini->getNextToken(ini->getSepsColon()));
	}
	else
	{
		*reinterpret_cast<Int *>(reinterpret_cast<char *>(instance) + 0x4B8) = INI::scanInt(token);
		*reinterpret_cast<Int *>(reinterpret_cast<char *>(instance) + 0x4BC) = *reinterpret_cast<Int *>(reinterpret_cast<char *>(instance) + 0x4B8);
	}

	*reinterpret_cast<Int *>(reinterpret_cast<char *>(instance) + 0x4B8) = ceilf(ConvertDurationFromMsecsToFrames((Real)*reinterpret_cast<Int *>(reinterpret_cast<char *>(instance) + 0x4B8)));
	*reinterpret_cast<Int *>(reinterpret_cast<char *>(instance) + 0x4BC) = ceilf(ConvertDurationFromMsecsToFrames((Real)*reinterpret_cast<Int *>(reinterpret_cast<char *>(instance) + 0x4BC)));
}
