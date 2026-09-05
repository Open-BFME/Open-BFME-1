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

class NetPacket
{
protected:
	static NetCommandMsg *readRequestGameSpyStatsAuthKeyMessage(UnsignedByte *data, Int &i);
};

NetCommandMsg *NetPacket::readRequestGameSpyStatsAuthKeyMessage(UnsignedByte *data, Int &i)
{
	BFMENetRequestGameSpyStatsAuthKeyCommandMsg *msg = new BFMENetRequestGameSpyStatsAuthKeyCommandMsg;
	char filename[256];
	char *c = filename;

	while (data[i] != 0) {
		*c = data[i];
		++c;
		++i;
	}
	*c = 0;
	++i;
	msg->setText1C(AsciiString(filename));
	return msg;
}
