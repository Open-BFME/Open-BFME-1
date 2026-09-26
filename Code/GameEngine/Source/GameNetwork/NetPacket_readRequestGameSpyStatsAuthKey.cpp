// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline

// Retail 0x0067EB80. Prior batch reached 187/187 with EH saved-esp / mov ecx,esp
// swapped on the by-value StringBase temporary. This round uses the
// StringInline private-base forwarding shape instead of a StringBase temporary.

#include "StringInline.h"

typedef int Int;
typedef unsigned char UnsignedByte;

class NetCommandMsg
{
public:
	NetCommandMsg();
	virtual ~NetCommandMsg();

protected:
	unsigned char m_bfmeHead[0x1C - 4];
};

class BFMENetRequestGameSpyStatsAuthKeyCommandMsg : public NetCommandMsg
{
public:
	BFMENetRequestGameSpyStatsAuthKeyCommandMsg();
	void setText1C(AsciiString text);

	AsciiString m_text1C;
};

class BFMENetGameSpyStatsAuthKeyCommandMsg : public NetCommandMsg
{
public:
	BFMENetGameSpyStatsAuthKeyCommandMsg();
	void setText1C(AsciiString text);
	void setText20(AsciiString text);

	AsciiString m_text1C;
	AsciiString m_text20;
};

class NetPacket
{
protected:
	static NetCommandMsg *readRequestGameSpyStatsAuthKeyMessage(UnsignedByte *packetData, Int &readOffset);
	static NetCommandMsg *readGameSpyStatsAuthKeyMessage(UnsignedByte *packetData, Int &readOffset);
};

NetCommandMsg *NetPacket::readRequestGameSpyStatsAuthKeyMessage(UnsignedByte *packetData, Int &readOffset)
{
	BFMENetRequestGameSpyStatsAuthKeyCommandMsg *msg = new BFMENetRequestGameSpyStatsAuthKeyCommandMsg;
	char textBuffer[256];
	char *textCursor = textBuffer;

	while (packetData[readOffset] != 0) {
		*textCursor = packetData[readOffset];
		++textCursor;
		++readOffset;
	}
	*textCursor = 0;
	++readOffset;
	msg->setText1C(AsciiString(textBuffer));
	return msg;
}

NetCommandMsg *NetPacket::readGameSpyStatsAuthKeyMessage(UnsignedByte *packetData, Int &readOffset)
{
	BFMENetGameSpyStatsAuthKeyCommandMsg *msg =
		new BFMENetGameSpyStatsAuthKeyCommandMsg;
	char textBuffer[256];
	char *textCursor = textBuffer;

	while (packetData[readOffset] != 0) {
		*textCursor = packetData[readOffset];
		++textCursor;
		++readOffset;
	}
	*textCursor = 0;
	++readOffset;
	msg->setText1C(AsciiString(textBuffer));

	textCursor = textBuffer;
	while (packetData[readOffset] != 0) {
		*textCursor = packetData[readOffset];
		++textCursor;
		++readOffset;
	}
	*textCursor = 0;
	++readOffset;
	msg->setText20(AsciiString(textBuffer));

	return msg;
}
