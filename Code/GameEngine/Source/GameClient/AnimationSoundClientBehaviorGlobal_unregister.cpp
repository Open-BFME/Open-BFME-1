// cl: /DNDEBUG /MD /EHsc

// AnimationSoundClientBehaviorGlobal::unregister, retail 0x00409140. No calls,
// so the whole body is the shape of the registry: four list ends at +0x08,
// +0x0C, +0x10 and +0x14 - two head/tail pairs, since +0x08 and +0x10 are
// replaced from the node's forward link and +0x0C and +0x14 from its backward
// one - and a count at +0x18. The node keeps those links at +0x14 and +0x18.
//
// Each end is compared and replaced unconditionally rather than only when the
// node is on that list: retail runs all four tests every time.

class AnimationSoundClientBehavior
{
public:
	unsigned char m_unmodelled_00[ 0x14 ];
	AnimationSoundClientBehavior *m_next;		// +0x14
	AnimationSoundClientBehavior *m_prev;		// +0x18
};

class AnimationSoundClientBehaviorGlobal
{
public:
	void unregister( AnimationSoundClientBehavior *behavior );

private:
	unsigned char m_unmodelled_00[ 8 ];
	AnimationSoundClientBehavior *m_firstHead;	// +0x08
	AnimationSoundClientBehavior *m_firstTail;	// +0x0C
	AnimationSoundClientBehavior *m_secondHead;	// +0x10
	AnimationSoundClientBehavior *m_secondTail;	// +0x14
	int m_count;								// +0x18
};

// ?unregister@AnimationSoundClientBehaviorGlobal@@QAEXPAVAnimationSoundClientBehavior@@@Z
void AnimationSoundClientBehaviorGlobal::unregister( AnimationSoundClientBehavior *behavior )
{
	if( m_firstHead == behavior )
		m_firstHead = behavior->m_next;

	if( m_firstTail == behavior )
		m_firstTail = behavior->m_prev;

	if( m_secondHead == behavior )
		m_secondHead = behavior->m_next;

	if( m_secondTail == behavior )
		m_secondTail = behavior->m_prev;

	if( behavior->m_next )
		behavior->m_next->m_prev = behavior->m_prev;

	if( behavior->m_prev )
		behavior->m_prev->m_next = behavior->m_next;

	behavior->m_next = 0;
	behavior->m_prev = 0;

	--m_count;
}
