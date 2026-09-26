// cl: /DNDEBUG /DWIN32 /MD /O2 /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef unsigned int UnsignedInt;
typedef int Int;
typedef bool Bool;

class GameMessage;
class BfmeByteStream;

class CRCInfo
{
public:
	Bool m_sawCRCMismatch;
	Bool m_skippedOne;
	_STL::list<UnsignedInt> m_data;
};

class GameLogic
{
public:
	void bfme_processLogicCRC(UnsignedInt crc, Int player, UnsignedInt frame,
		GameMessage *message, Bool forced, BfmeByteStream *stream);

	public:
	char m_prefix[0x6c];
	Bool m_crcProcessing;
};

extern GameLogic *TheGameLogic;

class RecorderClass
{
private:
	char m_prefix[8];
	CRCInfo *m_crcInfo;

public:
	void handleCRCMessage(UnsignedInt newCRC, Int playerIndex, Bool fromPlayback, UnsignedInt frame);
};

void RecorderClass::handleCRCMessage(UnsignedInt newCRC, Int playerIndex, Bool fromPlayback, UnsignedInt frame)
{
	if (fromPlayback)
		m_crcInfo->m_data.push_back(newCRC);
	if (!m_crcInfo->m_data.empty())
		m_crcInfo->m_data.pop_front();
	if (frame > 0 && !TheGameLogic->m_crcProcessing)
		TheGameLogic->bfme_processLogicCRC(newCRC, playerIndex, frame, 0, false, 0);
}
