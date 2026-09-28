// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: 0x009013A0 parses a '#' descriptor for its sole caller 0x00901F80,
// which calls it only when the model name starts with '#'. 0x00901160 splits
// the text on "!#" into strings and returns the count; exactly six fields are
// accepted: an int, a float, an '&'-separated texture list (or @NO_TEXTURE&),
// a string, an '&'-separated sub-object list (or @NO_SUBOBJ&) and an int.

#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>

typedef _STL::vector<_STL::string> Rva009013A0StringVector;

int rva00901160(Rva009013A0StringVector &out, const char *text, const char *delimiters);

bool parseDescriptor009013A0(
	const char *descriptor,
	_STL::string &field3,
	float &field1,
	int &field0,
	Rva009013A0StringVector &textures,
	Rva009013A0StringVector &subObjects,
	int &field5)
{
	Rva009013A0StringVector tokens;
	bool parsed = false;
	if (rva00901160(tokens, descriptor, "!#") == 6)
	{
		field0 = atoi(tokens[0].c_str());
		field1 = (float)atof(tokens[1].c_str());

		char buffer[2048];

		textures.clear();
		if (_strcmpi(tokens[2].c_str(), "@NO_TEXTURE&"))
		{
			strcpy(buffer, tokens[2].c_str());
			for (char *token = strtok(buffer, "&"); token; token = strtok(NULL, "&"))
				textures.push_back(_STL::string(token));
		}

		field3 = tokens[3].c_str();

		subObjects.clear();
		if (_strcmpi(tokens[4].c_str(), "@NO_SUBOBJ&"))
		{
			strcpy(buffer, tokens[4].c_str());
			for (char *token = strtok(buffer, "&"); token; token = strtok(NULL, "&"))
				subObjects.push_back(_STL::string(token));
		}

		field5 = atoi(tokens[5].c_str());
		parsed = true;
	}
	return parsed;
}
