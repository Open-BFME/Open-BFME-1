// cl: /DNDEBUG /MD /EHs-c-
// Destructor for the small-buffer conversion holder. It tail-jumps through
// the ILT to the out-of-line release member at retail 0x0005C6B0.

class Rva0005C6B0Holder
{
public:
	~Rva0005C6B0Holder(void);
	void release(void);

private:
	char *m_text;
	char m_buffer[1];
};

// ??1Rva0005C6B0Holder@@QAE@XZ
Rva0005C6B0Holder::~Rva0005C6B0Holder(void)
{
	if (m_text != m_buffer) {
		release();
	}
}
