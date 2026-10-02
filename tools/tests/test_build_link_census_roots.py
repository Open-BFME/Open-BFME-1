"""Root-cause checks for STLport include inventories used by link census."""
import json
import tempfile
import unittest
from pathlib import Path
from unittest.mock import patch

import sys
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build


class LinkCensusSearchRootTests(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory()
        self.addCleanup(self.temporary.cleanup)
        self.base = Path(self.temporary.name)
        self.root = self.base / "project"
        self.root.mkdir()
        self.source = self.root / "game" / "unit.cpp"
        self.source.parent.mkdir()
        self.source.write_text("#include <vector>\n")

    def test_stlport_parent_include_root_is_portable_and_exact(self):
        command = ["cl", "-I" + str(self.root)]
        with patch.object(build, "ROOT", self.root), \
                patch.object(build, "source_needs_stlport", return_value=True):
            roots = build._include_search_roots(self.source, command, {"INCLUDE": ""})
            keys = {build._root_key(root) for root in roots}
            self.assertIn("@ROOT_PARENT@/include", keys)
            self.assertNotIn("include", keys)  # no phantom source-dir/../include

            other_root = self.base / "other" / "project"
            with patch.object(build, "ROOT", other_root):
                self.assertEqual(build._root_from_key("@ROOT_PARENT@/include"),
                                 other_root.parent / "include")

            parent_include = self.base / "include"
            absent = build._directory_inventory(parent_include)
            self.assertEqual(absent, "absent")
            parent_include.mkdir()
            (parent_include / "algorithm").write_text("// a possible native-header shadow\n")
            self.assertNotEqual(build._directory_inventory(parent_include), absent)

    def test_parent_root_sidecar_stays_current_until_a_native_shadow_appears(self):
        early = self.root / "inputs" / "reference" / "shims" / "sweep"
        late = self.root / "inputs" / "reference" / "original"
        (early / "Common").mkdir(parents=True)
        (late / "Common").mkdir(parents=True)
        source = self.root / "game" / "unit.cpp"
        source.write_text('#include "Common/MessageStream.h"\n')
        original = late / "Common" / "MessageStream.h"
        original.write_text("#define PACKET_RANGE 6\n")
        output = self.root / "build" / "match" / "NetPacket.obj"
        output.parent.mkdir(parents=True)
        output.write_bytes(b"object")
        command = ["cl", "-I" + str(early), "-I" + str(late), "-I" + str(self.root)]
        env = {"INCLUDE": ""}
        with patch.object(build, "ROOT", self.root), \
                patch.object(build, "source_needs_stlport", return_value=True), \
                patch.object(build, "compiler_command", return_value=(command, env)), \
                patch.object(build, "_cmd_fingerprint", return_value="command"):
            inventory = build.search_inventory(source, command, env)
            build._write_deps_sidecar(source, output, "command",
                                      "Note: including file: " + str(original), True,
                                      command, env, inventory, [])
            self.assertTrue(build.compile_is_current(source, output))
            metadata = json.loads(build._deps_sidecar(output).read_text())
            self.assertIn("@ROOT_PARENT@/include", metadata["search_roots"])

            (self.root.parent / "sibling-checkout").mkdir()
            self.assertTrue(build.compile_is_current(source, output))
            native_include = self.root.parent / "include"
            native_include.mkdir()
            (native_include / "algorithm").write_text("// native-header shadow\n")
            self.assertFalse(build.compile_is_current(source, output))

    def test_session_metadata_is_ignored_but_checkout_headers_are_watched(self):
        (self.root / "tools").mkdir()
        with patch.object(build, "ROOT", self.root):
            before = build._directory_inventory(self.root)
            for name in (".agents", ".codex", ".aws"):
                metadata = self.root / name
                metadata.mkdir()
                (metadata / "session.h").write_text("// host metadata\n")
            bytecode = self.root / "tools" / "__pycache__"
            bytecode.mkdir(parents=True)
            (bytecode / "verification.cpython.pyc").write_bytes(b"generated cache")
            self.assertEqual(build._directory_inventory(self.root), before)
            self.assertIsNone(build._directory_inventory(bytecode))

            (self.root / "new-header.h").write_text("// possible include shadow\n")
            self.assertNotEqual(build._directory_inventory(self.root), before)

    def test_checkout_inventory_includes_root_cod_and_judgment_temp_files(self):
        with patch.object(build, "ROOT", self.root):
            before = build._directory_inventory(self.root)
            (self.root / "mission_objective.cod").write_text("assembly listing\n")
            after_cod = build._directory_inventory(self.root)
            self.assertNotEqual(after_cod, before)

            temporary = self.root / "targets" / "game" / "reverse" / "link_status.tmp"
            temporary.parent.mkdir(parents=True)
            temporary.write_text("staged judgment output\n")
            self.assertNotEqual(build._directory_inventory(self.root), after_cod)

    def test_explicit_include_from_omitted_tree_is_uncacheable(self):
        metadata = self.root / ".agents"
        metadata.mkdir()
        (metadata / "session.h").write_text("// compiler input\n")
        bytecode = self.root / "tools" / "__pycache__"
        bytecode.mkdir(parents=True)
        (bytecode / "module.h").write_text("// compiler input\n")
        with patch.object(build, "ROOT", self.root):
            for name in (".agents/session.h", "tools/__pycache__/module.h"):
                source = self.root / "game" / "explicit.cpp"
                source.write_text(f'#include "{name}"\n')
                self.assertTrue(build._include_escapes_search_roots(
                    source, False, [self.root], set()))


if __name__ == "__main__":
    unittest.main()
