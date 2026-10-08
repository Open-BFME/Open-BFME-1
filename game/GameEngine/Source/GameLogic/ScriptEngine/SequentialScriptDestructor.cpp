// SequentialScript complete destructor at retail 0x0033B2A0 (80 bytes).
// ??_GSequentialScript (0x0033B270) calls it through ILT 0x00033429, pinned
// ??1SequentialScript@@UAE@XZ (ilt_oracle: UAE exact at 0x0033B2A0). The body
// destroys two members through 0x00887940 (StringBase<char>::releaseBuffer)
// and ends with the inlined empty destructor of its offset-0 polymorphic base
// re-seating VA 0x01073744; its own vptr reset is not emitted (novtable). See
// game/GameEngine/Source/Common/R4VptrTailDestructors.cpp for the reading;
// the base and member types keep that file's address-derived names.

struct Gen01073744 { virtual ~Gen01073744() {} };

struct Gen00887940
{
	char m_body[ 4 ];
	Gen00887940();
	~Gen00887940();
};

class __declspec(novtable) SequentialScript : public Gen01073744
{
public:
	virtual ~SequentialScript();

private:
	char m_lead[ 8 ];
	Gen00887940 m_first;
	Gen00887940 m_second;
};

SequentialScript::~SequentialScript()
{
}
