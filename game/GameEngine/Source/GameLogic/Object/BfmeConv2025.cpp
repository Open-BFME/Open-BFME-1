class BfmePosTP;

class BfmeXTP
{
public:
	void bfmeFlagTP(int mode);
};

class PartitionData
{
public:
	void friend_updateCellsTouched();
};

class BfmeIfcTP
{
public:
	virtual void bfmeIfc00TP();
	virtual void bfmeIfc01TP();
	virtual void bfmeIfc02TP();
	virtual void bfmeIfc03TP();
	virtual PartitionData *bfmeGetPartTP();
};

class BfmeWTP
{
public:
	virtual void bfmeW00TP();
	virtual void bfmeW01TP();
	virtual void bfmeW02TP();
	virtual void bfmeW03TP();
	virtual void bfmeW04TP();
	virtual void bfmeW05TP();
	virtual void bfmeW06TP();
	virtual void bfmeW07TP();
	virtual void bfmeW08TP();
	virtual void bfmeW09TP();
	virtual void bfmeW10TP();
	virtual void bfmeW11TP();
	virtual void bfmeW12TP();
	virtual void bfmeW13TP();
	virtual void bfmeW14TP();
	virtual void bfmeW15TP();
	virtual void bfmeW16TP();
	virtual void bfmeW17TP();
	virtual void bfmeW18TP();
	virtual void bfmeW19TP();
	virtual void bfmeW20TP();
	virtual void bfmeW21TP();
	virtual void bfmeW22TP();
	virtual void bfmeW23TP();
	virtual void bfmeW24TP();
	virtual void bfmeW25TP();
	virtual void bfmeW26TP();
	virtual void bfmeW27TP();
	virtual void bfmeW28TP();
	virtual void bfmeW29TP();
	virtual void bfmeW30TP();
	virtual void bfmeW31TP();
	virtual void bfmeW32TP();
	virtual void bfmeW33TP();
	virtual void bfmeW34TP();
	virtual void bfmeW35TP();
	virtual void bfmeW36TP();
	virtual void bfmeW37TP();
	virtual void bfmeW38TP();
	virtual void bfmeW39TP();
	virtual void bfmeW40TP();
	virtual void bfmeW41TP();
	virtual void bfmeW42TP();
	virtual void bfmeW43TP();
	virtual void bfmeW44TP();
	virtual void bfmeW45TP();
	virtual void bfmeW46TP();
	virtual void bfmeW47TP();
	virtual void bfmeW48TP();
	virtual void bfmeW49TP();
	virtual void bfmeW50TP();
	virtual void bfmeW51TP();
	virtual void bfmeW52TP();
	virtual void bfmeW53TP();
	virtual void bfmeW54TP();
	virtual void bfmeW55TP();
	virtual void bfmeW56TP();
	virtual void bfmeW57TP();
	virtual void bfmeW58TP();
	virtual void bfmeW59TP();
	virtual void bfmeW60TP();
	virtual void bfmeW61TP();
	virtual void bfmeW62TP();
	virtual void bfmeW63TP();
	virtual void bfmeW64TP();
	virtual void bfmeW65TP();
	virtual void bfmeW66TP();
	virtual void bfmeW67TP();
	virtual void bfmeW68TP();
	virtual void bfmeW69TP();
	virtual void bfmeW70TP();
	virtual void bfmeW71TP();
	virtual void bfmeW72TP();
	virtual void bfmeW73TP();
	virtual void bfmeW74TP();
	virtual void bfmeW75TP();
	virtual void bfmeW76TP();
	virtual void bfmeW77TP();
	virtual void bfmeW78TP();
	virtual void bfmeW79TP();
	virtual void bfmeW80TP();
	virtual void bfmeW81TP();
	virtual void bfmeW82TP();
	virtual void bfmeW83TP();
	virtual void bfmeW84TP();
	virtual void bfmeW85TP();
	virtual void bfmeW86TP();
	virtual void bfmeW87TP();
	virtual void bfmeW88TP();
	virtual void bfmeW89TP();
	virtual void bfmeW90TP();
	virtual void bfmeW91TP();
	virtual void bfmeW92TP();
	virtual void bfmeW93TP();
	virtual void bfmeW94TP();
	virtual void bfmeW95TP();
	virtual void bfmeW96TP();
	virtual void bfmeW97TP();
	virtual void bfmeW98TP();
	virtual void bfmeW99TP();
	virtual void bfmeNotifyTP(const BfmePosTP *pos);
};

