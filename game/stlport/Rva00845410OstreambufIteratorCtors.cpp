// cl: /O2 /MD /EHsc
// Three ostreambuf_iterator-shaped constructors: a buffer pointer plus an
// ok flag (buffer != 0). STLport's narrow and wide instantiations emit
// identical bytes and no caller tells them apart, so each body keeps its
// retail address in the name.
//   0x00845410: from a streambuf pointer
//   0x00845870, 0x00845890: from a stream (rdbuf via the virtual basic_ios base)

class Rva00845410Buf;

struct Rva00845410IosBase
{
	char m_pad[0x58];
	Rva00845410Buf *m_buf;
};

struct Rva00845410Stream
{
	int *m_vbtable;
	Rva00845410Buf *rdbuf() const
	{
		return ((const Rva00845410IosBase *)((const char *)this + m_vbtable[1]))->m_buf;
	}
};

class Rva00845410OutIter
{
public:
	Rva00845410OutIter(Rva00845410Buf *buf);
	Rva00845410Buf *m_buf;
	bool m_ok;
};

// ??0Rva00845410OutIter@@QAE@PAVRva00845410Buf@@@Z
Rva00845410OutIter::Rva00845410OutIter(Rva00845410Buf *buf) : m_buf(buf), m_ok(buf != 0) {}

class Rva00845870OutIter
{
public:
	Rva00845870OutIter(Rva00845410Stream &s);
	Rva00845410Buf *m_buf;
	bool m_ok;
};

// ??0Rva00845870OutIter@@QAE@AAURva00845410Stream@@@Z
Rva00845870OutIter::Rva00845870OutIter(Rva00845410Stream &s) : m_buf(s.rdbuf()), m_ok(m_buf != 0) {}

class Rva00845890OutIter
{
public:
	Rva00845890OutIter(Rva00845410Stream &s);
	Rva00845410Buf *m_buf;
	bool m_ok;
};

// ??0Rva00845890OutIter@@QAE@AAURva00845410Stream@@@Z
Rva00845890OutIter::Rva00845890OutIter(Rva00845410Stream &s) : m_buf(s.rdbuf()), m_ok(m_buf != 0) {}
