// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringinline

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

	AsciiString m_text1C;
};

class BFMENetGameSpyStatsAuthKeyCommandMsg : public NetCommandMsg
{
public:
	BFMENetGameSpyStatsAuthKeyCommandMsg();

	AsciiString m_text1C;
	AsciiString m_text20;
};

// Native setters name the private base; keep the argument's inline-forwarder shape and ownership.
extern "C" void __identifier("?setText1C@BFMENetRequestGameSpyStatsAuthKeyCommandMsg@@QAEXV?$StringBase@D@@@Z")();
extern "C" void __identifier("?setText1C@BFMENetGameSpyStatsAuthKeyCommandMsg@@QAEXV?$StringBase@D@@@Z")();
extern "C" void __identifier("?setText20@BFMENetGameSpyStatsAuthKeyCommandMsg@@QAEXV?$StringBase@D@@@Z")();

typedef char NetStatsStringPayloadIsOneWord[(sizeof(AsciiString) == 4 && sizeof(StringBase<char>) == 4) ? 1 : -1];
typedef char NetStatsCodePointerIsOneWord[(sizeof(void (*)()) == 4) ? 1 : -1];

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
	union { void (*code)(); void (BFMENetRequestGameSpyStatsAuthKeyCommandMsg::*member)(AsciiString); } setter = {
		&__identifier("?setText1C@BFMENetRequestGameSpyStatsAuthKeyCommandMsg@@QAEXV?$StringBase@D@@@Z") };
	typedef char RequestSetterIsOneWord[(sizeof(setter) == 4 && sizeof(setter.member) == 4) ? 1 : -1];
	(msg->*setter.member)(AsciiString(textBuffer));
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
	union { void (*code)(); void (BFMENetGameSpyStatsAuthKeyCommandMsg::*member)(AsciiString); } firstSetter = {
		&__identifier("?setText1C@BFMENetGameSpyStatsAuthKeyCommandMsg@@QAEXV?$StringBase@D@@@Z") };
	typedef char AuthFirstSetterIsOneWord[(sizeof(firstSetter) == 4 && sizeof(firstSetter.member) == 4) ? 1 : -1];
	(msg->*firstSetter.member)(AsciiString(textBuffer));

	textCursor = textBuffer;
	while (packetData[readOffset] != 0) {
		*textCursor = packetData[readOffset];
		++textCursor;
		++readOffset;
	}
	*textCursor = 0;
	++readOffset;
	union { void (*code)(); void (BFMENetGameSpyStatsAuthKeyCommandMsg::*member)(AsciiString); } secondSetter = {
		&__identifier("?setText20@BFMENetGameSpyStatsAuthKeyCommandMsg@@QAEXV?$StringBase@D@@@Z") };
	typedef char AuthSecondSetterIsOneWord[(sizeof(secondSetter) == 4 && sizeof(secondSetter.member) == 4) ? 1 : -1];
	(msg->*secondSetter.member)(AsciiString(textBuffer));

	return msg;
}
