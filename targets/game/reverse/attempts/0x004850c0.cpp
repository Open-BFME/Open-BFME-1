// ?parseData@@YA_NPAPAXPAD1@Z
// partial score=0.6 date=2026-09-06
// cl: /Igame/GameEngine/Include /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/asciistringsetoutofline /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Igame/GameEngine/Source/Common/System /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#include "PreRTS.h"
#include "Lib/BaseType.h"
#include "GameClient/Gadget.h"
#include <string.h>
#include <stdlib.h>
struct LocalListboxData : ListboxData { char retailExtra[12]; };
static __declspec(noinline) Bool parseData( void **data, char *type, char *buffer )
{
  char *c;
  static EntryData eData;
  static SliderData sData;
  static LocalListboxData lData;
  static TextData tData;
	static RadioButtonData rData;
	static ComboBoxData cData;

  if( !strcmp( type, "VERTSLIDER" ) || !strcmp( type, "HORZSLIDER" ) ) 
	{

    memset( &sData, 0, sizeof( SliderData ) );

	  c = strtok( buffer, " \t\n\r" );
    sData.minVal = atoi(c);

	  c = strtok( NULL, " \t\n\r" );
    sData.maxVal = atoi(c);

    *data = &sData;

  } 
	else if( !strcmp( type, "SCROLLLISTBOX" ) ) 
	{

    memset( &lData, 0, sizeof( LocalListboxData ) );

	  c = strtok( buffer, " \t\n\r" );
    lData.listLength = atoi(c);

//	  c = strtok( NULL, " \t\n\r" );
//    lData.entryHeight = atoi(c);

	  c = strtok( NULL, " \t\n\r" );
    lData.autoScroll = atoi(c);

	  c = strtok( NULL, " \t\n\r" );
    lData.autoPurge = atoi(c);

	  c = strtok( NULL, " \t\n\r" );
    lData.scrollBar = atoi(c);

	  c = strtok( NULL, " \t\n\r" );
    lData.multiSelect = atoi(c);

		c = strtok( NULL, " \t\n\r" );
		lData.forceSelect = atoi(c);
		
    *data = &lData;

  } 
	else if( !strcmp( type, "ENTRYFIELD" ) ) 
	{

    memset( &eData, 0, sizeof( EntryData ) );

	  c = strtok( buffer, " \t\n\r" );
    eData.maxTextLen = atoi(c);

	  c = strtok( NULL, " \t\n\r" );
//    if (c)
//      eData.entryWidth = atoi(c);
//    else
//      eData.entryWidth = -1;

		c = strtok( NULL, " \t\n\r" );
		if (c)
		{
			eData.secretText = atoi(c);

			if( eData.secretText != FALSE )
				eData.secretText = TRUE;
		}
		else
			eData.secretText = FALSE;

		c = strtok( NULL, " \t\n\r" );
		if (c)
		{
			eData.numericalOnly = ( atoi(c) == 1 );
			eData.alphaNumericalOnly = ( atoi(c) == 2 );
			eData.aSCIIOnly = ( atoi(c) == 3 );
		}
		else
		{
			eData.numericalOnly = FALSE;
			eData.alphaNumericalOnly = FALSE;
			eData.aSCIIOnly = FALSE;
		}
    *data = &eData;

  } 
	else if( !strcmp( type, "STATICTEXT" ) ) 
	{

	  c = strtok( buffer, " \t\n\r" );
    tData.centered = atoi(c);
		
		if( tData.centered != FALSE )
			tData.centered = TRUE;

	  c = strtok( NULL, " \t\n\r" );

		/** @todo need to get a label from the translation manager, uncomment
		the following line and remove the WideChar assignment when
		we have it */
//		text = StringManagerFetch( c );
//		text = L"Need StrManager, Remove me!";
//		TheWindowManager->winStrcpy( tData.text, text );

		*data = &tData;

  }
	else if( !strcmp( type, "RADIOBUTTON" ) ) 
	{ 

		c = strtok( buffer, " \t\n\r" );
		rData.group = atoi(c);
/// @todo Colin: Why was this here???
//		if( tData.centered != FALSE )
//		{
//			tData.centered = TRUE;
//		}
		*data = &rData;
	}	
	else
    *data = NULL;

  return TRUE;

}  // end parseData
// forceParseData absent-from-retail: expose private static ABI.
Bool forceParseData(void **data,char*type,char*buffer) { return parseData(data,type,buffer); }
