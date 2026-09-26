// ?check@Rva00695E20LodGate@@QBE_NXZ
// cl: /DNDEBUG /MD /EHsc

// Retail 0x00695E20 checks this object's LOD selector against the active
// GameLODManager row.  The surrounding bytes prove the selector offset and
// the two-entry row range, but they do not prove a semantic method name.

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class GameLODManager
{
public:
	char m_padding0[0x174];
	bool m_rowFlags[2][8];
	char m_padding1[0x16cc - 0x184];

public:
	int m_activeRow;
};

extern GameLODManager *TheGameLODManager;

class Rva00695E20LodGate
{
public:
	bool check() const;

private:
	char m_padding0[0xb60];
	int m_lodSelector;
};

bool Rva00695E20LodGate::check() const
{
    if (m_lodSelector > 0 && m_lodSelector <= 5)
    {
        GameLODManager *lod = TheGameLODManager;
        if (!lod)
        {
            // Instruction-free barrier keeps the shared true return before
            // the row lookup, as in retail; moving it to the shared tail
            // lets VC7.1 reorder the branch targets.
            _ReadWriteBarrier();
            return true;
        }
        int row = lod->m_activeRow;
        if (row < 0 || row >= 2)
            return true;
        return lod->m_rowFlags[row][0];
    }
    return false;
}
