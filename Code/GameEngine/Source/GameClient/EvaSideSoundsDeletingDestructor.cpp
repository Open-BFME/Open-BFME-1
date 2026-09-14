// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: EvaSideSounds scalar-deleting destructor at retail RVA
// 0x00078480 (30 bytes). The wrapper calls the canonical element destructor
// through ILT 0x00022390 before conditionally invoking operator delete.
// Exact vector<EvaSideSounds> copy, fill-insert, push-back, and cleanup paths
// establish the 16-byte non-virtual record and its destructor identity.

class EvaSideSounds
{
public:
	~EvaSideSounds();
};

void forceEvaSideSoundsDelete(EvaSideSounds *sounds)
{
	delete sounds;
}
