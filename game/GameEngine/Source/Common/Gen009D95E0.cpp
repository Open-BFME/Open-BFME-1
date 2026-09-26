// cl: /DNDEBUG /MD /O2
// Clean C++ conversion of the real-number formatter at retail RVA 0x009D95E0.
extern "C" void __cdecl bfmeAppend(void *stream, const char *format, ...);
extern const char g_bfmeRealFormat[];

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
	bfmeAppend(this, g_bfmeRealFormat, *value, *value);
	m_pending = false;
	return this;
}
