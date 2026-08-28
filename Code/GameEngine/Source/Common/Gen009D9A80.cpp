// cl: /DNDEBUG /MD /O2
// Clean C++ conversion of the UnicodeString formatter at retail RVA 0x009D9A80.
extern "C" void __cdecl bfmeAppend(void *stream, const char *format, ...);
extern const char g_bfmeUnicodeStringFormat[];
extern const char g_bfmeEmptyUnicode[];

struct BfmeUnicodeString
{
	const unsigned short *storage;
};

class Gen009D9A80
{
public:
	Gen009D9A80 *bfmeEmit(BfmeUnicodeString *value);

private:
	unsigned char m_pad[4];
	bool m_pending;
};

Gen009D9A80 *Gen009D9A80::bfmeEmit(BfmeUnicodeString *value)
{
	if (!m_pending)
		bfmeAppend(this, 0);
	const unsigned short *text = value->storage
		? value->storage + 4
		: reinterpret_cast<const unsigned short *>(g_bfmeEmptyUnicode);
	bfmeAppend(this, g_bfmeUnicodeStringFormat, text);
	m_pending = false;
	return this;
}
