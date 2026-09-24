// ?dispatch@Rva000F99C0RecordDispatch@@QAEXPAVRva00365C20CallbackView@@@Z
// partial score=0.2583 date=2026-09-24
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /O2 /Ob2

struct Rva000F99C0Record
{
	unsigned char m_opaque00[0x60];
};

struct Rva000F99C0Payload6
{
	unsigned int m_word00;
	unsigned int m_word04;
	unsigned int m_word08;
	unsigned int m_word0c;
	unsigned int m_word10;
	unsigned int m_word14;
};

typedef char Rva000F99C0PayloadSize[
	sizeof(Rva000F99C0Payload6) == 0x18 ? 1 : -1];

class Rva00365C20CallbackView
{
public:
	void dispatch(const Rva000F99C0Record *record, unsigned int word08,
		unsigned int word0c, Rva000F99C0Payload6 payload, int index,
		const unsigned char *tail44);
};

#pragma comment( linker, "/alternatename:?dispatch@Rva00365C20CallbackView@@QAEXPBURva000F99C0Record@@IIURva000F99C0Payload6@@HPBE@Z=?j_00010a64@@YAXXZ" )

class Rva000F99C0RecordDispatch
{
public:
	void dispatch(Rva00365C20CallbackView *context);

private:
	int m_opaque00;
	Rva000F99C0Record *m_begin;
	Rva000F99C0Record *m_end;
	Rva000F99C0Record *m_capacity;
};

void Rva000F99C0RecordDispatch::dispatch(Rva00365C20CallbackView *context)
{
	unsigned int index = 0;
	while (index < (unsigned int)(m_end - m_begin))
	{
		Rva000F99C0Record *record = m_begin + index;
		Rva000F99C0Payload6 payload;
		payload.m_word00 = *(const unsigned int *)(record->m_opaque00 + 0x14);
		payload.m_word04 = *(const unsigned int *)(record->m_opaque00 + 0x18);
		payload.m_word08 = *(const unsigned int *)(record->m_opaque00 + 0x1c);
		payload.m_word0c = *(const unsigned int *)(record->m_opaque00 + 0x20);
		payload.m_word10 = *(const unsigned int *)(record->m_opaque00 + 0x24);
		payload.m_word14 = *(const unsigned int *)(record->m_opaque00 + 0x28);
		context->dispatch(record,
			*(const unsigned int *)(record->m_opaque00 + 0x08),
			*(const unsigned int *)(record->m_opaque00 + 0x0c), payload,
			*(const int *)(record->m_opaque00 + 0x40),
			record->m_opaque00 + 0x44);
		++index;
	}
}
