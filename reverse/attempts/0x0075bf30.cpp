// ?bfmeApplyZD@BfmeOwnerZD@@QAEXPAX@Z (identity unknown)
// partial score=0.97 date=2026-09-07
// 73/73, identical instruction set, THREE transposed instructions:
//   retail  mov ecx,[edi+0x44] / mov edx,[esi] / mov [esp+0xc],eax
//   MSVC    mov edx,[esi] / mov [esp+0xc],eax / mov ecx,[edi+0x44]
// i.e. retail reads the second argument before the receiver's vftable and puts
// the local's initialising store last; MSVC does the vftable first and the store
// second. Naming the second argument in a local declared after `value` does not
// move it. Pure scheduling of three loads.
// Everything else is settled: `&value` is a local that MSVC gives the DEAD `arg`
// parameter home slot ([[param-slot-is-the-buffer]],
// [[parameter-home-slot-reuse]]), the call is virtual slot 30 on `this`, and the
// two early returns share the shrink-wrapped pop edi / pop esi tails.
class ObjectAttemptDamageFlagHook
{
public:
	int value();

	unsigned char m_bfmeHeadZD[0x38];
	unsigned char m_bfmeAtZD[0xc];
	int m_bfme44ZD;
};

class BfmeHolderZD
{
public:
	unsigned char m_bfmeHeadZD[0xfc];
	ObjectAttemptDamageFlagHook *m_bfmeItemZD;
};

class RadiusDecalTemplate
{
public:
	void operator=(const RadiusDecalTemplate &other);
};

class BfmeSenderZD
{
public:
	virtual void bfmeV00ZD();
	virtual void bfmeV01ZD();
	virtual void bfmeV02ZD();
	virtual void bfmeV03ZD();
	virtual void bfmeV04ZD();
	virtual void bfmeV05ZD();
	virtual void bfmeV06ZD();
	virtual void bfmeV07ZD();
	virtual void bfmeV08ZD();
	virtual void bfmeV09ZD();
	virtual void bfmeV10ZD();
	virtual void bfmeV11ZD();
	virtual void bfmeV12ZD();
	virtual void bfmeV13ZD();
	virtual void bfmeV14ZD();
	virtual void bfmeV15ZD();
	virtual void bfmeV16ZD();
	virtual void bfmeV17ZD();
	virtual void bfmeV18ZD();
	virtual void bfmeV19ZD();
	virtual void bfmeV20ZD();
	virtual void bfmeV21ZD();
	virtual void bfmeV22ZD();
	virtual void bfmeV23ZD();
	virtual void bfmeV24ZD();
	virtual void bfmeV25ZD();
	virtual void bfmeV26ZD();
	virtual void bfmeV27ZD();
	virtual void bfmeV28ZD();
	virtual void bfmeV29ZD();
	virtual void bfmeSendZD(void *at, int value, int *out);
	};

	class BfmeOwnerZD : public BfmeSenderZD
	{
	public:
	void bfmeApplyZD(void *arg);

	unsigned char m_bfmeHeadZD[4];
	BfmeHolderZD *m_bfmeHolderZD;
	unsigned char m_bfmeMidZD[0x1c0];
	RadiusDecalTemplate m_bfmeSubZD;
};

void BfmeOwnerZD::bfmeApplyZD(void *arg)
{
	if (arg == 0)
		return;

	m_bfmeSubZD = *(RadiusDecalTemplate *)arg;

	ObjectAttemptDamageFlagHook *item = m_bfmeHolderZD->m_bfmeItemZD;

	if (item == 0)
		return;

	int value = item->value();
	int itemValue;
	itemValue = item->m_bfme44ZD;

	bfmeSendZD(item->m_bfmeAtZD, itemValue, &value);
}
