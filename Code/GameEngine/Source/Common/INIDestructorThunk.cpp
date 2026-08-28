// cl: /DNDEBUG /MD /EHsc
// readable body of ??1INI@@: Code/GameEngine/Source/Common/INI/INI_stl.cpp
// readable body of ??1INI@@QAE@XZ: Code/GameEngine/Source/Common/INI/ini_parsers.cpp
// Open-BFME5: INI dtor. members @+0x04 and @+0x834.

class Buffer
{
public:
	~Buffer();
private:
	unsigned char m_pad[4];
};

class INIMemberA
{
public:
	~INIMemberA();
private:
	unsigned char m_pad[4];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	~INI();
private:
	unsigned char m_gap0[4];
	Buffer m_a; // +0x04
	unsigned char m_gap[0x82c]; // to +0x834
	INIMemberA m_b; // +0x834
};

// ??1INI@@QAE@XZ
INI::~INI()
{
}
