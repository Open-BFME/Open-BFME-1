struct W3dBoxStruct
{
	int m_bfmeHeadEBD;
	unsigned char m_bfmeFlagsEBD;
	unsigned char m_bfmeTailEBD[3];
};

class OBBoxRenderObjClass
{
public:
	OBBoxRenderObjClass(const W3dBoxStruct &box);

	unsigned char m_bfmeBodyEBD[0x14c];
};

class AABoxRenderObjClass
{
public:
	AABoxRenderObjClass(const W3dBoxStruct &box);

	unsigned char m_bfmeBodyEBD[0x128];
};

class BfmeHostEBD
{
public:
	virtual void bfmeSlot00EBD();
	virtual void bfmeSlot01EBD();
	virtual void bfmeSlot02EBD();
	virtual void bfmeSlot03EBD();
	virtual void bfmeSlot04EBD();
	virtual void bfmeSlot05EBD();
	virtual void bfmeSlot06EBD();
	virtual void bfmeSlot07EBD();
	virtual void bfmeSlot08EBD();
	virtual void bfmeSlot09EBD();
	virtual char bfmeReadyEBD();
	virtual void bfmePrepareEBD();

	void *bfmeMakeBoxEBD();

	unsigned char m_bfmeHeadEBD[0x10];
	W3dBoxStruct *m_bfmeBoxEBD;
};

void *BfmeHostEBD::bfmeMakeBoxEBD()
{
	if (!bfmeReadyEBD())
		bfmePrepareEBD();

	W3dBoxStruct *box = m_bfmeBoxEBD;

	if (box == 0)
		return 0;

	if ((box->m_bfmeFlagsEBD & 1) != 0)
		return new OBBoxRenderObjClass(*m_bfmeBoxEBD);

	return new AABoxRenderObjClass(*m_bfmeBoxEBD);
}
