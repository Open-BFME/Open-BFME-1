// ??0GameMessage@@QAE@ABV0@@Z
// partial score=0.6205357142857143 date=2026-09-26
// cl: /DNDEBUG /MD /EHs-c- /Igame/Libraries/Source/WWVegas/WWLib
#include "message_stream.h"

struct GameMessageLocationRaw { Real x, y, z; };
struct GameMessagePixelRaw { Int x, y; };

union GameMessageArgumentType
{
	Int integer;
	Real real;
	Bool boolean;
	UnsignedInt id;
	GameMessageLocationRaw location;
	GameMessagePixelRaw pixel;
	struct { Int left, top, right, bottom; } pixelRegion;
	WideChar wideChar;
};

struct GameMessage::Argument
{
	void *vtable;
	Argument *m_next;
	GameMessageArgumentType m_data;
	Int m_type;
};

GameMessage::GameMessage(const GameMessage &source)
{
	m_playerIndex = source.m_playerIndex;
	m_type = source.m_type;
	m_argList = 0;
	m_argTail = 0;
	m_argCount = 0;
	m_list = 0;
	m_reserved1 = 0;
	m_reserved2 = 0;

	Int argumentCount = source.m_argCount;
	for (Int i = 0; i < argumentCount; ++i)
	{
		Argument *sourceArg = source.m_argList;
		Int index = 0;
		while (sourceArg && index < i)
		{
			sourceArg = sourceArg->m_next;
			++index;
		}
		if (sourceArg)
		switch (sourceArg->m_type)
		{
		case 0: { Int value = source.getArgument(i)->integer; Argument *arg = allocArg(); arg->m_data.integer = value; arg->m_type = 0; break; }
		case 1: { Real value = source.getArgument(i)->real; Argument *arg = allocArg(); arg->m_data.real = value; arg->m_type = 1; break; }
		case 2: { Bool value = source.getArgument(i)->boolean; Argument *arg = allocArg(); arg->m_data.boolean = value; arg->m_type = 2; break; }
		case 3: { UnsignedInt value = source.getArgument(i)->id; Argument *arg = allocArg(); arg->m_data.id = value; arg->m_type = 3; break; }
		case 4: { UnsignedInt value = source.getArgument(i)->id; Argument *arg = allocArg(); arg->m_data.id = value; arg->m_type = 4; break; }
		case 5: { UnsignedInt value = source.getArgument(i)->id; Argument *arg = allocArg(); arg->m_data.id = value; arg->m_type = 5; break; }
		case 6: { UnsignedInt value = source.getArgument(i)->id; Argument *arg = allocArg(); arg->m_data.id = value; arg->m_type = 6; break; }
		case 7: { GameMessageLocationRaw value = source.getArgument(i)->location; Argument *arg = allocArg(); arg->m_data.location = value; arg->m_type = 7; break; }
		case 8: { GameMessagePixelRaw value = source.getArgument(i)->pixel; Argument *arg = allocArg(); arg->m_data.pixel = value; arg->m_type = 8; break; }
		case 9: { const GameMessageArgumentType *value = source.getArgument(i); Argument *arg = allocArg(); arg->m_data.pixelRegion = value->pixelRegion; arg->m_type = 9; break; }
		case 10: { UnsignedInt value = source.getArgument(i)->id; Argument *arg = allocArg(); arg->m_data.id = value; arg->m_type = 10; break; }
		case 11: { const GameMessageArgumentType *value = source.getArgument(i); Argument *arg = allocArg(); arg->m_data.wideChar = value->wideChar; arg->m_type = 11; break; }
		}
	}
}
