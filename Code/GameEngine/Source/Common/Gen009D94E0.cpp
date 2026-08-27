// cl: /DNDEBUG /MD /O2
// Clean C++ conversion of the 64-bit integer formatter at retail RVA 0x009D94E0.
extern "C" void __cdecl bfmeAppend(void *stream, const char *format, ...);
extern const char g_bfmeInt64Format[];

class Gen009D94E0
{
public:
	Gen009D94E0 *bfmeEmit(const __int64 *value);

private:
	unsigned char m_pad[4];
	bool m_pending;
};

Gen009D94E0 *Gen009D94E0::bfmeEmit(const __int64 *value)
{
	if (!m_pending)
		bfmeAppend(this, 0);
	bfmeAppend(this, g_bfmeInt64Format, *value, *value);
	m_pending = false;
	return this;
}
