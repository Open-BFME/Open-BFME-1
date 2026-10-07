// cl: /DNDEBUG /MD /EHsc
//
// EvaEventFXNugget complete destructor at retail 0x00428970
// (5 bytes). ??_GEvaEventFXNugget (0x00428940, its own TU) calls it
// through ILT 0x000231C3; the body is one tail jump through ILT 0x000033F0
// into ??1FXNugget@@UAE@XZ (0x00427390), with no vptr re-seat
// of its own. novtable reproduces the missing re-seat; it lives apart from
// the ??_G TU because a novtable class there would no longer emit its
// vftable and ??_G.

class FXNugget
{
public:
	virtual ~FXNugget();
};

class __declspec(novtable) EvaEventFXNugget : public FXNugget
{
public:
	virtual ~EvaEventFXNugget();
};

EvaEventFXNugget::~EvaEventFXNugget()
{
}
