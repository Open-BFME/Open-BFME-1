// Address-derived GameClient update reconstruction at 0x003C2530.
// cl: /DNDEBUG /MD /O2 /EHsc

class BfmeB1083
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	char bfmeChk1083();
	char m_pad18[ 0x19C ];
	int m_frameCounter;
};

extern BfmeB1083 *g_bfmeSwitchDR;
extern BfmeB1083 *g_bfmeGameCW;
extern void setFPMode();
extern void j_000322e5();
extern void j_00028d08();
extern void j_00001e4c();
extern void j_0003f3c3();
extern void j_0002a64e();
extern void j_0001d688();
extern void j_00048cb6();

class Rva003C2530Owner
{
public:
	void update();
	void prepare();
	void frameA();
	void frameB();
	void frameC();
	void frameD();
	void frameE();

private:
	char m_pad00[ 0x28 ];
	void *m_callback;
	unsigned char m_enabled;
	unsigned char m_ready;
};

class Rva003C2530Callback
{
public:
	void notify();
};

void Rva003C2530Owner::update()
{
	typedef void (Rva003C2530Owner::*OwnerCall)();
	typedef void (Rva003C2530Callback::*CallbackCall)();
	union
	{
		void (*plain)();
		OwnerCall member;
	} ownerCall;
	union
	{
		void (*plain)();
		CallbackCall member;
	} callbackCall;
	if( m_enabled )
	{
		if( g_bfmeSwitchDR != 0 )
			g_bfmeSwitchDR->slot14();

		if( g_bfmeGameCW->bfmeChk1083() )
			return;

		ownerCall.plain = j_000322e5;
		( this->*ownerCall.member )();
		if( !m_ready )
			return;

		BfmeB1083 *game = g_bfmeGameCW;
		int &frameCounter = game->m_frameCounter;
		if( frameCounter == 0 )
			setFPMode();
		++frameCounter;
		callbackCall.plain = j_00028d08;
		if( m_callback != 0 )
			( ( ( Rva003C2530Callback * )m_callback )->*callbackCall.member )();
		ownerCall.plain = j_00001e4c;
		( this->*ownerCall.member )();
		ownerCall.plain = j_0003f3c3;
		( this->*ownerCall.member )();
		ownerCall.plain = j_0002a64e;
		( this->*ownerCall.member )();
		ownerCall.plain = j_0001d688;
		( this->*ownerCall.member )();
		ownerCall.plain = j_00048cb6;
		( this->*ownerCall.member )();
		g_bfmeGameCW->slot14();
		--g_bfmeGameCW->m_frameCounter;
	}
}
