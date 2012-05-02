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

all : naive_bayes
    
naive_bayes: naive_bayes_run.cpp $(SRC)/naive_bayes.cpp $(SRC)/abstract_instance.cpp $(SRC)/instance.cpp  $(SRC)/attribute.cpp $(SRC)/dataset.cpp $(SRC)/instance_container.cpp $(SRC)/attribute_container.cpp $(SRC)/special_functions.cpp $(SRC)/estimator.cpp  $(SRC)/normal_estimator.cpp $(SRC)/discrete_estimator.cpp $(SRC)/special_functions.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lm -lpthread $^ -o $@
clean :
	rm -f $(TESTS) *_unittest



