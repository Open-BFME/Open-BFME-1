// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /DZH_EMIT_POOL_GLUE /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4
#include "PreRTS.h"
#include <stdio.h>
#include "GameClient/GameWindowManager.h"

static const char *RetailAsciiString(const void *stringObject)
{
	const char *data = *(const char * const *)stringObject;
	return data ? data + 8 : (const char *)0x0107388B;
}

void PrintInfoRecursive(GameWindow *win, FILE *fp)
{
	if (!win)
		return;

	ICoord2D pos, size;
	win->winGetSize(&size.x, &size.y);
	win->winGetPosition(&pos.x, &pos.y);
	fprintf(fp, "ControlBarResizer %s\n", RetailAsciiString((const char *)win->winGetInstanceData() + 0x18C));
	fprintf(fp, "  AltPosition = X:%d Y:%d\n", pos.x, pos.y);
	fprintf(fp, "  AltSize = X:%d Y:%d\n", size.x, size.y);
	fprintf(fp, "END\n\n");

	PrintInfoRecursive(win->winGetChild(), fp);
	PrintInfoRecursive(win->winGetNext(), fp);
}
