class BfmeMsgXI;

class BfmeKindXI
{
public:
	unsigned char m_bfmeHeadXI[4];
	unsigned short volatile m_bfmeTypeXI;
};

class BfmeTargetXI
{
public:
	virtual void bfmeT000XI();
	virtual void bfmeT001XI();
	virtual void bfmeT002XI();
	virtual void bfmeT003XI();
	virtual void bfmeT004XI();
	virtual void bfmeT005XI();
	virtual void bfmeT006XI();
	virtual void bfmeT007XI();
	virtual void bfmeT008XI();
	virtual void bfmeT009XI();
	virtual void bfmeT010XI();
	virtual void bfmeT011XI();
	virtual void bfmeT012XI();
	virtual void bfmeT013XI();
	virtual void bfmeT014XI();
	virtual void bfmeT015XI();
	virtual void bfmeT016XI();
	virtual void bfmeT017XI();
	virtual void bfmeT018XI();
	virtual void bfmeT019XI();
	virtual void bfmeT020XI();
	virtual void bfmeT021XI();
	virtual void bfmeT022XI();
	virtual void bfmeT023XI();
	virtual void bfmeT024XI();
	virtual void bfmeT025XI();
	virtual void bfmeT026XI();
	virtual void bfmeT027XI();
	virtual void bfmeT028XI();
	virtual void bfmeT029XI();
	virtual void bfmeT030XI();
	virtual void bfmeT031XI();
	virtual void bfmeT032XI();
	virtual void bfmeT033XI();
	virtual void bfmeT034XI();
	virtual void bfmeT035XI();
	virtual void bfmeT036XI();
	virtual void bfmeT037XI();
	virtual void bfmeT038XI();
	virtual void bfmeT039XI();
	virtual void bfmeT040XI();
	virtual void bfmeT041XI();
	virtual void bfmeT042XI();
	virtual void bfmeT043XI();
	virtual void bfmeT044XI();
	virtual void bfmeT045XI();
	virtual void bfmeT046XI();
	virtual void bfmeT047XI();
	virtual void bfmeT048XI();
	virtual void bfmeT049XI();
	virtual void bfmeT050XI();
	virtual void bfmeT051XI();
	virtual void bfmeT052XI();
	virtual void bfmeT053XI();
	virtual void bfmeT054XI();
	virtual void bfmeT055XI();
	virtual void bfmeT056XI();
	virtual void bfmeT057XI();
	virtual void bfmeT058XI();
	virtual void bfmeT059XI();
	virtual void bfmeT060XI();
	virtual void bfmeT061XI();
	virtual void bfmeT062XI();
	virtual void bfmeT063XI();
	virtual void bfmeT064XI();
	virtual void bfmeT065XI();
	virtual void bfmeT066XI();
	virtual void bfmeT067XI();
	virtual void bfmeT068XI();
	virtual void bfmeT069XI();
	virtual void bfmeT070XI();
	virtual void bfmeT071XI();
	virtual void bfmeT072XI();
	virtual void bfmeT073XI();
	virtual void bfmeT074XI();
	virtual void bfmeT075XI();
	virtual void bfmeT076XI();
	virtual void bfmeT077XI();
	virtual void bfmeT078XI();
	virtual void bfmeT079XI();
	virtual void bfmeT080XI();
	virtual void bfmeT081XI();
	virtual void bfmeT082XI();
	virtual void bfmeT083XI();
	virtual void bfmeT084XI();
	virtual void bfmeT085XI();
	virtual void bfmeT086XI();
	virtual void bfmeT087XI();
	virtual void bfmeT088XI();
	virtual void bfmeT089XI();
	virtual void bfmeT090XI();
	virtual void bfmeT091XI();
	virtual void bfmeT092XI();
	virtual void bfmeT093XI();
	virtual void bfmeT094XI();
	virtual void bfmeT095XI();
	virtual void bfmeT096XI();
	virtual void bfmeT097XI();
	virtual void bfmeT098XI();
	virtual void bfmeT099XI();
	virtual void bfmeT100XI();
	virtual void bfmeT101XI();
	virtual void bfmeT102XI();
	virtual void bfmeT103XI();
	virtual void bfmeT104XI();
	virtual void bfmeT105XI();
	virtual void bfmeT106XI();
	virtual void bfmeT107XI();
	virtual void bfmeT108XI();
	virtual void bfmeTakeXI(BfmeMsgXI *msg, int flag);

	void bfmeUseXI(BfmeMsgXI *msg);
};

class BfmeHubXI
{
public:
	virtual void bfmeH00XI();
	virtual void bfmeH01XI();
	virtual void bfmeH02XI();
	virtual void bfmeH03XI();
	virtual void bfmeH04XI();
	virtual void bfmeH05XI();
	virtual void bfmeH06XI();
	virtual void bfmeH07XI();
	virtual void bfmeH08XI();
	virtual void bfmeH09XI();
	virtual void bfmeH10XI();
	virtual void bfmeH11XI();
	virtual void bfmeH12XI();
	virtual void bfmeH13XI();
	virtual void bfmeH14XI();
	virtual void bfmeH15XI();
	virtual void bfmeH16XI();
	virtual void bfmeH17XI();
	virtual void bfmeH18XI();
	virtual void bfmeH19XI();
	virtual void bfmeH20XI();
	virtual void bfmeH21XI();
	virtual void bfmeH22XI();
	virtual void bfmeH23XI();
	virtual void bfmeH24XI();
	virtual void bfmeH25XI();
	virtual BfmeTargetXI *bfmeTopXI();
};

class BfmeMsgXI
{
public:
	BfmeKindXI *m_bfmeKindXI;
};

class BfmeOwnerXI
{
public:
	void bfmeSendXI(BfmeMsgXI *msg);

	BfmeTargetXI *bfmeFindXI();

	unsigned char m_bfmeHeadXI[0x1fc];
	BfmeHubXI *m_bfmeHubXI;
};

void BfmeOwnerXI::bfmeSendXI(BfmeMsgXI *msg)
{
	BfmeKindXI *kind = msg->m_bfmeKindXI;

	if (kind != 0)
	{
		int type = kind->m_bfmeTypeXI;

		if (type == 1)
			return;
	}

	BfmeHubXI *hub = m_bfmeHubXI;

	if (hub != 0)
	{
		BfmeTargetXI *target = hub->bfmeTopXI();

		if (target != 0)
		{
			target->bfmeTakeXI(msg, 0);
			return;
		}
	}

	BfmeTargetXI *other = bfmeFindXI();

	if (other != 0)
		other->bfmeUseXI(msg);
}
