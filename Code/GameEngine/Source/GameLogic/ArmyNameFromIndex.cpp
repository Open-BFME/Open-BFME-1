// cl: /DNDEBUG /MD /EHsc

class AsciiString
{
public:
	void set(const char *text);
};

void __stdcall armyNameFromIndex(unsigned int index, AsciiString *out)
{
	switch (index)
	{
	case 0:
		out->set("TopArmy");
		break;
	case 1:
		out->set("BottomArmy");
		break;
	case 2:
		out->set("RightArmy");
		break;
	case 3:
		out->set("LeftArmy");
		break;
	}
}
