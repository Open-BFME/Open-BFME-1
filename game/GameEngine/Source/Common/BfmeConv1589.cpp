// cl: /Iinputs/reference/shims/ini /Iinputs/reference/shims/iniexception /Iinputs/reference/shims/ini_noinline /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// Open-BFME5 conversions.

#define __PLACEMENT_VEC_NEW_INLINE
#define _strcmpi BfmeIniHeaderStrcmpi
#define strtok BfmeIniHeaderStrtok
#include "../../../../inputs/reference/shims/ini_noinline/Common/INI.h"
#undef strtok
#undef _strcmpi

class BfmeStrVSO : public AsciiString
{
public:
	BfmeStrVSO() : AsciiString() { }
	BfmeStrVSO(const BfmeStrVSO &other) : AsciiString(other) { }
	~BfmeStrVSO();
	void bfmeAssignVSO(const BfmeStrVSO &other);
};

class BfmeSrcVSO : public INI
{
public:
	BfmeStrVSO bfmeMakeVSO();
};
extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *left, const char *right);
extern "C" __declspec(dllimport) char *__cdecl strtok(char *text, const char *delimiters);

void bfmeApplyVSO(BfmeSrcVSO *src, int unused, BfmeStrVSO *out)
{
	out->bfmeAssignVSO(src->bfmeMakeVSO());
}

BfmeStrVSO BfmeSrcVSO::bfmeMakeVSO()
{
	BfmeStrVSO accumulated;
	for (;;)
	{
		readLine();
		AsciiString line(m_buffer);
		const char *delimiters = m_seps;
		char *token = strtok(m_buffer, delimiters);
		if (token != 0 && _strcmpi(m_endScriptToken, token) == 0)
			break;

		char *data = *(char **)&line;
		int length = data != 0 ? *(unsigned short *)(data + 4) : 0;
		const char *text = data != 0 ? data + 8 : "";
		((StringBase<char> &)accumulated).concat(text, length);
	}
	return accumulated;
}
