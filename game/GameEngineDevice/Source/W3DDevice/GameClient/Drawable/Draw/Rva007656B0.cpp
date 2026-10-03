// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/campaignmanagerascii /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// RVA 007656B0..007657AA (250 bytes): two-pointer cdecl nugget extraction. The matched caller in
// FXEventParser007764E0.cpp proves the existing address-qualified ABI.
#define _STLP_USE_STATIC_LIB
#include "PreRTS.h"
#include "GameClient/ParticleSys.h"
struct FxNugget007764E0;
struct Rva0076CEE0Element {
 AsciiString at00;
 bool at04;
 int at08,at0c,at10,at14,at18,at1c;
 bool at20;
};
struct Rva007656B0Record {
 AsciiString at00;
 bool at04;
 int at08,at0c,at10,at14;
 char at18[64];
};
// Stored callback is the address-preserved ILT 000236D7 -> 0075B710.
// Its existing matched set(Rva0075B710Obj*, int) writes receiver+0xC8.
void __cdecl j_000236d7();
void __cdecl extractNugget007656B0(const FxNugget007764E0 *nugget,Rva0076CEE0Element *out)
{
 Rva007656B0Record record=*(const Rva007656B0Record*)((const char*)nugget+0xb4);
 out->at14=(int)nugget;
 out->at18=(int)&j_000236d7;
 out->at00=record.at00;
 out->at04=record.at04;
 out->at08=record.at08;
 out->at0c=record.at0c;
 out->at10=record.at10;
 out->at18=0;
 out->at14=0;
 out->at1c=(int)TheParticleSystemManager->findTemplate(AsciiString(record.at18));
}
