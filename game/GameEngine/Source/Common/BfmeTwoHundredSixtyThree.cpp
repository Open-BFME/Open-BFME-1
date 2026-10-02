// cl: /Od
// Two values passed on along with what the worker below makes of the first,
// built without optimisation. Both callees are pinned by address; nothing here
// names them.

int bfmeMakeOX(void *one);

// The helper the worker below calls is retail's BfmeS1155::bfmeFind1155 (its
// three arguments are pushed and its this comes from the caller's this).
class BfmeS1155
{
public:
	unsigned int bfmeFind1155(const char *s, unsigned int pos, unsigned int n);
};

class BfmeThingPD
{
public:
	void bfmeGoPD(void *one, void *two);
};

void BfmeThingPD::bfmeGoPD(void *one, void *two)
{
	reinterpret_cast<BfmeS1155 *>(this)->bfmeFind1155(
		reinterpret_cast<const char *>(one), reinterpret_cast<unsigned int>(two),
		(unsigned int)bfmeMakeOX(one));
}
