// ?d_0019aff0@@YAXXZ
// partial score=0.75 date=2026-09-09
// ?bfmeGoRva0019AFF0@SidesInfo@@QAEPAV1@PAX@Z
class SidesInfo
{
public:
	SidesInfo *bfmeGoRva0019AFF0(void *param);
	~SidesInfo();
};

class Rva0019AFF0Temp
{
public:
	Rva0019AFF0Temp(void *param);	// retail 0x0004A8A4 (shared body)
	void bfmeInit(void *other);	// retail 0x0000EA48 (shared body)

private:
	unsigned char m_pad[0x18];
};

SidesInfo *SidesInfo::bfmeGoRva0019AFF0(void *param)
{
	Rva0019AFF0Temp temp(param);
	temp.bfmeInit(this);
	reinterpret_cast<SidesInfo &>(temp).~SidesInfo();
	return this;
}
