// cl: /DNDEBUG /MD /O2 /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// BFME per-frame peer checksum report handler: RVA 0x0038B430, 1078 bytes.
// Called by gameplay MSG_LOGIC_CRC at 0x0039A0D6, local CRC generation at
// 0x0038DDF0, and replay CRC processing at 0x0009B60A through ILT 0x00038361.
// BFME keeps sorted per-frame linked records and a player-report bitmask;
// the Zero Hour reference's m_cachedCRCs map is not this implementation.
// Ret 0x18 and the three callers prove all six argument slots. The final
// pointer is an optional diagnostic memory stream, not a scalar checksum.
// Slot and wrapper names below describe the observed interfaces; they do not
// assert unavailable original class spellings. StreamList bodies are the
// retail STLport pointer-list push_back/size/pop_front operations.
#include <list>
extern "C" __declspec(dllimport) void __cdecl free(void*);
class BfmeByteStream
{
	public: void *takeBuffer(int*);
};
class BFMECRCStreamList: public _STL::list<BfmeByteStream*>
{
	public: void push_back(BfmeByteStream* const&);
	unsigned int size()const;
	void pop_front();
};
struct CRCRecord
{
	unsigned frame,crc,count,mask;
	BfmeByteStream *stream;
	CRCRecord*next;
};
class GameMessage
{
	public: void appendIntegerArgument(int);
	void appendTimestampArgument(unsigned);
	void appendBooleanArgument(bool);
};
class MessageStream
{
	public:
#define SLOT(n) virtual void slot##n();
	SLOT(0) SLOT(1) SLOT(2) SLOT(3) SLOT(4) SLOT(5) SLOT(6) SLOT(7) SLOT(8) SLOT(9) SLOT(10) SLOT(11) SLOT(12)
	virtual GameMessage* appendMessage(int);
	void propagateMessages();
};
class Network
{
	public:
	SLOT(0) SLOT(1) SLOT(2) SLOT(3) SLOT(4) SLOT(5) SLOT(6) SLOT(7) SLOT(8)
	virtual void liteupdate(bool);
	SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15) SLOT(16) SLOT(17) SLOT(18) SLOT(19)
	SLOT(20) SLOT(21) SLOT(22) SLOT(23) SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29)
	virtual void quitGame();
	SLOT(31) SLOT(32) SLOT(33) SLOT(34)
	virtual bool isPacketRouter();
	SLOT(36) virtual int getNumPlayers();
};
enum RecorderModeType
{
	RECORDER_PLAYBACK=1
};
class RecorderClass
{
	public:RecorderModeType getMode();
	char pad[0x2a0];
	unsigned players;
};
struct GlobalData
{
	char pad[0xcb4];
	unsigned networkRunAheadSlack; // +0xCB4, NetworkRunAheadSlack INI field
};
extern MessageStream *TheMessageStream;
extern Network *TheNetwork;
extern RecorderClass *TheRecorder;
extern GlobalData *TheGlobalData;
// VA 0x012A6F38: -1 disables the forced diagnostic frame.
extern int forcedCRCFrame;
// VA 0x012ED4E8: allows checks to continue after mismatch details are added.
extern bool ignoreCRCMismatches;
class GameLogic
{
	public:
	void bfme_processLogicCRC(unsigned crc,int player,unsigned frame,GameMessage *message,bool forced,BfmeByteStream *stream);
	void bfme_appendGameOverDetails();
	void bfme_reportDesync(BfmeByteStream*,unsigned,int);
	char pad[0x3c];
	unsigned currentFrame;
	int pad40;
	CRCRecord *first;
	BFMECRCStreamList::iterator streamIt;
	BFMECRCStreamList streams;
	char pad50[0x1c];
	bool sawMismatch;
};
extern GameLogic *TheGameLogic;
void GameLogic::bfme_processLogicCRC(unsigned crc,int player,unsigned frame,GameMessage *message,bool forced,BfmeByteStream *stream)
{
	CRCRecord *entry = first;
	CRCRecord *previous = 0;
	while (entry && frame>entry->frame)
	{
		previous=entry;
		entry=entry->next;
	}
	if (!forced && forcedCRCFrame!=currentFrame && (!entry || frame!=entry->frame))
	{
		if (message)message->appendBooleanArgument(false);
		entry=new CRCRecord;
		if (!entry)return;
		entry->crc=crc;
		entry->frame=frame;
		entry->stream = 0;
		if (stream)
		{
			entry->stream=stream;
			entry->count = 0;
			entry->mask = 0;
			streams.push_back(entry->stream);
			// Keep the diagnostic stream window aligned with network slack plus three.
			if (streams.size()>TheGlobalData->networkRunAheadSlack+3)
			{
				streamIt=streams.begin();
				BfmeByteStream *oldStream = *streamIt;
				if (oldStream)
				{
					int byteCount;
					free(oldStream->takeBuffer(&byteCount));
				}
				streams.pop_front();
			}
		}
		else
		{
			entry->count=1;
			entry->mask=1<<player;
		}
		if (!previous)
		{
			entry->next = first;
			first=entry;
		}
		else
		{
			entry->next=previous->next;
			previous->next=entry;
		}
		return;
	}
	bool fake=forcedCRCFrame!=-1 && forcedCRCFrame!=currentFrame;
	if (forced || forcedCRCFrame==currentFrame || (!fake && crc!=entry->crc && !TheGameLogic->sawMismatch))
	{
		bfme_appendGameOverDetails();
		if (!ignoreCRCMismatches || forcedCRCFrame==currentFrame)
		{
			streamIt=streams.begin();
			if (streamIt!=streams.end())
			{
				if (TheNetwork)
				{
					if (!sawMismatch && (!forced || TheNetwork->isPacketRouter()))
					{
						if (TheNetwork->isPacketRouter() && forced)
						{
							GameMessage *out=TheMessageStream->appendMessage(0x449);
							out->appendIntegerArgument(crc);
							out->appendTimestampArgument(currentFrame);
							out->appendBooleanArgument(TheRecorder->getMode()==1);
							out->appendBooleanArgument(true);
						}
						else if (message && !forced)message->appendBooleanArgument(true);
					}
					TheMessageStream->propagateMessages();
					if (TheNetwork)TheNetwork->liteupdate(false);
				}
				for (;streamIt!=streams.end();++streamIt)
				{
					bfme_reportDesync(*streamIt,frame,player);
					if (!TheRecorder || TheRecorder->getMode()!=1)
					{
						GameMessage *out=TheMessageStream->appendMessage(0x449);
						out->appendIntegerArgument(crc);
						out->appendTimestampArgument(currentFrame);
						out->appendBooleanArgument(TheRecorder->getMode()==1);
						out->appendBooleanArgument(true);
						TheMessageStream->propagateMessages();
						if (TheNetwork)TheNetwork->liteupdate(false);
					}
				}
				streams.clear();
				if (!TheRecorder || TheRecorder->getMode()!=1)if (TheNetwork)TheNetwork->quitGame();
			}
			else bfme_reportDesync(entry->stream,0,player);
			return;
		}
	}
	if (message && !forced)message->appendBooleanArgument(false);
	if (!(entry->mask & (1 << player)))
	{
		++entry->count;
		entry->mask |= (1 << player);
	}
	if (TheRecorder && TheRecorder->getMode()==1)
	{
		if (entry->count==TheRecorder->players)
		{
			if (previous)previous->next=entry->next;
			else first=entry->next;
			delete entry;
		}
	}
	else if (entry->count==TheNetwork->getNumPlayers())
	{
		if (previous)previous->next=entry->next;
		else first=entry->next;
		delete entry;
	}
}
