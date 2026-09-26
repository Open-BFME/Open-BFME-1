// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/stringbaseunicode /Iinputs/reference/shims/stringbaseascii /Iinputs/reference/shims/asciistringsetoutofline /Iinputs/reference/shims/fullfade /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#define Matrix4x4 Matrix4
#include "PreRTS.h"
#include "GameClient/GameWindowTransitions.h"

// BFME's Display rectangle entrypoints take floating-point coordinates and are
// nonvirtual, unlike the Zero Hour Display header's integer/virtual surface.
class Display
{
public:
	void drawOpenRect(float x, float y, float width, float height, float lineWidth, int color);
	void drawFillRect(float x, float y, float width, float height, int color);
};
extern Display *TheDisplay;

void FlashTransition::draw()
{
	switch (m_drawState)
	{
	case FLASHTRANSITION_FADE_IN_1:
		TheDisplay->drawOpenRect((float)(m_pos.x + 1), (float)(m_pos.y + 1), (float)(m_size.x - 2), (float)m_size.y, 1.0f, 0x64ffcb2d);
		TheDisplay->drawFillRect((float)(m_pos.x + 1), (float)(m_pos.y + 1), (float)(m_size.x - 2), (float)m_size.y, 0x21ffcb2d);
		break;
	case FLASHTRANSITION_FADE_IN_2:
		TheDisplay->drawOpenRect((float)(m_pos.x + 1), (float)(m_pos.y + 1), (float)(m_size.x - 2), (float)m_size.y, 1.0f, 0x96ffcb2d);
		TheDisplay->drawFillRect((float)(m_pos.x + 1), (float)(m_pos.y + 1), (float)(m_size.x - 2), (float)m_size.y, 0x42ffcb2d);
		break;
	case FLASHTRANSITION_FADE_IN_3:
		TheDisplay->drawOpenRect((float)(m_pos.x + 1), (float)(m_pos.y + 1), (float)(m_size.x - 2), (float)m_size.y, 1.0f, 0xc8ffcb2d);
		TheDisplay->drawFillRect((float)(m_pos.x + 1), (float)(m_pos.y + 1), (float)(m_size.x - 2), (float)m_size.y, 0x63ffcb2d);
		break;
	case FLASHTRANSITION_FADE_TO_BACKGROUND_1:
		TheDisplay->drawOpenRect((float)(m_pos.x + 1), (float)(m_pos.y + 1), (float)(m_size.x - 2), (float)m_size.y, 1.0f, 0xfaffcb2d);
		TheDisplay->drawFillRect((float)(m_pos.x + 1), (float)(m_pos.y + 1), (float)(m_size.x - 2), (float)m_size.y, 0x4bffcb2d);
		break;
	case FLASHTRANSITION_FADE_TO_BACKGROUND_2:
		TheDisplay->drawOpenRect((float)(m_pos.x + 1), (float)(m_pos.y + 1), (float)(m_size.x - 2), (float)m_size.y, 1.0f, 0xfaffcb2d);
		TheDisplay->drawFillRect((float)(m_pos.x + 1), (float)(m_pos.y + 1), (float)(m_size.x - 2), (float)m_size.y, 0x32ffcb2d);
		break;
	case FLASHTRANSITION_FADE_TO_BACKGROUND_3:
		TheDisplay->drawOpenRect((float)(m_pos.x + 1), (float)(m_pos.y + 1), (float)(m_size.x - 2), (float)m_size.y, 1.0f, 0xfaffcb2d);
		TheDisplay->drawFillRect((float)(m_pos.x + 1), (float)(m_pos.y + 1), (float)(m_size.x - 2), (float)m_size.y, 0x19ffcb2d);
		break;
	case FLASHTRANSITION_FADE_TO_BACKGROUND_4:
		TheDisplay->drawOpenRect((float)(m_pos.x + 1), (float)(m_pos.y + 1), (float)(m_size.x - 2), (float)m_size.y, 1.0f, 0xfaffcb2d);
		TheDisplay->drawFillRect((float)(m_pos.x + 1), (float)(m_pos.y + 1), (float)(m_size.x - 2), (float)m_size.y, 0x0affcb2d);
		break;
	}
}
