// ?notifyUnlessKind@@YAXPAURva0024F280Holder@@H@Z
// partial score=0.9 date=2026-09-06
struct Rva0024F280Type { int m_0; int m_kind; };
struct Rva0024F280Template { char m_pad[0x1c]; Rva0024F280Type* m_type; };
struct Rva0024F280Pad { char m_pad[0x20]; };
struct Rva0024F280Sink { void notify(int value, int mode); };
struct Rva0024F280Target : Rva0024F280Pad, Rva0024F280Sink {
	char m_rest[0x30 - 0x21];
	Rva0024F280Template* m_template;
};
struct Rva0024F280Holder { char m_pad[0x204]; Rva0024F280Target* m_target; };
void notifyUnlessKind(Rva0024F280Holder* holder, int value)
{
	if (!holder)
		return;
	Rva0024F280Target* t = holder->m_target;
	if (!t)
		return;
	Rva0024F280Type* type = t->m_template->m_type;
	int kind = type ? type->m_kind : 999999;
	if (kind == 0x38 || kind == 0xf)
		return;
	t->notify(value, 2);
}
