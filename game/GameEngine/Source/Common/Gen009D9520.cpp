// cl: /DNDEBUG /MD /O2
// Clean C++ conversion of the unsigned integer formatter at retail RVA 0x009D9520.
extern "C" void __cdecl bfmeAppend(void *stream, const char *format, ...);
extern const char g_bfmeUnsignedIntFormat[];

class Gen009D9520
{
public:
	Gen009D9520 *bfmeEmit(const unsigned int *value);

private:
	unsigned char m_pad[4];
	bool m_pending;
};

Gen009D9520 *Gen009D9520::bfmeEmit(const unsigned int *value)
{
	if (!m_pending)
		bfmeAppend(this, 0);
	unsigned int widened = *value;
	bfmeAppend(this, g_bfmeUnsignedIntFormat, widened, widened);
	m_pending = false;
	return this;
}
