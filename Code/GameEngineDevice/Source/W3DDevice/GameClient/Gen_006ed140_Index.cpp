// cl: /DNDEBUG /MD /EHsc

// Retail 0x006ED140. return (char *)m_base + index * 0x38.

struct Gen_006ed140_Elem { unsigned char m[0x38]; };

class Gen_006ed140
{
public:
	Gen_006ed140_Elem *at(int index);

private:
	Gen_006ed140_Elem *m_base;
};

// ?at@Gen_006ed140@@QAEPAUGen_006ed140_Elem@@H@Z
Gen_006ed140_Elem *Gen_006ed140::at(int index)
{
	return m_base + index;
}
