// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: NetFileCommandMsg::getPortableFilename at 0x0067D250 and
// NetFileAnnounceCommandMsg::getPortableFilename at 0x0067D2E0.
//
// Four matched NetPacket helpers apiece name these 32-byte by-value copies.
// Both classes keep the portable filename at +0x1C (vptr plus 0x18 of other
// command fields), so retail's `add ecx, 0x1C` is the same on each body.
// The copy that remains is StringBase<char>'s at 0x00887B60.

template <typename T>
class StringBase
{
	friend class NetFileCommandMsg;
	friend class NetFileAnnounceCommandMsg;

private:
	StringBase(const StringBase<T> &other);
	~StringBase();

	void *m_data;
};

class NetFileCommandMsg
{
public:
	virtual ~NetFileCommandMsg();
	StringBase<char> getPortableFilename(void);

private:
	unsigned char m_unmodelled_04[0x18];
	StringBase<char> m_portableFilename;
};

class NetFileAnnounceCommandMsg
{
public:
	virtual ~NetFileAnnounceCommandMsg();
	StringBase<char> getPortableFilename(void);

private:
	unsigned char m_unmodelled_04[0x18];
	StringBase<char> m_portableFilename;
};

// ?getPortableFilename@NetFileCommandMsg@@QAE?AV?$StringBase@D@@XZ
StringBase<char> NetFileCommandMsg::getPortableFilename(void)
{
	return m_portableFilename;
}

// ?getPortableFilename@NetFileAnnounceCommandMsg@@QAE?AV?$StringBase@D@@XZ
StringBase<char> NetFileAnnounceCommandMsg::getPortableFilename(void)
{
	return m_portableFilename;
}
