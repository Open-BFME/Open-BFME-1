// cl: /GS /EHs-c-
// Retail starts this request at 0x007F7AE0 after a separate 15-byte reply
// adapter and an alignment int3. It joins two caller-supplied lists and sends
// them with eight other caller-supplied words to FESL service slot 0x18.
class Rva007E8810Message;
class Rva007F7980Browser;
class BfmeC994
{
public:
	BfmeC994(char *buffer, int capacity);
	char m_data[0x34];
};
class BfmeMsg1052 : public BfmeC994
{
public:
	BfmeMsg1052(char *buffer, int capacity) : BfmeC994(buffer, capacity) {}
	~BfmeMsg1052();
};
void Rva00800040JoinI64(const __int64 *parts, unsigned count,
	char *dest, unsigned destSize, char separator);
void Rva00800170Join(const char **parts, unsigned count,
	char *dest, unsigned destSize, char separator);
void __cdecl Rva007F7AD0Callback(Rva007E8810Message *message,
	Rva007F7980Browser *browser);

class Rva007F7AE0RequestService
{
public:
	virtual void v00() = 0;
	virtual void v04() = 0;
	virtual void v08() = 0;
	virtual void v0c() = 0;
	virtual void v10() = 0;
	virtual void v14() = 0;
	virtual void send(BfmeMsg1052 *message,
		int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8,
		const char *ids, const char *strings) = 0;
};
class Rva007F7AE0AsyncService
{
public:
	virtual void v00() = 0;
	virtual void v04() = 0;
	virtual void send(BfmeMsg1052 *message,
		void (__cdecl *callback)(Rva007E8810Message *, Rva007F7980Browser *),
		Rva007F7980Browser *browser, int transaction) = 0;
};
class Rva007F7AE0Owner
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0c();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1c();
	virtual void v20();
	virtual void v24();
	virtual void v28();
	virtual void v2c();
	virtual void v30();
	virtual void v34();
	virtual void v38();
	virtual void v3c();
	virtual void v40();
	virtual void beforeRequest();

	void request(int a1, int a2, int a3, int a4,
		int a5, int a6, int a7, int a8,
		const __int64 *ids, unsigned idCount,
		const char **strings, unsigned stringCount);
	char m_pad04[0x0c];
	Rva007F7AE0RequestService *m_request;
	Rva007F7AE0AsyncService *m_async;
	char m_pad18[0x2c4];
	char m_buffer[0x400];
	int m_transaction;
};
void Rva007F7AE0Owner::request(int a1, int a2, int a3, int a4,
	int a5, int a6, int a7, int a8,
	const __int64 *ids, unsigned idCount,
	const char **strings, unsigned stringCount)
{
	beforeRequest();
	BfmeMsg1052 message(m_buffer, sizeof(m_buffer));
	char stringText[0x100];
	char idText[0x100];
	stringText[0] = 0;
	idText[0] = 0;
	Rva00800040JoinI64(ids, idCount, idText, sizeof(idText), ';');
	Rva00800170Join(strings, stringCount, stringText, sizeof(stringText), ';');
	m_request->send(&message, a1, a2, a3, a4, a5, a6, a7, a8,
		idText, stringText);
	m_async->send(&message, Rva007F7AD0Callback,
		(Rva007F7980Browser *)this, m_transaction);
}
