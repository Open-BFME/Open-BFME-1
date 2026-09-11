// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/display /Ireference/shims/mouselayout /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "Common/Debug.h"

extern HWND ApplicationHWnd;

typedef unsigned int UnsignedInt;
typedef short Short;
typedef int Int;

struct ICoord2D
{
	Int x;
	Int y;
};

enum MouseButtonState
{
	MBS_Up = 0,
	MBS_Down,
	MBS_DoubleClick,
};

struct MouseIO
{
	ICoord2D pos;
	UnsignedInt time;
	Int wheelPos;
	ICoord2D deltaPos;
	MouseButtonState leftState;
	Int leftEvent;
	Int leftFrame;
	MouseButtonState rightState;
	Int rightEvent;
	Int rightFrame;
	MouseButtonState middleState;
	Int middleEvent;
	Int middleFrame;
};

// The retail GameClient vtable's getFrame entry is slot 0x68.  The BFME
// global is pinned under this address-derived view so the call remains tied to
// the existing global without inventing a second GameClient layout here.
class ClientRoot4120
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual UnsignedInt getFrame();
};

extern ClientRoot4120 *TheGameClient;

// BFME carries an additional 0x10-byte tail in Mouse before Win32Mouse's
// Win32 event ring.  This TU-local prefix keeps the real event fields at the
// retail offsets without altering the shared layout shim.
class Win32Mouse
{
protected:
	void translateEvent( UnsignedInt eventIndex, MouseIO *result );

	struct Win32MouseEvent
	{
		UINT msg;
		WPARAM wParam;
		LPARAM lParam;
		DWORD time;
	};

	char m_bfme_mouse_prefix[0x4E14];
	Win32MouseEvent m_eventBuffer[256];
};

// Translate a Win32 mouse event to the engine's MouseIO representation.
void Win32Mouse::translateEvent( UnsignedInt eventIndex, MouseIO *result )
{
	UINT msg = m_eventBuffer[ eventIndex ].msg;
	WPARAM wParam = m_eventBuffer[ eventIndex ].wParam;
	LPARAM lParam = m_eventBuffer[ eventIndex ].lParam;
	UnsignedInt frame;

	if( TheGameClient )
		frame = TheGameClient->getFrame();
	else
		frame = 1;

	result->leftState = result->middleState = result->rightState = MBS_Up;
	result->leftFrame = result->middleFrame = result->rightFrame = 0;
	result->pos.x = result->pos.y = result->wheelPos = 0;
	result->time = m_eventBuffer[ eventIndex ].time;

	switch( msg )
	{
		case WM_LBUTTONDOWN:
		{
			result->leftState = MBS_Down;
			result->leftFrame = frame;
			result->pos.x = LOWORD( lParam );
			result->pos.y = HIWORD( lParam );
			break;
		}

		case WM_LBUTTONUP:
		{
			result->leftState = MBS_Up;
			result->leftFrame = frame;
			result->pos.x = LOWORD( lParam );
			result->pos.y = HIWORD( lParam );
			break;
		}

		case WM_LBUTTONDBLCLK:
		{
			result->leftState = MBS_DoubleClick;
			result->leftFrame = frame;
			result->pos.x = LOWORD( lParam );
			result->pos.y = HIWORD( lParam );
			break;
		}

		case WM_MBUTTONDOWN:
		{
			result->middleState = MBS_Down;
			result->middleFrame = frame;
			result->pos.x = LOWORD( lParam );
			result->pos.y = HIWORD( lParam );
			break;
		}

		case WM_MBUTTONUP:
		{
			result->middleState = MBS_Up;
			result->middleFrame = frame;
			result->pos.x = LOWORD( lParam );
			result->pos.y = HIWORD( lParam );
			break;
		}

		case WM_MBUTTONDBLCLK:
		{
			result->middleState = MBS_DoubleClick;
			result->middleFrame = frame;
			result->pos.x = LOWORD( lParam );
			result->pos.y = HIWORD( lParam );
			break;
		}

		case WM_RBUTTONDOWN:
		{
			result->rightState = MBS_Down;
			result->rightFrame = frame;
			result->pos.x = LOWORD( lParam );
			result->pos.y = HIWORD( lParam );
			break;
		}

		case WM_RBUTTONUP:
		{
			result->rightState = MBS_Up;
			result->rightFrame = frame;
			result->pos.x = LOWORD( lParam );
			result->pos.y = HIWORD( lParam );
			break;
		}

		case WM_RBUTTONDBLCLK:
		{
			result->rightState = MBS_DoubleClick;
			result->rightFrame = frame;
			result->pos.x = LOWORD( lParam );
			result->pos.y = HIWORD( lParam );
			break;
		}

		case WM_MOUSEMOVE:
		{
			result->pos.x = LOWORD( lParam );
			result->pos.y = HIWORD( lParam );
			break;
		}

		case 0x020A:
		{
			POINT p;
			p.x = LOWORD( lParam );
			p.y = HIWORD( lParam );
			ScreenToClient( ApplicationHWnd, &p );
			result->wheelPos = (Short)HIWORD( wParam );
			result->pos.x = p.x;
			result->pos.y = p.y;
			break;
		}

		default:
		{
			DEBUG_CRASH(( "translateEvent: Unknown Win32 mouse event [%d,%d,%d]\n",
							 msg, wParam, lParam ));
			return;
		}
	}
}
