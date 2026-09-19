// cl: /DNDEBUG /MD /EHs-c- /Oy-

// Retail stores three words per entry and asks the object to remove an
// existing function and user pair through virtual slot 31 before insertion.

extern void *DebugReAllocMemory(void *, unsigned);

extern "C" void *(__cdecl *bfme_memmove_ptr)(void *, const void *, unsigned);
#define memmove (*bfme_memmove_ptr)

struct Rva00889BF0Entry
{
	unsigned priority;
	void *function;
	void *user;
};

class Rva00889BF0Context
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08();
	virtual void slot0C(); virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1C(); virtual void slot20();
	virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38();
	virtual void slot3C(); virtual void slot40(); virtual void slot44();
	virtual void slot48(); virtual void slot4C(); virtual void slot50();
	virtual void slot54(); virtual void slot58(); virtual void slot5C();
	virtual void slot60(); virtual void slot64(); virtual void slot68();
	virtual void slot6C(); virtual void slot70(); virtual void slot74();
	virtual void slot78(); virtual void remove(void *, void *);

	Rva00889BF0Entry *entries;
	unsigned count;

	void insert(unsigned priority, void *function, void *user);
};

// ?insert@Rva00889BF0Context@@QAEXIPAX0@Z
void Rva00889BF0Context::insert(unsigned priority, void *function, void *user)
{
	if (!function)
		return;

	remove(function,user);

	unsigned k=0;
	while (k<count && entries[k].priority>=priority)
		++k;

	entries=(Rva00889BF0Entry *)DebugReAllocMemory(
		entries,(count+1)*sizeof(Rva00889BF0Entry));
	memmove(entries+k+1,entries+k,(count-k)*sizeof(void *));
	++count;
	entries[k].priority=priority;
	entries[k].function=function;
	entries[k].user=user;
}
