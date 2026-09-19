// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: HitReactionBehaviorModuleData dtor. dual Buffer SEH.

class Buffer
{
public:
	~Buffer();
private:
	unsigned char m_pad[4];
};

class HitReactionBehaviorModuleDataBase
{
public:
	virtual ~HitReactionBehaviorModuleDataBase() {}
private:
	unsigned char m_pad[0x14];
};

class __declspec(novtable) HitReactionBehaviorModuleData : public HitReactionBehaviorModuleDataBase
{
public:
	virtual ~HitReactionBehaviorModuleData();
private:
	Buffer m_a;
	Buffer m_b;
};

// ??1HitReactionBehaviorModuleData@@UAE@XZ
HitReactionBehaviorModuleData::~HitReactionBehaviorModuleData()
{
}
