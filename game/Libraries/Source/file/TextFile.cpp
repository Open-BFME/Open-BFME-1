// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// RVA 0x009CC020: BfmeOwnVTU's text-file tokenizer, called once from the
// 0x009CC220 constructor (BfmeOwnVTUCtor.cpp).
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

extern "C" int g_Va0134CC58[0x100];

class File
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual int read(void *buffer, int bytes);
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
	virtual int size(void);
};

struct Rva009CBFA0Elem
{
	int m_words[2];
};

class BfmeOwnVTU
{
public:
	virtual ~BfmeOwnVTU();

	bool bfmeApplyVTU(File *file);

private:
	char *m_buffer;
	_STL::vector<Rva009CBFA0Elem> m_tokens;
};

bool BfmeOwnVTU::bfmeApplyVTU(File *file)
{
	int lineStart = 1;
	int size = file->size();
	int i = 0;
	char *token = 0;
	int line = 1;
	m_buffer = new char[size + 1];
	file->read(m_buffer, size);
	m_buffer[size] = 0;
	int cls = g_Va0134CC58[(unsigned char)m_buffer[0]];
	while (i < size) {
		switch (cls) {
		case 0:
		case 2: {
			bool meaningful = cls == 0;
			if (lineStart == 1) {
				token = m_buffer + i;
				++i;
				cls = g_Va0134CC58[(unsigned char)m_buffer[i]];
			}
			lineStart = 0;
			while ((i < size && cls == 0) || cls == 2) {
				if (cls == 2)
					m_buffer[i] = ' ';
				else
					meaningful = true;
				++i;
				cls = g_Va0134CC58[(unsigned char)m_buffer[i]];
			}
			if (meaningful) {
				Rva009CBFA0Elem elem;
				elem.m_words[0] = (int)token;
				elem.m_words[1] = line;
				m_tokens.push_back(elem);
			} else {
				token = 0;
			}
			break;
		}
		case 1:
			lineStart = 1;
			while (i < size && cls == 1) {
				line += m_buffer[i] == '\r';
				m_buffer[i] = 0;
				++i;
				cls = g_Va0134CC58[(unsigned char)m_buffer[i]];
			}
			break;
		case 3:
			while (i < size && cls != 1) {
				m_buffer[i] = 0;
				++i;
				cls = g_Va0134CC58[(unsigned char)m_buffer[i]];
			}
			lineStart = 1;
			break;
		}
	}
	return true;
}
