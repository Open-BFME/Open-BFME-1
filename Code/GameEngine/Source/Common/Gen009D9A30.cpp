// cl: /DNDEBUG /MD /O2
// Clean C++ conversion of the AsciiString formatter at retail RVA 0x009D9A30.
extern "C" void __cdecl bfmeAppend(void *stream, const char *format, ...);
extern const char g_bfmeAsciiStringFormat[];
extern const char g_bfmeEmptyAscii[];

struct BfmeAsciiString
{
	const char *storage;
};

class Gen009D9A30
{
public:
	Gen009D9A30 *bfmeEmit(BfmeAsciiString *value);

private:
	unsigned char m_pad[4];
	bool m_pending;
};

Gen009D9A30 *Gen009D9A30::bfmeEmit(BfmeAsciiString *value)
{
	if (!m_pending)
		bfmeAppend(this, 0);
	const char *text = value->storage ? value->storage + 8 : g_bfmeEmptyAscii;
	bfmeAppend(this, g_bfmeAsciiStringFormat, text);
	m_pending = false;
	return this;
}
