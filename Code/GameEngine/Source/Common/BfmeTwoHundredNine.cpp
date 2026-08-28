// Four short questions put through a table: a held piece asked in turn, a reader
// peeked at before it steps on, a buffer handed the next byte, and two things
// compared for sameness.

class BfmeItemHS
{
public:
	virtual void bfmeSpare000HS(void) = 0;
	virtual void bfmeSpare001HS(void) = 0;
	virtual void bfmeSpare002HS(void) = 0;
	virtual void bfmeSpare003HS(void) = 0;
	virtual void bfmeSpare004HS(void) = 0;
	virtual void bfmeSpare005HS(void) = 0;
	virtual void bfmeSpare006HS(void) = 0;
	virtual void bfmeSpare007HS(void) = 0;
	virtual void bfmeSpare008HS(void) = 0;
	virtual void bfmeSpare009HS(void) = 0;
	virtual void bfmeSpare010HS(void) = 0;
	virtual void bfmeSpare011HS(void) = 0;
	virtual void bfmeSpare012HS(void) = 0;
	virtual void bfmeSpare013HS(void) = 0;
	virtual void bfmeSpare014HS(void) = 0;
	virtual void bfmeSpare015HS(void) = 0;
	virtual void bfmeSpare016HS(void) = 0;
	virtual void bfmeSpare017HS(void) = 0;
	virtual void bfmeSpare018HS(void) = 0;
	virtual void bfmeSpare019HS(void) = 0;
	virtual void bfmeSpare020HS(void) = 0;
	virtual void bfmeSpare021HS(void) = 0;
	virtual void bfmeSpare022HS(void) = 0;
	virtual void bfmeSpare023HS(void) = 0;
	virtual void bfmeSpare024HS(void) = 0;
	virtual void bfmeSpare025HS(void) = 0;
	virtual void bfmeSpare026HS(void) = 0;
	virtual void bfmeSpare027HS(void) = 0;
	virtual void bfmeSpare028HS(void) = 0;
	virtual void bfmeSpare029HS(void) = 0;
	virtual void bfmeSpare030HS(void) = 0;
	virtual void bfmeSpare031HS(void) = 0;
	virtual void bfmeSpare032HS(void) = 0;
	virtual void bfmeSpare033HS(void) = 0;
	virtual void bfmeSpare034HS(void) = 0;
	virtual void bfmeSpare035HS(void) = 0;
	virtual void bfmeSpare036HS(void) = 0;
	virtual void bfmeSpare037HS(void) = 0;
	virtual void bfmeSpare038HS(void) = 0;
	virtual void bfmeSpare039HS(void) = 0;
	virtual void bfmeSpare040HS(void) = 0;
	virtual void bfmeSpare041HS(void) = 0;
	virtual void bfmeSpare042HS(void) = 0;
	virtual void bfmeSpare043HS(void) = 0;
	virtual void bfmeSpare044HS(void) = 0;
	virtual void bfmeSpare045HS(void) = 0;
	virtual void bfmeSpare046HS(void) = 0;
	virtual void bfmeSpare047HS(void) = 0;
	virtual void bfmeSpare048HS(void) = 0;
	virtual void bfmeSpare049HS(void) = 0;
	virtual void bfmeSpare050HS(void) = 0;
	virtual void bfmeSpare051HS(void) = 0;
	virtual void bfmeSpare052HS(void) = 0;
	virtual void bfmeSpare053HS(void) = 0;
	virtual void bfmeSpare054HS(void) = 0;
	virtual void bfmeSpare055HS(void) = 0;
	virtual void bfmeSpare056HS(void) = 0;
	virtual void bfmeSpare057HS(void) = 0;
	virtual void bfmeSpare058HS(void) = 0;
	virtual void bfmeSpare059HS(void) = 0;
	virtual void bfmeSpare060HS(void) = 0;
	virtual void bfmeSpare061HS(void) = 0;
	virtual void bfmeSpare062HS(void) = 0;
	virtual void bfmeSpare063HS(void) = 0;
	virtual void bfmeSpare064HS(void) = 0;
	virtual void bfmeSpare065HS(void) = 0;
	virtual void bfmeSpare066HS(void) = 0;
	virtual void bfmeSpare067HS(void) = 0;
	virtual void bfmeSpare068HS(void) = 0;
	virtual void bfmeSpare069HS(void) = 0;
	virtual void bfmeSpare070HS(void) = 0;
	virtual void bfmeSpare071HS(void) = 0;
	virtual void bfmeSpare072HS(void) = 0;
	virtual void bfmeSpare073HS(void) = 0;
	virtual void bfmeSpare074HS(void) = 0;
	virtual void bfmeSpare075HS(void) = 0;
	virtual void bfmeSpare076HS(void) = 0;
	virtual void bfmeSpare077HS(void) = 0;
	virtual void bfmeSpare078HS(void) = 0;
	virtual void bfmeSpare079HS(void) = 0;
	virtual void bfmeSpare080HS(void) = 0;
	virtual void bfmeSpare081HS(void) = 0;
	virtual void bfmeSpare082HS(void) = 0;
	virtual void bfmeSpare083HS(void) = 0;
	virtual void bfmeSpare084HS(void) = 0;
	virtual void bfmeSpare085HS(void) = 0;
	virtual void bfmeSpare086HS(void) = 0;
	virtual void bfmeSpare087HS(void) = 0;
	virtual void bfmeSpare088HS(void) = 0;
	virtual void bfmeSpare089HS(void) = 0;
	virtual void bfmeSpare090HS(void) = 0;
	virtual void bfmeSpare091HS(void) = 0;
	virtual void bfmeSpare092HS(void) = 0;
	virtual void bfmeSpare093HS(void) = 0;
	virtual void bfmeSpare094HS(void) = 0;
	virtual int bfmeAskHS(void) = 0;
};

