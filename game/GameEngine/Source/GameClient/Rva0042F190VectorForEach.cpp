// cl: /DNDEBUG /MD /O2
// Two-argument thiscall over a pointer vector at +0xE4/+0xE8.

class BfmeObj9F
{
public:
	void bfmeGo9F(unsigned int, unsigned char);
};

struct Rva0042F190Args
{
	unsigned int a;
	unsigned char b;
};

class Rva0042F190Host
{
public:
	void forEach(Rva0042F190Args args);

private:
	unsigned char m_prefix[0xE4];
	BfmeObj9F **m_begin;
	BfmeObj9F **m_end;
};

// ?forEach@Rva0042F190Host@@QAEXURva0042F190Args@@@Z
void Rva0042F190Host::forEach(Rva0042F190Args args)
{
	for (BfmeObj9F **it = m_begin; it != m_end; ++it)
		(*it)->bfmeGo9F(args.a, args.b);
}
