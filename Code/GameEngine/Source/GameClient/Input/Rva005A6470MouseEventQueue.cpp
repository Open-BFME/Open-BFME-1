// cl: /O2 /Ob0

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct ICoord2D
{
	int x;
	int y;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MessageStream.h
class GameMessage
{
public:
	void appendPixelArgument(const ICoord2D &position);
	void appendIntegerArgument(int value);
};

#define RVA005A6470_STREAM_SLOT(n) virtual void slot##n();
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MessageStream.h
class MessageStream
{
public:
	RVA005A6470_STREAM_SLOT(00) RVA005A6470_STREAM_SLOT(01)
	RVA005A6470_STREAM_SLOT(02) RVA005A6470_STREAM_SLOT(03)
	RVA005A6470_STREAM_SLOT(04) RVA005A6470_STREAM_SLOT(05)
	RVA005A6470_STREAM_SLOT(06) RVA005A6470_STREAM_SLOT(07)
	RVA005A6470_STREAM_SLOT(08) RVA005A6470_STREAM_SLOT(09)
	RVA005A6470_STREAM_SLOT(10) RVA005A6470_STREAM_SLOT(11)
	RVA005A6470_STREAM_SLOT(12)
	virtual GameMessage *appendMessage(int type);
};
#undef RVA005A6470_STREAM_SLOT

extern MessageStream *TheMessageStream;
__declspec(dllimport) unsigned long __stdcall timeGetTime();

struct Rva005A6470MouseEvent
{
	int m_type;
	ICoord2D m_position;
	int m_value;
	int m_unused;
	unsigned char m_flags;
};

class Rva005A6470MouseEventQueue
{
public:
	void emit(Rva005A6470MouseEvent *event);
};

void Rva005A6470MouseEventQueue::emit(Rva005A6470MouseEvent *event)
{
	if (event->m_flags & 1)
		return;
	event->m_flags |= 1;
	TheMessageStream->appendMessage(0xB4);
	GameMessage *message = TheMessageStream->appendMessage(event->m_type);
	message->appendPixelArgument(event->m_position);
	message->appendIntegerArgument(event->m_value);
	message->appendIntegerArgument(timeGetTime());
}
