// cl: /DNDEBUG /MD /O2
// Clean C++ conversion of the signed-short formatter at retail RVA 0x009D9560.
extern "C" void __cdecl bfmeAppend(void *stream, const char *format, ...);
extern const char g_bfmeShortFormat[];

class Gen009D9560
{
public:
	Gen009D9560 *bfmeEmit(const short *value);

private:
	unsigned char m_pad[4];
	bool m_pending;
};

Gen009D9560 *Gen009D9560::bfmeEmit(const short *value)
{
	if (!m_pending)
		bfmeAppend(this, 0);
	int widened = *value;
	bfmeAppend(this, g_bfmeShortFormat, widened, widened);
	m_pending = false;
	return this;
}
