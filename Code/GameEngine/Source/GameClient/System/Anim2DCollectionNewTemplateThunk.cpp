// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/ini /Ireference/shims/iniexception /Ireference/shims/ini_noinline /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

// Allocate, construct, push onto the front of a list.
//
// 0x1C is pushed to operator new, so the template is twenty-eight bytes, and
// `mov [eax+4], ecx` puts the list link in the second word rather than the first.
//
// The constructor takes its AsciiString by value, so a temporary is
// copy-constructed on the stack and the function needs an EH frame to destroy it
// if the constructor throws. That temporary is why this uses the real
// AsciiString rather than a stand-in: a hand-rolled four-byte class with a
// declared copy constructor produces the same instructions in a different order.
#include "PreRTS.h"
#include "Common/AsciiString.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Anim2D.h
class Anim2DTemplate
{
public:
	Anim2DTemplate( AsciiString name );

	Int m_00;
	Anim2DTemplate *m_next;

private:
	Int m_08, m_0c, m_10, m_14, m_18;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Anim2D.h
class Anim2DCollection
{
public:
	Anim2DTemplate *newTemplate( const AsciiString &name );

private:
	unsigned char m_head[8];
	Anim2DTemplate *m_templateList;
};

// ?newTemplate@Anim2DCollection@@QAEPAVAnim2DTemplate@@ABVAsciiString@@@Z
Anim2DTemplate *Anim2DCollection::newTemplate( const AsciiString &name )
{
	Anim2DTemplate *tmpl = new Anim2DTemplate( name );

	tmpl->m_next = m_templateList;
	m_templateList = tmpl;

	return tmpl;
}
