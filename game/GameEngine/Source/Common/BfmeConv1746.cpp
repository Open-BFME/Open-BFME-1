class BfmeSinkAV;

class Object;

class AIGroup
{
public:
	void add(Object *member);
};

class BfmeVecAV
{
public:
	void **m_bfmeBeginAV;
	void **m_bfmeEndAV;
};

void __stdcall bfmeEachAV(BfmeVecAV *range, BfmeSinkAV *sink)
{
	for (void **it = range->m_bfmeBeginAV; it != range->m_bfmeEndAV; ++it)
		((AIGroup *)sink)->add((Object *)*it);
}
