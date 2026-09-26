// Open-BFME5: clean C++ conversion of the two-stage child finalization.

class Rva0017AE40Child
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void finishFirstStage();
	virtual void slot18();
	virtual void slot1C();
	virtual void finishSecondStage(int mode);
};

class Rva0017AE40Owner
{
public:
	void finalizeChild();

private:
	void finishOwner();
	char m_pad00[0x6C];
	Rva0017AE40Child *m_child;
};

void Rva0017AE40Owner::finalizeChild()
{
	m_child->finishFirstStage();
	m_child->finishSecondStage(0);
	finishOwner();
}