class BfmeThingHS
{
public:
	int bfmeAskHS(void);

private:
	unsigned char m_bfmeHead[0x34];		// 0x00
	BfmeItemHS *m_bfmeItem;			// 0x34
};

int BfmeThingHS::bfmeAskHS(void)
{
	if (m_bfmeItem != 0 && m_bfmeItem->bfmeAskHS() != 0)
		return 1;

	return 0;
}

class BfmeThingHT
{
public:
	virtual void bfmeSpare000HT(void) = 0;
	virtual void bfmeSpare001HT(void) = 0;
	virtual void bfmeSpare002HT(void) = 0;
	virtual void bfmeSpare003HT(void) = 0;
	virtual void bfmeSpare004HT(void) = 0;
	virtual void bfmeSpare005HT(void) = 0;
	virtual void bfmeSpare006HT(void) = 0;
	virtual void bfmeSpare007HT(void) = 0;
	virtual void bfmeSpare008HT(void) = 0;
	virtual void bfmeSpare009HT(void) = 0;
	virtual void bfmeSpare010HT(void) = 0;
	virtual void bfmeSpare011HT(void) = 0;
	virtual void bfmeSpare012HT(void) = 0;
	virtual void bfmeSpare013HT(void) = 0;
	virtual void bfmeSpare014HT(void) = 0;
	virtual void bfmeSpare015HT(void) = 0;
	virtual void bfmeSpare016HT(void) = 0;
	virtual void bfmeSpare017HT(void) = 0;
	virtual void bfmeSpare018HT(void) = 0;
	virtual void bfmeSpare019HT(void) = 0;
	virtual void bfmeSpare020HT(void) = 0;
	virtual void bfmeSpare021HT(void) = 0;
	virtual void bfmeSpare022HT(void) = 0;
	virtual void bfmeSpare023HT(void) = 0;
	virtual void bfmeSpare024HT(void) = 0;
	virtual void bfmeSpare025HT(void) = 0;
	virtual void bfmeSpare026HT(void) = 0;
	virtual void bfmeSpare027HT(void) = 0;
	virtual void bfmeSpare028HT(void) = 0;
	virtual void bfmeSpare029HT(void) = 0;
	virtual void bfmeSpare030HT(void) = 0;
	virtual void bfmeSpare031HT(void) = 0;
	virtual void bfmeSpare032HT(void) = 0;
	virtual void bfmeSpare033HT(void) = 0;
	virtual void bfmeSpare034HT(void) = 0;
	virtual void bfmeSpare035HT(void) = 0;
	virtual void bfmeSpare036HT(void) = 0;
	virtual void bfmeSpare037HT(void) = 0;
	virtual void bfmeSpare038HT(void) = 0;
	virtual void bfmeSpare039HT(void) = 0;
	virtual void bfmeSpare040HT(void) = 0;
	virtual void bfmeSpare041HT(void) = 0;
	virtual void bfmeSpare042HT(void) = 0;
	virtual void bfmeSpare043HT(void) = 0;
	virtual void bfmeSpare044HT(void) = 0;
	virtual void bfmeSpare045HT(void) = 0;
	virtual void bfmeSpare046HT(void) = 0;
	virtual void bfmeSpare047HT(void) = 0;
	virtual void bfmeSpare048HT(void) = 0;
	virtual void bfmeSpare049HT(void) = 0;
	virtual void bfmeSpare050HT(void) = 0;
	virtual void bfmeSpare051HT(void) = 0;
	virtual void bfmeSpare052HT(void) = 0;
	virtual void bfmeSpare053HT(void) = 0;
	virtual void bfmeSpare054HT(void) = 0;
	virtual void bfmeSpare055HT(void) = 0;
	virtual void bfmeSpare056HT(void) = 0;
	virtual void bfmeSpare057HT(void) = 0;
	virtual void bfmeSpare058HT(void) = 0;
	virtual void bfmeSpare059HT(void) = 0;
	virtual void bfmeSpare060HT(void) = 0;
	virtual void bfmeSpare061HT(void) = 0;
	virtual void bfmeSpare062HT(void) = 0;
	virtual void bfmeSpare063HT(void) = 0;
	virtual void bfmeSpare064HT(void) = 0;
	virtual void bfmeSpare065HT(void) = 0;
	virtual void bfmeSpare066HT(void) = 0;
	virtual void bfmeSpare067HT(void) = 0;
	virtual void bfmeSpare068HT(void) = 0;
	virtual void bfmeSpare069HT(void) = 0;
	virtual void bfmeSpare070HT(void) = 0;
	virtual void bfmeSpare071HT(void) = 0;
	virtual void bfmeSpare072HT(void) = 0;
	virtual void bfmeSpare073HT(void) = 0;
	virtual void bfmeSpare074HT(void) = 0;
	virtual void bfmeSpare075HT(void) = 0;
	virtual void bfmeSpare076HT(void) = 0;
	virtual void bfmeSpare077HT(void) = 0;
	virtual void bfmeSpare078HT(void) = 0;
	virtual void bfmeSpare079HT(void) = 0;
	virtual void bfmeSpare080HT(void) = 0;
	virtual void bfmeSpare081HT(void) = 0;
	virtual void bfmeSpare082HT(void) = 0;
	virtual void bfmeSpare083HT(void) = 0;
	virtual void bfmeSpare084HT(void) = 0;
	virtual void bfmeSpare085HT(void) = 0;
	virtual void bfmeSpare086HT(void) = 0;
	virtual void bfmeSpare087HT(void) = 0;
	virtual int bfmePeekHT(void) = 0;
	virtual int bfmeNextHT(void) = 0;

