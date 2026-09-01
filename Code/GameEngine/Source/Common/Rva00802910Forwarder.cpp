// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: address-derived forwarding body at retail 0x00802910.  The
// receiver layout and the fourteen stack arguments are fixed by the body: it
// first calls virtual slot +0x28 on itself, then invokes the direct retail
// callee at 0x007F6740 on the pointer at +4, passing the pointer at +8 first.

class Rva00802910Interface
{
public:
	virtual void slot00(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot0C(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot18(void) = 0;
	virtual void slot1C(void) = 0;
	virtual void slot20(void) = 0;
	virtual void slot24(void) = 0;
	virtual void prepare(void) = 0;
};

class Rva007F6740Receiver
{
public:
	void call(void *context, int a1, int a2, int a3, int a4, int a5,
		int a6, int a7, int a8, int a9, int a10, int a11, int a12,
		int a13, int a14);
};

class Rva00802910Owner : public Rva00802910Interface
{
public:
	void forward(int a1, int a2, int a3, int a4, int a5, int a6, int a7,
		int a8, int a9, int a10, int a11, int a12, int a13, int a14);

private:
	Rva007F6740Receiver *m_receiver;
	void *m_context;
};

void Rva00802910Owner::forward(int a1, int a2, int a3, int a4, int a5,
	int a6, int a7, int a8, int a9, int a10, int a11, int a12, int a13,
	int a14)
{
	prepare();
	m_receiver->call(m_context, a1, a2, a3, a4, a5, a6, a7, a8, a9,
		a10, a11, a12, a13, a14);
}
