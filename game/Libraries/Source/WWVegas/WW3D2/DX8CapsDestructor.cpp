// cl: /DNDEBUG /MD /EHsc
// ??1DX8Caps@@QAE@XZ
// retail 0x00903E00. Destroys CompactLog, CapsLog, then DriverDLL (Direct3D* has no dtor).
// Upstream DX8Caps declares no destructor: retail's is the implicit inline one,
// kept as one COMDAT (dx8wrapper's Enumerate_Devices inlines it, Compute_Caps
// and its unwind funclet call 0x00903E00), so it is emitted here the same way.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/wwstring.h
class StringClass
{
	void Free_String(void);
	char *m_Buffer;
public:
	~StringClass()
	{
		Free_String();
	}
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8caps.h
class DX8Caps
{
private:
	char m_pad[0x29C];
	StringClass DriverDLL;
	void *Direct3D;
	StringClass CapsLog;
	StringClass CompactLog;
};

void Force_DX8Caps_Deleting_Destructor(DX8Caps *caps)
{
	delete caps;
}
