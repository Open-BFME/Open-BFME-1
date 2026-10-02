// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/iniexception
//
// Open-BFME5: BFME's FXList CullingInfo field parser at 0x00427840 (324B).
// The retail FieldParse table at 0x00CF2118 registers CullingInfo, and the
// six strings at 0x010F3238..0x010F3330 (including the FXList.cpp source path)
// all xref this body.  The callback consumes colon-separated tokens through
// INI's +0x41c separator pointer, filling the three culling fields at +0x14,
// +0x1c and +0x20.  The retail names in its diagnostics identify the latter
// pair as m_cullTrackingMax and m_cullTrackingMin.

typedef unsigned int UnsignedInt;
typedef float Real;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	const char *getNextTokenOrNull(const char *seps);
	const char *getNextToken(const char *seps);
	const char *getSepsColon() const { return m_sepsColon; }
	static Real scanReal(const char *token);
	static UnsignedInt scanUnsignedInt(const char *token);

private:
	char m_unreconstructed_000[0x41c];
	const char *m_sepsColon;
};

// Retail VA 0x0135933c is MSVCR71's _strcmpi import slot.  Keeping the
// cached function pointer local reproduces the retail EBX/EBP register shape.
typedef int (__cdecl *LookupFn)(const char *, const char *);
extern "C" LookupFn g_lookup;

// BFME's retail logic rate.
#define BFME_LOGIC_FRAMES_PER_SECOND 5.0f

// BFME layout: INIExceptionCtor.cpp at retail 0x00850600 stores the message
// pointer at +0 and argument count at +4.  A real throw supplies retail
// ThrowInfo 0x011DFC30 (__TI1?AVINIException@@), whose copy/unwind entries own
// the exception lifetime.
#include "Common/INIException.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/FXList.h
class FXList
{
public:
	static void parseCullingInfo(INI *ini, void *instance, void *store, const void *userData);

private:
	char m_unreconstructed_00[0x14];
	UnsignedInt m_trackingFrames;
	char m_unreconstructed_18[4];
	UnsignedInt m_cullTrackingMax;
	UnsignedInt m_cullTrackingMin;
};

// ?parseCullingInfo@FXList@@SAXPAVINI@@PAX1PBX@Z
void FXList::parseCullingInfo(INI *ini, void *instance, void *store, const void *userData)
{
	FXList *list = (FXList *)instance;
	const char *token = ini->getNextTokenOrNull(ini->getSepsColon());
	if (token != 0)
	{
		LookupFn compare = g_lookup;
		do
		{
			if (compare(token, "TrackingSeconds") == 0)
			{
				list->m_trackingFrames = (UnsignedInt)(INI::scanReal(ini->getNextToken(0)) * BFME_LOGIC_FRAMES_PER_SECOND);
			}
			else if (compare(token, "StartCullingAbove") == 0)
			{
				list->m_cullTrackingMin = INI::scanUnsignedInt(ini->getNextToken(0));
			}
			else if (compare(token, "CullAllAbove") == 0)
			{
				list->m_cullTrackingMax = INI::scanUnsignedInt(ini->getNextToken(0));
			}
			else
			{
				throw INIException(3, "bad colon spacing, or unexpected token in FXList::parseCullingInfo");
			}
			token = ini->getNextTokenOrNull(ini->getSepsColon());
		} while (token != 0);
	}

	if (list->m_cullTrackingMax == 0)
	{
		throw INIException(3, "m_cullTrackingMax == 0 in FXList::parseCullingInfo");
	}
	if (list->m_cullTrackingMin == 0)
	{
		throw INIException(3, "m_cullTrackingMin == 0 in FXList::parseCullingInfo");
	}
	if (list->m_cullTrackingMax <= list->m_cullTrackingMin)
		list->m_cullTrackingMax = list->m_cullTrackingMin + 1;
}
