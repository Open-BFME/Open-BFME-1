// Address-derived self accessors.  Their ILT thunks prove member-call ABI,
// but no caller, vtable, or string evidence identifies the owning classes.

class SelfAccessor0069B8D0
{
public:
	SelfAccessor0069B8D0 *getSelf0069B8D0();
};

SelfAccessor0069B8D0 *SelfAccessor0069B8D0::getSelf0069B8D0()
{
	return this;
}

class SelfAccessor0069B8E0
{
public:
	SelfAccessor0069B8E0 *getSelf0069B8E0();
};

SelfAccessor0069B8E0 *SelfAccessor0069B8E0::getSelf0069B8E0()
{
	return this;
}
