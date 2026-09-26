// cl: /DNDEBUG /MD /EHsc

class BfmeFlagSink
{
public:
	virtual void v00(); virtual void v01();
	virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05();
	virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09();
	virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13();
	virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17();
	virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21();
	virtual void v22();
	virtual void refreshFlag();
};

struct BfmeFlagData
{
	unsigned char m_pad00[0x270];
	bool m_invertedFlag;
};

class BfmeStateFlagOwner
{
public:
	virtual void v00() = 0; virtual void v01() = 0;
	virtual void v02() = 0; virtual void v03() = 0;
	virtual void v04() = 0; virtual void v05() = 0;
	virtual void v06() = 0; virtual void v07() = 0;
	virtual void v08() = 0; virtual void v09() = 0;
	virtual void v10() = 0; virtual void v11() = 0;
	virtual void v12() = 0; virtual void v13() = 0;
	virtual void v14() = 0; virtual void v15() = 0;
	virtual void v16() = 0; virtual void v17() = 0;
	virtual void v18() = 0; virtual void v19() = 0;
	virtual void v20() = 0; virtual void v21() = 0;
	virtual void v22() = 0; virtual void v23() = 0;
	virtual void v24() = 0; virtual void v25() = 0;
	virtual void v26() = 0; virtual void v27() = 0;
	virtual void v28() = 0; virtual void v29() = 0;
	virtual void updateBase(int value) = 0;

	void updateCachedState();
	void bfmeRefreshStateFlag();

private:
	BfmeFlagData *m_data;
	unsigned char m_pad08[0xdc];
	BfmeFlagSink m_sink;
	unsigned char m_padE8[0x139];
	bool m_cachedFlag;
};

void BfmeStateFlagOwner::bfmeRefreshStateFlag()
{
	updateBase(0);
	updateCachedState();
	if (m_cachedFlag != !m_data->m_invertedFlag)
		m_sink.refreshFlag();
}
