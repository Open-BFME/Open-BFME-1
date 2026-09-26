class Matrix3DTN;

class BfmeXTN
{
public:
	void bfmeFlagTN(int mode);
};

class PartitionData
{
public:
	void friend_updateCellsTouched();
};

class BfmeIfcTN
{
public:
	virtual void bfmeIfc00TN();
	virtual void bfmeIfc01TN();
	virtual void bfmeIfc02TN();
	virtual void bfmeIfc03TN();
	virtual PartitionData *bfmeGetPartTN();
};

class BfmeWTN
{
public:
	virtual void bfmeW00TN();
	virtual void bfmeW01TN();
	virtual void bfmeW02TN();
	virtual void bfmeW03TN();
	virtual void bfmeW04TN();
	virtual void bfmeW05TN();
	virtual void bfmeW06TN();
	virtual void bfmeW07TN();
	virtual void bfmeW08TN();
	virtual void bfmeW09TN();
	virtual void bfmeW10TN();
	virtual void bfmeW11TN();
	virtual void bfmeW12TN();
	virtual void bfmeW13TN();
	virtual void bfmeW14TN();
	virtual void bfmeW15TN();
	virtual void bfmeW16TN();
	virtual void bfmeW17TN();
	virtual void bfmeW18TN();
	virtual void bfmeW19TN();
	virtual void bfmeW20TN();
	virtual void bfmeW21TN();
	virtual void bfmeW22TN();
	virtual void bfmeW23TN();
	virtual void bfmeW24TN();
	virtual void bfmeW25TN();
	virtual void bfmeW26TN();
	virtual void bfmeW27TN();
	virtual void bfmeW28TN();
	virtual void bfmeW29TN();
	virtual void bfmeW30TN();
	virtual void bfmeW31TN();
	virtual void bfmeW32TN();
	virtual void bfmeW33TN();
	virtual void bfmeW34TN();
	virtual void bfmeW35TN();
	virtual void bfmeW36TN();
	virtual void bfmeW37TN();
	virtual void bfmeW38TN();
	virtual void bfmeW39TN();
	virtual void bfmeW40TN();
	virtual void bfmeW41TN();
	virtual void bfmeW42TN();
	virtual void bfmeW43TN();
	virtual void bfmeW44TN();
	virtual void bfmeW45TN();
	virtual void bfmeW46TN();
	virtual void bfmeW47TN();
	virtual void bfmeW48TN();
	virtual void bfmeW49TN();
	virtual void bfmeW50TN();
	virtual void bfmeW51TN();
	virtual void bfmeW52TN();
	virtual void bfmeW53TN();
	virtual void bfmeW54TN();
	virtual void bfmeW55TN();
	virtual void bfmeW56TN();
	virtual void bfmeW57TN();
	virtual void bfmeW58TN();
	virtual void bfmeW59TN();
	virtual void bfmeW60TN();
	virtual void bfmeW61TN();
	virtual void bfmeW62TN();
	virtual void bfmeW63TN();
	virtual void bfmeW64TN();
	virtual void bfmeW65TN();
	virtual void bfmeW66TN();
	virtual void bfmeW67TN();
	virtual void bfmeW68TN();
	virtual void bfmeW69TN();
	virtual void bfmeW70TN();
	virtual void bfmeW71TN();
	virtual void bfmeW72TN();
	virtual void bfmeW73TN();
	virtual void bfmeW74TN();
	virtual void bfmeW75TN();
	virtual void bfmeW76TN();
	virtual void bfmeW77TN();
	virtual void bfmeW78TN();
	virtual void bfmeW79TN();
	virtual void bfmeW80TN();
	virtual void bfmeW81TN();
	virtual void bfmeW82TN();
	virtual void bfmeW83TN();
	virtual void bfmeW84TN();
	virtual void bfmeW85TN();
	virtual void bfmeW86TN();
	virtual void bfmeW87TN();
	virtual void bfmeW88TN();
	virtual void bfmeW89TN();
	virtual void bfmeW90TN();
	virtual void bfmeW91TN();
	virtual void bfmeW92TN();
	virtual void bfmeW93TN();
	virtual void bfmeW94TN();
	virtual void bfmeW95TN();
	virtual void bfmeW96TN();
	virtual void bfmeW97TN();
	virtual void bfmeW98TN();
	virtual void bfmeNotifyTN(const Matrix3DTN *m);
};

