// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: ShareBufferClass<unsigned short> destructor
// Load buffer, install interim vtbl, free buffer, install final vtbl.

extern "C" char ShareBufferClassUnsignedShort_vtbl_interim;
extern "C" char ShareBufferClassUnsignedShort_vtbl_final;

void __cdecl operator_delete_sized(void *p);

// object-symbol used by ledger: ShareBufferClassUnsignedShort dtor (QAE)
class ShareBufferClassUnsignedShort
{
public:
	~ShareBufferClassUnsignedShort();

private:
	char *m_vtbl;
	unsigned int m_04;
	void *m_buf;
};

// ??1?$ShareBufferClass@G@@UAE@XZ
ShareBufferClassUnsignedShort::~ShareBufferClassUnsignedShort()
{
	void *buf = m_buf;
	m_vtbl = &ShareBufferClassUnsignedShort_vtbl_interim;
	operator_delete_sized(buf);
	m_vtbl = &ShareBufferClassUnsignedShort_vtbl_final;
}
