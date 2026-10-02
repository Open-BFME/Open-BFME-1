// cl: /O2 /Ob0
// The two calls at +0x03 and +0x0B are StringBase<char>::releaseBuffer
// (0x00887940) -- the buffer drop every retail string teardown runs through,
// including ~AsciiString's bare `jmp` to it.  releaseBuffer is a private
// StringBase member with no out-of-line body outside
// game/Libraries/Source/string/StringBase.cpp, so this TU mirrors the template
// (the shape GameSpyLoginPreferences_addLogin.cpp uses for the same class) and
// befriends the one class that calls it: the reference it emits is the real
// StringBase.cpp definition's own mangled name.

class Rva00466730;

template <class T>
class StringBase
{
	friend class Rva00466730;

private:
	void releaseBuffer();
	void *m_data;
};

class Rva00466730
{
	StringBase<char> m_00;
	StringBase<char> m_04;
	int m_08;
	int m_0C;
	unsigned char m_flags;

public:
	void reset();
};

void Rva00466730::reset()
{
	m_00.releaseBuffer();
	m_04.releaseBuffer();
	m_flags &= 0xF4;
	m_08 = 0;
	m_0C = -1;
}