// ?bfmeSetState1285@BfmeNode1285@@QAEXH@Z
// partial score=0.8 date=2026-09-11
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
//
// 126 bytes against retail 127, with three instructions left in the loop body.
// Retail holds the descriptor in ecx and the records pointer in edx, then builds
// the record pointer into a fresh eax with lea eax,[edx+ebp]. MSVC loads the
// descriptor into edx and the records pointer into eax, then consumes that
// register with add eax,ebp, which saves the byte that makes this 126.
//
// The first _ReadWriteBarrier is what restores retail reload of m_descriptor at
// +0x32; without it MSVC serves the loop-top read from the register the loop
// guard left in eax. A volatile-qualified read of m_descriptor does the same.
// The second barrier is what produces retail test dword ptr [eax],ecx; without
// it MSVC folds the record pointer into the mask load and spends a register on
// the loaded mask.
//
// Ruled out for the lea: inlining the records load into the record expression,
// reading m_state before the records pointer, offset-on-the-left pointer
// arithmetic, a function-scope record local, hoisting the two field addresses
// out of the if, a ternary or two-branch clamp, and /O1, which emits 115 bytes.

extern "C" void _ReadWriteBarrier( void );
#pragma intrinsic( _ReadWriteBarrier )

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

	BfmeSubmitter1283 *submitter = (BfmeSubmitter1283 *)&info->m_slot;
	int offset;
	info->m_state = state;
	info->m_slot.bfmeReset1285( 0 );

	int index = 0;
	if ( info->m_descriptor->m_count > 0 )
	{
		offset = 0;
		do
		{
			_ReadWriteBarrier();
			BfmeStateRecord1285 *records = info->m_descriptor->m_records;
			int currentState = info->m_state;
			BfmeStateRecord1285 *record = (BfmeStateRecord1285 *)
				((char *)records + offset);
			_ReadWriteBarrier();
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
