// EA FESL gamebrowser guarded four-argument request at retail 0x007F6050.

// Retail 0x007E86C0: the shared seven-byte cleanup the FESL message bodies call
// (store the base vtable 0x01129358 into *this, then ret).  The local message's
// user-declared destructor is the only reference to it, so the scope-exit calls
// are spelled through this neutral declaration instead.  The definition lives in
// game/gen_small/fun_005.cpp.
class Gen_007e86c0
{
public:
	void m();
};

class BfmeMsgVJH
{
public:
	BfmeMsgVJH(char *buf, int n) throw();
	char m_pad[0x34];
};

class Rva007E8810Message
{
public:
	void setError(int code) throw();
};

// 0x007E88A0 is DEFINED in the ledger as ?valid@W3DVideoBuffer@@UAE_NXZ, and
// the matched ?videoBufferValue@Rva007F5A70Owner@@QAEHPAVW3DVideoBuffer@@@Z at
// 0x007F5A80 calls it directly on a W3DVideoBuffer*, so the qualified
// non-virtual call below is the spelling that mangles to the defining name.
// No game/ header declares W3DVideoBuffer.
class W3DVideoBuffer
{
public:
	virtual bool valid( void ) throw();                              // 0x007E88A0
};

class BfmeAsk992
{
public:
	int bfmeGet992C() throw();
};

class BfmeAVJR
{
public:
	virtual void v00() throw();
	virtual void v04() throw();
	virtual void v08() throw();
	virtual void v0c() throw();
	virtual void v10() throw();
	virtual void v14() throw();
	virtual void v18() throw();
	virtual void v1c() throw();
	virtual void v20() throw();
	virtual void v24() throw();
	virtual void v28() throw();
	virtual void v2c() throw();
	virtual void v30() throw();
	virtual void v34() throw();
	virtual void v38() throw();
	virtual void v3c() throw();
	virtual void v40() throw();
	virtual void v44() throw();
	virtual void v48() throw();
	virtual void v4c() throw();
	virtual void v50() throw();
	virtual void v54() throw();
	virtual void sendFour(BfmeMsgVJH *msg, int a1, int a2, int a3,
		int a4) throw();
};

extern void __stdcall BfmeGameBrowserVJRCallback();

class BfmeBVJR
{
public:
	virtual void v00() throw();
	virtual void v04() throw();
	virtual void send(BfmeMsgVJH *msg, void (__stdcall *callback)(),
		void *owner, int value) throw();
};

class BfmeSinkErrorVJR
{
public:
	virtual void v00() throw();
	virtual void v04() throw();
	virtual void v08() throw();
	virtual void v0c() throw();
	virtual void v10() throw();
	virtual void v14() throw();
	virtual void v18() throw();
	virtual void v1c() throw();
	virtual void v20() throw();
	virtual void v24() throw();
	virtual void v28() throw();
	virtual void v2c() throw();
	virtual void v30() throw();
	virtual void v34() throw();
	virtual void v38() throw();
	virtual void v3c() throw();
	virtual void v40() throw();
	virtual void v44() throw();
	virtual void sendError(int value) throw();
};

class BfmeSinkZeroVJR
{
public:
	virtual void v00() throw();
	virtual void v04() throw();
	virtual void v08() throw();
	virtual void v0c() throw();
	virtual void v10() throw();
	virtual void v14() throw();
	virtual void v18() throw();
	virtual void v1c() throw();
	virtual void v20() throw();
	virtual void v24() throw();
	virtual void v28() throw();
	virtual void v2c() throw();
	virtual void v30() throw();
	virtual void v34() throw();
	virtual void v38() throw();
	virtual void v3c() throw();
	virtual void v40() throw();
	virtual void v44() throw();
	virtual void sendZero(int value) throw();
};

class BfmeThingVJR
{
public:
	void bfmeGoVJR(int a1, int a2, int a3, int a4) throw();

	char m_pad00[0x10];
	BfmeAVJR *m_bfme10;
	BfmeBVJR *m_bfme14;
	char m_pad18[4];
	union
	{
		BfmeSinkErrorVJR *m_bfme1cError;
		BfmeSinkZeroVJR *m_bfme1cZero;
	};
	char m_pad20[8];
	int m_bfme28;
	int m_bfme2c;
	int m_bfme30;
	char m_bfme34;
	char m_bfme35;
	char m_pad36[0x2a6];
	char m_bfmeBuf[0x400];
	int m_bfme6dc;
};

void BfmeThingVJR::bfmeGoVJR(int a1, int a2, int a3, int a4) throw()
{
	BfmeMsgVJH msg(m_bfmeBuf, 0x400);
	if (m_bfme34 && m_bfme30 >= 3)
	{
		m_bfme10->sendFour(&msg, a1, a2, a3, a4);
		m_bfme14->send(&msg, BfmeGameBrowserVJRCallback, this, m_bfme6dc);
		reinterpret_cast< Gen_007e86c0 * >( &msg )->m();
		return;
	}
	if (m_bfme35)
	{
		Rva007E8810Message *view = (Rva007E8810Message *)&msg;
		BfmeAsk992 *ask = (BfmeAsk992 *)&msg;
		view->setError(-0x6f);
		if (((W3DVideoBuffer *)&msg)->W3DVideoBuffer::valid())
		{
			int error = ask->bfmeGet992C();
			BfmeSinkErrorVJR *sink = m_bfme1cError;
			sink->sendError(error);
			reinterpret_cast< Gen_007e86c0 * >( &msg )->m();
			return;
		}
		else
		{
			BfmeSinkZeroVJR *sink = m_bfme1cZero;
			sink->sendZero(0);
			reinterpret_cast< Gen_007e86c0 * >( &msg )->m();
			return;
		}
	}
	reinterpret_cast< Gen_007e86c0 * >( &msg )->m();
}
