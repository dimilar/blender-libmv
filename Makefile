CXX = clang++

ARCH := core-avx2

STD  := c++11

ifdef debug
    OPT_FLAGS := -g3
else
    OPT_FLAGS := -O3    
endif

INCDIR := -I. -I/scratch/progs/llvm/include/c++/v1 -I/usr/include/eigen3\
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
-I../../intern/guardedalloc

LDDIR  := -L /scratch/progs/llvm/lib

CXXFLAGS := $(OPT_FLAGS) -std=$(STD) -fopenmp -march=$(ARCH) -Wall -fPIC -DLINUX $(INCDIR) \
	-DWITH_LIBMV\
	-DWITH_LIBMV_GUARDED_ALLOC\
	-DGOOGLE_GLOG_DLL_DECL=\
	-DLIBMV_NO_FAST_DETECTOR=

LDFLAGS := $(LDDIR) -stdlib=libc++  -lc++abi

BUILD_DIR = build
PROGRAMS = libmv.so
all:$(PROGRAMS)

BASE_OBJECTS = $(patsubst libmv/base/%.cc,$(BUILD_DIR)/%.o,$(shell find libmv/base -name \*.cc))
NUM_OBJECTS = $(patsubst libmv/numeric/%.cc,$(BUILD_DIR)/%.o,$(shell find libmv/numeric -name \*.cc))
SP_OBJECTS = $(patsubst libmv/simple_pipeline/%.cc,$(BUILD_DIR)/%.o,$(shell find libmv/simple_pipeline -name \*.cc))
IMG_OBJECTS = $(patsubst libmv/image/%.cc,$(BUILD_DIR)/%.o,$(shell find libmv/image -name \*.cc))
TR_OBJECTS = $(patsubst libmv/tracking/%.cc,$(BUILD_DIR)/%.o,$(shell find libmv/tracking -name \*.cc))
MV_OBJECTS = $(patsubst libmv/multiview/%.cc,$(BUILD_DIR)/%.o,$(shell find libmv/multiview -name \*.cc))
CAPI_OBJECTS = $(patsubst %.cc,$(BUILD_DIR)/%.o,$(wildcard *.cc))

$(BASE_OBJECTS): $(BUILD_DIR)/%.o: libmv/base/%.cc
	$(CXX) -c $(CXXFLAGS) $< -o $@
$(IM_OBJECTS): $(BUILD_DIR)/%.o: libmv/image/%.cc
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
$(PROGRAMS): $(BASE_OBJECTS) $(IM_OBJECTS) $(TR_OBJECTS) $(MV_OBJECTS) $(NUM_OBJECTS) $(SP_OBJECTS) $(CAPI_OBJECTS)
	$(CXX) -shared $(CXXFLAGS)  -o $@ $^ $(LDFLAGS)

clean:
	@rm -rf $(PROGRAMS) *.o

recompile:clean all

.PHONY: check-syntax

check-syntax:
	$(CXX) $(CXXFLAGS) -Wall -Wextra -pedantic -fsyntax-only $(CHK_SOURCES)
