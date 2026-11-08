// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ob1 /Iinputs/reference/shims/ini /Iinputs/reference/shims/xfer /Iinputs/reference/shims/ini_parser /Iinputs/reference/shims/gameaudio /Iinputs/reference/shims/zhcanonascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// INI block parser for an opacity envelope: three opacity reals, then five
// millisecond durations stored as whole logic frames, until End.
#include "PreRTS.h"
#include "Common/INI.h"
#include <math.h>
// Retail FMUL operands reference VA01082C38 (binary32 0.005f).
namespace Rva000B9EA0Arithmetic {
    inline float ConvertDurationFromMsecsToFrames(float value) { return value * 0.005f; }
}
extern "C" int __cdecl strcmp(const char *, const char *);
#pragma intrinsic(strcmp)
class Rva000B9EA0Store
{
public:
	float m_initialOpacity;
	float m_peakOpacity;
	float m_sustainOpacity;
	int m_0c;
	int m_initialDelay;
	int m_attackTime;
	int m_decayTime;
	int m_sustainTime;
	int m_releaseTime;
	int m_24;
};
class Rva000B9EA0Parse
{
public:
	static void parse(INI *ini, void *instance, void *store, const void *userData);
};
void Rva000B9EA0Parse::parse(INI *ini, void *instance, void *store, const void *userData)
{
	Rva000B9EA0Store *s = (Rva000B9EA0Store *)store;
	s->m_0c = 0;
	s->m_24 = 0;
	for (const char *token = ini->getNextTokenOrNull(); token != NULL; token = ini->getNextTokenOrNull())
	{
		if (strcmp(token, "InitialOpacity") == 0)
			s->m_initialOpacity = INI::scanReal(ini->getNextToken());
		else if (strcmp(token, "PeakOpacity") == 0)
			s->m_peakOpacity = INI::scanReal(ini->getNextToken());
		else if (strcmp(token, "SustainOpacity") == 0)
			s->m_sustainOpacity = INI::scanReal(ini->getNextToken());
		else if (strcmp(token, "AttackTime") == 0)
			s->m_attackTime = (int)ceil(Rva000B9EA0Arithmetic::ConvertDurationFromMsecsToFrames((float)INI::scanUnsignedInt(ini->getNextToken())));
		else if (strcmp(token, "DecayTime") == 0)
			s->m_decayTime = (int)ceil(Rva000B9EA0Arithmetic::ConvertDurationFromMsecsToFrames((float)INI::scanUnsignedInt(ini->getNextToken())));
		else if (strcmp(token, "SustainTime") == 0)
			s->m_sustainTime = (int)ceil(Rva000B9EA0Arithmetic::ConvertDurationFromMsecsToFrames((float)INI::scanUnsignedInt(ini->getNextToken())));
		else if (strcmp(token, "ReleaseTime") == 0)
			s->m_releaseTime = (int)ceil(Rva000B9EA0Arithmetic::ConvertDurationFromMsecsToFrames((float)INI::scanUnsignedInt(ini->getNextToken())));
		else if (strcmp(token, "InitialDelay") == 0)
			s->m_initialDelay = (int)ceil(Rva000B9EA0Arithmetic::ConvertDurationFromMsecsToFrames((float)INI::scanUnsignedInt(ini->getNextToken())));
		else if (strcmp(token, "End") == 0)
			break;
	}
}
