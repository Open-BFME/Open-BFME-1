// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/stringbaseunicode /Iinputs/reference/shims/stringbaseascii /Iinputs/reference/shims/asciistringsetoutofline /Iinputs/reference/shims/fullfade /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// FadeTransition::draw, retail 0x0059C580. Zero Hour twin at
// GeneralsMD/Code/GameEngine/Source/GameClient/GUI/GameWindowTransitionsStyles.cpp.
// Retail retains the nine alpha steps and Transition/FadeTransition layout,
// but uses GameWindow enabled image at +0x48 and a nonvirtual float-coordinate
// Display::drawImage call (ILT 0x0000A114).
#define Matrix4x4 Matrix4
#include "PreRTS.h"
#include "GameClient/GameWindowTransitions.h"
class Display { public: void drawImage(const Image*,float,float,float,float,int,int=2); };
extern Display *TheDisplay;
void FadeTransition::draw( void )
{
	if(!m_win)
		return;
	const Image *image = *reinterpret_cast<const Image **>(reinterpret_cast<char *>(m_win) + 0x48);
	switch (m_drawState) 
	{
		case FADETRANSITION_FADE_IN_1:
		{
			TheDisplay->drawImage(image, m_pos.x, m_pos.y, m_pos.x + m_size.x, m_pos.y + m_size.y, ((unsigned int)0xffffff | ((unsigned int)25 << 24)));
		}
		break;
		case FADETRANSITION_FADE_IN_2:
		{
			TheDisplay->drawImage(image, m_pos.x, m_pos.y, m_pos.x + m_size.x, m_pos.y + m_size.y, ((unsigned int)0xffffff | ((unsigned int)50 << 24)));
		}
		break;
		case FADETRANSITION_FADE_IN_3:
		{
			TheDisplay->drawImage(image, m_pos.x, m_pos.y, m_pos.x + m_size.x, m_pos.y + m_size.y, ((unsigned int)0xffffff | ((unsigned int)75 << 24)));
		}
		break;
		case FADETRANSITION_FADE_IN_4:
		{
			TheDisplay->drawImage(image, m_pos.x, m_pos.y, m_pos.x + m_size.x, m_pos.y + m_size.y, ((unsigned int)0xffffff | ((unsigned int)100 << 24)));
		}
		break;
		case FADETRANSITION_FADE_IN_5:
		{
			TheDisplay->drawImage(image, m_pos.x, m_pos.y, m_pos.x + m_size.x, m_pos.y + m_size.y, ((unsigned int)0xffffff | ((unsigned int)125 << 24)));
		}
		break;
		case FADETRANSITION_FADE_IN_6:
		{
			TheDisplay->drawImage(image, m_pos.x, m_pos.y, m_pos.x + m_size.x, m_pos.y + m_size.y, ((unsigned int)0xffffff | ((unsigned int)150 << 24)));
		}
		break;
		case FADETRANSITION_FADE_IN_7:
		{
			TheDisplay->drawImage(image, m_pos.x, m_pos.y, m_pos.x + m_size.x, m_pos.y + m_size.y, ((unsigned int)0xffffff | ((unsigned int)175 << 24)));
		}
		break;
		case FADETRANSITION_FADE_IN_8:
		{
			TheDisplay->drawImage(image, m_pos.x, m_pos.y, m_pos.x + m_size.x, m_pos.y + m_size.y, ((unsigned int)0xffffff | ((unsigned int)200 << 24)));
		}
		break;
		case FADETRANSITION_FADE_IN_9:
		{
			TheDisplay->drawImage(image, m_pos.x, m_pos.y, m_pos.x + m_size.x, m_pos.y + m_size.y, ((unsigned int)0xffffff | ((unsigned int)225 << 24)));
		}
	}
}
	