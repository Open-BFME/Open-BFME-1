// cl: /Iinputs/reference/shims/dx8wrapper /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Igame/Libraries/Source/WWVegas/WWLib
// ?dup_0090b4e0@@YAXXZ
// Retail 0x0090B4E0. The witnessed vtable at 0x0113A4F8 has six four-byte
// slots: +00 deleting dtor 0x00D0BB40; +04 VectorClass equality 0x00D081A0;
// +08 DynamicVector Resize 0x00D0B550; +0C DynamicVector Clear 0x00D0B440;
// +10 ID(const T&) 0x00D0B540; +14 ID(const T*) 0x00D0B510. The last body
// checks IsValid and divides (pointer - Vector) by 1464; the preceding body is
// the six-byte -1 stub. The constructor/destructor and allocation loop in
// VectorClass<T> at 0x009080A0 provide independent nontrivial element evidence.
#include "../WWLib/vector.h"

#include "rddesc.h"

// This address-qualified element keeps this independently witnessed vector
// specialization distinct from older conflicting generic constructor pins.
struct Rva009080A0Element { RenderDeviceDescClass value; };
typedef char Rva009080A0ElementWidth[(sizeof(Rva009080A0Element) == 0x5B8) ? 1 : -1];

// Suppress vector.h's inline base implementation here and call the witnessed
// out-of-line VectorClass<Rva009080A0Element> body at 0x009080A0.
template <>
VectorClass<Rva009080A0Element>::VectorClass(
	int size, const Rva009080A0Element *array);

// Keep this forwarding TU from emitting template member bodies based on the
// intentionally incomplete descriptor shell. Their retail implementations
// remain the already-landed, independently verified bodies.
template <> VectorClass<Rva009080A0Element>::~VectorClass();
template <> bool VectorClass<Rva009080A0Element>::operator==(
	const VectorClass<Rva009080A0Element> &) const;
template <> bool VectorClass<Rva009080A0Element>::Resize(
	int, const Rva009080A0Element *);
template <> void VectorClass<Rva009080A0Element>::Clear();
template <> int VectorClass<Rva009080A0Element>::ID(
	const Rva009080A0Element *);
template <> int VectorClass<Rva009080A0Element>::ID(
	const Rva009080A0Element &);
template <> DynamicVectorClass<Rva009080A0Element>::~DynamicVectorClass();
template <> bool DynamicVectorClass<Rva009080A0Element>::Resize(
	int, const Rva009080A0Element *);
template <> void DynamicVectorClass<Rva009080A0Element>::Clear();
template <> int DynamicVectorClass<Rva009080A0Element>::ID(
	const Rva009080A0Element *);
template <> int DynamicVectorClass<Rva009080A0Element>::ID(
	const Rva009080A0Element &);

template DynamicVectorClass<Rva009080A0Element>::DynamicVectorClass(
	unsigned int, const Rva009080A0Element *);
