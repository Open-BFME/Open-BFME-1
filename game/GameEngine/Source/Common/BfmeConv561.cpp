// stlport

#include <vector>

class Rva003BDC50
{
public:
	void run();
};

class Rva003BFAB0
{
public:
	void run(bool value);
};

struct BfmePlayerArmyStringHeader
{
	int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	char m_text[1];
};

class AsciiString
{
public:
	bool isEmpty() const
	{
		return !m_data || m_data->m_length == 0;
	}

private:
	BfmePlayerArmyStringHeader *m_data;
};

class LivingWorldPlayerArmy;

class LivingWorldArmy
{
public:
	void replenish(LivingWorldPlayerArmy *playerArmy);
};

class BfmeLivingWorldCampaignManager
{
public:
	LivingWorldArmy *findArmy(const AsciiString &name);
};

extern BfmeLivingWorldCampaignManager *TheLivingWorldCampaignManager;

class LivingWorldPlayerArmy
{
public:
	int currentCommandPoints() const;
	char m_unmodelled[0x50];
	int m_minCommandPoints;
	AsciiString m_replenishArmyName;
};

class BfmeSubBZF
{
public:
	void bfmeOneBZF();

private:
	char m_unmodelled[0x18];
	std::vector<LivingWorldPlayerArmy> m_playerArmies;
};

class BfmeThingBZF
{
public:
	void bfmeGoBZF();
	unsigned char m_bfmeHead[0x170];
	BfmeSubBZF m_bfmeSub;
};

// Retail's loads at 0x00383950 are 0x012F1028: the global BfmeConv2113.cpp
// defines; this TU keeps its own view type and casts at the use.
class Glo012F1028Type;
// Retail 0x012F1028 is EA's TheLivingWorldLogic (data_rows.csv owns
// ?TheLivingWorldLogic@@3PAVLivingWorldLogic@@A, LivingWorldLogic.cpp); the
// Glo012F1028 spelling is only a pin nothing defines.
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;
#define Glo012F1028 ( reinterpret_cast<Glo012F1028Type *>( TheLivingWorldLogic ) )

// The matched caller at 0x00383950 reaches this method through ILT 0x0000E458.
// Retail 0x00366130 walks the sub-object's 0x58-byte Living World player-army
// records and repeats the already recovered player-army load-post process.
void BfmeSubBZF::bfmeOneBZF()
{
	for (unsigned int i = 0; i < m_playerArmies.size(); ++i)
	{
		LivingWorldPlayerArmy *playerArmy = &m_playerArmies[i];
		if (playerArmy->currentCommandPoints() < playerArmy->m_minCommandPoints &&
			!playerArmy->m_replenishArmyName.isEmpty())
		{
			LivingWorldArmy *army =
				TheLivingWorldCampaignManager->findArmy(playerArmy->m_replenishArmyName);
			if (army)
				army->replenish(playerArmy);
		}
	}
}

void BfmeThingBZF::bfmeGoBZF()
{
	m_bfmeSub.bfmeOneBZF();
	reinterpret_cast<Rva003BDC50 *>(Glo012F1028)->run();
	reinterpret_cast<Rva003BFAB0 *>(Glo012F1028)->run(false);
}
