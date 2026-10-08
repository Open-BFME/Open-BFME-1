// cl: /DNDEBUG /MD /EHsc
//
// ExperienceLevelCreate complete destructor at retail 0x0024F720
// (5 bytes). ??_GExperienceLevelCreate (0x0024F6F0, its own TU) calls it
// through ILT 0x00008058; the body is one tail jump through ILT 0x0001C657
// into ??1CreateModule@@MAE@XZ (0x0024F400), with no vptr re-seat of its
// own. novtable reproduces the missing re-seat; it lives apart from the
// ??_G TU because a novtable class there would no longer emit its vftable.

class CreateModule
{
protected:
	virtual ~CreateModule();
};

class __declspec(novtable) ExperienceLevelCreate : public CreateModule
{
public:
	virtual ~ExperienceLevelCreate();
};

ExperienceLevelCreate::~ExperienceLevelCreate()
{
}
