# 0048A130: TransitionGroup::getTotalFrames

The 52-byte body at 0x0048A130 was matched as the placeholder
?maxv@Rva0048A130@@QAEHXZ (Rva0048A130Max.cpp). symbols.csv pins
?getTotalFrames@TransitionGroup@@QAEHXZ at its ILT 0x00032470 (see below). The matched
TransitionGroup::init (0x0048AC10) calls that ILT and stores result + 3 in
the transition handler end frame. The body sits inside the TransitionGroup
method run (update 0x0048A080, reverse 0x0048A180) and walks this+4, the
m_transitionWindowList, returning the maximum of each TransitionWindow
m_frameDelay (+4) plus its Transition m_frameLength (+4) when present: the
ZH GameWindowTransitions.cpp TransitionGroup::getTotalFrames. It now lives in
GameWindowTransitionGroupInit.cpp with its TransitionGroup siblings.

ILT order check: tools/ilt_oracle.py rejects ?getTotalFrames@TransitionGroup
(every access/const/return variant and a dozen method spellings), while
?reverse@ and ?init@TransitionGroup at the neighbouring bodies fit. The class
is kept and the method takes the address-derived name getTotalFrames_0048A130;
the contradicted pin at ILT 0x00032470 is retired; both callers are respelled.
