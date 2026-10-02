// cl: /DNDEBUG /MD /EHsc
// BFME SentenceData vector append with its non-trivial record assignment.

struct BfmeSentenceDataStruct
{
	void *surface;
	int fields[8];
};

// The record take-over this body calls sits at retail 0x0093D9B0 and is
// defined as BfmeThingFT::bfmeTakeFT
// (game/GameEngine/Source/Common/BfmeOneHundredNinetyEight.cpp).  Both take
// `this` plus one pointer and return `this`, so the call site is spelled
// through the defined name rather than a local assignment operator.
class BfmeThingFT
{
public:
	BfmeThingFT &bfmeTakeFT(const BfmeThingFT *from);
};

class BfmeSentenceDataVector
{
public:
	virtual ~BfmeSentenceDataVector(void);
	virtual bool Equal(const BfmeSentenceDataVector &that) const;
	virtual bool Resize(int size, const BfmeSentenceDataStruct *array = 0);
	virtual void Clear(void);

	bool Add(const BfmeSentenceDataStruct &object);

private:
	BfmeSentenceDataStruct *vector;
	int vector_max;
	bool is_valid;
	bool is_allocated;
	bool pad[2];
	int active_count;
	int growth_step;
};

// Object spelling for the retail
// ?Add@?$DynamicVectorClass@USentenceDataStruct@Render2DSentenceClass@@@@QAE_NABUSentenceDataStruct@Render2DSentenceClass@@@Z
bool BfmeSentenceDataVector::Add(const BfmeSentenceDataStruct &object)
{
	if (active_count >= vector_max) {
		if ((is_allocated || !vector_max) && growth_step > 0) {
			if (!Resize(vector_max + growth_step))
				return false;
		} else {
			return false;
		}
	}

	int index = active_count;
	const BfmeSentenceDataStruct *incoming = &object;
	active_count = index + 1;
	BfmeSentenceDataStruct *base = vector;
	reinterpret_cast<BfmeThingFT *>(base + index)->bfmeTakeFT(
		reinterpret_cast<const BfmeThingFT *>(incoming));
	return true;
}
