// cl: /DNDEBUG /MD /EHsc

// The call at retail 0x0056C09x goes through ILT 0x3EA4 to the matched
// 0x0056AB50 body, which reads this same object.
class Rva0056AB50Owner
{
public:
	void *getSelectedItemData();
};

class Rva0056C090
{
public:
	void update(int unused);

private:
	unsigned char m_pad[0x258];
	int m_state;
};

void Rva0056C090::update(int unused)
{
	if (m_state == 0)
	{
		if (reinterpret_cast<Rva0056AB50Owner *>(this)->getSelectedItemData())
			m_state = 12;
	}
}
