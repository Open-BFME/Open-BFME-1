// ??0Gen006E2310@@QAE@XZ
// cl: /DNDEBUG /MD /EHsc

class BfmeA1134
{
public:
	BfmeA1134( void );
	virtual ~BfmeA1134( void );
};

class BfmeB1137
{
public:
	BfmeB1137( void );
	char m_storage[0xe8];
};

// The patcher resolves this DIR32 to BFME's process-global slot.  Keeping the
// TU-local volatile view gives MSVC 7.1 the retail EH/store order.
static BfmeB1137 * volatile g_bfmeObj006e1be0;

class Gen006E2310 : public BfmeA1134
{
public:
	Gen006E2310( void );

private:
	unsigned char m_unmodelled[0xa8];
	volatile int m_ac;
	volatile int m_b0;
	volatile int m_b4;
	volatile char m_b8;
	unsigned char m_pad_b9[3];
	volatile int m_bc;
	volatile int m_c0;
	volatile int m_c4;
	volatile int m_c8;
	volatile int m_cc;
	volatile int m_d0;
	volatile int m_d4;
	volatile int m_d8;
	volatile int m_dc;
	volatile int m_e0;
	volatile int m_e4;
	volatile int m_e8;
	volatile int m_ec;
	volatile int m_f0;
	volatile int m_f4;
};

Gen006E2310::Gen006E2310( void )
{
	g_bfmeObj006e1be0 = new BfmeB1137;
	m_ac = 0;
	m_b0 = 0;
	m_b8 = 0;
	m_bc = 0;
	m_c0 = 0;
	m_b4 = 0xff;
	m_c4 = 0;
	m_c8 = 0;
	m_cc = 0;
	m_d0 = 0;
	m_d4 = 0;
	m_d8 = 0;
	m_dc = 0;
	m_e0 = 0;
	m_e4 = 0;
	m_ec = 0;
	m_f0 = 0;
	m_f4 = 0;
	m_e8 = 0x555555;
}
