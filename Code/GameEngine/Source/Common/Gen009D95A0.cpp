// cl: /DNDEBUG /MD /O2
// Clean C++ conversion of the unsigned-short formatter at retail RVA 0x009D95A0.
extern "C" void __cdecl bfmeAppend(void *stream, const char *format, ...);
extern const char g_bfmeUnsignedShortFormat[];

class Gen009D95A0
{
public:
	Gen009D95A0 *bfmeEmit(const unsigned short *value);

private:
	unsigned char m_pad[4];
	bool m_pending;
};

Gen009D95A0 *Gen009D95A0::bfmeEmit(const unsigned short *value)
{
	if (!m_pending)
		bfmeAppend(this, 0);
	unsigned int widened = *value;
	bfmeAppend(this, g_bfmeUnsignedShortFormat, widened, widened);
	m_pending = false;
	return this;
}
