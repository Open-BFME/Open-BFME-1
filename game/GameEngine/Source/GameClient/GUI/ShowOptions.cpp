// cl: /DNDEBUG /MD
//
// Retail 0x0055E290: zero the 10 option-flag bytes, then open Options.apt
// unless the Options singleton at 0x012F4AD4 already exists.  The two
// incoming bytes are stored at 0x012F4AD1 / 0x012F4AD0 for the screen.

#include "../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Shell.h
class Shell
{
public:
	void push( AsciiString filename, bool shutdownImmediate = false );
};

extern Shell *TheShell;
class BfmeAptScreenOptions;
extern BfmeAptScreenOptions *g_obj12F4AD4;
unsigned char g_optByte12F4AD0;
unsigned char g_optByte12F4AD1;
// The Options constructor clears this four-byte cell; Save and Cancel
// pass its value to stopAudioEvent. Retail's loader initializes it to zero.
void *g_Va012F4AE4 = 0;
extern unsigned char g_optFlag12F4AD8;
extern unsigned char g_optFlag12F4AD9;
extern unsigned char g_optFlag12F4ADA;
extern unsigned char g_optFlag12F4ADB;
extern unsigned char g_optFlag12F4ADC;
extern unsigned char g_optFlag12F4ADD;
extern unsigned char g_optFlag12F4ADE;
extern unsigned char g_optFlag12F4ADF;
extern unsigned char g_optFlag12F4AE0;
extern unsigned char g_optFlag12F4AE1;

// ?_bfme_showOptions@@YAXHH@Z
void _bfme_showOptions( int a, int b )
{
	g_optFlag12F4AD8 = 0;
	g_optFlag12F4AD9 = 0;
	g_optFlag12F4ADA = 0;
	g_optFlag12F4ADB = 0;
	g_optFlag12F4ADC = 0;
	g_optFlag12F4ADD = 0;
	g_optFlag12F4ADE = 0;
	g_optFlag12F4ADF = 0;
	g_optFlag12F4AE0 = 0;
	g_optFlag12F4AE1 = 0;
	if( reinterpret_cast<void * &>(g_obj12F4AD4) == 0 )
	{
		g_optByte12F4AD1 = (unsigned char)a;
		g_optByte12F4AD0 = (unsigned char)b;
		TheShell->push( AsciiString( "Options.apt" ), false );
	}
}
