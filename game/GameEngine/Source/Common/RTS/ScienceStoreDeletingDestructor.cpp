// cl: /O2
// Open-BFME: ScienceStore scalar-deleting destructor wrapper, retail
// 0x00076E90 (30 bytes). ScienceStore vtable 0x01075F14 slot zero routes
// here through ILT 0x0002CDC2; the matched constructor at 0x00076E50
// installs that vtable and the wrapper calls destructor ILT 0x00004BEC.

class ScienceStore
{
public:
    __declspec(noinline) virtual ~ScienceStore();
};

ScienceStore::~ScienceStore()
{
}