class BfmeZTP
{
public:
	virtual void bfmeZ00TP();
	virtual void bfmeZ01TP();
	virtual void bfmeZ02TP();
	virtual void bfmeZ03TP();
	virtual void bfmeZ04TP();
	virtual void bfmeZ05TP();
	virtual void bfmeZ06TP();
	virtual void bfmeZ07TP();
	virtual void bfmeZ08TP();
	virtual void bfmeZ09TP();
	virtual void bfmeZ10TP();
	virtual void bfmeZ11TP();
	virtual void bfmeZ12TP();
	virtual void bfmeZ13TP();
	virtual void bfmeZ14TP();
	virtual void bfmeZ15TP();
	virtual void bfmeZ16TP();
	virtual void bfmeZ17TP();
	virtual void bfmeZ18TP();
	virtual void bfmeZ19TP();
	virtual void bfmeZ20TP();
	virtual void bfmeZ21TP();
	virtual void bfmeZ22TP();
	virtual void bfmeZ23TP();
	virtual void bfmeZ24TP();
	virtual void bfmeZ25TP();
	virtual BfmeWTP *bfmeGetWTP();
};

class BfmeInnerTP
{
public:
	void bfmeApplyTP(int mode);
};

class BfmeSubTP
{
public:
	void bfmeFinishTP();

	unsigned char m_bfmeHeadTP[0x20];
	BfmeInnerTP m_bfmeInnerTP;
};

struct Rva00367E30Logic
{
	unsigned char m_bfmeHeadTP[0x3c];
	unsigned int m_bfmeFrameTP;
};

extern Rva00367E30Logic *TheBfmeGameLogic;

class BfmeHostTP
{
public:
	virtual void bfmeSlot00TP();
	virtual void bfmeSlot01TP();
	virtual void bfmeSlot02TP();
	virtual void bfmeSlot03TP();
	virtual void bfmeSlot04TP();
	virtual void bfmeSlot05TP();
	virtual void bfmeSlot06TP();
	virtual void bfmeSlot07TP();
	virtual void bfmeSlot08TP();
	virtual void bfmeSlot09TP();
	virtual BfmeXTP *bfmeGetXTP();

	void bfmeSetPositionTP(const BfmePosTP *pos, bool flag);
	void bfmeSetPosTP(const BfmePosTP *pos);
	void bfmeMarkTP(unsigned int frame);

	unsigned char m_bfmeHeadTP[0x64];
	int *m_bfmeVbTP;
	unsigned char m_bfmePadTP[0x190];
	BfmeZTP *m_bfmeZTP;
	unsigned char m_bfmePadBTP[4];
	BfmeSubTP *m_bfmeSubTP;
};

void BfmeHostTP::bfmeSetPositionTP(const BfmePosTP *pos, bool flag)
{
	bfmeSetPosTP(pos);

	bfmeMarkTP(TheBfmeGameLogic->m_bfmeFrameTP);
	bfmeMarkTP(TheBfmeGameLogic->m_bfmeFrameTP);

	BfmeXTP *x = bfmeGetXTP();

	if (x != 0)
		x->bfmeFlagTP(1);

	bfmeSetPosTP(pos);

	BfmeIfcTP *ifc = (BfmeIfcTP *)((char *)&m_bfmeVbTP + m_bfmeVbTP[1]);

	if (ifc->bfmeGetPartTP() != 0)
	{
		BfmeIfcTP *ifc2 = (BfmeIfcTP *)((char *)&m_bfmeVbTP + m_bfmeVbTP[1]);

		ifc2->bfmeGetPartTP()->friend_updateCellsTouched();
	}

	BfmeZTP *z = m_bfmeZTP;

	if (z != 0)
	{
		BfmeWTP *w = z->bfmeGetWTP();

		if (w != 0)
			w->bfmeNotifyTP(pos);
	}

	if (!flag)
	{
		BfmeSubTP *s = m_bfmeSubTP;

		if (s != 0)
		{
			s->m_bfmeInnerTP.bfmeApplyTP(2);

			s->bfmeFinishTP();
		}
	}
}
