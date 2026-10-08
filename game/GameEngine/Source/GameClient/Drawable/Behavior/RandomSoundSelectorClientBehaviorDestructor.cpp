// RandomSoundSelectorClientBehavior complete destructor at retail 0x00607BD0
// (11 bytes). ??_GRandomSoundSelectorClientBehavior (0x00607BA0) calls it
// through ILT 0x0004374D, pinned ??1RandomSoundSelectorClientBehavior@@UAE@XZ
// (ilt_oracle: UAE exact at 0x00607BD0). Its own body is empty; the inline
// base destructor re-seats the shared client-module vftable VA 0x0108ACB8
// and tail-jumps through ILT 0x0002B8C8. That vftable is named by its
// decorated symbol (dir32 records it as ??_7ASCB_MiddleBase@@6B@, emitted by
// AnimationSoundClientBehaviorDestructors.cpp); novtable keeps this TU from
// storing or emitting a vftable of its own.

extern "C" const void *__identifier("??_7ASCB_MiddleBase@@6B@")[];

class Rva0002B8C8TailBase
{
public:
	virtual ~Rva0002B8C8TailBase();
};

class __declspec(novtable) RandomSoundSelectorClientBehavior : public Rva0002B8C8TailBase
{
public:
	virtual ~RandomSoundSelectorClientBehavior();
};

RandomSoundSelectorClientBehavior::~RandomSoundSelectorClientBehavior()
{
	*(const void *volatile *)this = (const void *)__identifier("??_7ASCB_MiddleBase@@6B@");
}
