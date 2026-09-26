// cl: /O2 /Ob0

class Rva008AC9E0
{
	char m_pad[0x48];
	float *m_arr;

public:
	float get(int i);
};

float Rva008AC9E0::get(int i)
{
	return m_arr[i];
}
