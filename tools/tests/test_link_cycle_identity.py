"""Canonical COFF identity and receipt regression cases adapted from BFME2 02518d74b1."""
import sys
import struct
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import link_cycle as lc

TEXT, RDATA, ANON = 0x60500020, 0x40300040, "?A0x{}"


def emit(secs, syms, order=None, stamp=0, anon="218df5bc", shuffle=False):
    """A COFF object as cl writes one: a section definition (with its aux: COMDAT
    selection and parent) for each section in file `order`, its own symbols after
    it (a COMDAT's leader first), then the undefined names (reversed if `shuffle`,
    which also reverses each section's relocation records). secs: dicts name,
    flags, body, sel, assoc (logical index), relocs [(site, target, type)], target
    a symbol name or ("sec", logical index); syms: dicts name, sec (logical index,
    or 0 undefined), value, cls, weak (default's name). "{}" in names and bodies
    takes the anonymous namespace's hash."""
    order = list(range(len(secs))) if order is None else order
    fileno = {k: n + 1 for n, k in enumerate(order)}
    A = ANON.format(anon)
    strings = bytearray()

    def field(n):
        raw = n.replace("{}", A).encode("latin-1")
        if len(raw) <= 8:
            return raw.ljust(8, b"\0")
        strings.extend(raw + b"\0")
        return struct.pack("<II", 0, 4 + len(strings) - len(raw) - 1)
    table, index = [], {}                     # [(name, secno, value, cls, aux: bytes / weak default / None)]
    for k in order:
        s = secs[k]
        index[("sec", k)] = len(table)
        table.append((s["name"], fileno[k], 0, lc.STATIC,
                      struct.pack("<IHHIHBBH", len(s["body"]), len(s.get("relocs", ())), 0, 0,
                                  fileno[s["assoc"]] if s.get("assoc") is not None else 0, s.get("sel", 0), 0, 0)))
        for y in syms:
            if y.get("sec") == k:
                index[y["name"]] = len(table)
                table.append((y["name"], fileno[k], y.get("value", 0), y.get("cls", lc.EXTERNAL), None))
    rest = [y for y in syms if y.get("sec") is None]
    for y in reversed(rest) if shuffle else rest:
        index[y["name"]] = len(table)
        table.append((y["name"], 0, 0, y.get("cls", lc.EXTERNAL), y.get("weak")))
    raw_index, at = [], 0
    for t in table:
        raw_index.append(at)
        at += 2 if t[4] else 1
    real = {key: raw_index[v] for key, v in index.items()}
    symtab = bytearray()
    for name, sec, val, cls, aux in table:
        if isinstance(aux, str):
            aux = struct.pack("<II", real[aux], 3).ljust(18, b"\0")
        symtab += field(name) + struct.pack("<IhHBB", val, sec, 0x20 if sec > 0 else 0, cls, 1 if aux else 0)
        symtab += aux or b""
    hdr_end = 20 + 40 * len(order)
    shdr, bodies = bytearray(), bytearray()
    for k in order:
        s = secs[k]
        body = s["body"].replace(b"{}", A.encode()) if isinstance(s["body"], bytes) else s["body"]
        ptr = hdr_end + len(bodies)
        bodies += body
        relocs = list(s.get("relocs", ()))
        relocs = relocs[::-1] if shuffle else relocs
        rptr = hdr_end + len(bodies) if relocs else 0
        for va, target, ty in relocs:
            bodies += struct.pack("<IIH", va, real[target], ty)
        shdr += field(s["name"]) + struct.pack("<IIIIIIHHI", 0, 0, len(body), ptr if body else 0, rptr, 0,
                                               len(relocs), 0, s["flags"])
    return (struct.pack("<HHIIIHH", 0x14C, len(order), stamp, hdr_end + len(bodies), len(symtab) // 18, 0, 0)
            + shdr + bodies + symtab + struct.pack("<I", 4 + len(strings)) + strings)


def canon(raw):
    return lc.canonical_identity(lc.parse_coff(raw) + (raw,))


def ident(raw):
    return lc.object_identity(lc.parse_coff(raw) + (raw,))


def thunk_object():
    """Two adjustor thunks (COMDATs cl permutes), each with an associative .rdata,
    a .text holding a call through an anonymous-namespace function, RTTI-like
    bytes naming it, and a weak external."""
    C = lc.COMDAT
    secs = [dict(name=".drectve", flags=0x100A00, body=b"/DEFAULTLIB:LIBC "),
            dict(name=".text", flags=TEXT, body=b"\xe8\0\0\0\0\xc3", relocs=[(1, "?f@{}@@YAXXZ", lc.REL32)]),
            dict(name=".text", flags=TEXT | C, sel=2, body=b"\x83\xe9\x04\xe9\0\0\0\0",
                 relocs=[(4, "??_GA@@UAEPAXI@Z", lc.REL32)]),
            dict(name=".text", flags=TEXT | C, sel=2, body=b"\x83\xe9\x08\xe9\0\0\0\0",
                 relocs=[(4, "??_GB@@UAEPAXI@Z", lc.REL32)]),
            dict(name=".rdata", flags=RDATA | C, sel=5, assoc=2, body=b"\0\0\0\0", relocs=[(0, ("sec", 2), 6)]),
            dict(name=".rdata", flags=RDATA | C, sel=5, assoc=3, body=b"\0\0\0\0", relocs=[(0, ("sec", 3), 6)]),
            dict(name=".data", flags=0xC0300040, body=b".?AVV@{}@@\0\0\0\0\0\0",
                 relocs=[(12, "?f@{}@@YAXXZ", 6), (16, "_weak", 6)]),
            dict(name=".text", flags=TEXT | C, sel=2, body=b"\xc3")]
    syms = [dict(name="_main", sec=1), dict(name="$L1", sec=1, value=5, cls=lc.STATIC),
            dict(name="??_EA@@W3AEPAXI@Z", sec=2), dict(name="??_EB@@W7AEPAXI@Z", sec=3),
            dict(name="_vt", sec=6), dict(name="?f@{}@@YAXXZ", sec=7, cls=lc.STATIC),
            dict(name="??_GA@@UAEPAXI@Z"), dict(name="??_GB@@UAEPAXI@Z"), dict(name="_dflt"),
            dict(name="_weak", cls=lc.WEAK, weak="_dflt")]
    return secs, syms


def test_canonical_identity_drops_what_two_compiles_of_one_tu_vary_in():
    """Research lc-repro-bfme2: 20 of 18,301 objects of two exports of one tree
    differed by anonymous-namespace hash (4), relocation symbol indices (6) and
    permuted adjustor-thunk COMDATs (10). Each, and all together, compare equal."""
    secs, syms = thunk_object()
    base = emit(secs, syms)
    variants = {"time stamp": emit(secs, syms, stamp=0x5F00AA11),
                "anonymous-namespace hash": emit(secs, syms, anon="6a92f4f5"),
                "symbol and relocation order": emit(secs, syms, shuffle=True),
                "COMDAT numbering": emit(secs, syms, order=[0, 1, 3, 2, 5, 4, 6, 7]),
                "all of them": emit(secs, syms, order=[0, 1, 7, 3, 2, 6, 5, 4], anon="c4c9395d", shuffle=True,
                                    stamp=7)}
    for why, raw in variants.items():
        assert canon(raw) == canon(base), why
        if why != "time stamp":
            assert ident(raw) != ident(base), why          # what object_identity (core_sha256) refuses


def test_canonical_identity_binds_code_relocations_and_bindings():
    """No over-acceptance: every change the linker or the image would see moves
    the canonical identity."""
    import copy
    secs, syms = thunk_object()
    base = canon(emit(secs, syms))

    def mutated(f, **kw):
        s, y = copy.deepcopy(secs), copy.deepcopy(syms)
        f(s, y)
        return canon(emit(s, y, **kw))

    def sym(y, name):
        return next(x for x in y if x["name"] == name)
    mutations = {
        "code byte": lambda s, y: s[2].update(body=b"\x83\xe9\x08\xe9\0\0\0\0"),
        "thunk bodies swapped between leaders": lambda s, y: (
            s[2].update(body=secs[3]["body"], relocs=secs[3]["relocs"]),
            s[3].update(body=secs[2]["body"], relocs=secs[2]["relocs"])),
        "data byte": lambda s, y: s[6].update(body=b".?AVW@{}@@\0\0\0\0\0\0"),
        "relocation target (another symbol)": lambda s, y: s[2].update(relocs=[(4, "??_GB@@UAEPAXI@Z", lc.REL32)]),
        "relocation target (another section)": lambda s, y: s[4].update(relocs=[(0, ("sec", 3), 6)]),
        "relocation site": lambda s, y: s[1].update(relocs=[(0, "?f@{}@@YAXXZ", lc.REL32)]),
        "relocation type": lambda s, y: s[1].update(relocs=[(1, "?f@{}@@YAXXZ", 6)]),
        "relocation dropped": lambda s, y: s[6].update(relocs=s[6]["relocs"][:1]),
        "binding external -> static": lambda s, y: sym(y, "_main").update(cls=lc.STATIC),
        "binding static -> external": lambda s, y: sym(y, "?f@{}@@YAXXZ").update(cls=lc.EXTERNAL),
        "symbol value": lambda s, y: sym(y, "$L1").update(value=4),
        "symbol section": lambda s, y: sym(y, "_vt").update(sec=1),
        "symbol renamed": lambda s, y: sym(y, "??_EA@@W3AEPAXI@Z").update(name="??_EA@@W7AEPAXI@Z"),
        "COMDAT selection": lambda s, y: s[2].update(sel=1),
        "associative parent": lambda s, y: s[4].update(assoc=3),
        "weak external default": lambda s, y: sym(y, "_weak").update(weak="??_GA@@UAEPAXI@Z"),
        "section flags": lambda s, y: s[1].update(flags=TEXT | 0x2000),
        "directive": lambda s, y: s[0].update(body=b"/DEFAULTLIB:LIBCMT "),
    }
    for why, f in mutations.items():
        assert mutated(f) != base, why
        assert mutated(f, order=[0, 1, 3, 2, 5, 4, 6, 7], shuffle=True, anon="6a92f4f5") != base, why


def test_canonical_identity_keeps_plain_section_order_and_mixed_anonymous_hashes():
    secs = [dict(name=".text", flags=TEXT, body=b"\x90\xc3"), dict(name=".text", flags=TEXT, body=b"\xcc\xc3")]
    syms = [dict(name="_a", sec=0), dict(name="_b", sec=1)]
    # two non-COMDAT .text sections link in object order: swapping them is a different object
    assert canon(emit(secs, syms)) != canon(emit(secs, syms, order=[1, 0]))
    # one hash is renamed; two different ones in one object are not taken for one
    one = [dict(name=".text", flags=TEXT, body=b"?A0x218df5bc\0")]
    two = [dict(name=".text", flags=TEXT, body=b"?A0x6a92f4f5\0")]
    named = [dict(name="?f@?A0x218df5bc@@YAXXZ", sec=0)]
    assert canon(emit(one, named)) != canon(emit(two, named))
    assert canon(emit(one, named)) == canon(emit(two, [dict(name="?f@?A0x6a92f4f5@@YAXXZ", sec=0)]))


def test_receipt_canon_core_replaces_the_object_digests_only():
    r = {"rules": "link-cycle-2", "commit": "c", "series": {"credit_unique_bytes": 5}, "objects_digest": "o1",
         "provenance_sha256": "p1", "canon_rules": lc.CANON_RULES, "objects_canon_digest": "k",
         "provenance_canon_sha256": "q"}
    other_builder = dict(r, objects_digest="o2", provenance_sha256="p2")
    lc.stamp_cores(r)
    lc.stamp_cores(other_builder)
    assert r["core_sha256"] != other_builder["core_sha256"]
    assert r["core_canon_sha256"] == other_builder["core_canon_sha256"]
    for k, v in (("objects_canon_digest", "k2"), ("provenance_canon_sha256", "q2"), ("series", {})):
        moved = dict(r, **{k: v})
        lc.stamp_cores(moved)
        assert moved["core_canon_sha256"] != r["core_canon_sha256"], k
    old = {"rules": "link-cycle-2", "objects_digest": "o1"}            # a receipt from before: no canon core
    lc.stamp_cores(old)
    assert "core_canon_sha256" not in old



def test_text_digests_ignore_the_hosts_line_endings(tmp_path):
    """git archive writes text with the host's core.autocrlf endings: two builders
    of one commit must bind one tool digest and one ledger digest."""
    (tmp_path / "crlf.py").write_bytes(b"a = 1\r\nb = 2\r\n")
    (tmp_path / "lf.py").write_bytes(b"a = 1\nb = 2\n")
    (tmp_path / "other.py").write_bytes(b"a = 1\nb = 3\n")
    assert lc.text_sha256(tmp_path / "crlf.py") == lc.text_sha256(tmp_path / "lf.py")
    assert lc.text_sha256(tmp_path / "other.py") != lc.text_sha256(tmp_path / "lf.py")


# ---- shadow rule data-fold-1: export-proven read-only data folds ---------------------------
LIT, NULLCHR = "??_C@_00CNPNBAHC@?$AA@", "?TheNullChr@?1??str@?$StringBase@D@@QBEPBDXZ@4DB"
RO, RW = 0x40300040, 0xC0300040                                        # object .rdata / .data section flags
# image section characteristics: the linked image's, and retail's (whose .text and .rdata headers say writable)


def test_context_binds_all_data_and_relocation_inputs(tmp_path):
    import link_cycle_context as ctx
    reverse = tmp_path / "targets/game/reverse"
    reverse.mkdir(parents=True)
    for name in ("functions.csv", "symbols.csv", "data_rows.csv", "dir32_addresses.csv", "imports.csv"):
        (reverse / name).write_text("header\nold\n")
    derived = tmp_path / "build/reloc_ledger"
    derived.mkdir(parents=True)
    (derived / "ledger.csv").write_text("site_va,kind\n0x401000,DIR32\n")
    before = ctx.input_hashes(tmp_path)
    assert before["targets/game/reverse/exports.csv"] is None
    for path in (reverse / "data_rows.csv", reverse / "dir32_addresses.csv", derived / "ledger.csv"):
        old = path.read_bytes()
        path.write_bytes(old + b"change\n")
        changed = ctx.input_hashes(tmp_path)
        assert changed != before
        path.write_bytes(old)
        assert ctx.input_hashes(tmp_path) == before
    (derived / "items.csv").write_text("new evidence\n")
    assert ctx.input_hashes(tmp_path) != before


def test_tool_digest_covers_subprocess_helpers_and_normalizes_text(tmp_path):
    import link_cycle_context as ctx
    tools = tmp_path / "tools"
    tools.mkdir()
    for name in ("build.py", "dump_apply.py", "dump_relocs.py", "reloc_ledger.py", "new_dynamic_helper.py"):
        (tools / name).write_bytes(b"# helper\r\n")
    before = ctx.tool_dependencies(tmp_path)
    assert set(before) >= {"build.py", "dump_apply.py", "dump_relocs.py", "reloc_ledger.py", "link_cycle_context.py"}
    (tools / "dump_apply.py").write_bytes(b"# helper\n")
    assert ctx.tool_dependencies(tmp_path) == before
    (tools / "new_dynamic_helper.py").write_text("# changed\n")
    assert ctx.tool_dependencies(tmp_path) != before
    driver = tmp_path / "active_driver.py"
    driver.write_text("# the actual running driver\n")
    assert ctx.tool_dependencies(tmp_path, driver)["link_cycle.py"] == ctx.text_sha256(driver)


def test_profile_or_rule_provider_change_breaks_compatibility(monkeypatch):
    import link_cycle_context as ctx
    deps = {"link_cycle.py": "a", "link_census.py": "b"}
    before = ctx.rule_identity(deps)
    assert before["id"] != "link-cycle-2"
    assert ctx.rule_identity(dict(deps, **{"link_census.py": "changed"})) != before
    monkeypatch.setattr(ctx, "PROFILE", dict(ctx.PROFILE, credit="different"))
    assert ctx.rule_identity(deps) != before


def test_instance_identity_is_distinct_from_reproducible_core(tmp_path):
    import copy
    import json
    r = {"commit": "a" * 40, "rules": lc.RULES, "series": {"credit_unique_bytes": 10}}
    first = lc.write_receipt(tmp_path, copy.deepcopy(r))
    archived = tmp_path / "measurements" / first["tag"] / "receipt.json"
    original = archived.read_bytes()
    second = lc.write_receipt(tmp_path, copy.deepcopy(r))
    assert first["tag"] != second["tag"]
    assert first["receipt_sha256"] != second["receipt_sha256"]
    assert first["core_sha256"] == second["core_sha256"]
    assert archived.read_bytes() == original
    assert lc.sha256(archived) == first["receipt_sha256"]
    assert json.loads((tmp_path / "receipt.json.identity.json").read_text()) == second


def test_core_binds_graph_rule_profile_environment_and_data_inputs():
    r = {"rules": lc.RULES, "rule_identity": {"id": lc.RULES, "profile_sha256": "old"},
         "closure_graph_sha256": "g", "inputs": {"data_rows.csv": "old"}, "measure_env": {"capstone": "5"}}
    old = lc.digest_of(lc.receipt_core(r))
    for key, value in (("rule_identity", {}), ("closure_graph_sha256", "new"),
                       ("inputs", {"data_rows.csv": "new"}), ("measure_env", {"capstone": "6"})):
        assert lc.digest_of(lc.receipt_core(dict(r, **{key: value}))) != old


def test_bfme1_wrong_retail_copy_still_charges_despite_proven_kept_copy():
    # BFME2 retail-truth-4 can exempt a discarded wrong copy here. BFME1 must charge it.
    copies = [("kept.obj", "right", "retail"), ("loser.obj", "wrong", "wrong")]
    loses, rule = lc.census.keep_rule(copies)
    assert rule == "retail"
    assert loses == {"kept.obj": False, "loser.obj": True}
    assert lc.RULES == "bfme1-link-cycle-1"


def test_provenance_uses_bfme1_current_object_owner_and_canonical_identity(tmp_path, monkeypatch):
    import json
    source, obj = tmp_path / "game/a.cpp", tmp_path / "build/a.obj"
    source.parent.mkdir()
    obj.parent.mkdir()
    source.write_text("void f() {}\n")
    lc.write_coff(obj, [(".text", TEXT, b"\xc3", 0)], [("_f", 1, 0, lc.EXTERNAL)])
    obj.with_suffix(".deps.json").write_text('{"command": "synthetic"}')
    monkeypatch.setattr(lc, "ROOT", tmp_path)
    monkeypatch.setattr(lc.census, "_object_sources", lambda rows: {obj: source})
    calls = []

    def current(src, path, **kw):
        calls.append((src, path, kw))
        return True
    monkeypatch.setattr(lc.build, "compile_is_current", current)
    out = tmp_path / "out"
    out.mkdir()
    digest, proofs, canon = lc.provenance([], [obj], lc.Objects([obj]), out)
    record = json.loads((out / "provenance.json").read_text())["build/a.obj"]
    assert calls and proofs == {"deps": 1}
    assert record["object_canon"] and canon["objects_canon_digest"]
    assert digest == lc.sha256(out / "provenance.json")
    # A COFF symbol-type mutation is invisible to the older identity but bound
    # by the canonical one. Unchanged compile receipts must not excuse it.
    import pytest
    raw = bytearray(obj.read_bytes())
    table = struct.unpack_from("<I", raw, 8)[0]
    raw[table + 14] ^= 0x20
    obj.write_bytes(raw)
    with pytest.raises(SystemExit, match="changed with no compile"):
        lc.provenance([], [obj], lc.Objects([obj]), out)
    monkeypatch.setattr(lc.build, "compile_is_current", lambda *a, **kw: False)
    with pytest.raises(SystemExit, match="not current"):
        lc.provenance([], [obj], lc.Objects([obj]), out)


def test_dirty_refusal_and_explicit_flag_are_bound(tmp_path, monkeypatch):
    import subprocess
    import link_cycle_context as ctx
    reverse = tmp_path / "targets/game/reverse"
    reverse.mkdir(parents=True)
    (reverse / "data_rows.csv").write_text("data\n")
    compiler = tmp_path / "toolchain/Vc7/bin"
    compiler.mkdir(parents=True)
    for name in ("cl.exe", "link.exe", "lib.exe"):
        (compiler / name).write_bytes(b"synthetic compiler")
    libraries = compiler.parent / "lib"
    libraries.mkdir()
    for name in ("msvcrt.lib", "oldnames.lib"):
        (libraries / name).write_bytes(b"synthetic runtime")
    monkeypatch.setattr(lc, "ROOT", tmp_path)
    monkeypatch.setattr(lc, "git", lambda *a, **kw: "dirty" if a[0] == "status" else "a" * 40)
    monkeypatch.setattr(lc.subprocess, "run", lambda *a, **kw: subprocess.CompletedProcess(a, 0, b"", b""))
    monkeypatch.setattr(lc.build, "vc71_root", lambda: compiler.parents[1])
    monkeypatch.setattr(ctx, "tool_dependencies", lambda *a: {"build.py": "synthetic"})
    monkeypatch.setattr(ctx, "target_identity", lambda p: {"sha256": "target", "image_base": lc.BASE, "machine": 0x14C})
    monkeypatch.setattr(lc, "measure_env", lambda: {"python": "synthetic"})
    import pytest
    with pytest.raises(SystemExit, match="dirty tree"):
        lc.input_state()
    assert lc.input_state(final=True)["dirty"] is True
    state = lc.input_state(allow_dirty=True)
    assert state["dirty"] is True and state["allow_dirty"] is True
    assert state["rule_identity"]["id"] == ctx.RULES
    assert state["target"]["sha256"] == state["retail_sha256"] == "target"
    assert state["inputs"]["targets/game/reverse/data_rows.csv"]
    assert set(state["runtime_libraries_sha256"]) == {"Vc7/lib/msvcrt.lib", "Vc7/lib/oldnames.lib"}
    (libraries / "msvcrt.lib").write_bytes(b"changed runtime")
    changed = lc.input_state(allow_dirty=True)
    assert state["runtime_libraries_sha256"] != changed["runtime_libraries_sha256"]
    assert lc.receipt_core(state) != lc.receipt_core(changed)


def test_archival_refuses_artifacts_that_changed_after_measurement(tmp_path):
    import pytest
    graph = tmp_path / lc.CLOSURE_GRAPH
    graph.write_bytes(b"old graph")
    receipt = {"commit": "a" * 40, "rules": lc.RULES, "closure_graph_sha256": lc.sha256(graph)}
    graph.write_bytes(b"different graph")
    with pytest.raises(SystemExit, match="moved before archival"):
        lc.write_receipt(tmp_path, receipt)
    assert not (tmp_path / "receipt.json").exists()


def test_remeasurement_preserves_original_receipt_and_artifacts(tmp_path, monkeypatch):
    import json
    import types
    out = tmp_path / "run"
    out.mkdir()
    originals = {"receipt.json": b'{"rules":"link-cycle-2"}', "link_status.csv": b"original status\n",
                 lc.CLOSURE_GRAPH: b"original graph"}
    for name, raw in originals.items():
        (out / name).write_bytes(raw)
    reverse = tmp_path / "reverse"
    reverse.mkdir()
    (reverse / "ghidra_functions.csv").write_text("rva\n")
    monkeypatch.setattr(lc, "REVERSE", reverse)
    monkeypatch.setattr(lc, "input_state", lambda *a, **kw: {"commit": "a" * 40})
    monkeypatch.setattr(lc.census, "ledger", lambda: [])
    monkeypatch.setattr(lc.census, "objects", lambda rows: ([], []))
    monkeypatch.setattr(lc, "analyze", lambda *a: ([], {}))
    monkeypatch.setattr(lc, "pe_view", lambda *a: (None, b"", {".text": (0x1000, 16)}, {}))
    monkeypatch.setattr(lc, "load_pins", lambda: ({}, {}))
    monkeypatch.setattr(lc, "plan_order", lambda *a: ([], {}, {}))
    monkeypatch.setattr(lc, "filler_chunks", lambda *a: [])

    def provenance(rows, present, objs, destination, **kwargs):
        (destination / "provenance.json").write_text("{}")
        return lc.sha256(destination / "provenance.json"), {}, {}

    def measure(*args, artifact_out):
        assert artifact_out != out
        (artifact_out / lc.CLOSURE_GRAPH).write_bytes(b"diagnostic graph")
        (artifact_out / "link_status.csv").write_bytes(b"diagnostic status\n")
        return {"credit_unique_bytes": 0, "closure_graph_sha256": lc.sha256(artifact_out / lc.CLOSURE_GRAPH),
                "link_status_sha256": lc.sha256(artifact_out / "link_status.csv")}
    monkeypatch.setattr(lc, "provenance", provenance)
    monkeypatch.setattr(lc, "measure", measure)
    args = types.SimpleNamespace(out=str(out), raw_dumps=True, allow_dirty=False, shift_base=lc.SHIFT_BASE)
    assert lc.remeasure(args) == 0
    for name, raw in originals.items():
        assert (out / name).read_bytes() == raw
    (diagnostic,) = (out / "remeasured").iterdir()
    receipt = json.loads((diagnostic / "receipt.json").read_text())
    assert receipt["rules"] == lc.RULES
    assert receipt["authoritative"] is False
    assert receipt["source_receipt_sha256"] == lc.sha256(out / "receipt.json")


def test_semantic_rules_ignore_unrelated_tools_but_bind_measurement_providers():
    import link_cycle_context as ctx
    deps = {name: "before" for name in ctx.MEASUREMENT_FILES}
    before = ctx.rule_identity(deps)
    unrelated = dict(deps, unrelated_fleet_tool="changed")
    assert ctx.rule_identity(unrelated) == before
    assert ctx.digest(unrelated) != ctx.digest(deps)
    for name in ctx.MEASUREMENT_FILES:
        assert ctx.rule_identity(dict(deps, **{name: "changed"})) != before, name


def test_driver_local_imports_are_declared_semantic_dependencies():
    import ast
    import link_cycle_context as ctx
    tools = Path(lc.__file__).parent
    tree = ast.parse(Path(lc.__file__).read_text())
    local = set()
    for node in ast.walk(tree):
        names = [a.name for a in node.names] if isinstance(node, ast.Import) else (
            [node.module] if isinstance(node, ast.ImportFrom) and node.module else [])
        for name in names:
            filename = name.split(".")[0] + ".py"
            if (tools / filename).is_file():
                local.add(filename)
    assert local <= set(ctx.MEASUREMENT_FILES), local - set(ctx.MEASUREMENT_FILES)


def test_clean_run_evidence_binds_both_observations_and_diagnostic_options():
    import copy
    import types
    import link_cycle_context as ctx
    start = {"commit": "a" * 40, "snapshot": False, "dirty": False}
    args = types.SimpleNamespace()
    base = dict(start, compile_failed=[], warm_start={"stale": False})
    lc.record_run_evidence(base, start, dict(start), args)
    assert base["authoritative"] is True
    assert ctx.run_authority_failure(base) is None
    original_core = lc.digest_of(lc.receipt_core(base))
    for phase in ("start", "end"):
        receipt = copy.deepcopy(base)
        receipt["checkout_" + phase]["dirty"] = True
        assert ctx.run_authority_failure(receipt) == "dirty-" + phase
        assert lc.digest_of(lc.receipt_core(receipt)) != original_core
    for flag in ctx.RUN_OPTIONS:
        receipt = copy.deepcopy(base)
        receipt["run_options"][flag] = True
        assert ctx.run_authority_failure(receipt) == "diagnostic"
        assert lc.digest_of(lc.receipt_core(receipt)) != original_core
    for flag in ("allow_dirty", "allow_stale_cache", "measure_only"):
        receipt = dict(start, compile_failed=[], warm_start={"stale": False})
        lc.record_run_evidence(receipt, start, start, types.SimpleNamespace(**{flag: True}))
        assert receipt["authoritative"] is False
    snapshot = dict(start, snapshot=True)
    receipt = dict(snapshot, compile_failed=[], warm_start={"stale": False})
    lc.record_run_evidence(receipt, snapshot, snapshot, args)
    assert receipt["authoritative"] is False
    receipt = dict(start, compile_failed=[], warm_start={"stale": False})
    lc.record_run_evidence(receipt, start, start, args, remeasure=True)
    assert receipt["authoritative"] is False
    receipt = dict(start, compile_failed=[], warm_start={"stale": False})
    lc.record_run_evidence(receipt, start, dict(start, dirty=True), args)
    assert receipt["authoritative"] is False


def test_incomplete_or_changed_run_evidence_cannot_confer_authority():
    import copy
    import types
    import link_cycle_context as ctx
    start = {"commit": "a" * 40, "snapshot": False, "dirty": False}
    base = dict(start, compile_failed=[], warm_start={"stale": False})
    lc.record_run_evidence(base, start, start, types.SimpleNamespace())
    for key in ("checkout_start", "checkout_end", "run_options", "compile_failed", "warm_start"):
        r = copy.deepcopy(base)
        del r[key]
        assert ctx.run_authority_failure(r) == "missing-evidence"
    for change, reason in (({"compile_failed": ["f.cpp"]}, "compile-failed"),
                           ({"warm_start": {"stale": True}}, "diagnostic"),
                           ({"moved_during_run": ["objects_digest"]}, "inputs-moved")):
        assert ctx.run_authority_failure(dict(base, **change)) == reason
