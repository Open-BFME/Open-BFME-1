// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/stringbaseunicode /Iinputs/reference/shims/stringbaseascii /Iinputs/reference/shims/asciistringsetoutofline /Iinputs/reference/shims/fullfade /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#define Matrix4x4 Matrix4
#include "PreRTS.h"
#include "GameClient/GameWindowTransitions.h"

class Display;
extern Display *TheDisplay;

class Bfme5Host { public: void bfmeRunB(int, int, int, int, int); };
class Gen_00433690 { public: void bfmeRun(void *, void *, void *, void *, void *, void *); };

// Preserve the float argument bits while calling the ledger declarations.
typedef void (Bfme5Host::*FillRectCall)(float, float, float, float, int);
typedef void (Gen_00433690::*OpenRectCall)(float, float, float, float, float, int);
#define drawFillRect(display, x, y, width, height, color) (reinterpret_cast<Bfme5Host *>(display)->*reinterpret_cast<FillRectCall>(&Bfme5Host::bfmeRunB))(x, y, width, height, color)
#define drawOpenRect(display, x, y, width, height, lineWidth, color) (reinterpret_cast<Gen_00433690 *>(display)->*reinterpret_cast<OpenRectCall>(&Gen_00433690::bfmeRun))(x, y, width, height, lineWidth, color)

void FlashTransition::draw()
{
	switch (m_drawState)
	{
	case FLASHTRANSITION_FADE_IN_1:
		drawOpenRect(TheDisplay, (float)(m_pos.x + 1), (float)(m_pos.y + 1), (float)(m_size.x - 2), (float)m_size.y, 1.0f, 0x64ffcb2d);
		drawFillRect(TheDisplay, (float)(m_pos.x + 1), (float)(m_pos.y + 1), (float)(m_size.x - 2), (float)m_size.y, 0x21ffcb2d);
		break;
	case FLASHTRANSITION_FADE_IN_2:
		drawOpenRect(TheDisplay, (float)(m_pos.x + 1), (float)(m_pos.y + 1), (float)(m_size.x - 2), (float)m_size.y, 1.0f, 0x96ffcb2d);
		drawFillRect(TheDisplay, (float)(m_pos.x + 1), (float)(m_pos.y + 1), (float)(m_size.x - 2), (float)m_size.y, 0x42ffcb2d);
		break;
	case FLASHTRANSITION_FADE_IN_3:
		drawOpenRect(TheDisplay, (float)(m_pos.x + 1), (float)(m_pos.y + 1), (float)(m_size.x - 2), (float)m_size.y, 1.0f, 0xc8ffcb2d);
		drawFillRect(TheDisplay, (float)(m_pos.x + 1), (float)(m_pos.y + 1), (float)(m_size.x - 2), (float)m_size.y, 0x63ffcb2d);
		break;
	case FLASHTRANSITION_FADE_TO_BACKGROUND_1:
		drawOpenRect(TheDisplay, (float)(m_pos.x + 1), (float)(m_pos.y + 1), (float)(m_size.x - 2), (float)m_size.y, 1.0f, 0xfaffcb2d);
		drawFillRect(TheDisplay, (float)(m_pos.x + 1), (float)(m_pos.y + 1), (float)(m_size.x - 2), (float)m_size.y, 0x4bffcb2d);
		break;
	case FLASHTRANSITION_FADE_TO_BACKGROUND_2:
		drawOpenRect(TheDisplay, (float)(m_pos.x + 1), (float)(m_pos.y + 1), (float)(m_size.x - 2), (float)m_size.y, 1.0f, 0xfaffcb2d);
		drawFillRect(TheDisplay, (float)(m_pos.x + 1), (float)(m_pos.y + 1), (float)(m_size.x - 2), (float)m_size.y, 0x32ffcb2d);
		break;
	case FLASHTRANSITION_FADE_TO_BACKGROUND_3:
		drawOpenRect(TheDisplay, (float)(m_pos.x + 1), (float)(m_pos.y + 1), (float)(m_size.x - 2), (float)m_size.y, 1.0f, 0xfaffcb2d);
		drawFillRect(TheDisplay, (float)(m_pos.x + 1), (float)(m_pos.y + 1), (float)(m_size.x - 2), (float)m_size.y, 0x19ffcb2d);
		break;
	case FLASHTRANSITION_FADE_TO_BACKGROUND_4:
		drawOpenRect(TheDisplay, (float)(m_pos.x + 1), (float)(m_pos.y + 1), (float)(m_size.x - 2), (float)m_size.y, 1.0f, 0xfaffcb2d);
		drawFillRect(TheDisplay, (float)(m_pos.x + 1), (float)(m_pos.y + 1), (float)(m_size.x - 2), (float)m_size.y, 0x0affcb2d);
		break;
	}
}
