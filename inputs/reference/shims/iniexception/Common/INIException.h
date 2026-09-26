#pragma once

class INIException
{
public:
	char *mFailureMessage;
	int m_argCount;
	INIException(const char *errorMessage);
	INIException(int argCount, const char *errorMessage, ...);
	INIException(const INIException &that);
	~INIException();
};

