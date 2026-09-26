// cl: /DNDEBUG /MD /O2
// Clean C++ conversion of the unsigned-byte formatter at retail RVA 0x009D9420.
extern "C" void __cdecl bfmeAppend(void *stream, const char *format, ...);
extern const char g_bfmeUnsignedByteFormat[];

class Gen009D9420
{
public:
	Gen009D9420 *bfmeEmit(const unsigned char *value);
private:
	unsigned char m_pad[4];
	bool m_pending;
};

Gen009D9420 *Gen009D9420::bfmeEmit(const unsigned char *value)
{
	if (!m_pending)
		bfmeAppend(this, 0);
	unsigned int widened = *value;
	bfmeAppend(this, g_bfmeUnsignedByteFormat, widened, widened);
	m_pending = false;
	return this;
}
