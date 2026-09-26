// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the helper attach at retail 0x00755E70, 124 bytes.  A
// function-local static helper is published through a global and then handed
// this, after which the object finishes up.

class Gen_00755E70;

class BfmeHelperYS
{
public:
	BfmeHelperYS(void);

	~BfmeHelperYS(void);

	void bfmeAttachYS(Gen_00755E70 *owner);

private:
	char m_bfmeRaw[0x30];
};

extern BfmeHelperYS *g_bfmeCurrentYS;				// retail 0x01304B64

class Gen_00755E70
{
public:
	void bfmeBeginYS(void);

	void bfmeFinishYS(void);
};

// ?bfmeBeginYS@Gen_00755E70@@QAEXXZ
void Gen_00755E70::bfmeBeginYS(void)
{
	static BfmeHelperYS s_bfmeHelperYS;

	BfmeHelperYS *helper = &s_bfmeHelperYS;

	g_bfmeCurrentYS = helper;

	helper->bfmeAttachYS(this);

	bfmeFinishYS();
}
