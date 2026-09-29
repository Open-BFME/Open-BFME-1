// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ob1 /Iinputs/reference/shims/ini /Iinputs/reference/shims/xfer /Iinputs/reference/shims/ini_parser /Iinputs/reference/shims/gameaudio /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// INI block parser for an opacity envelope: three opacity reals, then five
// millisecond durations stored as whole logic frames, until End.
#include "PreRTS.h"
#include "Common/INI.h"
#include <math.h>
extern "C" int __cdecl strcmp(const char *, const char *);
#pragma intrinsic(strcmp)
class Rva000B9EA0Store
{
public:
	float m_00;
	float m_04;
	float m_08;
	int m_0c;
	int m_10;
	int m_14;
	int m_18;
	int m_1c;
	int m_20;
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
			s->m_00 = INI::scanReal(ini->getNextToken());
		else if (strcmp(token, "PeakOpacity") == 0)
			s->m_04 = INI::scanReal(ini->getNextToken());
		else if (strcmp(token, "SustainOpacity") == 0)
			s->m_08 = INI::scanReal(ini->getNextToken());
		else if (strcmp(token, "AttackTime") == 0)
			s->m_14 = (int)ceil(ConvertDurationFromMsecsToFrames((float)INI::scanUnsignedInt(ini->getNextToken())));
		else if (strcmp(token, "DecayTime") == 0)
			s->m_18 = (int)ceil(ConvertDurationFromMsecsToFrames((float)INI::scanUnsignedInt(ini->getNextToken())));
		else if (strcmp(token, "SustainTime") == 0)
			s->m_1c = (int)ceil(ConvertDurationFromMsecsToFrames((float)INI::scanUnsignedInt(ini->getNextToken())));
		else if (strcmp(token, "ReleaseTime") == 0)
			s->m_20 = (int)ceil(ConvertDurationFromMsecsToFrames((float)INI::scanUnsignedInt(ini->getNextToken())));
		else if (strcmp(token, "InitialDelay") == 0)
			s->m_10 = (int)ceil(ConvertDurationFromMsecsToFrames((float)INI::scanUnsignedInt(ini->getNextToken())));
		else if (strcmp(token, "End") == 0)
			break;
	}
}
