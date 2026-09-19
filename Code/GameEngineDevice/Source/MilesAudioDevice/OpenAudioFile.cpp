// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ??1BfmeRecordBQ@@QAE@XZ
// The caller through ILT 0x0003DAD2 and the matched BfmeRecordBQ constructor
// identify this record.  The OpenAudioFile diagnostics identify its +0x34
// count and +0x2C file buffer, while the cleanup callers establish +0x40 as
// the compressed-file flag.

template <typename T>
class StringBase;

class BfmeRecordBQ;

template <>
class StringBase<char>
{
	friend class BfmeRecordBQ;

private:
	~StringBase()
	{
		releaseBuffer();
	}

	void releaseBuffer();

	void *m_data;
};

class BfmeAwakenLog
{
public:
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
	virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
	virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
	virtual void v30(); virtual BfmeAwakenLog *v34(int value);
	virtual BfmeAwakenLog *v38(const char *message);
	virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48();
	virtual BfmeAwakenLog *v4c(int value);
};

class BfmeAwakenDebug
{
public:
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
	virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
	virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
	virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
	virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
	virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
	virtual void v60();
	virtual void v64(); virtual void v68();
	virtual BfmeAwakenLog *v6c(int first, int second);
};

extern BfmeAwakenDebug *TheBfmeAwakenDebug;
extern bool _bfme_debugReportingEnabled(void);
extern void _bfme_debugRecordCallsite(int kind);
extern "C" __declspec(dllimport) void __stdcall AIL_mem_free_lock(void *ptr);
void __cdecl operator delete[](void *block);

class BfmeRecordBQ
{
public:
	~BfmeRecordBQ();

private:
	StringBase<char> m_name;
	int m_owner;
	int m_slots[9];
	char *m_file;
	int m_accountingValue;
	int m_openCount;
	int m_stamp;
	int m_bucket;
	unsigned char m_compressed;
	unsigned char m_active;
	unsigned char m_reserved;
};

BfmeRecordBQ::~BfmeRecordBQ()
{
	if (m_openCount)
	{
		if (_bfme_debugReportingEnabled())
		{
			_bfme_debugRecordCallsite(1);
			TheBfmeAwakenDebug->v60();
			TheBfmeAwakenDebug->v6c(0, 0)
				->v38("Attempting to close OpenAudioFile with an open count of ")
				->v34(m_openCount)
				->v38(". This will probably crash the game!")
				->v4c(2);
		}
	}

	if (m_file)
	{
		if (m_compressed)
			AIL_mem_free_lock(m_file);
		else
			delete [] m_file;
		m_file = 0;
	}
}
