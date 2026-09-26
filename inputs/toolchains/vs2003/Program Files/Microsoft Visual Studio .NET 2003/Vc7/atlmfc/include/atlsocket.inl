// This is a part of the Active Template Library.
// Copyright (C) Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Active Template Library Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the	
// Active Template Library product.

namespace ATL
{
////////////////////////////////////////////////////////////////////////////
// CSocketAddr implmenetation. 
////////////////////////////////////////////////////////////////////////////

inline CSocketAddr::CSocketAddr()
{
	m_pAddrs = NULL;
}

inline CSocketAddr::~CSocketAddr()
{
	if (m_pAddrs != NULL)
	{
		FreeAddrInfo(m_pAddrs);
		m_pAddrs = NULL;
	}
}

inline int CSocketAddr::FindAddr(
	LPCTSTR szHost,
	LPCTSTR szPortOrServiceName,
	int flags,
	int addr_family,
	int sock_type,
	int ai_proto
)
{
	if (m_pAddrs)
	{
		FreeAddrInfo(m_pAddrs);
		m_pAddrs = NULL;
	}

	ADDRINFOT hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_flags = flags;
	hints.ai_family = addr_family;
	hints.ai_socktype = sock_type;
	hints.ai_protocol = ai_proto;
	return ::GetAddrInfo(szHost, szPortOrServiceName, &hints, &m_pAddrs);
}

inline int CSocketAddr::FindAddr(
	LPCTSTR szHost,
	int nPortNo,
	int flags,
	int addr_family,
	int sock_type,
	int ai_proto
)
{
	// convert port number to string
	TCHAR buff[12];
	LPTSTR pszPort = _itot(nPortNo, buff, 10);
	return FindAddr(szHost, pszPort, flags, addr_family, sock_type, ai_proto);
}

inline int CSocketAddr::FindINET4Addr
(
	LPCTSTR szHost,
	int nPortNo,
	int flags /* = 0 */,
	int sock_type /* = SOCK_STREAM */
)
{
	// convert port number to string
	TCHAR buff[12];
	LPTSTR pszPort = _itot(nPortNo, buff, 10);
	return FindAddr(szHost, pszPort, flags, PF_INET, sock_type, IPPROTO_IP);
}

inline int CSocketAddr::FindINET6Addr
(
	LPCTSTR szHost,
	int nPortNo,
	int flags /* = 0 */,
	int sock_type /* = SOCK_STREAM */
)
{
	// convert port number to string
	TCHAR buff[12];
	LPTSTR pszPort = _itot(nPortNo, buff, 10);
	return FindAddr(szHost, pszPort, flags, PF_INET6, sock_type, IPPROTO_IPV6);
}

inline ADDRINFOT* const CSocketAddr::GetAddrInfoList() const
{
	return m_pAddrs;
}

inline ADDRINFOT* const CSocketAddr::GetAddrInfo(int nIndex /* = 0 */) const
{
	if (!m_pAddrs)
		return NULL;
	ADDRINFOT *pAI = m_pAddrs;
	while (nIndex > 0 && pAI != NULL)
	{
		pAI = pAI->ai_next;
		nIndex --;
	}
	return pAI;
}


}; // namespace ATL