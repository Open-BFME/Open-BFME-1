// cl: /DNDEBUG /MD /EHs-c-
// BFME's out-of-line FXList::doFXObj(fx, primary, secondary) static wrapper.
// ZH inlines `if (fx) fx->doFXObj(...)`. Retail also consults a bool member
// through ILT 0x00011F77 (body 0x0042DAA0) and skips the play when it is set.

class Object;

class FXList
{
public:
	static void doFXObj(const FXList *fx, const Object *primary, const Object *secondary);
	bool bfmeIsBlocked(void) const;
	void doFXObj(const Object *primary, const Object *secondary) const;
};

// ?doFXObj@FXList@@SAXPBV1@PBVObject@@1@Z
void FXList::doFXObj(const FXList *fx, const Object *primary, const Object *secondary)
{
	if (fx)
	{
		if (!fx->bfmeIsBlocked())
			fx->doFXObj(primary, secondary);
	}
}
