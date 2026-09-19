// cl: /O2 /Ob2 /DNDEBUG /MD /EHs-c-

// The carved body at 0x00412670 returns its receiver and has no proven class owner.
class Rva00412670Self
{
public:
	Rva00412670Self *get();
};

// ?get@Rva00412670Self@@QAEPAV1@XZ
Rva00412670Self *Rva00412670Self::get()
{
	return this;
}
