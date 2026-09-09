// ?lookup@Rva007FA2C0@@QAEPAURva007F96C0Rec@@PAX@Z
// partial score=0.9 date=2026-09-09
// cl: /O2
// The FESL transactor scans populated 0x18-byte records for a matching key.

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct Rva007F9A40Key
{
	const char *a;
	const char *b;
	int c;
	bool matches(const Rva007F9A40Key *other) const;
};

struct Rva007F96C0Rec
{
	char present;
	char pad[3];
	Rva007F9A40Key key;
	int value10;
	int value14;
};

class Rva007FA2C0
{
public:
	Rva007F96C0Rec *lookup(void *key);

private:
	char pad00[0x10];
	volatile int count;
	char pad14[0x394];
	Rva007F96C0Rec records[0x20];
};

Rva007F96C0Rec *Rva007FA2C0::lookup(void *key)
{
	int i = 0;
	Rva007F96C0Rec *record;
	if (key == 0)
		goto fail;
	record = records;
	for (;;)
	{
		_ReadWriteBarrier();
		if (i >= count)
			goto fail;
		if (record->present != 0 &&
			((Rva007F9A40Key *)key)->matches(&record->key))
			return record;
		++i;
		++record;
	}

fail:
	return 0;
}
