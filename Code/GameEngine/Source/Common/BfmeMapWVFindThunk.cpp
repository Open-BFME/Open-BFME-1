// Clean C++ owner for the Open-BFME5 incremental-link thunk at RVA 0x0002AF2C.
// BfmeMapWV::lookup uses this same range-search ABI; retail forwards the
// signed key to the canonical BfmeFindWT implementation at 0x00747770.

class BfmeMapWV
{
public:
	int find(int key);
};

class BfmeFindWT
{
public:
	int find(int key);
};

int BfmeMapWV::find(int key)
{
	return ((BfmeFindWT *)this)->find(key);
}
