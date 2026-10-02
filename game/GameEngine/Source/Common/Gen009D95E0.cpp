// cl: /DNDEBUG /MD /O2
// Clean C++ conversion of the real-number formatter at retail RVA 0x009D95E0.
extern "C" void __cdecl bfmeAppend(void *stream, const char *format, ...);
// Retail 0x009D9608 reads the .rdata literal at 0x0114433C, "%1.6f=%f\n".
// It is a compiler-pooled string, not a named global, so it is spelled inline.
#define bfmeRealFormat "%1.6f=%f\n"

class Gen009D95E0
{
public:
	Gen009D95E0 *bfmeEmit(const float *value);

private:
	unsigned char m_pad[4];
	bool m_pending;
};

Gen009D95E0 *Gen009D95E0::bfmeEmit(const float *value)
{
	if (!m_pending)
		bfmeAppend(this, 0);
	bfmeAppend(this, bfmeRealFormat, *value, *value);
	m_pending = false;
	return this;
}
