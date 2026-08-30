// ?d_0082af80@@YAXXZ
// partial score=0.9 date=2026-08-30
// cl: /Od
struct BfmeTag82AF80 {};
class BfmeText82AF80 { public: void bfmeClear82AF80(int unused); private: int m_zero; char *m_text; };
void BfmeText82AF80::bfmeClear82AF80(int unused)
{
	char *text;
	BfmeTag82AF80 tag;

	text = m_text;
	tag = BfmeTag82AF80();
	*text = 0;
}
