// cl: /O2 /Ob0

extern "C" int __stdcall closesocket(unsigned int);

class Rva00885980
{
	char m_lead[4];
	unsigned int m_sock;

public:
	int close();
};

int Rva00885980::close()
{
	closesocket(m_sock);
	return 0;
}
