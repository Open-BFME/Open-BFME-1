// cl: /DNDEBUG /MD /O2
// Clean C++ conversion of the word formatter at retail RVA 0x009D93A0.
extern "C" void __cdecl bfmeAppend(void *stream, const char *format, ...);
extern const char g_bfmeWordFormat[];

class Gen009D93A0
{
public:
	Gen009D93A0 *bfmeEmit(const unsigned int *value);

private:
	unsigned char m_pad[4];
	bool m_pending;
};

Gen009D93A0 *Gen009D93A0::bfmeEmit(const unsigned int *value)
{
	if (!m_pending)
	{
		m_pending = true;
		bfmeAppend(this, 0);
	}
	bfmeAppend(this, g_bfmeWordFormat, *value);
	return this;
}
