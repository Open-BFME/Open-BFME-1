# The FX and LobbyUtils "file stream" constructors are STLport string streams

Three rows named STLport 4.5.3 file-stream constructors that STLport does not
have (`basic_filebuf(int)`, `basic_ofstream(int)`) or that retail's body does
not match (`basic_ifstream(const char*, int)`). The real file-stream tables are
0x0112F314 (`basic_filebuf<char>`, installed by the matched
`FilebufInstantiations.cpp` ctor and dtor), 0x0112FC28 / 0x0112FC84
(`basic_ifstream<char>` and its vbtable) and 0x0112FC30 / 0x0112FC54
(`basic_ofstream<char>`), all stored by the WWLib STLport ctor rows.

* **0x005C7370 is `basic_stringbuf<char>::basic_stringbuf(openmode)`.** It builds
  the `basic_streambuf<char>` base inline (table 0x0112EBD4, locale ctor), then
  stores 0x0110759C, the table the matched `~basic_stringbuf` (0x0053AC40) and
  `basic_stringbuf(const string&, openmode)` (0x0053C660) store, sets the mode at
  +0x54 and default-constructs the string at +0x58 (ILT 0x0004048A to
  `basic_string()`), which is STLport's
  `: basic_streambuf(), _M_mode(__mode), _M_str() {}`. Compiled from the real
  STLport headers in `stlport_narrow_stringbuf.cpp`, `probe.py` reports it exact.
* **0x005CC3F0 is `basic_ostringstream<char>::basic_ostringstream(openmode)`.** It
  constructs the basic_ios virtual base (vbtable 0x0110FE3C), runs
  `basic_ostream(0)`, stores 0x0110FCAC, builds the member at +4 by calling
  0x005C7370 with `mode | 0x10` (`ios_base::out`), then `init(&buf)`: STLport's
  `: basic_ostream(0), _M_buf(__mode | ios_base::out) { this->init(&_M_buf); }`.
  Its virtual base sits at +0x70; the matched `basic_ofstream<char>` ctors, whose
  member is a filebuf, put it at +0xB8.
* **0x0053FB00 is `basic_istringstream<char>::basic_istringstream(const string&,
  openmode)`.** The same shell with `_M_gcount` zeroed, table 0x011075E0,
  vbtable 0x01107640, and the member at +8 built by 0x0053C660, the matched
  `basic_stringbuf(const string&, openmode)`, from the string argument and
  `mode | 8` (`ios_base::in`). `basic_ifstream(const char*, openmode)` would
  default-construct a filebuf and call `open`, which this body never does, and
  the matched `basic_ifstream<char>` ctors put the virtual base at +0xBC, not
  +0x74.
* The FX writeINI sources built the same misnamed pair inline; they now use
  `basic_ostringstream`/`basic_stringbuf`, and their destructor calls reach
  `~basic_stringbuf` (0x0053AC40, ILT 0x00044459) and 0x005C7180, the
  ostringstream-level destructor that stores 0x0110FCAC.
