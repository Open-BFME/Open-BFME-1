class BfmeSubEVM
{
public:
	void bfmeApplyEVM(int mode);
};

class BfmeObjEVM
{
public:
	virtual void bfmeSlot00EVM();
	virtual void bfmeSlot01EVM();
	virtual void bfmeSlot02EVM();
	virtual void bfmeSlot03EVM();
	virtual void bfmeSlot04EVM();
	virtual void bfmeSlot05EVM();
	virtual void bfmeSlot06EVM();
	virtual void bfmeSlot07EVM();
	virtual void bfmeSlot08EVM();
	virtual void bfmeSlot09EVM();
	virtual void bfmeSlot10EVM();
	virtual void bfmeSlot11EVM();
	virtual void bfmeSlot12EVM();
	virtual void bfmeSlot13EVM();
	virtual void bfmeSlot14EVM();
	virtual void bfmeSlot15EVM();
	virtual void bfmeSlot16EVM();
	virtual void bfmeSlot17EVM();
	virtual void bfmeSlot18EVM();
	virtual void bfmeSlot19EVM();
	virtual void bfmeSlot20EVM();
	virtual void bfmeSlot21EVM();
	virtual void bfmeSlot22EVM();
	virtual void bfmeSlot23EVM();
	virtual void bfmeSlot24EVM();
	virtual void bfmeSlot25EVM();
	virtual void bfmeSlot26EVM();
	virtual void bfmeSlot27EVM();
	virtual void bfmeSlot28EVM();
	virtual void bfmeSlot29EVM();
	virtual void bfmeSlot30EVM();
	virtual void bfmeSlot31EVM();
	virtual void bfmeSlot32EVM();
	virtual void bfmeSlot33EVM();
	virtual void bfmeSlot34EVM();
	virtual void bfmeSlot35EVM();
	virtual void bfmeSlot36EVM();
	virtual void bfmeSlot37EVM();
	virtual void bfmeSlot38EVM();
	virtual void bfmeSlot39EVM();
	virtual void bfmeSlot40EVM();
	virtual void bfmeSlot41EVM();
	virtual void bfmeSlot42EVM();
	virtual void bfmeSlot43EVM();
	virtual void bfmeSlot44EVM();
	virtual void bfmeSlot45EVM();
	virtual void bfmeSlot46EVM();
	virtual void bfmeSlot47EVM();
	virtual void bfmeSlot48EVM();
	virtual void bfmeSlot49EVM();
	virtual void bfmeSlot50EVM();
	virtual void bfmeSlot51EVM();
	virtual void bfmeSlot52EVM();
	virtual void bfmeSlot53EVM();
	virtual void bfmeSlot54EVM();
	virtual void bfmeSlot55EVM();
	virtual void bfmeSlot56EVM();
	virtual void bfmeSlot57EVM();
	virtual void bfmeSlot58EVM();
	virtual void bfmeSlot59EVM();
	virtual void bfmeSlot60EVM();
	virtual void bfmeSlot61EVM();
	virtual void bfmeSlot62EVM();
	virtual void bfmeSlot63EVM();
	virtual void bfmeSlot64EVM();
	virtual void bfmeSlot65EVM();
	virtual void bfmeSlot66EVM();
	virtual void bfmeSlot67EVM();
	virtual void bfmeSlot68EVM();
	virtual void bfmeSlot69EVM();
	virtual void bfmeSlot70EVM();
	virtual void bfmeSlot71EVM();
	virtual void bfmeSlot72EVM();
	virtual void bfmeSlot73EVM();
	virtual void bfmeSlot74EVM();
	virtual void bfmeSlot75EVM();
	virtual void bfmeSlot76EVM();
	virtual void bfmeSlot77EVM();
	virtual void bfmeSlot78EVM();
	virtual void bfmeSlot79EVM();
	virtual void bfmeSlot80EVM();
	virtual void bfmeSlot81EVM();
	virtual void bfmeSlot82EVM();
	virtual void bfmeSlot83EVM();
	virtual void bfmeSlot84EVM();
	virtual void bfmeSlot85EVM();
	virtual void bfmeSlot86EVM();
	virtual void bfmeSlot87EVM();
	virtual void bfmeSlot88EVM();
	virtual void bfmeSlot89EVM();
	virtual void bfmeSlot90EVM();
	virtual void bfmeSlot91EVM();
	virtual void bfmeSlot92EVM();
	virtual void bfmeSlot93EVM();
	virtual void bfmeSlot94EVM();
	virtual void bfmeSlot95EVM();
	virtual char bfmeCheckAEVM();
	virtual void bfmeSlot97EVM();
	virtual void bfmeSlot98EVM();
	virtual char bfmeCheckBEVM();

	unsigned char m_bfmeHeadEVM[0x1c];
	BfmeSubEVM m_bfmeSubEVM;
};

class BfmeArgEVM
{
public:
	unsigned char m_bfmeHeadEVM[0x204];
	BfmeObjEVM *m_bfmeObjEVM;
};

char __stdcall bfmeTryEVM(BfmeArgEVM *arg, int unused)
{
	BfmeObjEVM *obj = arg->m_bfmeObjEVM;

	if (obj == 0)
		return 0;

	if (obj->bfmeCheckBEVM())
	{
		obj->m_bfmeSubEVM.bfmeApplyEVM(2);
		return 1;
	}

	return obj->bfmeCheckAEVM() != 0;
}
