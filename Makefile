CXX = clang++

ARCH := core-avx2

STD  := c++11

ifdef debug
    OPT_FLAGS := -g3
else
    OPT_FLAGS := -O3 -fopenmp -fPIC
endif

INCDIR := -I. -I/usr/include/c++/v1 -I/usr/include/eigen3\
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

LDDIR  := -L/opt/intel/lib/intel64 -L/opt/intel/mkl/lib/intel64

CXXFLAGS := $(OPT_FLAGS) -std=$(STD) -fopenmp -march=$(ARCH) -Wall -fPIC -DLINUX $(INCDIR) \
	-DWITH_LIBMV\
	-DGOOGLE_GLOG_DLL_DECL=\
	-DLIBMV_NO_FAST_DETECTOR=
# -DWITH_LIBMV_GUARDED_ALLOC\

LDFLAGS := $(LDDIR) -stdlib=libc++  -lc++abi

BUILD_DIR = build
PROGRAMS = libmv.so mvtest
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
$(BUILD_DIR)/mvtest.o:demo/mvtest.cc
	$(CXX) -c $(CXXFLAGS) $< -o $@
libmv.so: $(CAPI_OBJECTS)  $(BASE_OBJECTS) $(TR_OBJECTS) $(MV_OBJECTS) $(NUM_OBJECTS) $(SP_OBJECTS) $(IMG_OBJECTS)
	$(CXX) -shared $(CXXFLAGS)  -o $@ $^ $(LDFLAGS) -stdlib=libc++ -lc++abi
mvtest:$(PROGRMS) $(BUILD_DIR)/mvtest.o
	$(CXX)  $(CXXFLAGS) -o $@ $^ -L./ -lmv -lgtest -lgflags -lglog -lspqr -Wl,-Bstatic -lsuitesparseconfig -Wl,-Bdynamic -lrt -Wl,-Bdynamic -lrt -lceres -lgflags -L/scratch/progs/libSuiteSparse/lib  -Wl,-Bstatic -lcholmod -lccolamd -lcamd -lcolamd -lamd -lsuitesparseconfig -lmetis -Wl,-Bdynamic -L/opt/intel/lib/intel64 -L/opt/intel/mkl/lib/intel64 -lmkl_intel_lp64 -lmkl_core -lmkl_intel_thread -lintlc -liomp5 -limf -L/scratch/progs/llvm/lib $(shell pkg-config --libs opencv) -stdlib=libc++ -lc++abi -lpng
clean:
	@rm -rf $(PROGRAMS) *.o $(BUILD_DIR)/*.o

recompile:clean all

.PHONY: check-syntax

check-syntax:
	$(CXX) $(CXXFLAGS) -Wall -Wextra -pedantic -fsyntax-only $(CHK_SOURCES)
