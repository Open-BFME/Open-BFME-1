// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// stlport
// VA 0x012A6918 is the matched data row Rva00EA6918ModelConditionNames
// (parseModelConditionFlags.cpp); retail 0x0022A1F0 returns that address.
extern const char *Rva00EA6918ModelConditionNames[];
#define ModelConditionNames Rva00EA6918ModelConditionNames
#include "Common/BitFlags.h"

struct Rva0022A1F0ConstantGetter
{
	void *get();
};

void *Rva0022A1F0ConstantGetter::get()
{
	return (void *)ModelConditionNames;
}

struct Rva0022A200ConstantGetter
{
	void *get();
};

void *Rva0022A200ConstantGetter::get()
{
	return (void *)BitFlags<86>::getBitNames();
}
