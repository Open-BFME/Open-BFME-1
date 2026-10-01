// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// The reply adapter at 0x007F8640 is separately matched; this is the
// immediately following request body at 0x007F8650.
class BfmeHostBT;
class BfmeC994
{
public:
	BfmeC994(char *buffer, int capacity);
	char m_data[0x34];
};

// The trailing cleanup at 0x007F8693 is retail body 0x007E86C0, matched as
// the shim ?m@Gen_007e86c0@@QAEXXZ (game/gen_small/fun_005.cpp).
class Gen_007e86c0
{
public:
	void m();
};

class BfmeMsg1052 : public BfmeC994
{
public:
	BfmeMsg1052(char *buffer, int capacity) : BfmeC994(buffer, capacity) {}
};

void __cdecl Rva007F8640Callback(void *payload, BfmeHostBT *host);

class Rva007F8650RequestService
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3C() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual void slot48() = 0;
	virtual void send(BfmeC994 *message) = 0;
};

class Rva007F8650AsyncService
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void send(BfmeC994 *message,
		void (__cdecl *callback)(void *, BfmeHostBT *),
		BfmeHostBT *owner, int transaction) = 0;
};

class Rva007F8650Owner
{
public:
	void request();
	char m_pad00[0x10];
	Rva007F8650RequestService *m_request;
	Rva007F8650AsyncService *m_async;
	char m_pad18[0x2c4];
	char m_buffer[0x400];
	int m_transaction;
};

void Rva007F8650Owner::request()
{
	BfmeMsg1052 message(m_buffer, sizeof(m_buffer));
	m_request->send(&message);
	m_async->send(&message, Rva007F8640Callback, (BfmeHostBT *)this, m_transaction);
	((Gen_007e86c0 *)&message)->m();
}
