// ?rva004879A0@Rva004879A0@@QAEPAVGameWindow@@PAV2@PAX@Z
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/GameEngine/Include /Ireference/shims/asciistringsetoutofline /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /ICode/GameEngine/Source/Common/System /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4
#include "PreRTS.h"
#include "GameClient/GameWindow.h"
#include "GameClient/WinInstanceData.h"
#include <string.h>

class Open2479440Record
{
public:
	void *m0;
	int m1;
	int m2;
	int m3;
	int m4;
	int m5;
	int m6;
	int m7;
	int m8;
	int m9;
	int m10;
	int m11;
	int m12;
};

class Rva00479440
{
public:
	void publish( Open2479440Record *out, char keep );
};

extern "C" void *Rva00484F60GetDataTemplate( char *type, UnsignedInt *size );
GameWindow *createGadget( char *type, void *data, Open2479440Record *record,
	GameWindow *source );

class Rva004879A0
{
public:
	GameWindow *rva004879A0( GameWindow *source, void *unused );
};

GameWindow *Rva004879A0::rva004879A0( GameWindow *source, void *unused )
{
	if( source == 0 )
		return 0;

	WinInstanceData *instance = source->winGetInstanceData();
	if( instance == 0 )
		return 0;

	UnsignedInt style = instance->m_style;
	char *type = 0;
	if( ( style & 0x00000001 ) != 0 )
		type = "PUSHBUTTON";
	else if( ( style & 0x00000004 ) != 0 )
		type = "CHECKBOX";
	else if( ( style & 0x00002000 ) != 0 )
		type = "TABCONTROL";
	else if( ( style & 0x00000002 ) != 0 )
		type = "RADIOBUTTON";
	else if( ( style & 0x00000010 ) != 0 )
		type = "HORZSLIDER";
	else if( ( style & 0x00000008 ) != 0 )
		type = "VERTSLIDER";
	else if( ( style & 0x00000020 ) != 0 )
		type = "SCROLLLISTBOX";
	else if( ( style & 0x00008000 ) != 0 )
		type = "COMBOBOX";
	else if( ( style & 0x00000100 ) != 0 )
		type = "PROGRESSBAR";
	else if( ( style & 0x00000080 ) != 0 )
		type = "STATICTEXT";
	else if( ( style & 0x00000040 ) != 0 )
		type = "ENTRYFIELD";
	else
		return 0;

	Open2479440Record record;
	record.m0 = 0;
	record.m1 = 0;
	record.m2 = 0;
	record.m3 = 0;
	record.m4 = 0;
	record.m5 = 0;
	record.m6 = 0;
	record.m7 = 0;
	record.m8 = 0;
	record.m9 = 0;
	record.m10 = 0;
	record.m11 = 0;
	record.m12 = 0;
	reinterpret_cast<Rva00479440 *>( source )->publish( &record, 1 );
	record.m0 = unused;

	void *userData = source->winGetUserData();
	void *data = 0;
	if( userData != 0 )
	{
		UnsignedInt size = 0;
		data = Rva00484F60GetDataTemplate( type, &size );
		if( data == 0 )
			return 0;
		memcpy( data, userData, size );
	}

	return createGadget( type, data, &record, source );
}
