// cl: /DNDEBUG /MD /EHsc
// ??1DX8Caps@@QAE@XZ
// retail 0x00903E00. Destroys CompactLog, CapsLog, then DriverDLL (Direct3D* has no dtor).

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/wwstring.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8caps.h
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
