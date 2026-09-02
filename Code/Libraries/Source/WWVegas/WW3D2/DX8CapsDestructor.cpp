// cl: /DNDEBUG /MD /EHsc
// ??1DX8Caps@@QAE@XZ
// retail 0x00903E00. Destroys CompactLog, CapsLog, then DriverDLL (Direct3D* has no dtor).

class StringClass
{
	void Free_String(void);
	char *m_data;
public:
	~StringClass()
	{
		Free_String();
	}
};

class DX8Caps
{
public:
	~DX8Caps();

private:
	char m_pad[0x29C];
	StringClass DriverDLL;
	void *Direct3D;
	StringClass CapsLog;
	StringClass CompactLog;
};

// ??1DX8Caps@@QAE@XZ
DX8Caps::~DX8Caps()
{
}
