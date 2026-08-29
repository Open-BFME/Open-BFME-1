// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// readable body of ?setPitch@W3DView@@: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DView.cpp

#include "GameClient/View.h"

// BFME's W3DView layout differs from the shared Zero Hour header.  This
// focused declaration keeps only the member call identities needed by the
// retail setPitch body; the flags are addressed from the verified BFME
// offsets below.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DView.h
class W3DView : public View
{
public:
	virtual void setPitch( Real angle );

private:
	void setCameraTransform();
};

void W3DView::setPitch( Real angle )
{
	View::setPitch( angle );

	unsigned char *view_bytes = reinterpret_cast<unsigned char *>(this);
	view_bytes[0x1DC] = 0;
	view_bytes[0x204] = 0;
	view_bytes[0x27C] = 0;
	view_bytes[0x228] = 0;
	view_bytes[0x27D] = 0;
	setCameraTransform();
}
