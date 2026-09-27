// cl: /O2 /DNDEBUG /MD /EHsc
// Rva00588E00 guarded living-world bounty scale, retail 0x00588E00 (51 bytes).
// Guarded twin of Rva00588DE0Scale: a nil receiver or a clear flag byte at
// +0x2C falls back to g_bfmeDefaultBU; otherwise the int percent from
// CampaignObject::getBountyBonusPercent (retail 0x003BDCF0, reached through
// the pinned ILT) is converted in x87 and scaled by g_01076C24.
extern const float g_01076C24;
extern float g_bfmeDefaultBU;

class CampaignObject
{
public:
	int getBountyBonusPercent();
	unsigned char m_pad[ 0x2C ];
	unsigned char m_flag2C;
};

extern CampaignObject *TheLivingWorldLogic;

// ?Rva00588E00Value@@YAMXZ
float Rva00588E00Value()
{
	if (TheLivingWorldLogic)
	{
		if (TheLivingWorldLogic->m_flag2C)
		{
			return TheLivingWorldLogic->getBountyBonusPercent() * g_01076C24 + g_bfmeDefaultBU;
		}
	}
	return g_bfmeDefaultBU;
}
