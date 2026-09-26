// cl: /DNDEBUG /MD /EHsc
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

// BFME's retail logic rate is the global float at VA 0x01075344.
#define BFME_LOGIC_FRAMES_PER_SECOND (*(const Real *)0x01075344)

// BFME layout: INIExceptionCtor.cpp at retail 0x00850600 stores the message
// pointer at +0 and argument count at +4. The direct noreturn throw helper
// below supplies retail ThrowInfo 0x011DFC30, whose copy/unwind entries own
// the exception lifetime; this view does not generate replacement metadata.
class INIException
{
public:
	INIException(int code, const char *format, ...);
	INIException(const INIException &other);

private:
	char *mFailureMessage;
	int m_argCount;
};

extern void __declspec(noreturn) __stdcall _CxxThrowException(void *object, void *throwInfo);

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
			if (compare(token, (const char *)0x010F3330) == 0)
			{
				list->m_trackingFrames = (UnsignedInt)(INI::scanReal(ini->getNextToken(0)) * BFME_LOGIC_FRAMES_PER_SECOND);
			}
			else if (compare(token, (const char *)0x010F3318) == 0)
			{
				list->m_cullTrackingMin = INI::scanUnsignedInt(ini->getNextToken(0));
			}
			else if (compare(token, (const char *)0x010F3308) == 0)
			{
				list->m_cullTrackingMax = INI::scanUnsignedInt(ini->getNextToken(0));
			}
			else
			{
				INIException error(3, (const char *)0x010F3278);
				_CxxThrowException(&error, (void *)0x011DFC30);
			}
			token = ini->getNextTokenOrNull(ini->getSepsColon());
		} while (token != 0);
	}

	if (list->m_cullTrackingMax == 0)
	{
		INIException error(3, (const char *)0x010F32C8);
		_CxxThrowException(&error, (void *)0x011DFC30);
	}
	if (list->m_cullTrackingMin == 0)
	{
		INIException error(3, (const char *)0x010F3238);
		_CxxThrowException(&error, (void *)0x011DFC30);
	}
	if (list->m_cullTrackingMax <= list->m_cullTrackingMin)
		list->m_cullTrackingMax = list->m_cullTrackingMin + 1;
}
