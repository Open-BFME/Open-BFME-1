// cl: /DNDEBUG /MD /EHsc

typedef int Int;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct BfmeAsciiStringData
{
	unsigned char m_header[8];
	char m_text[1];
};

class AsciiString
{
public:
	BfmeAsciiStringData *m_data;
};

struct BfmeGotBPA
{
	unsigned char m_header[0x14];
	void *m_value;
};

class BfmeThingBPA
{
public:
	void *bfmeGoBPA(void *what);
	BfmeGotBPA *m_end;
};

class BfmeAwakenLog
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual BfmeAwakenLog *slot38(const char *text);
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual BfmeAwakenLog *slot4C(int value);
};

class BfmeAwakenDebug
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual BfmeAwakenLog *slot6C(int first, int second);
};

extern BfmeAwakenDebug *TheBfmeAwakenDebug;
extern void _bfme_debugRecordCallsite(int kind);
extern const char Rva006A16B0Empty[];

class Rva0007F560Factory : public BfmeThingBPA
{
public:
	void *lookup(const AsciiString &name);
};

void *Rva0007F560Factory::lookup(const AsciiString &name)
{
	const AsciiString *input = &name;
	void *result = bfmeGoBPA((void *)input);
	if (!result)
	{
		_bfme_debugRecordCallsite(1);
		TheBfmeAwakenDebug->slot60();
		BfmeAwakenLog *report = TheBfmeAwakenDebug->slot6C(
			(Int)result, (Int)result);
		_ReadWriteBarrier();
		report = report->slot38("Unknown game detail option : ");
		_ReadWriteBarrier();
		const char *text;
		if (input->m_data)
			text = input->m_data->m_text;
		else
			text = Rva006A16B0Empty;
		report->slot38(text)->slot4C(1);
	}
	if (*reinterpret_cast<void **>((unsigned char *)result + 4))
	{
		_bfme_debugRecordCallsite(1);
		TheBfmeAwakenDebug->slot60();
		BfmeAwakenLog *report = TheBfmeAwakenDebug->slot6C(0, 0);
		_ReadWriteBarrier();
		report = report->slot38("\n\nOption Type Mismatch : ");
		_ReadWriteBarrier();
		const char *text;
		if (input->m_data)
			text = input->m_data->m_text;
		else
			text = Rva006A16B0Empty;
		report->slot38(text)->slot4C(1);
	}
	return result;
}
