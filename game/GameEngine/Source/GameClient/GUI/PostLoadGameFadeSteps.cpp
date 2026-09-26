// cl: /DNDEBUG
//
// 0x003C0610 (139B). Posts the two load-game fade steps onto the timed-op
// list at 0x012ED584: parchmentMapFadeLoadGame via ILT 0x004283DF, then
// soloMordorFadeLoadGame via ILT 0x004470E1. Same key 0x012ED588 both times.
// Wrapper/holder are the Rva003BE8F0 / Rva003C00B0 pair (vftable 0x010EDB7C),
// defined locally so `new Wrapper(slot)` inlines; poster is the ILT at
// 0x0000FC72 (body 0x0007BA90). Slot immediates are the ILTs, not the bodies.

struct LoadGameFadeSlot
{
	LoadGameFadeSlot(void *fn) : m_fn(fn) {}

	void *m_fn;
};

class LoadGameFadeWrapperHead
{
public:
	LoadGameFadeWrapperHead() throw() : m_refCount(0) {}
	virtual void loadGameFadeWrapperAnchor();

	unsigned int m_refCount;
};

class LoadGameFadeWrapper : public LoadGameFadeWrapperHead
{
public:
	__forceinline LoadGameFadeWrapper(const LoadGameFadeSlot &slot) throw()
		: m_slot(slot) {}

	LoadGameFadeSlot m_slot;
};

class LoadGameFadeHolder
{
public:
	__forceinline LoadGameFadeHolder(LoadGameFadeSlot binding) throw()
	{
		m_ptr = new LoadGameFadeWrapper(binding);
		if (m_ptr != 0)
			m_ptr->m_refCount++;
	}
	~LoadGameFadeHolder() {}

	LoadGameFadeWrapper *m_ptr;
};

void postTimedOp(LoadGameFadeHolder holder, void *key);

// ?postLoadGameFadeSteps@@YAXXZ
void postLoadGameFadeSteps()
{
	postTimedOp(
		LoadGameFadeSlot(reinterpret_cast<void *>(0x004283DF)),
		reinterpret_cast<void *>(0x012ED588));
	postTimedOp(
		LoadGameFadeSlot(reinterpret_cast<void *>(0x004470E1)),
		reinterpret_cast<void *>(0x012ED588));
}
