// cl: /DNDEBUG /MD /EHsc
// readable body of ??0TerrainLogic@@QAE@XZ: Code/GameEngine/Source/GameLogic/Map/TerrainLogic.cpp
// Open-BFME5: TerrainLogic::TerrainLogic, retail 0x006BE070 (46 bytes).
//
// Local ABI-slice replica.  sizeof(TerrainLogic) is 0x1904 and the class has
// TWO vptrs (this+0 and this+4), both re-written by this constructor after the
// base constructor ??0TerrainLogicBase@@QAE@XZ returns; the base itself (body
// 0x001ADB80, entered through the incremental-link thunk 0x0004629F this body
// encodes) writes 0x01073744 at +0, calls SubsystemInterface's constructor at
// 0x009A1A30 with ecx = this+4, then re-writes both vptrs and zeroes +0x18
// through +0x28 -- so the base subobject reaches at least 0x2C and +0x0C is a
// BASE member this constructor assigns, not a member of TerrainLogic.

class TerrainLogicBaseFirst { public: virtual ~TerrainLogicBaseFirst(); };
class TerrainLogicBaseSecond { public: virtual ~TerrainLogicBaseSecond(); };

class TerrainLogicBase : public TerrainLogicBaseFirst, public TerrainLogicBaseSecond
{
public:
	TerrainLogicBase();
	virtual ~TerrainLogicBase();

protected:
	char	_bfme_pad_08[4];		// this+0x08
	int	m_slot0c;				// this+0x0c
	char	_bfme_pad_10[0x18ec];// this+0x10 .. 0x18fb
	int	m_slot18fc;				// this+0x18fc
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class TerrainLogic : public TerrainLogicBase
{
public:
	TerrainLogic();
	virtual ~TerrainLogic();

private:
	float	m_slot1900;			// this+0x1900
};

// ??0TerrainLogic@@QAE@XZ
TerrainLogic::TerrainLogic() :
	m_slot1900(1.0f)
{
	m_slot18fc = 0;
	m_slot0c = 0;
}
