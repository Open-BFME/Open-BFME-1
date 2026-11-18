// stlport
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// BFME widens WindowLayoutInfo with one scalar and two AsciiString members.

#include <list>

#include "../../../Include/Common/ScalarTypes.h"

class WindowLayout;
class GameWindow;

typedef void (*WindowLayoutInitFunc)(WindowLayout *, void *);
typedef void (*WindowLayoutUpdateFunc)(WindowLayout *, void *);
typedef void (*WindowLayoutShutdownFunc)(WindowLayout *, void *);

#include "../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

typedef std::list<GameWindow *> GameWindowList;

class WindowLayoutInfo
{
public:
	WindowLayoutInfo();

	UnsignedInt version;
	WindowLayoutInitFunc init;
	WindowLayoutUpdateFunc update;
	WindowLayoutShutdownFunc shutdown;
	void *_bfme_unk_10;
	AsciiString initNameString;
	AsciiString updateNameString;
	AsciiString shutdownNameString;
	AsciiString _bfme_unk_20;
	AsciiString _bfme_unk_24;
	GameWindowList windows;
};

WindowLayoutInfo::WindowLayoutInfo() :
	version(0),
	init(0),
	update(0),
	shutdown(0),
	_bfme_unk_10(0),
	initNameString(AsciiString::TheEmptyString),
	updateNameString(AsciiString::TheEmptyString),
	shutdownNameString(AsciiString::TheEmptyString)
{
	windows.clear();
}
