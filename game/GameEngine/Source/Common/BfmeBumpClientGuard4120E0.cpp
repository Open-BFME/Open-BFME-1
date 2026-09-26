
// cl: /O2 /Ob1 /DNDEBUG /MD
//
// Retail 0x004120E0 (49B): if counter at 0x012F12F0 is already non-zero, still
// increments it; else if TheGameClient is set, call vslot+0x30, walk the
// returned chain via +0x104 until null, then increment the counter.

class ClientNode4120
{
public:
	char m_pad[0x104];
	ClientNode4120 *m_next;					///< +0x104
};

class ClientRoot4120
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual void v10();
	virtual void v11();
	virtual ClientNode4120 *getHead();		///< slot 12 / +0x30
};

extern ClientRoot4120 *TheGameClient;		///< 0x012F1464
extern int g_bfmeCounter4120;				///< 0x012F12F0

// ?bfmeBumpClientGuard@@YAXXZ
void bfmeBumpClientGuard()
{
	if (!g_bfmeCounter4120)
	{
		ClientRoot4120 *client = TheGameClient;
		if (client)
		{
			ClientNode4120 *n = client->getHead();
			if (n)
			{
				do
				{
					n = n->m_next;
				} while (n);
			}
		}
	}
	++g_bfmeCounter4120;
}
