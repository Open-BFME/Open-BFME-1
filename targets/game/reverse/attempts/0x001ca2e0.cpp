// ?d_001ca2e0@@YAXXZ
// partial score=0.98 date=2026-09-07
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc-

// The Object activation body at retail 0x001CA2E0. The constructor at
// 0x001D29A0 and Rva002491F0::apply at 0x002491F0 both call this body through
// the retail thunk at 0x0002AE5F. The +0x368 byte records that activation has
// registered the object with the shroud, partition, window, or owner system.

typedef unsigned int UnsignedInt;

class PartitionData
{
public:
	void makeDirty();
};

class ThingTemplate
{
public:
	void *m_vtable;
	ThingTemplate *m_nextOverride;
	unsigned char m_pad08[0xc8 - 0x08];
	UnsignedInt m_flagsC8;
	UnsignedInt m_flagsCC;
	UnsignedInt m_flagsD0;
	UnsignedInt m_flagsD4;

	ThingTemplate *getFinalOverride();
};

class BfmeShroudManager
{
public:
	void rva008F73A0(void *record);
};

class BfmePartitionManager
{
public:
	void rva009F2660(void *record);
};

class BfmeWindowManager
{
public:
	void rva009A2590(void *record);
};

class BfmeAIData
{
private:
	unsigned char m_pad00[0xb5];

public:
	unsigned char m_targetDispatchEnabled;
};

class AI
{
private:
	unsigned char m_pad00[0x14];

public:
	BfmeAIData *m_data;
};

class BfmeRva491F0Object;

class BfmeOwnerBR
{
public:
	void rva000143D0(BfmeRva491F0Object *object);
};

extern BfmeShroudManager *TheShroudManager;
extern BfmePartitionManager *ThePartitionManager;
extern AI *TheAI;
extern bool g_aiTargetDispatchSuppressed;
extern BfmeWindowManager *g_bfmeWindowManager;
extern "C" BfmeOwnerBR *g_bfmeOwnerBR;

class BfmeRva491F0Object
{
public:
	void activate();
	ThingTemplate *getTemplate() const
	{
		ThingTemplate *thingTemplate = m_template;
		if (thingTemplate == 0)
			return 0;
		if (thingTemplate->m_nextOverride != 0)
			thingTemplate = thingTemplate->m_nextOverride->getFinalOverride();
		return thingTemplate;
	}

private:
	void *m_vtable;
	ThingTemplate *m_template;
	unsigned char m_pad08[0x64 - 0x08];
	unsigned int m_shroudRecord[2];
	unsigned int m_partitionRecord;
	unsigned int m_windowRecord;
	unsigned char m_pad74[0x368 - 0x74];
	unsigned char m_active;
	unsigned char m_pad369[0x3b0 - 0x369];
	PartitionData *m_partitionData;
};

void BfmeRva491F0Object::activate()
{
	ThingTemplate *thingTemplate = getTemplate();
	if ((thingTemplate->m_flagsD0 & 0x01000000) != 0)
	{
		if ((getTemplate()->m_flagsD4 & 0x01000000) == 0)
			return;

		if (TheShroudManager != 0 && m_partitionData == 0)
		{
			TheShroudManager->rva008F73A0(&m_shroudRecord);
			m_active = 1;
		}

		if (m_partitionData != 0)
			m_partitionData->makeDirty();
		return;
	}

	if ((getTemplate()->m_flagsC8 & 0x02000000) == 0)
	{
		if (TheShroudManager != 0 && m_partitionData == 0)
		{
			TheShroudManager->rva008F73A0(&m_shroudRecord);
		}

		if (m_partitionData != 0)
			m_partitionData->makeDirty();

		if (ThePartitionManager != 0)
			ThePartitionManager->rva009F2660(&m_partitionRecord);
	}

	UnsignedInt flags = getTemplate()->m_flagsC8;
	bool dispatchTargets = ((flags >> 30) & 1) == 0;
	if (g_aiTargetDispatchSuppressed)
		dispatchTargets = false;

	if ((getTemplate()->m_flagsD4 & 0x1000) == 0 ||
		TheAI->m_data->m_targetDispatchEnabled != 0)
	{
		if (dispatchTargets && g_bfmeWindowManager != 0)
		{
			void *windowRecord = 0;
			if (this != 0)
				windowRecord = (void *)&m_windowRecord;
			g_bfmeWindowManager->rva009A2590(windowRecord);
		}
	}

	if (g_bfmeOwnerBR != 0)
	{
		g_bfmeOwnerBR->rva000143D0(this);
		m_active = 1;
	}
}
