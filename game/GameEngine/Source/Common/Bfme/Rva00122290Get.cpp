// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// stlport

#include "Common/BitFlags.h"

void *Rva00122290Get()
{
	return BitFlags<11>::getBitNames();
}
