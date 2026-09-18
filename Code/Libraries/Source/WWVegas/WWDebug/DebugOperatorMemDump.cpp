// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /EHs-c- /Oy-

extern "C" __declspec(dllimport) int __cdecl sprintf(
	char *, const char *, ...);
extern "C" __declspec(dllimport) int __stdcall IsBadReadPtr(
	const void *, unsigned long);

class Debug
{
public:
	class MemDump
	{
	public:
		const unsigned char *m_startPtr;
		unsigned m_numItems;
		unsigned m_bytePerItem;
		bool m_absAddr;
		bool m_withChars;
	};

	virtual ~Debug();
	virtual void pad01();
	virtual void pad02();
	virtual void pad03();
	virtual void pad04();
	virtual void pad05();
	virtual void pad06();
	virtual void pad07();
	virtual void pad08();
	virtual void pad09();
	virtual void pad10();
	virtual void pad11();
	virtual void pad12();
	virtual Debug &operator<<(const char *);
	virtual Debug &operator<<(const MemDump &);

private:
	unsigned char m_pad04[0x14];
	unsigned char m_pad18[0x9c78];
	unsigned char m_lastWasCR[0x64];
	int m_curType;
};

Debug &Debug::operator<<(const MemDump &dump)
{
	unsigned itemPerLine;
	const unsigned char *cur;
	unsigned i;
	unsigned k;
	unsigned l;
	char buf[9];

	if (m_curType == 7)
		return *this;

	if (!m_lastWasCR[m_curType * 16])
		(*this) << (const char *)0x01080294;

	itemPerLine = (dump.m_withChars ? 64 : 65) /
		(1 + 2 * dump.m_bytePerItem + (dump.m_withChars ? 1 : 0));
	if (!itemPerLine)
		itemPerLine = 1;

	cur = dump.m_startPtr;
	for (i = 0; i < dump.m_numItems;
		i += itemPerLine, cur += itemPerLine * dump.m_bytePerItem)
	{
		sprintf(buf, (const char *)0x011313dc,
			dump.m_absAddr ? unsigned(cur) : cur - dump.m_startPtr);
		(*this) << buf;

		const unsigned char *curByte = cur;
		for (k = 0; k < itemPerLine; ++k, curByte += dump.m_bytePerItem)
		{
			(*this) << (const char *)0x0108ed1c;
			if (k + i >= dump.m_numItems)
			{
				for (l = dump.m_bytePerItem; l; --l)
					(*this) << (const char *)0x010e8b00;
			}
			else if (IsBadReadPtr(curByte, dump.m_bytePerItem))
			{
				for (l = dump.m_bytePerItem; l; --l)
					(*this) << (const char *)0x01133114;
			}
			else
			{
				curByte += dump.m_bytePerItem;
				for (l = 0; l < dump.m_bytePerItem; ++l)
				{
					sprintf(buf, (const char *)0x01131468, *--curByte);
					(*this) << buf;
				}
			}
		}

		if (!dump.m_withChars)
			continue;
		(*this) << (const char *)0x0108ed1c;
		curByte = cur;
		for (k = 0; k < itemPerLine; ++k, curByte += dump.m_bytePerItem)
		{
			if (k + i >= dump.m_numItems)
				break;
			else if (IsBadReadPtr(curByte, dump.m_bytePerItem))
			{
				for (l = dump.m_bytePerItem; l; --l)
					(*this) << (const char *)0x01076c14;
			}
			else
			{
				buf[1] = 0;
				for (l = 0; l < dump.m_bytePerItem; ++l)
				{
					*buf = curByte[l] > ' ' ? curByte[l] : '.';
					(*this) << buf;
				}
			}
		}
		(*this) << (const char *)0x01080294;
	}

	return *this;
}
