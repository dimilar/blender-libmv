CXX = clang++
CC = gcc
STD  := c++11

ifdef debug
    OPT_FLAGS := -g3
else
    OPT_FLAGS := -O3 -fopenmp -fPIC
endif

INCDIR :=\
	-I/usr/include/c++/v1\
	-I/usr/include/eigen3\
	-Ilibmv/base\
	-Ilibmv/logging\
	-Ilibmv/numeric\
	-Ilibmv/simple_pipeline\
	-Ilibmv/image\
	-Ilibmv/tracking\
	-Ilibmv/multiview\
	-I../gtest/include\
	-I../../tests/gtests\
	-Ithird\
	-I../../intern/guardedalloc\
	-I./\
	$(shell pkg-config --cflags opencv)

LDDIR  := -L/opt/intel/lib/intel64 -L/opt/intel/mkl/lib/intel64 -L./

CXXFLAGS := $(OPT_FLAGS) -std=$(STD) -fopenmp -Wall -fPIC -DLINUX $(INCDIR) \
	-DWITH_LIBMV\
	-DGOOGLE_GLOG_DLL_DECL=\
	-DLIBMV_NO_FAST_DETECTOR=
# -DWITH_LIBMV_GUARDED_ALLOC
CFLAGS = $(OPT_FLAGS) -fopenmp\
-DHAVE_STDBOOL_H -DNDEBUG -DWITH_INTERNATIONAL -D_FILE_OFFSET_BITS=64 -D_LARGEFILE64_SOURCE -D_LARGEFILE_SOURCE -D__LITTLE_ENDIAN__ -D__MMX__ -D__SSE2__ -D__SSE__ -Wall -Wcast-align -Werror=declaration-after-statement -Werror=implicit-function-declaration -Werror=return-type -Wstrict-prototypes -Wmissing-prototypes -Wno-char-subscripts -Wno-unknown-pragmas -Wpointer-arith -Wunused-parameter -Wwrite-strings -Wlogical-op -Wundef -Winit-self -Wnonnull -Wmissing-include-dirs -Wno-div-by-zero -Wtype-limits -Wuninitialized -Wredundant-decls -Wno-error=unused-but-set-variable -fopenmp -msse2 -msse -pipe -fPIC -funsigned-char -fno-strict-aliasing -Wextra -Wno-sign-conversion -fPIC -DLINUX -I./bli -I./dna -I./imbuf -I./bke -I./
LDFLAGS := $(LDDIR) 

ifeq "$(CXX)" "clang++"
	LDFLAGS += -stdlib=libc++ -lc++abi
else
	LDFLAGS += -lc++ -lc++abi
endif

BUILD_DIR = build
PROGRAMS = mvtest
all:build_dir $(PROGRAMS)

BASE_OBJECTS = $(patsubst libmv/base/%.cc,$(BUILD_DIR)/%.o,$(shell find libmv/base -name \*.cc|grep -v test))
NUM_OBJECTS = $(patsubst libmv/numeric/%.cc,$(BUILD_DIR)/%.o,$(shell find libmv/numeric -name \*.cc|grep -v test))
SP_OBJECTS = $(patsubst libmv/simple_pipeline/%.cc,$(BUILD_DIR)/%.o,$(shell find libmv/simple_pipeline -name \*.cc|grep -v test))
IMG_OBJECTS = $(patsubst libmv/image/%.cc,$(BUILD_DIR)/%.o,$(shell find libmv/image -name \*.cc|grep -v test))
TR_OBJECTS = $(patsubst libmv/tracking/%.cc,$(BUILD_DIR)/%.o,$(shell find libmv/tracking -name \*.cc|grep -v test))
MV_OBJECTS = $(patsubst libmv/multiview/%.cc,$(BUILD_DIR)/%.o,$(shell find libmv/multiview -name \*.cc|grep -v test))
CAPI_OBJECTS = $(patsubst %.cc,$(BUILD_DIR)/%.o,$(wildcard *.cc))
C_OBJECTS= $(patsubst %.c,$(BUILD_DIR)/%.o,$(wildcard *.c))
# MEM_OBJECTS= $(patsubst %.c,$(BUILD_DIR)/%.o,$(wildcard guardedalloc/intern/*.c))

$(BASE_OBJECTS): $(BUILD_DIR)/%.o: libmv/base/%.cc
	$(CXX) -c $(CXXFLAGS) $< -o $@
$(IMG_OBJECTS): $(BUILD_DIR)/%.o: libmv/image/%.cc
	$(CXX) -c $(CXXFLAGS) $< -o $@
$(TR_OBJECTS): $(BUILD_DIR)/%.o: libmv/tracking/%.cc
	$(CXX) -c $(CXXFLAGS) $< -o $@
$(MV_OBJECTS): $(BUILD_DIR)/%.o: libmv/multiview/%.cc
	$(CXX) -c $(CXXFLAGS) $< -o $@
$(NUM_OBJECTS): $(BUILD_DIR)/%.o: libmv/numeric/%.cc
	$(CXX) -c $(CXXFLAGS) $< -o $@
$(SP_OBJECTS): $(BUILD_DIR)/%.o: libmv/simple_pipeline/%.cc
	$(CXX) -c $(CXXFLAGS) $< -o $@
$(CAPI_OBJECTS):$(BUILD_DIR)/%.o: %.cc
	$(CXX) -c $(CXXFLAGS) $< -o $@
$(C_OBJECTS):$(BUILD_DIR)/%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@
$(MEM_OBJECTS):$(BUILD_DIR)/%.o: guardedalloc/intern/%.c
	$(CC) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/mvtest.o:demo/mvtest.cc
	$(CXX) -c $(CXXFLAGS) $< -o $@
libmv.so: $(CAPI_OBJECTS)  $(BASE_OBJECTS) $(TR_OBJECTS) $(MV_OBJECTS) $(NUM_OBJECTS) $(SP_OBJECTS) $(IMG_OBJECTS)
	$(CXX) -shared $(CXXFLAGS)  -o $@ $^ $(LDFLAGS)


mvtest: $(PROGRMS) $(C_OBJECTS) $(BUILD_DIR)/mvtest.o 
	$(CXX)  $(CXXFLAGS) -o $@ $^ -lmv -lgtest -lgflags -lglog -lceres $(shell pkg-config --libs opencv) $(LDFLAGS) -lpng -lz

.PHONY: build_dir
build_dir:
	@mkdir -p $(BUILD_DIR)

clean:
	@rm -rf $(PROGRAMS) $(C_OBJECTS)


recompile:clean all

.PHONY: check-syntax

check-syntax:
	$(CXX) $(CXXFLAGS) -Wall -Wextra -pedantic -fsyntax-only $(CHK_SOURCES)
