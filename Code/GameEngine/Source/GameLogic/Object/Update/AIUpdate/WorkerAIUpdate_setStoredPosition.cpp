// cl: /DNDEBUG /MD
// WorkerAIUpdate wrapper around BfmeThingCTA::bfmeGoCTA.  Same shape as
// SupplyTruckAIUpdate_setStoredPosition.cpp; stored Coord3D sits at +0x404.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

class BfmeThingCTA
{
public:
	void bfmeGoCTA(void *one, void *two);

private:
	unsigned char m_bfmeHead[8];
	void *m_bfmeSub;
	unsigned char m_bfmeGap[0x24];
	void *m_bfmeOut;
	unsigned char m_bfmeGap2[0x14];
	void *m_bfmeVal;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/WorkerAIUpdate.h
class WorkerAIUpdate : public BfmeThingCTA
{
public:
	void setStoredPosition(Coord3D *pos, int cmdSource);

private:
	unsigned char m_gap4c[0x3B8];
	Coord3D m_storedPosition;
	unsigned char m_hasStoredPosition;
};

void WorkerAIUpdate::setStoredPosition(Coord3D *pos, int cmdSource)
{
	bfmeGoCTA(pos, (void *)cmdSource);
	if (!cmdSource && pos)
	{
		m_storedPosition = *pos;
		m_hasStoredPosition = 1;
	}
}
