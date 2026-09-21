#!/usr/bin/env python3
"""One vocabulary for `blocker=` tags, so shared blockers can be clustered.

Workers write `blocker=NAME` in re_attempts.log evidence. NAME was free text:
on 2026-09-21 the log held 1,433 tags and the largest group was 33 bodies,
because one problem had a dozen spellings (compiler-register-schedule,
register-role-allocation, compiler-register-coloring, ...). A lane that hands
one shared problem to one stronger session cannot cluster free text.

`canonical(tag)` maps any spelling onto a small fixed family. re_log rewrites
a new tag as `blocker=<family>/<original>`, so the detail survives and the
family is greppable; old rows are never rewritten (the log is append-only) and
are classified when read. Rules are ordered: the first family whose keyword
occurs in the tag wins, so the specific families come before the broad ones.
"""
import re

FAMILIES = (
    ("no-lever", ("lever", "exhausted")),
    ("eh", ("unwind", "funclet", "exception", "eh-", "-eh", "seh", "try-", "catch", "scopetable", "trylevel")),
    ("stack-slot", ("stack", "slot", "frame", "local-order", "spill", "temporary", "temp-")),
    ("regalloc", ("register", "regalloc", "reg-", "coloring", "colouring", "callee-saved", "allocation",
                  "esi", "edi", "ebx", "ebp", "eax", "ecx", "edx")),
    ("boundary", ("boundary", "carve", "overlap", "extent", "size-mismatch", "split", "fragment")),
    ("layout", ("layout", "struct", "field", "offset", "member", "vtable", "padding", "alignment")),
    ("callee", ("callee", "call-target", "pin", "import", "thunk", "unresolved", "reloc", "symbol-missing", "ilt-")),
    ("identity", ("identity", "name", "class", "mangl", "signature", "convention", "abi", "prototype")),
    ("inline", ("inline", "inlin", "outlined", "intrinsic")),
    ("stl", ("stl", "template", "container", "allocator", "iterator", "string-class")),
    ("float", ("float", "x87", "fpu", "fp-", "double", "ftol", "sse2", "-sse")),
    ("codegen-order", ("schedul", "encoding", "order", "branch", "block", "jump", "cse", "peephole", "tail", "merge",
                       "instruction", "codegen", "select", "loop", "switch", "commut")),
    ("toolchain", ("compiler", "msvc", "flag", "pragma", "optimi", "cl-", "linker", "lto", "pgo")),
)
NAMES = tuple(name for name, _ in FAMILIES) + ("other",)
TAG = re.compile(r"(?:^|(?<=\s))blocker=(\S+)")


def canonical(tag):
    """Family of one tag. An already-canonical `family/detail` keeps its family."""
    text = tag.strip().lower()
    head = text.split("/", 1)[0]
    if head in NAMES:
        return head
    for name, keywords in FAMILIES:
        if any(word in text for word in keywords):
            return name
    return "other"


def normalise(evidence):
    """Rewrite every `blocker=x` in an evidence line as `blocker=family/x`.
    Idempotent; a tag that already names a family is left alone."""
    def swap(match):
        tag = match.group(1)
        if tag.split("/", 1)[0].lower() in NAMES:
            return match.group(0)
        return f"blocker={canonical(tag)}/{tag}"
    return TAG.sub(swap, evidence)


def families(evidence):
    """Distinct families named in one evidence line, in order of appearance."""
    return list(dict.fromkeys(canonical(tag) for tag in TAG.findall(evidence)))
