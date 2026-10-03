// cl: /DNDEBUG /MD /GX-
// Retail 0x008038F0, 123 bytes through RET 4 at 0x00803968.
// Address-derived sender and envelope layout views; native constructors and
// destruction recover the stack initialization order. See identity evidence
// 008038f0-native-envelope.md for the independent lifetime and slot contracts.

class Rva007E86B0Base {
public:
 Rva007E86B0Base();
 virtual ~Rva007E86B0Base();
 int m_04;
};
class Rva008038F0Tail : public Rva007E86B0Base {
public:
 Rva008038F0Tail() { m_08 = 0; m_0c = 0; m_04 = 0; }
 int m_08;
 int m_0c;
};
struct Rva008038F0Prefix {
 Rva008038F0Prefix() : m_00(0),m_04(0),m_08(0),m_0c(0),m_10(0) {}
 int m_00,m_04,m_08,m_0c;
 char m_10;
};
struct Rva008038F0Envelope {
 Rva008038F0Prefix param;
 Rva008038F0Tail guard;
};

class BfmeC994
{
public:
	char m_pad00[0x10];
	int m_10;
	int m_14;
	char m_pad18[4];
	int m_1c;
	int m_20;
};

class Rva008038F0Dispatch
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c(Rva008038F0Prefix *param);
};

class Rva008038F0Holder
{
public:
	int m_00;
	Rva008038F0Dispatch m_field04;
};

class Rva008038F0Sender
{
public:
	void send(BfmeC994 *message);

	char m_pad[0x10];
	Rva008038F0Holder *m_10;
};

void Rva008038F0Sender::send(BfmeC994 *message)
{
	Rva008038F0Envelope frame;

	frame.param.m_00 = message->m_1c;
	frame.param.m_04 = message->m_20;
	frame.param.m_08 = message->m_10;
	frame.param.m_0c = message->m_14;

	m_10->m_field04.slot0c(&frame.param);
}
