CXX = clang++

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
# -DWITH_LIBMV_GUARDED_ALLOC\

LDFLAGS := $(LDDIR) 

ifeq "$(CXX)" "clang++"
	LDFLAGS += -stdlib=libc++ -lc++abi
else
	LDFLAGS += -lc++ -lc++abi
endif

BUILD_DIR = build
PROGRAMS = libmv.so mvtest
all:build_dir $(PROGRAMS)

BASE_OBJECTS = $(patsubst libmv/base/%.cc,$(BUILD_DIR)/%.o,$(shell find libmv/base -name \*.cc|grep -v test))
NUM_OBJECTS = $(patsubst libmv/numeric/%.cc,$(BUILD_DIR)/%.o,$(shell find libmv/numeric -name \*.cc|grep -v test))
SP_OBJECTS = $(patsubst libmv/simple_pipeline/%.cc,$(BUILD_DIR)/%.o,$(shell find libmv/simple_pipeline -name \*.cc|grep -v test))
IMG_OBJECTS = $(patsubst libmv/image/%.cc,$(BUILD_DIR)/%.o,$(shell find libmv/image -name \*.cc|grep -v test))
TR_OBJECTS = $(patsubst libmv/tracking/%.cc,$(BUILD_DIR)/%.o,$(shell find libmv/tracking -name \*.cc|grep -v test))
MV_OBJECTS = $(patsubst libmv/multiview/%.cc,$(BUILD_DIR)/%.o,$(shell find libmv/multiview -name \*.cc|grep -v test))
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
	$(CXX) -shared $(CXXFLAGS)  -o $@ $^ $(LDFLAGS)


mvtest: $(PROGRMS) $(BUILD_DIR)/mvtest.o
	$(CXX)  $(CXXFLAGS) -o $@ $^ -lmv -lgtest -lgflags -lglog -lceres $(shell pkg-config --libs opencv) $(LDFLAGS) -lpng

.PHONY: build_dir
build_dir:
	@mkdir -p $(BUILD_DIR)

clean:
	@rm -rf $(PROGRAMS) *.o $(BUILD_DIR)/*.o


recompile:clean all

.PHONY: check-syntax

check-syntax:
	$(CXX) $(CXXFLAGS) -Wall -Wextra -pedantic -fsyntax-only $(CHK_SOURCES)
