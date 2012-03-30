PROJECT_DIR = ..
GMOCK_DIR = ../external
# Where to find user code.

# Flags passed to the preprocessor.
CPPFLAGS +=  -I$(GMOCK_DIR)/include -I$(PROJECT_DIR)/include -L$(GMOCK_DIR)/lib

# Flags passed to the C++ compiler.
CXXFLAGS += -g -Wall -Wextra 

# All tests produced by this Makefile.  Remember to add new tests you
# created to the list.
# All Google Test headers
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

# All Google Mock headers
GMOCK_HEADERS = $(GMOCK_DIR)/include/gmock/*.h \
                $(GMOCK_DIR)/include/gmock/internal/*.h \
                $(GTEST_HEADERS)

# House-keeping build targets.

SRC = $(PROJECT_DIR)/src
INCLUDE = $(PROJECT_DIR)/include

all :attribute_unittest instance_unittest
    
attribute_unittest: attribute_unittest.cpp  $(PROJECT_DIR)/src/attribute.cpp $(PROJECT_DIR)/include/attribute.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lgmock -lgmock_main -lpthread $^ -o $@

instance_unittest: instance_unittest.cpp $(SRC)/instance.cpp $(SRC)/attribute.cpp $(SRC)/dataset.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lgmock -lgmock_main -lpthread $^ -o $@
clean :
	rm -f $(TESTS) *_unittest



