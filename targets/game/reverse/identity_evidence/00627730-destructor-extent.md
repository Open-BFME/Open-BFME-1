# DownloadManager destructor: complete extent and allocator

Retail entry00627730 reaches RET006277E0 then INT3:177 bytes. The old75-byte
claim ends inside CALL0062777A to operator delete00881EB0 and excludes
WSACleanup, the queued-download list destruction and both wide-string
releases. Ghidra create_function at00A27730 independently recovers177 bytes;
the local PE decode proves the actual contiguous terminal extent.

The retained destructor identity has the GeneralsMD DownloadManager twin.
Both use the same native destructor: delete m_download, conditionally call
WSACleanup and clear m_winsockInit, then implicit member destruction.
The imported slot013596E8 names WSOCK32.WSACleanup. The retail list at+18
calls ILT0003AA1C ->00627270 to clear36-byte nodes, then deallocates the
36-byte sentinel through __node_alloc<false,0>::_M_deallocate at0082E5F0.
Wide strings+14 and+10 release through008881D0. No new pins are introduced.

The existing TU's allocator configuration emits operator delete instead of
the sized node allocator after the old prefix. A separate native destructor
TU uses the existing BFME_STLP_NODE_ALLOC configuration with the canonical
DownloadManager declaration. Other QueuedDownload instantiations keep their
existing allocator configuration. This is a TU-scoped split, not a shared
header or a replacement STL implementation.

The parent's handler00C3FD31 loads FuncInfo00E2F838, whose three-state unwind
map identifies actions00C3FD10(state0,-1),00C3FD1B(state1,0), and00C3FD26
(state2,1). The first two11-byte actions reload saved receiver[ebp-10], add
10/14 respectively and tail-jump through0003B304 ->0005EEA0, the canonical
wide-string destructor. Their compiler labels are selected from the new
native parent's state map, not from byte similarity or adjacency. The third
existing generated action remains separate pending its own recovery.

New native COFF unwind states are (-1,$L33922),(0,$L33923),(1,$L33924);
these match the retail toState sequence exactly. Existing first two action
rows move to $L33922/$L33923 with their parent. The source includes the
canonical declarations; no duplicate class or guessed callee ABI is added.
