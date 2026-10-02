// cl: /DNDEBUG /MD /EHsc
// Retail VA 0x0107388B is the NUL byte used by null AsciiString fallbacks.
// The existing DIR32 ledger pins this exact symbol to that byte; this defines
// its initial image value without claiming a larger string or buffer extent.
extern const char g_bfmeEmptyAscii[1] = { 0 };
