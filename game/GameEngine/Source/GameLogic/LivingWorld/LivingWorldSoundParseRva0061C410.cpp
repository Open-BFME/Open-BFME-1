// cl: /DNDEBUG /MD /EHsc /Igame/GameEngine/Include /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath
// stlport
// Retail 0x0061C410 parses LivingWorldSound; its diagnostic literal names the block.
#include "Common/INI/INI.h"
#include "region.h"
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class BfmeAwakenLog
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34();
	virtual BfmeAwakenLog *slot38(const char *text);
	virtual void slot3C(); virtual void slot40(); virtual void slot44(); virtual void slot48();
	virtual void slot4C(int report);
};
class BfmeAwakenDebug
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4C();
	virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5C();
	virtual void slot60(); virtual void slot64(); virtual void slot68();
	virtual BfmeAwakenLog *slot6C(int first, int second);
};
struct BfmeAwakenDebugEqualityVtable
{
	void *m_slots00[24];
	void (__fastcall *slot60)(BfmeAwakenDebug *debug, BfmeAwakenDebugEqualityVtable *table);
	void *m_slots64[2];
	BfmeAwakenLog *(__fastcall *slot6C)(BfmeAwakenDebug *debug, int first, int second);
};
extern BfmeAwakenDebug *TheBfmeAwakenDebug;
extern bool _bfme_debugReportingEnabled();
extern void _bfme_debugRecordCallsite(int kind);

class BfmeItemEQV;
class BfmeLivingWorldManager
{
public:
	BfmeItemEQV *rva006155e0(void *key);
};
class BfmeGameCW;
extern BfmeGameCW *g_bfmeGameCW;
extern Region2D Rva012F7078Region;
extern FieldParse Rva011172B0SoundFields[];

struct Rva0061C410Sound
{
	void *m_vtable;
	AsciiString m_name;
	float m_position[3];
	void *m_audio;
	unsigned int m_flags;
	Region2D m_zoom;
};

#define REPORT_SOUND_ERROR(MESSAGE) \
	do { \
		if (_bfme_debugReportingEnabled()) { \
			_bfme_debugRecordCallsite(1); \
			TheBfmeAwakenDebug->slot60(); \
			TheBfmeAwakenDebug->slot6C(0, 0)->slot38("LivingWorldSound ")->slot38(token)->slot38(MESSAGE)->slot4C(2); \
		} \
	} while (0)
#define REPORT_SOUND_EQUALITY(MESSAGE) \
	do { \
		if (_bfme_debugReportingEnabled()) { \
			_bfme_debugRecordCallsite(1); \
			BfmeAwakenDebug *debug = TheBfmeAwakenDebug; \
			BfmeAwakenDebugEqualityVtable *table = *(BfmeAwakenDebugEqualityVtable **)debug; \
			table->slot60(debug, table); \
			TheBfmeAwakenDebug->slot6C(0, 0)->slot38("LivingWorldSound ")->slot38(token)->slot38(MESSAGE)->slot4C(2); \
		} \
	} while (0)


void parseLivingWorldSoundRva0061C410(INI *ini)
{
	const char *token = ini->getNextToken();
	if (token == 0)
		return;
	Rva0061C410Sound *sound;
	{
		AsciiString name(token);
		sound = (Rva0061C410Sound *)
			((BfmeLivingWorldManager *)g_bfmeGameCW)->rva006155e0(&name);
	}
	ini->initFromINI(sound, Rva011172B0SoundFields);
	if (!sound->m_audio)
		REPORT_SOUND_ERROR(": Sound not found");
	unsigned int flags = sound->m_flags;
	int count = 0;
	if (flags & 2) count = 1;
	if (flags & 1) ++count;
	if (flags & 4) ++count;
	if (count > 1)
		REPORT_SOUND_ERROR(": Flags should include at most ONE of ZOOMED_OUT, ZOOMED_IN, and ZOOMING_IN");
	if (!(sound->m_flags & 5) && !sound->m_zoom.IsExactlyEqualTo(Rva012F7078Region))
	{
		REPORT_SOUND_ERROR(": No point in specifying a zoom region unless you have the flag ZOOMED_IN or ZOOMING_IN");
		return;
	}
	if (sound->m_zoom.x_min > sound->m_zoom.x_max)
	{
		REPORT_SOUND_ERROR(": ZoomRegionLow X: should be less than ZoomRegionHigh X:");
		unsigned int high = *reinterpret_cast<unsigned int *>(&sound->m_zoom.x_max);
		_ReadWriteBarrier();
		float low = sound->m_zoom.x_min;
		_ReadWriteBarrier();
		*reinterpret_cast<unsigned int *>(&sound->m_zoom.x_min) = high;
		_ReadWriteBarrier();
		sound->m_zoom.x_max = low;
	}
	else if (sound->m_zoom.x_min == sound->m_zoom.x_max)
		REPORT_SOUND_EQUALITY(": ZoomRegionLow X: is equal to ZoomRegionHigh X:. This sound cannot play");
	if (sound->m_zoom.y_min > sound->m_zoom.y_max)
	{
		REPORT_SOUND_ERROR(": ZoomRegionLow Y: should be less than ZoomRegionHigh Y:");
		unsigned int high = *reinterpret_cast<unsigned int *>(&sound->m_zoom.y_max);
		_ReadWriteBarrier();
		float low = sound->m_zoom.y_min;
		_ReadWriteBarrier();
		*reinterpret_cast<unsigned int *>(&sound->m_zoom.y_min) = high;
		_ReadWriteBarrier();
		sound->m_zoom.y_max = low;
	}
	else if (sound->m_zoom.y_min == sound->m_zoom.y_max)
		REPORT_SOUND_EQUALITY(": ZoomRegionLow Y: is equal to ZoomRegionHigh Y:. This sound cannot play");
}
