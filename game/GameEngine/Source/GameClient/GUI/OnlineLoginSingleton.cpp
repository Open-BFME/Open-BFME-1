// Singleton storage, independently established in BFME 1 by the matched
// constructor 0x005538A0 and destructor 0x0054CB60. Both use VA 0x012F4AAC.
// BFME 2 aa505f34 has no corresponding login provider; no donor layout used.
// cl: /DNDEBUG /MD
class BfmeAptScreenOnlineLogin;
BfmeAptScreenOnlineLogin *TheBfmeOnlineLogin = 0;