class BfmeZTN
{
public:
	virtual void bfmeZ00TN();
	virtual void bfmeZ01TN();
	virtual void bfmeZ02TN();
	virtual void bfmeZ03TN();
	virtual void bfmeZ04TN();
	virtual void bfmeZ05TN();
	virtual void bfmeZ06TN();
	virtual void bfmeZ07TN();
	virtual void bfmeZ08TN();
	virtual void bfmeZ09TN();
	virtual void bfmeZ10TN();
	virtual void bfmeZ11TN();
	virtual void bfmeZ12TN();
	virtual void bfmeZ13TN();
	virtual void bfmeZ14TN();
	virtual void bfmeZ15TN();
	virtual void bfmeZ16TN();
	virtual void bfmeZ17TN();
	virtual void bfmeZ18TN();
	virtual void bfmeZ19TN();
	virtual void bfmeZ20TN();
	virtual void bfmeZ21TN();
	virtual void bfmeZ22TN();
	virtual void bfmeZ23TN();
	virtual void bfmeZ24TN();
	virtual void bfmeZ25TN();
	virtual BfmeWTN *bfmeGetWTN();
};

struct Rva00367E30Logic
{
	unsigned char m_bfmeHeadTN[0x3c];
	unsigned int m_bfmeFrameTN;
};

extern Rva00367E30Logic *TheBfmeGameLogic;

class BfmeThingTN
{
public:
	virtual void bfmeSlot00TN();
	virtual void bfmeSlot01TN();
	virtual void bfmeSlot02TN();
	virtual void bfmeSlot03TN();
	virtual void bfmeSlot04TN();
	virtual void bfmeSlot05TN();
	virtual void bfmeSlot06TN();
	virtual void bfmeSlot07TN();
	virtual void bfmeSlot08TN();
	virtual void bfmeSlot09TN();
	virtual BfmeXTN *bfmeGetXTN();

	void bfmeSetTransformTN(const Matrix3DTN *m);
	void bfmeSetMatrixTN(const Matrix3DTN *m);
	void bfmeMarkTN(unsigned int frame);

	unsigned char m_bfmeHeadTN[0x64];
	int *m_bfmeVbTN;
	unsigned char m_bfmePadTN[0x190];
	BfmeZTN *m_bfmeZTN;
};

void BfmeThingTN::bfmeSetTransformTN(const Matrix3DTN *m)
{
	bfmeSetMatrixTN(m);

	bfmeMarkTN(TheBfmeGameLogic->m_bfmeFrameTN);
	bfmeMarkTN(TheBfmeGameLogic->m_bfmeFrameTN);

	BfmeXTN *x = bfmeGetXTN();

	if (x != 0)
		x->bfmeFlagTN(1);

	bfmeSetMatrixTN(m);

	BfmeIfcTN *ifc = (BfmeIfcTN *)((char *)&m_bfmeVbTN + m_bfmeVbTN[1]);

	if (ifc->bfmeGetPartTN() != 0)
	{
		BfmeIfcTN *ifc2 = (BfmeIfcTN *)((char *)&m_bfmeVbTN + m_bfmeVbTN[1]);

		ifc2->bfmeGetPartTN()->friend_updateCellsTouched();
	}

	BfmeZTN *z = m_bfmeZTN;

	if (z != 0)
	{
		BfmeWTN *w = z->bfmeGetWTN();

		if (w != 0)
			w->bfmeNotifyTN(m);
	}
}
