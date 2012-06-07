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

all:string_utility_unittest attribute_unittest instance_unittest special_function_unittest estimator_unittest  naive_bayes_unittest
    
string_utility_unittest: string_trim_unittest.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lgmock -lgmock_main -lpthread $^ -o $@

attribute_unittest: attribute_unittest.cpp  $(PROJECT_DIR)/src/attribute.cpp $(PROJECT_DIR)/include/attribute.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lgmock -lgmock_main -lpthread $^ -o $@

instance_unittest: instance_unittest.cpp $(SRC)/abstract_instance.cpp $(SRC)/instance.cpp  $(SRC)/attribute.cpp $(SRC)/dataset.cpp $(SRC)/instance_container.cpp $(SRC)/attribute_container.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lgmock -lgmock_main -lpthread $^ -o $@

special_function_unittest: special_function_unittest.cpp $(SRC)/special_functions.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lgmock -lgmock_main -lpthread $^ -o $@

estimator_unittest: estimator_unittest.cpp $(SRC)/estimator.cpp  $(SRC)/normal_estimator.cpp $(SRC)/discrete_estimator.cpp $(SRC)/special_functions.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lgmock -lgmock_main -lpthread $^ -o $@

naive_bayes_unittest: naive_bayes_unittest.cpp $(SRC)/naive_bayes.cpp $(SRC)/abstract_instance.cpp $(SRC)/instance.cpp  $(SRC)/attribute.cpp $(SRC)/dataset.cpp $(SRC)/instance_container.cpp $(SRC)/attribute_container.cpp $(SRC)/special_functions.cpp $(SRC)/estimator.cpp  $(SRC)/binary_estimator.cpp $(SRC)/normal_estimator.cpp $(SRC)/discrete_estimator.cpp $(SRC)/special_functions.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lgmock -lgmock_main -lpthread $^ -o $@


clean :
	rm -f $(TESTS) *_unittest



