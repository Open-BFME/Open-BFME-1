// cl: /DNDEBUG /MD /EHsc

// Retail 0x007239A0. Out-of-line WW3D::Get_Frame_Time -- the header inline
// `return SyncTime - PreviousSyncTime` compiled as its own body.

class WW3D
{
public:
	static unsigned int SyncTime;
	static unsigned int PreviousSyncTime;
	static unsigned int Get_Frame_Time(void);
};

// ?Get_Frame_Time@WW3D@@SAIXZ
unsigned int WW3D::Get_Frame_Time(void)
{
	return SyncTime - PreviousSyncTime;
}