	int bfmeGetHT(void);
};

int BfmeThingHT::bfmeGetHT(void)
{
	int one = bfmePeekHT();

	if (one == -1)
		return one;

	if (one != 0)
		return one;

	return bfmeNextHT();
}

struct BfmeBufHU
{
	const unsigned char *m_bfmeAt;		// 0x0
	int m_bfmeLeft;				// 0x4
};


class BfmeThingHU
{
public:
	virtual void bfmeSpare000HU(void) = 0;
	virtual void bfmeSpare001HU(void) = 0;
	virtual void bfmeSpare002HU(void) = 0;
	virtual void bfmeSpare003HU(void) = 0;
	virtual void bfmeSpare004HU(void) = 0;
	virtual void bfmeSpare005HU(void) = 0;
	virtual void bfmeSpare006HU(void) = 0;
	virtual int bfmePeekHU(void) = 0;

	int bfmeGetHU(void);

private:
	BfmeBufHU *m_bfmeBuf;			// 0x4
};

int BfmeThingHU::bfmeGetHU(void)
{
	int one = bfmePeekHU();

	if (one == -1)
		return one;

	BfmeBufHU *buf = m_bfmeBuf;

	--buf->m_bfmeLeft;

	const unsigned char *at = buf->m_bfmeAt;

	buf->m_bfmeAt = at + 1;

	return *at;
}


