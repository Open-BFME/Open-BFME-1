// ?bfmeMinAF@BfmeOwnerAF@@QAEXPAVBfmeThingAF@@PAH@Z (identity unknown)
// partial score=0.97 date=2026-09-07
// 93/93, exact size; the whole two-iteration loop matches byte for byte. Only
// the first four head instructions differ, and purely by register name:
//   retail  esi <- a1 (thing), edi <- this, then `lea esi,[edi+0x1e8]` reuses
//           esi for the slot pointer and keeps `this` in edi
//   MSVC    edi <- a1 (thing), esi <- this, then `add esi,0x1e8` -- same size
// [[argument-shuttle-register]]. Naming `thing` in a local, and pinning the
// out-pointer read with *(int *volatile *)& so it lands just before the loop
// (retail's position), both leave the head unchanged.
// Everything else is settled and was needed: the guarded sub pointer MUST be a
// named local or MSVC loads it into eax and copies to ecx (2 bytes,
// [[local-picks-ecx-receiver]]); the two flag tests are plain `int & 1` and
// `int & 0x14` members, which narrow to `test byte ptr` on their own -- no union
// needed here because neither member is also written as a dword.
class BfmeSubAF
{
public:
	virtual void bfmeS00AF();
	virtual void bfmeS01AF();
	virtual void bfmeS02AF();
	virtual void bfmeS03AF();
	virtual void bfmeS04AF();
	virtual void bfmeS05AF();
	virtual void bfmeS06AF();
	virtual void bfmeS07AF();
	virtual void bfmeS08AF();
	virtual void bfmeS09AF();
	virtual void bfmeS10AF();
	virtual void bfmeS11AF();
	virtual void bfmeS12AF();
	virtual void bfmeS13AF();
	virtual void bfmeS14AF();
	virtual void bfmeS15AF();
	virtual void bfmeS16AF();
	virtual void bfmeS17AF();
	virtual void bfmeS18AF();
	virtual void bfmeS19AF();
	virtual void bfmeS20AF();
	virtual void bfmeS21AF();
	virtual void bfmeS22AF();
	virtual void bfmeS23AF();
	virtual void bfmeS24AF();
	virtual void bfmeS25AF();
	virtual void bfmeS26AF();
	virtual void bfmeS27AF();
	virtual void bfmeS28AF();
	virtual void bfmeS29AF();
	virtual void bfmeS30AF();
	virtual void bfmeS31AF();
	virtual void bfmeS32AF();
	virtual void bfmeS33AF();
	virtual void bfmeS34AF();
	virtual void bfmeS35AF();
	virtual void bfmeS36AF();
	virtual void bfmeS37AF();
	virtual void bfmeS38AF();
	virtual void bfmeS39AF();
	virtual void bfmeS40AF();
	virtual void bfmeS41AF();
	virtual void bfmeS42AF();
	virtual void bfmeS43AF();
	virtual void bfmeS44AF();
	virtual void bfmeS45AF();
	virtual void bfmeS46AF();
	virtual void bfmeS47AF();
	virtual void bfmeS48AF();
	virtual void bfmeS49AF();
	virtual void bfmeS50AF();
	virtual void bfmeS51AF();
	virtual void bfmeS52AF();
	virtual void bfmeS53AF();
	virtual void bfmeS54AF();
	virtual void bfmeS55AF();
	virtual void bfmeS56AF();
	virtual void bfmeS57AF();
	virtual void bfmeS58AF();
	virtual void bfmeS59AF();
	virtual void bfmeS60AF();
	virtual void bfmeS61AF();
	virtual void bfmeS62AF();
	virtual void bfmeS63AF();
	virtual void bfmeS64AF();
	virtual void bfmeS65AF();
	virtual void bfmeS66AF();
	virtual void bfmeS67AF();
	virtual void bfmeS68AF();
	virtual void bfmeS69AF();
	virtual void bfmeS70AF();
	virtual void bfmeS71AF();
	virtual void bfmeS72AF();
	virtual void bfmeS73AF();
	virtual void bfmeS74AF();
	virtual void bfmeS75AF();
	virtual void bfmeS76AF();
	virtual void bfmeS77AF();
	virtual void bfmeS78AF();
	virtual void bfmeS79AF();
	virtual void bfmeS80AF();
	virtual void bfmeS81AF();
	virtual void bfmeS82AF();
	virtual void bfmeS83AF();
	virtual void bfmeS84AF();
	virtual void bfmeS85AF();
	virtual void bfmeS86AF();
	virtual void bfmeS87AF();
	virtual void bfmeS88AF();
	virtual void bfmeS89AF();
	virtual void bfmeS90AF();
	virtual void bfmeS91AF();
	virtual void bfmeS92AF();
	virtual void bfmeS93AF();
	virtual void bfmeS94AF();
	virtual void bfmeS95AF();
	virtual void bfmeS96AF();
	virtual void bfmeS97AF();
	virtual void bfmeS98AF();
	virtual char bfmeBusyAF();
};

class BfmeSlotAF
{
public:
	int bfmeCostAF();
};

class BfmeThingAF
{
public:
	unsigned char m_bfmeHeadAF[0x1a4];
	int m_bfmeStateAF;
	unsigned char m_bfmeMidAF[0x5c];
	BfmeSubAF *m_bfmeSubAF;
	unsigned char m_bfmeMid2AF[0x13c];
	int m_bfmeFlagsAF;
};

class BfmeOwnerAF
{
public:
	void bfmeMinAF(BfmeThingAF *thing, int *best);

	unsigned char m_bfmeHeadAF[0x1e8];
	BfmeSlotAF *m_bfmeSlotsAF[2];
};

void BfmeOwnerAF::bfmeMinAF(BfmeThingAF *thing, int *best)
{
	BfmeSubAF *sub = thing->m_bfmeSubAF;

	if (sub != 0 && sub->bfmeBusyAF() != 0)
		return;

	if ((thing->m_bfmeFlagsAF & 1) != 0)
		return;

	if ((thing->m_bfmeStateAF & 0x14) != 0)
		return;

	for (int i = 0; i < 2; i++)
	{
		BfmeSlotAF *slot = m_bfmeSlotsAF[i];

		if (slot != 0)
		{
			int cost = slot->bfmeCostAF();

			if (cost < *best)
				*best = cost;
		}
	}
}
