class BfmeSinkAV
{
public:
	void bfmeAddAV(void *item);
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
		sink->bfmeAddAV(*it);
}
