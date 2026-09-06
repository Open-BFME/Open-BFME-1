// ?update@Rva001A2BE0Base2@@UAEXXZ
// partial score=0.9 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc /O2 /Ob0
//
// Open-BFME: retail 0x001A2BE0 size 285. Near-twin of the already-landed
// TerrainLogic::update (marked present-unmatched in
// Code/.../TerrainLogic.cpp) with BFME's true layout: TerrainLogic's own
// data is 0x10 bytes larger before the water-update array/count and 8
// bytes larger before m_bridgeDamageStatesChanged, Snapshot (the vtable
// TerrainLogic's own new virtuals extend, reached via the this-4 thunk)
// carries 7 more slots before setWaterHeight (0x70 not 0x54), and
// LOGICFRAMES_PER_SECOND is BFME's 30, not ZH's 5. This is a fresh
// address-derived twin per docs/matching.md rather than an edit to the
// shared TerrainLogic/Snapshot headers or the LOGICFRAMES_PER_SECOND
// macro (both used project-wide).

extern float g_bfmeZeroCY; // retail 0x01075350 (0.0f)

class Rva001A2BE0GameLogic
{
public:
	unsigned char m_pad[0x3c];
	unsigned int m_frame; // +0x3c, getFrame() inlined to a plain field read
};

extern Rva001A2BE0GameLogic *g_rva001A2BE0GameLogic; // retail 0x012F0898

struct Rva001A2BE0WaterEntry
{
	void *m_waterTable;
	float m_changePerFrame;
	float m_targetHeight;
	float m_damageAmount;
	float m_currentHeight;
};

class Rva001A2BE0Base1 // stand-in for Snapshot: TerrainLogic's own new
                       // virtuals (setWaterHeight) extend this vtable
{
public:
	virtual void bfmeSnapSlot_0();
	virtual void bfmeSnapSlot_1();
	virtual void bfmeSnapSlot_2();
	virtual void bfmeSnapSlot_3();
	virtual void bfmeSnapSlot_4();
	virtual void bfmeSnapSlot_5();
	virtual void bfmeSnapSlot_6();
	virtual void bfmeSnapSlot_7();
	virtual void bfmeSnapSlot_8();
	virtual void bfmeSnapSlot_9();
	virtual void bfmeSnapSlot_10();
	virtual void bfmeSnapSlot_11();
	virtual void bfmeSnapSlot_12();
	virtual void bfmeSnapSlot_13();
	virtual void bfmeSnapSlot_14();
	virtual void bfmeSnapSlot_15();
	virtual void bfmeSnapSlot_16();
	virtual void bfmeSnapSlot_17();
	virtual void bfmeSnapSlot_18();
	virtual void bfmeSnapSlot_19();
	virtual void bfmeSnapSlot_20();
	virtual void bfmeSnapSlot_21();
	virtual void bfmeSnapSlot_22();
	virtual void bfmeSnapSlot_23();
	virtual void bfmeSnapSlot_24();
	virtual void bfmeSnapSlot_25();
	virtual void bfmeSnapSlot_26();
	virtual void bfmeSnapSlot_27();
	virtual void setWaterHeight(void *water, float height, float damage, int flag);
};

class Rva001A2BE0Base2 // stand-in for SubsystemInterface: update() lives here
{
public:
	virtual void update();
};

class Rva001A2BE0Host : public Rva001A2BE0Base1, public Rva001A2BE0Base2
{
};

#define RVA001A2BE0_FLAG(edi) (*(unsigned char *)((edi) + 0x34))
#define RVA001A2BE0_COUNT(edi) (*(int *)((edi) + 0x548))
#define RVA001A2BE0_ENTRY(edi, i) (*(Rva001A2BE0WaterEntry *)((edi) + 0x48 + (i) * sizeof(Rva001A2BE0WaterEntry)))

void Rva001A2BE0Base2::update()
{
	char *edi = (char *)this;

	RVA001A2BE0_FLAG(edi) = 0;

	if (RVA001A2BE0_COUNT(edi))
	{
		const void *water;
		float changePerFrame, damageAmount, targetHeight, currentHeight;
		bool finalTransition, doDamageThisFrame = (g_rva001A2BE0GameLogic->m_frame % 30) == 0;

		for (int i = RVA001A2BE0_COUNT(edi) - 1; i >= 0; --i)
		{
			Rva001A2BE0WaterEntry *entry = &RVA001A2BE0_ENTRY(edi, i);
			water = entry->m_waterTable;
			changePerFrame = entry->m_changePerFrame;
			targetHeight = entry->m_targetHeight;
			damageAmount = entry->m_damageAmount;
			currentHeight = entry->m_currentHeight;

			finalTransition = false;
			if (changePerFrame > g_bfmeZeroCY)
			{
				if (currentHeight + changePerFrame >= targetHeight)
					finalTransition = true;
			}
			else
			{
				if (currentHeight + changePerFrame <= targetHeight)
					finalTransition = true;
			}

			if (finalTransition)
			{
				((Rva001A2BE0Base1 *)(edi - 4))->setWaterHeight(const_cast<void *>(water), targetHeight, damageAmount, 1);

				for (int j = i; j < RVA001A2BE0_COUNT(edi); j++)
					RVA001A2BE0_ENTRY(edi, i) = RVA001A2BE0_ENTRY(edi, j);
				RVA001A2BE0_COUNT(edi) -= 1;
			}
			else
			{
				if (!doDamageThisFrame)
					damageAmount = 0.0f;

				currentHeight += changePerFrame;
				entry->m_currentHeight = currentHeight;

				((Rva001A2BE0Base1 *)(edi - 4))->setWaterHeight(const_cast<void *>(water), currentHeight, damageAmount, 0);
			}
		}
	}
}

