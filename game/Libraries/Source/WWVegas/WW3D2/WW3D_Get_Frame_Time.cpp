// cl: /DNDEBUG /MD /EHsc

// Retail 0x007239A0. Out-of-line WW3D::Get_Frame_Time -- the header inline
// `return SyncTime - PreviousSyncTime` compiled as its own body.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/ww3d.h
class WW3D
{
public:
	static unsigned int Get_Frame_Time(void);

private:
	static unsigned int SyncTime;
	static unsigned int PreviousSyncTime;
};

// ?Get_Frame_Time@WW3D@@SAIXZ
unsigned int WW3D::Get_Frame_Time(void)
{
	return SyncTime - PreviousSyncTime;
}
