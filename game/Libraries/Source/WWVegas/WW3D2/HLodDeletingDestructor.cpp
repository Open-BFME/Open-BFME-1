// cl: /EHs-c-
//
// Compiler-owned scalar-deleting wrapper for the matched HLodClass complete
// destructor at retail 0x0097BB40. The standalone declaration intentionally
// uses global operator delete, matching this retail wrapper.

class Rva0097BB40HLod
{
public:
	virtual ~Rva0097BB40HLod();
};

void ForceRva0097BB40HLodDeletingDestructor()
{
	Rva0097BB40HLod value;
}
