// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x0094C280 (51 B, ret 4) and 0x0094C060 (52 B, ret 8) are the same
// refcounted-handle + 16-byte-tail copy idiom as the landed Small03cRefCopy
// pair (0x0094C260/0x0094C410): handle word copied with a null-guarded
// halfword inc at handle+4, then a 4-word tail copy. 0x0094C280 takes both
// from one source struct; 0x0094C060 takes the handle and the tail through
// two pointers (hence ret 8). IDENTITY IS NOT RECOVERED: both names keep
// their address tokens (one-identity rule).
struct Rva0094C280Tail
{
	int m_b;
	int m_c;
	int m_d;
	int m_e;
};
struct Rva0094C280Src
{
	void *m_handle;
	Rva0094C280Tail m_tail;
};
class Rva0094C280Box
{
public:
	Rva0094C280Box *copyFrom(const Rva0094C280Src *src);
	void *m_handle;
	Rva0094C280Tail m_tail;
};
// mov eax,ecx / handle copy + null-guarded halfword inc at handle+4 / tail struct copy.
Rva0094C280Box *Rva0094C280Box::copyFrom(const Rva0094C280Src *src)
{
	m_handle = src->m_handle;
	if (m_handle)
		++*(unsigned short *)((char *)m_handle + 4);
	m_tail = src->m_tail;
	return this;
}
struct Rva0094C060Tail
{
	int m_b;
	int m_c;
	int m_d;
	int m_e;
};
struct Rva0094C060Head
{
	void *m_handle;
};
class Rva0094C060Box
{
public:
	Rva0094C060Box *copyFrom(const Rva0094C060Head *a, const Rva0094C060Tail *b);
	void *m_handle;
	Rva0094C060Tail m_tail;
};
// mov eax,ecx / handle copy + null-guarded halfword inc at handle+4 / 16-byte tail copy off the second pointer.
Rva0094C060Box *Rva0094C060Box::copyFrom(const Rva0094C060Head *a, const Rva0094C060Tail *b)
{
	m_handle = a->m_handle;
	if (m_handle)
		++*(unsigned short *)((char *)m_handle + 4);
	m_tail = *b;
	return this;
}
struct Rva0094C2F0Key
{
	int m_value;
};
struct Rva0094C2F0Head
{
	void *m_handle;
};
class Rva0094C2F0Box
{
public:
	Rva0094C2F0Box *copyFrom(const Rva0094C2F0Key *a, const Rva0094C2F0Head *b);
	int m_key;
	void *m_handle;
};
// mov eax,ecx / plain key word off the first pointer / handle off the second with the null-guarded halfword inc.
Rva0094C2F0Box *Rva0094C2F0Box::copyFrom(const Rva0094C2F0Key *a, const Rva0094C2F0Head *b)
{
	m_key = a->m_value;
	m_handle = b->m_handle;
	if (m_handle)
		++*(unsigned short *)((char *)m_handle + 4);
	return this;
}
struct Rva0094C310Tail
{
	int m_b;
	int m_c;
	int m_d;
	int m_e;
};
struct Rva0094C310Head
{
	void *m_handle;
};
class Rva0094C310Box
{
public:
	Rva0094C310Box *copyFrom(const Rva0094C310Head *a, const Rva0094C310Tail *b);
	void *m_handle;
	Rva0094C310Tail m_tail;
};
// Byte-identical to 0x0094C060: handle off the first pointer, 16-byte tail off the second.
Rva0094C310Box *Rva0094C310Box::copyFrom(const Rva0094C310Head *a, const Rva0094C310Tail *b)
{
	m_handle = a->m_handle;
	if (m_handle)
		++*(unsigned short *)((char *)m_handle + 4);
	m_tail = *b;
	return this;
}
