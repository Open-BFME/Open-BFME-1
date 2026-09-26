// cl: /DNDEBUG /MD /EHsc
// WWDownload FTP.CPP MyIPAddress body.

struct hostent
{
	char *h_name;
	char **h_aliases;
	short h_addrtype;
	short h_length;
	char **h_addr_list;
};

struct sockaddr_in
{
	unsigned short sin_family;
	unsigned short sin_port;
	unsigned long sin_addr;
	unsigned char sin_zero[8];
};

extern "C" int __stdcall getsockname(
	unsigned int socket, void *name, int *nameLength);
extern "C" int __stdcall gethostname(
	char *name, int length);
extern "C" struct hostent *__stdcall gethostbyname(
	const char *name);
extern "C" unsigned long __stdcall inet_addr(
	const char *address);

unsigned long MyIPAddress(int sockfd)
{
	int test = 99;
	int i;
	char pBuffer[256];
	char *pAddr;
	struct hostent *pHE;
	unsigned long ip;
	struct sockaddr_in sin;

	if (sockfd != -1)
	{
		i = sizeof(sin);
		getsockname(sockfd, (struct sockaddr *)&sin, &i);

		ip = sin.sin_addr;
	}
	else
	{
		if (gethostname(pBuffer, 256) != 0)
		{
			return 0x80040001;
		}

		pHE = gethostbyname(pBuffer);

		if (pHE == 0)
		{
			return 0x80040001;
		}

		ip = 0;
		i = 0;

		while ((pAddr = pHE->h_addr_list[i++]) != 0)
		{
			ip = *((unsigned long *)pAddr);

			if ((ip != 0) && (ip != inet_addr("127.0.0.1")))
			{
				break;
			}
			else
			{
				ip = 0;
			}
		}
	}

	if (ip == 0)
	{
		return 0x80040001;
	}

	return ip;
}
