EMCC := emcc
CFLAGS := -Os -g $(CFLAGS)
LDFLAGS := -Iinclude/ $(LDFLAGS)
EMLIBFLAGS := --no-entry $(EMFLAGS)
EMRUNFLAGS := $(EMFLAGS)

OUT = out
JSOUT = jsout

# Output files.
NATIVE := $(OUT)/main.out
WASMRUN := $(OUT)/main.wasm
WASMLIB := $(OUT)/lib.wasm
JSRUN := $(JSOUT)/main.js
JSLIB := $(JSOUT)/lib.js

PROJECT_SOURCES := $(shell find . -iname 'lib.c' -exec dirname {} \;)

NATIVE_TARGETS := $(PROJECT_SOURCES:%=%/$(NATIVE))
WASM_LIB_TARGETS := $(PROJECT_SOURCES:%=%/$(WASMLIB))
WASM_RUN_TARGETS := $(PROJECT_SOURCES:%=%/$(WASMRUN))
WASM_JSRUN_TARGETS := $(PROJECT_SOURCES:%=%/$(JSRUN))
WASM_JSLIB_TARGETS := $(PROJECT_SOURCES:%=%/$(JSLIB))

.PHONY: $(PROJECT_SOURCES) all clean js native wasm clean_js clean_native

all: wasm native js

$(PROJECT_SOURCES): %: %/$(NATIVE) %/$(WASMRUN) %/$(WASMLIB) %/$(JSRUN) %/$(JSLIB)

%/$(JSOUT):
	mkdir -p $@

%/$(OUT):
	mkdir -p $@

.PRECIOUS: %/$(JSOUT) %/$(OUT)

%/$(OUT)/main.out: %/lib.c %/main.c | %/$(OUT)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

%/$(OUT)/lib.wasm: %/lib.c | %/$(OUT)
	$(EMCC) $(CFLAGS) $(LDFLAGS) $(EMLIBFLAGS) $^ -o $@

%/$(OUT)/main.wasm: %/main.c %/lib.c | %/$(OUT)
	$(EMCC) $(CFLAGS) $(LDFLAGS) $(EMRUNFLAGS) $^ -o $@

%/$(JSOUT)/lib.js: %/lib.c | %/$(JSOUT)
	$(EMCC) $(CFLAGS) $(LDFLAGS) $(EMLIBFLAGS) $^ -o $@

%/$(JSOUT)/main.js: %/main.c %/lib.c | %/$(JSOUT)
	$(EMCC) $(CFLAGS) $(LDFLAGS) $(EMRUNFLAGS) $^ -o $@

native: $(NATIVE_TARGETS)
wasm: $(WASM_LIB_TARGETS) $(WASM_RUN_TARGETS)
js: $(WASM_JSLIB_TARGETS) $(WASM_JSRUN_TARGETS)

clean_js:
	rm -vf $(WASM_JSRUN_TARGETS)
	rm -vf $(WASM_JSRUN_TARGETS:%/main.js=%/main.wasm)
	rm -vf $(WASM_JSLIB_TARGETS)
	rm -vf $(WASM_JSLIB_TARGETS:%/lib.js=%/lib.wasm)

clean_wasm:
	rm -vf $(WASM_RUN_TARGETS)
	rm -vf $(WASM_LIB_TARGETS)

clean_native:
	rm -vf $(NATIVE_TARGETS)

clean: clean_native clean_js clean_wasm
	-rmdir $(NATIVE_TARGETS:%/main.out=%)
	-rmdir $(WASM_JSRUN_TARGETS:%/main.js=%)
