// cl: /EHsc
// stlport

#include <vector>

class BFMERetailAsciiString
{
public:
	~BFMERetailAsciiString()
	{
		releaseBuffer();
	}

private:
	void releaseBuffer();
	char *m_data;
};

struct Gen_t_00770380_p8cd
{
	int m_data[2];
	Gen_t_00770380_p8cd();
	Gen_t_00770380_p8cd(const Gen_t_00770380_p8cd &);
	~Gen_t_00770380_p8cd();
	Gen_t_00770380_p8cd &operator=(const Gen_t_00770380_p8cd &);
};

struct Rva0077AD90Element
{
	BFMERetailAsciiString m_name;
	char m_padding[0x0c];
	_STL::vector<Gen_t_00770380_p8cd> m_entries;
	char m_tail[0x50];
};

template class _STL::vector<Rva0077AD90Element>;