class BfmeThingHX
{
public:
	virtual void bfmeSpare000HX(void) = 0;
	virtual void bfmeSpare001HX(void) = 0;
	virtual void bfmeSpare002HX(void) = 0;
	virtual void bfmeSpare003HX(void) = 0;
	virtual void bfmeSpare004HX(void) = 0;
	virtual void bfmeSpare005HX(void) = 0;
	virtual void bfmeSpare006HX(void) = 0;
	virtual void bfmeSpare007HX(void) = 0;
	virtual void bfmeSpare008HX(void) = 0;
	virtual void bfmeSpare009HX(void) = 0;
	virtual void bfmeSpare010HX(void) = 0;
	virtual void bfmeSpare011HX(void) = 0;
	virtual void bfmeSpare012HX(void) = 0;
	virtual void bfmeSpare013HX(void) = 0;
	virtual void bfmeSpare014HX(void) = 0;
	virtual void bfmeSpare015HX(void) = 0;
	virtual void bfmeSpare016HX(void) = 0;
	virtual void bfmeSpare017HX(void) = 0;
	virtual void bfmeSpare018HX(void) = 0;
	virtual void bfmeSpare019HX(void) = 0;
	virtual void bfmeSpare020HX(void) = 0;
	virtual void bfmeSpare021HX(void) = 0;
	virtual void bfmeSpare022HX(void) = 0;
	virtual void bfmeSpare023HX(void) = 0;
	virtual void bfmeSpare024HX(void) = 0;
	virtual void bfmeSpare025HX(void) = 0;
	virtual void bfmeSpare026HX(void) = 0;
	virtual void bfmeSpare027HX(void) = 0;
	virtual void bfmeSpare028HX(void) = 0;
	virtual void bfmeSpare029HX(void) = 0;
	virtual void bfmeSpare030HX(void) = 0;
	virtual void bfmeSpare031HX(void) = 0;
	virtual void bfmeSpare032HX(void) = 0;
	virtual void bfmeSpare033HX(void) = 0;
	virtual void bfmeSpare034HX(void) = 0;
	virtual void bfmeSpare035HX(void) = 0;
	virtual void bfmeSpare036HX(void) = 0;
	virtual void bfmeSpare037HX(void) = 0;
	virtual void bfmeSpare038HX(void) = 0;
	virtual void bfmeSpare039HX(void) = 0;
	virtual void bfmeSpare040HX(void) = 0;
	virtual void bfmeSpare041HX(void) = 0;
	virtual void bfmeSpare042HX(void) = 0;
	virtual void bfmeSpare043HX(void) = 0;
	virtual void bfmeSpare044HX(void) = 0;
	virtual void bfmeSpare045HX(void) = 0;
	virtual void bfmeSpare046HX(void) = 0;
	virtual void bfmeSpare047HX(void) = 0;
	virtual void bfmeSpare048HX(void) = 0;
	virtual void bfmeSpare049HX(void) = 0;
	virtual void bfmeSpare050HX(void) = 0;
	virtual void bfmeSpare051HX(void) = 0;
	virtual void bfmeSpare052HX(void) = 0;
	virtual void bfmeSpare053HX(void) = 0;
	virtual void bfmeSpare054HX(void) = 0;
	virtual void bfmeSpare055HX(void) = 0;
	virtual void bfmeSpare056HX(void) = 0;
	virtual void bfmeSpare057HX(void) = 0;
	virtual void bfmeSpare058HX(void) = 0;
	virtual void bfmeSpare059HX(void) = 0;
	virtual void bfmeSpare060HX(void) = 0;
	virtual void bfmeSpare061HX(void) = 0;
	virtual void bfmeSpare062HX(void) = 0;
	virtual void bfmeSpare063HX(void) = 0;
	virtual void bfmeSpare064HX(void) = 0;
	virtual void bfmeSpare065HX(void) = 0;
	virtual void bfmeSpare066HX(void) = 0;
	virtual void bfmeSpare067HX(void) = 0;
	virtual void bfmeSpare068HX(void) = 0;
	virtual void bfmeSpare069HX(void) = 0;
	virtual void bfmeSpare070HX(void) = 0;
	virtual void bfmeSpare071HX(void) = 0;
	virtual void bfmeSpare072HX(void) = 0;
	virtual void bfmeSpare073HX(void) = 0;
	virtual void bfmeSpare074HX(void) = 0;
	virtual void bfmeSpare075HX(void) = 0;
	virtual void bfmeSpare076HX(void) = 0;
	virtual void bfmeSpare077HX(void) = 0;
	virtual void bfmeSpare078HX(void) = 0;
	virtual void bfmeSpare079HX(void) = 0;
	virtual void bfmeSpare080HX(void) = 0;
	virtual void bfmeSpare081HX(void) = 0;
	virtual void bfmeSpare082HX(void) = 0;
	virtual void bfmeSpare083HX(void) = 0;
	virtual void bfmeSpare084HX(void) = 0;
	virtual void bfmeSpare085HX(void) = 0;
	virtual void bfmeSpare086HX(void) = 0;
	virtual int bfmeDoHX(void *first, void *second) = 0;

	int bfmeAskHX(void *first, void *second);
};

int BfmeThingHX::bfmeAskHX(void *first, void *second)
{
	return bfmeDoHX(first, second) == 0;
}

