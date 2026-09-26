// Retail 0x000623F0, 151 bytes. This callback updates the second AI target.

template <class T> class StringBase
{
public:
	~StringBase() { releaseBuffer(); }

	void *m_data;
	void set(const StringBase<T> &text);

private:
	StringBase(const T *text);
	friend int __cdecl Rva000623F0(char **argv, int argc);
	void releaseBuffer();
};

extern bool g_aiTargetDispatchSuppressed;

struct Rva006C9270GlobalData
{
	unsigned char m_head[0x29];
	unsigned char m_flag;
	unsigned char m_middle[0xb8a];
	unsigned char m_tail;
};

extern Rva006C9270GlobalData *TheWritableGlobalData;

int __cdecl Rva000623F0(char **argv, int argc)
{
	if(argc >= 2)
	{
		const char *argument = argv[1];

		{
			const StringBase<char> &text = StringBase<char>(argument);
			reinterpret_cast<StringBase<char> *>(0x012F08A8u)->set(text);
		}

		g_aiTargetDispatchSuppressed = true;
		TheWritableGlobalData->m_flag = 1;
		TheWritableGlobalData->m_tail = 0;

		return 2;
	}

	return 1;
}
