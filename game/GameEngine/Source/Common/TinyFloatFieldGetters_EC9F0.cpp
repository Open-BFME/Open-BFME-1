// Float-field getter at 0x000EC9F0.
//
//     fld dword ptr [ecx+0x3FC] / ret
//
// Identity is not recovered. The class name is the retail RVA.

class Rva000EC9F0
{
public:
	float get();
	char m_lead[0x3FC];
	float m_value;
};

float Rva000EC9F0::get()
{
	return m_value;
}

// Float-field getter at 0x000F9440.
//
//     fld dword ptr [ecx+0x3BC] / ret
//
// Identity is not recovered. The class name is the retail RVA.

class Rva000F9440
{
public:
	float get();
	char m_lead[0x3BC];
	float m_value;
};

float Rva000F9440::get()
{
	return m_value;
}

// Float-field getter at 0x000FBFA0.
//
//     fld dword ptr [ecx+0x3A4] / ret
//
// Identity is not recovered. The class name is the retail RVA.

class Rva000FBFA0
{
public:
	float get();
	char m_lead[0x3A4];
	float m_value;
};

float Rva000FBFA0::get()
{
	return m_value;
}
