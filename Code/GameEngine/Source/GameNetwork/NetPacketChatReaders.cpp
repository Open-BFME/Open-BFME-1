// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable body of ?readChatMessage@NetPacket@@KAPAVNetCommandMsg@@PAEAAH@Z: Code/GameEngine/Source/GameNetwork/NetPacket.cpp
// readable body of ?readDisconnectChatMessage@NetPacket@@KAPAVNetCommandMsg@@PAEAAH@Z: Code/GameEngine/Source/GameNetwork/NetPacket.cpp

// The inline wide-string copy preserves the by-value setText temporary's retail EH shape.

#include <string.h>
#include <wchar.h>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;

void *__cdecl operator new(unsigned int size);

static int stringLength(const unsigned short *s)
{
	return (int)wcslen((const wchar_t *)s);
}

class NetCommandMsg
{
public:
	virtual ~NetCommandMsg();
};

template <typename T>
class StringBase
{
	friend class UnicodeString;

public:
	void set(const T *str) { set(str, stringLength(str)); }
	void set(const T *str, int len);

private:
	StringBase() { m_data = 0; }
	StringBase(const StringBase<T> &src);
	~StringBase();

	struct Header;

	Header *m_data;
};

class UnicodeString : private StringBase<UnsignedShort>
{
public:
	UnicodeString() {}
	UnicodeString(const UnicodeString &other) : StringBase<UnsignedShort>(other) {}
	~UnicodeString() {}
	void set(const UnsignedShort *str) { StringBase<UnsignedShort>::set(str); }
};

class NetChatCommandMsg : public NetCommandMsg
{
public:
	NetChatCommandMsg();
	virtual ~NetChatCommandMsg();
	void setText(UnicodeString text);
	void setPlayerMask(Int playerMask);

	UnsignedInt m_base[6];
	UnicodeString m_text;
	Int m_playerMask;
};

class NetDisconnectChatCommandMsg : public NetCommandMsg
{
public:
	NetDisconnectChatCommandMsg();
	virtual ~NetDisconnectChatCommandMsg();
	void setText(UnicodeString text);

	UnsignedInt m_base[6];
	UnicodeString m_text;
};

class NetPacket
{
protected:
	static NetCommandMsg *readChatMessage(UnsignedByte *packetData, Int &readOffset);
	static NetCommandMsg *readDisconnectChatMessage(UnsignedByte *packetData, Int &readOffset);
};

NetCommandMsg *NetPacket::readChatMessage(UnsignedByte *packetData, Int &readOffset)
{
	NetChatCommandMsg *msg = new NetChatCommandMsg;

	UnsignedShort textBuffer[256];
	UnsignedByte textLength;
	Int playerMask;
	memcpy(&textLength, packetData + readOffset, sizeof(UnsignedByte));
	++readOffset;
	memcpy(textBuffer, packetData + readOffset, textLength * sizeof(UnsignedShort));
	readOffset += textLength * sizeof(UnsignedShort);
	textBuffer[textLength] = 0;
	memcpy(&playerMask, packetData + readOffset, sizeof(Int));
	readOffset += sizeof(Int);

	UnicodeString messageText;
	messageText.set(textBuffer);

	msg->setText(messageText);
	msg->setPlayerMask(playerMask);
	return msg;
}

NetCommandMsg *NetPacket::readDisconnectChatMessage(UnsignedByte *packetData, Int &readOffset)
{
	NetDisconnectChatCommandMsg *msg = new NetDisconnectChatCommandMsg;

	UnsignedShort textBuffer[256];
	UnsignedByte textLength;
	memcpy(&textLength, packetData + readOffset, sizeof(UnsignedByte));
	++readOffset;
	memcpy(textBuffer, packetData + readOffset, textLength * sizeof(UnsignedShort));
	readOffset += textLength * sizeof(UnsignedShort);
	textBuffer[textLength] = 0;

	UnicodeString messageText;
	messageText.set(textBuffer);

	msg->setText(messageText);
	return msg;
}
