// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: WindowLayout::getFilename, retail 0x004EA450.
//
// Matched callers findScreenByFilename, WOLBuddyOverlayRCMenuInit and
// setUnignoreText all call this 32-byte by-value copy. The Zero Hour inline
// is `return m_filenameString;` and MemoryPoolObject's vptr puts that member
// at +0x04, which is the `add ecx, 4` retail emits.
//
// The copy has to be the StringBase<char> body at 0x00887B60, not the
// 19-byte AsciiString forwarder at 0x0005EE50: retail's getter calls the
// base. AsciiString privately inherits and inlines the forwarder so the
// call that remains is the base's (docs/shape_levers.md, stringinline).

template <typename T>
class StringBase
{
	friend class AsciiString;

private:
	StringBase(const StringBase<T> &other);
	~StringBase();

	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/WindowLayout.h
class WindowLayout
{
public:
	virtual ~WindowLayout();
	AsciiString getFilename(void);

private:
	AsciiString m_filenameString;
};

// ?getFilename@WindowLayout@@QAE?AVAsciiString@@XZ
AsciiString WindowLayout::getFilename(void)
{
	return m_filenameString;
}
