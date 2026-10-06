// Export the open program's analysis as TSV tables for tools/ghidra_refdb.py, which
// loads them into a read-only SQLite reference snapshot:
//   -postScript export_refdb.java <out_dir>
// Writes functions.tsv, xrefs.tsv, strings.tsv, data.tsv, switches.tsv, types.tsv and
// meta.tsv. Every table is written in address (or type-path) order and carries RVAs
// (VA - image base), so two runs over the same project produce identical files.
// Never run against a project an owner has open: copy it first (ghidra_refdb.py does).
//@category Export
import java.io.File;
import java.io.PrintWriter;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;
import java.util.List;

import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.address.AddressIterator;
import ghidra.program.model.data.Composite;
import ghidra.program.model.data.DataType;
import ghidra.program.model.data.DataTypeComponent;
import ghidra.program.model.data.Enum;
import ghidra.program.model.data.FunctionDefinition;
import ghidra.program.model.data.TypeDef;
import ghidra.program.model.listing.Data;
import ghidra.program.model.listing.DataIterator;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionIterator;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.InstructionIterator;
import ghidra.program.model.listing.Listing;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.ReferenceManager;
import ghidra.program.model.symbol.Symbol;

public class export_refdb extends GhidraScript {
	private long base;

	private static String esc(String s) {
		if (s == null) {
			return "";
		}
		StringBuilder b = new StringBuilder(s.length());
		for (char c : s.toCharArray()) {
			switch (c) {
				case '\\': b.append("\\\\"); break;
				case '\t': b.append("\\t"); break;
				case '\n': b.append("\\n"); break;
				case '\r': b.append("\\r"); break;
				default: b.append(c);
			}
		}
		return b.toString();
	}

	private String rva(Address a) {
		return String.format("0x%08X", a.getOffset() - base);
	}

	private PrintWriter open(File dir, String name) throws Exception {
		return new PrintWriter(new File(dir, name), StandardCharsets.UTF_8);
	}

