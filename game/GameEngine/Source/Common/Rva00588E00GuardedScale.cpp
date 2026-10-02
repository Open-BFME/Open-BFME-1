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

// Retail 0x012F1028 is EA's `LivingWorldLogic *TheLivingWorldLogic`, defined
// once in game/GameEngine/Source/GameLogic/LivingWorld/LivingWorldLogic.cpp.
// CampaignObject above is this TU's own view of that address, so the reads cast.
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

// ?Rva00588E00Value@@YAMXZ
float Rva00588E00Value()
{
	if (TheLivingWorldLogic)
	{
		CampaignObject *campaign = (CampaignObject *)TheLivingWorldLogic;

		if (campaign->m_flag2C)
		{
			return campaign->getBountyBonusPercent() * g_01076C24 + g_bfmeDefaultBU;
		}
	}
	return g_bfmeDefaultBU;
}
