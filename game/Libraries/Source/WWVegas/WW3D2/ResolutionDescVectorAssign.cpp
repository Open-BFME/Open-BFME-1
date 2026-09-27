// cl: /Iinputs/reference/shims/dx8wrapper /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// Open-BFME1: VectorClass<ResolutionDescClass>::operator=, retail 0x00905C80
// (217 bytes) -- dxwrapper.cpp instantiates this member from Zero Hour's
// vector.h, but that header's operator= drops the two IsValid stores the
// retail WWLib body makes: retail sets IsValid = false right after the
// virtual Clear() call and writes the second flag through al in the same pair
// as IsAllocated (mov al,1 / mov [esi+0xd],al / mov [esi+0xc],al), then
// writes IsValid = true in the zero-length branch too.  Those three stores
// are the whole 10-byte delta between this body and dxwrapper.cpp's, so the
// retail template is reproduced here as an explicit specialization of the
// header's own member rather than by editing the shared header.

#include "winbase_shim.h"
#include "rddesc.h"

template <>
VectorClass<ResolutionDescClass> &VectorClass<ResolutionDescClass>::operator=(VectorClass<ResolutionDescClass> const &vec)
{
	if (this != &vec) {
		Clear();
		IsValid = false;
		VectorMax = vec.Length();
		if (VectorMax) {
			Vector = W3DNEWARRAY ResolutionDescClass[VectorMax];
			if (Vector) {
				IsAllocated = true;
				IsValid = true;
				for (int index = 0; index < VectorMax; index++) {
					Vector[index] = vec[index];
				}
			}
		} else {
			Vector = 0;
			IsAllocated = false;
			IsValid = true;
		}
	}
	return(*this);
}
