// ?bfmeSetState1285@BfmeNode1285@@QAEXH@Z
// partial score=0.4 date=2026-09-02
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class BfmeStateSlot1285
{
public:
	void bfmeReset1285( int value );
};

struct BfmeStateRecord1285
{
	int m_mask;
	int m_value;
	int m_gap08;
	float m_weight;
	char m_gap10[ 0x24 - 0x10 ];
	float m_tail;
	char m_gap28[ 0x44 - 0x28 ];
};

struct BfmeStateDescriptor1285
{
	char m_gap00[ 0x2c ];
	int m_count;
	BfmeStateRecord1285 *m_records;
};

struct BfmeNodeState1285
{
	char m_gap00[ 0x0c ];
	BfmeStateDescriptor1285 *m_descriptor;
	char m_gap10[ 0x1c - 0x10 ];
	int m_state;
	BfmeStateSlot1285 m_slot;
};

class BfmeSubmitter1283
{
public:
	void bfmeSubmit1283( int a0, int a1, int a2, int a3, int a4, int a5,
		int a6, float *weight, int a8, int a9, int a10, int a11 );
};

class BfmeNode1285
{
public:
	void bfmeSetState1285( int state );

private:
	char m_gap00[ 0x50 ];
	BfmeNodeState1285 *m_info;
};

void BfmeNode1285::bfmeSetState1285( int state )
{
	BfmeNodeState1285 *info = m_info;
	if ( state == info->m_state )
		return;

	int offset;
	BfmeSubmitter1283 *submitter = (BfmeSubmitter1283 *)&info->m_slot;
	info->m_state = state;
	info->m_slot.bfmeReset1285( 0 );

	int index = 0;
	if ( info->m_descriptor->m_count > 0 )
	{
		offset = 0;
		do
		{
			BfmeStateRecord1285 *records = info->m_descriptor->m_records;
			int currentState = info->m_state;
			BfmeStateRecord1285 *record = (BfmeStateRecord1285 *)
				((char *)records + offset);
			if ( (record->m_mask & currentState) != 0 )
			{
				submitter->bfmeSubmit1283(
					0, index, record->m_value, 0, (int)this, 0,
					-1, &record->m_tail, (int)&record->m_weight, 0, 0, 0 );
			}
			++index;
			offset += 0x44;
		} while ( index < info->m_descriptor->m_count );
	}
}
