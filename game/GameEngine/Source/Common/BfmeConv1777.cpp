// Retail defines this singleton as `BfmeGameCW *g_bfmeGameCW`
// (?g_bfmeGameCW@@3PAVBfmeGameCW@@A); this TU only needs the pointer's
// address, so it forward-declares the class and reinterprets it. The +0x16C
// member address is taken in bytes, so it does not need sizeof(BfmeGameCW).
class BfmeGameCW;
// Retail 0x012F706C is ?TheLivingWorldManager@@3PAVLivingWorldManager@@A (data_rows.csv,
// LivingWorld/LivingWorldManager.cpp); g_bfmeGameCW was only a pin.
class LivingWorldManager;
extern LivingWorldManager *TheLivingWorldManager;
#define g_bfmeGameCW ( *(BfmeGameCW **)&TheLivingWorldManager )

// Retail calls ILT 0x00032010 -> 0x003A48B0, the row defined in
// LivingWorld/Rva003A48B0ApplyByName.cpp as Rva003A48B0Owner::applyByName;
// the member spelling below forwards to that definition.
class AsciiString;
class Rva003A48B0Owner
{
public:
	void applyByName(const AsciiString *name, char flag, int mode);
};

class BfmeOwnCZ
{
public:
	void bfmeSetCZ(int enable);
	void bfmeApplyCZ(void *target, int first, int second)
	{
		reinterpret_cast<Rva003A48B0Owner *>(this)->applyByName(
			(const AsciiString *)target, (char)first, second);
	}

	unsigned char m_bfmeHeadCZ[0x38];
	char m_bfmeStateCZ;
};

void BfmeOwnCZ::bfmeSetCZ(int enable)
{
	if ((char)enable)
	{
		if (m_bfmeStateCZ == 0)
			bfmeApplyCZ((char *)g_bfmeGameCW + 0x16c, enable, 1);
	}
	else
	{
		if (m_bfmeStateCZ != 0)
			bfmeApplyCZ((char *)g_bfmeGameCW + 0x16c, 1, 2);
	}

	m_bfmeStateCZ = (char)enable;
}