	@Override
	public void run() throws Exception {
		String[] args = getScriptArgs();
		if (args.length != 1) {
			throw new IllegalArgumentException("usage: <out_dir>");
		}
		File dir = new File(args[0]);
		dir.mkdirs();
		base = currentProgram.getImageBase().getOffset();
		Listing listing = currentProgram.getListing();

		try (PrintWriter w = open(dir, "meta.tsv")) {
			w.println("program\t" + esc(currentProgram.getName()));
			w.println("executable_sha256\t" + esc(currentProgram.getExecutableSHA256()));
			w.println("executable_path\t" + esc(currentProgram.getExecutablePath()));
			w.println(String.format("image_base\t0x%08X", base));
			w.println("language\t" + esc(currentProgram.getLanguageID().toString()));
		}

		try (PrintWriter w = open(dir, "functions.tsv")) {
			FunctionIterator it = currentProgram.getFunctionManager().getFunctions(true);
			while (it.hasNext() && !monitor.isCancelled()) {
				Function f = it.next();
				Address entry = f.getEntryPoint();
				Address end = f.getBody().getMaxAddress();
				w.println(rva(entry) + "\t" + f.getBody().getNumAddresses() + "\t"
					+ (end == null ? "" : rva(end)) + "\t" + f.getBody().getNumAddressRanges() + "\t"
					+ esc(f.getName(true)) + "\t" + f.getSymbol().getSource() + "\t"
					+ (f.isThunk() ? 1 : 0) + "\t" + esc(f.getCallingConventionName()) + "\t"
					+ esc(f.getSignature().getPrototypeString()));
			}
		}

		ReferenceManager rm = currentProgram.getReferenceManager();
		try (PrintWriter w = open(dir, "xrefs.tsv")) {
			AddressIterator it = rm.getReferenceSourceIterator(currentProgram.getMinAddress(), true);
			while (it.hasNext() && !monitor.isCancelled()) {
				Address from = it.next();
				if (!from.isMemoryAddress()) {
					continue;
				}
				Function owner = currentProgram.getFunctionManager().getFunctionContaining(from);
				List<String> rows = new ArrayList<>();
				for (Reference r : rm.getReferencesFrom(from)) {
					Address to = r.getToAddress();
					if (!to.isMemoryAddress()) {
						continue;
					}
					rows.add(rva(from) + "\t" + rva(to) + "\t" + r.getReferenceType() + "\t"
						+ r.getOperandIndex() + "\t" + (owner == null ? "" : rva(owner.getEntryPoint())));
				}
				Collections.sort(rows);
				for (String row : rows) {
					w.println(row);
				}
			}
		}

		try (PrintWriter strings = open(dir, "strings.tsv");
				PrintWriter data = open(dir, "data.tsv")) {
			DataIterator it = listing.getDefinedData(true);
			while (it.hasNext() && !monitor.isCancelled()) {
				Data d = it.next();
				Symbol label = d.getPrimarySymbol();
				String type = d.getDataType().getPathName();
				if (d.hasStringValue()) {
					Object value = d.getValue();
					strings.println(rva(d.getAddress()) + "\t" + d.getLength() + "\t" + esc(type) + "\t"
						+ esc(value == null ? "" : value.toString()));
				}
				data.println(rva(d.getAddress()) + "\t" + d.getLength() + "\t" + esc(type) + "\t"
					+ esc(label == null ? "" : label.getName(true)));
			}
		}

		try (PrintWriter w = open(dir, "switches.tsv")) {
			InstructionIterator it = listing.getInstructions(true);
			while (it.hasNext() && !monitor.isCancelled()) {
				Instruction ins = it.next();
				if (!ins.getFlowType().isComputed() || !ins.getFlowType().isJump()) {
					continue;
				}
				Address[] flows = ins.getFlows();
				if (flows == null || flows.length == 0) {
					continue;
				}
				Function owner = currentProgram.getFunctionManager().getFunctionContaining(ins.getAddress());
				// getFlows() follows the jump table in table order: that order is the case index.
				for (int i = 0; i < flows.length; i++) {
					w.println((owner == null ? "" : rva(owner.getEntryPoint())) + "\t"
						+ rva(ins.getAddress()) + "\t" + i + "\t" + rva(flows[i]));
				}
			}
		}

		try (PrintWriter w = open(dir, "types.tsv")) {
			List<String> rows = new ArrayList<>();
			Iterator<DataType> it = currentProgram.getDataTypeManager().getAllDataTypes();
			while (it.hasNext()) {
				DataType t = it.next();
				String path = esc(t.getPathName());
				String kind = t instanceof Composite ? (t instanceof ghidra.program.model.data.Union ? "union" : "struct")
					: t instanceof Enum ? "enum" : t instanceof TypeDef ? "typedef"
					: t instanceof FunctionDefinition ? "function" : "other";
				String detail = t instanceof TypeDef ? esc(((TypeDef) t).getDataType().getPathName())
					: t instanceof FunctionDefinition ? esc(((FunctionDefinition) t).getPrototypeString()) : "";
				rows.add(path + "\t\t" + kind + "\t" + t.getLength() + "\t\t\t" + detail);
				if (t instanceof Composite) {
					for (DataTypeComponent c : ((Composite) t).getDefinedComponents()) {
						rows.add(path + "\t" + String.format("%08d", c.getOffset()) + "\tmember\t" + c.getLength()
							+ "\t" + esc(c.getFieldName()) + "\t" + esc(c.getDataType().getPathName()) + "\t");
					}
				} else if (t instanceof Enum) {
					Enum e = (Enum) t;
					for (String name : e.getNames()) {
						rows.add(path + "\t" + String.format("%020d", e.getValue(name)) + "\tvalue\t"
							+ e.getLength() + "\t" + esc(name) + "\t\t");
					}
				}
			}
			Collections.sort(rows);
			for (String row : rows) {
				w.println(row);
			}
		}
	}
}
