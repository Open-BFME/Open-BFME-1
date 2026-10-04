// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /Ob2

// Retail 0x000F9940 (102 bytes).  This is a no-argument member of the same
// 0x60-byte record vector used by the matched 0x000F94B0 accessor and the
// 0x000F9670 lookup.  Its first call and every loop call load the same global
// at 0x012F1028.  The call targets are bodies at 0x003C3AC0 and 0x003C3B50:
// both receive that exact global object.  The former passes its +0x68/+0x6C
// vector pair to the range helper; the latter uses +0x68/+0x6C/+0x70 as one
// three-pointer vector and appends the supplied 0x60-byte record.  The retail
// method names are unavailable, so the single proven owner uses neutral RVA
// method names rather than unrelated receiver classes or semantic guesses.

struct P6Elem003C3B50
{
	unsigned char m_opaque[0x60];
};

class BfmeRecordVector
{
public:
	unsigned int size() const
	{
		return (unsigned int)(m_end - m_begin);
	}

	P6Elem003C3B50 &operator[](unsigned int index)
	{
		return m_begin[index];
	}

private:
	P6Elem003C3B50 *m_begin;
	P6Elem003C3B50 *m_end;
	P6Elem003C3B50 *m_storageEnd;
};

// Retail 0x012F1028 is EA's `LivingWorldLogic *TheLivingWorldLogic`.  The two
// callees below are the bodies the ledger records at 0x003C3AC0 and 0x003C3B50
// -- `Rva003C3AC0::forward` (game/GameEngine/Source/Common/
// S1SubObjectPairCalls.cpp) and `Gen003C3B50::bfmeAppend` (game/GameEngine/
// Source/Common/P6MemberVectorPushBack.cpp) -- and both take that exact object
// as their receiver, so each call is made through a local view class carrying
// the defining name.  Both views hold the same 0x68 opaque head followed by
// the record vector those bodies walk.
class Rva003C3AC0
{
public:
	void forward();

private:
	unsigned char m_opaque00[0x68];
	BfmeRecordVector m_records;
};

class Gen003C3B50
{
public:
	void bfmeAppend(const P6Elem003C3B50 *value);

private:
	unsigned char m_opaque00[0x68];
	BfmeRecordVector m_records;
};

// Retail 0x012F1028 is EA's `LivingWorldLogic *TheLivingWorldLogic`, defined
// once in game/GameEngine/Source/GameLogic/LivingWorld/LivingWorldLogic.cpp.
// The two view classes above are this TU's own view of that address, so the
// two reads cast at the use.
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

class BfmeVecVLH
{
public:
	void rva000F9940();

private:
	int m_opaque00;
	BfmeRecordVector m_records;
};

// ?rva000F9940@BfmeVecVLH@@QAEXXZ
void BfmeVecVLH::rva000F9940()
{
	((Rva003C3AC0 *)TheLivingWorldLogic)->forward();

	for (unsigned int index = 0; index < m_records.size(); ++index)
	{
		((Gen003C3B50 *)TheLivingWorldLogic)->bfmeAppend(&m_records[index]);
	}
}
