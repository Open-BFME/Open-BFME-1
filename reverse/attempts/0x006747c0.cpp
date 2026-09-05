// ?d_006747c0@NetCommandMsg@@QAEPAV1@PAVAsciiString@@@Z
// partial score=0.55 date=2026-09-05
// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib

#include "string_base.h"

extern const char g_bfmeEmptyAscii[];

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;

inline void *operator new(unsigned int, void *place) { return place; }

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString() { m_text = 0; }
	AsciiString(const char *str)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(str);
	}
	AsciiString(const AsciiString &that)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(*(const StringBase<char> *)&that);
	}
	~AsciiString()
	{
		((StringBase<char> *)this)->releaseBuffer();
	}
	void __cdecl format(AsciiString fmt, ...);

private:
	char *m_text;
};

struct BfmeStringData
{
	UnsignedShort m_refCount;
	UnsignedShort m_numCharsAllocated;
	UnsignedShort m_len;
	UnsignedShort m_pad;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandMsg.h
enum NetCommandType
{
	NETCOMMANDTYPE_FRAMEINFO = 3
};

Bool DoesCommandRequireACommandID(NetCommandType type);

class NetCommandRef;
class NetPacket
{
public:
	static NetCommandRef *ConstructNetCommandMsgFromRawData(unsigned char *data, unsigned short len);
};

class NetCommandMsg
{
public:
	UnsignedInt getExecutionFrame() { return m_executionFrame; }
	UnsignedInt getPlayerID() { return m_playerID; }
	UnsignedShort getID() { return m_id; }
	NetCommandType getNetCommandType() { return m_commandType; }

	NetCommandMsg *d_006747c0(AsciiString *out);

	void *m_vptr;								// this+0x00
	UnsignedInt m_timestamp;					// this+0x04
	UnsignedInt m_executionFrame;				// this+0x08
	UnsignedInt m_playerID;					// this+0x0C
	UnsignedShort m_id;						// this+0x10
	NetCommandType m_commandType;				// this+0x14
	Int m_referenceCount;						// this+0x18
};

NetCommandMsg *NetCommandMsg::d_006747c0(AsciiString *out)
{
	AsciiString typeNameHolder;
	AsciiString result;

	if (DoesCommandRequireACommandID(m_commandType)) {
		BfmeStringData *hdr = *(BfmeStringData **)(void *)NetPacket::ConstructNetCommandMsgFromRawData((unsigned char *)&typeNameHolder, (unsigned short)m_commandType);
		const char *name = hdr ? (const char *)(hdr + 1) : g_bfmeEmptyAscii;
		result.format(AsciiString("%s, frame=%d, player=%d, id=%d"), name, m_executionFrame, m_playerID, m_id);
	} else {
		BfmeStringData *hdr = *(BfmeStringData **)(void *)NetPacket::ConstructNetCommandMsgFromRawData((unsigned char *)&typeNameHolder, (unsigned short)m_commandType);
		const char *name = hdr ? (const char *)(hdr + 1) : g_bfmeEmptyAscii;
		result.format(AsciiString("%s, frame=%d, player=%d"), name, m_executionFrame, m_playerID);
	}

	new (out) AsciiString(result);
	return this;
}
