// ??0Rva0061DA30Base@@QAE@VAsciiString@@@Z
// partial score=0.758 date=2026-09-28
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
#include "ascii_string.h"
class Rva0061DA30Base {
public:
 Rva0061DA30Base(AsciiString name);
 virtual ~Rva0061DA30Base();
 AsciiString m_name;
	volatile int m_bfme08;
	volatile int m_bfme0c;
	volatile int m_bfme10;
	volatile int m_bfme14;
	volatile int m_bfme18;
	volatile int m_bfme1c;
	volatile int m_bfme20;
	volatile int m_bfme24;
	volatile int m_bfme28;
	volatile int m_bfme2c;
	volatile int m_bfme30;
	volatile int m_bfme34;
	volatile int m_bfme38;
	volatile int m_bfme3c;
	volatile int m_bfme40;
	volatile int m_bfme44;
	volatile int m_bfme48;
	volatile char m_bfme4c;
	volatile int m_bfme50;
	volatile int m_bfme54;
	volatile int m_bfme58;
	volatile int m_bfme5c;
	volatile int m_bfme60;
	volatile int m_bfme64;
	float m_bfme68;
	volatile char m_bfme6c;
	float m_bfme70;
	float m_bfme74;
	float m_bfme78;
	volatile char m_bfme7c;
	volatile int m_bfme80;
	float m_bfme84;
	float m_bfme88;
	float m_bfme8c;
	float m_bfme90;
	float m_bfme94;
	float m_bfme98;
	float m_bfme9c;
};
Rva0061DA30Base::Rva0061DA30Base(AsciiString name) : m_name(name)
{
	m_bfme08 = 0;
	m_bfme0c = 0;
	m_bfme10 = 0;
	m_bfme14 = 0;
	m_bfme1c = 0;
	m_bfme18 = 0;
	m_bfme20 = 0;
	m_bfme24 = 0;
	m_bfme28 = 0;
	m_bfme30 = 0;
	m_bfme34 = 0;
	m_bfme3c = 0;
	m_bfme44 = 0;
	m_bfme48 = 0;
	m_bfme4c = 0;

	{
	int one = 1;
	m_bfme2c = one;
	m_bfme38 = one;
	m_bfme40 = one;
	}

	m_bfme50 = 0;
	m_bfme54 = 0;
	m_bfme58 = 0;
	m_bfme5c = 0;
	m_bfme60 = 0;
	m_bfme64 = 0;

	m_bfme68 = 0.1f;
	m_bfme6c = 0;

	{
	float oneF = 1.0f;
	m_bfme70 = oneF;
	m_bfme74 = oneF;
	m_bfme78 = 0.001f;
	m_bfme7c = 0;

	m_bfme80 = 0;
	m_bfme84 = 6.27f;
	m_bfme88 = 0.3f;
	m_bfme8c = oneF;
	m_bfme90 = oneF;
	m_bfme94 = oneF;
	m_bfme98 = oneF;
	m_bfme9c = oneF;
	}
}


