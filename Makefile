.PHONY: all build run test clean
.SECONDEXPANSION:
.SECONDARY:

BOOST_LOCATION := $(shell test -f .boost_location && cat .boost_location ; true)

ifneq 'yes' '$(VERBOSE)'
hidecmd := @
endif

CPPFLAGS += -Wall -Wextra -Werror -Wno-missing-field-initializers -Werror=vla \
            -Wold-style-cast $(if $(BOOST_LOCATION),-isystem $(BOOST_LOCATION))
CXXFLAGS += -g

system := $(shell uname)
TIMEOUT_CMD := $(if $(filter Darwin,$(system)),gtimeout,timeout)

ifneq 'MINGW' '$(patsubst MINGW%,MINGW,$(system))'
CXXFLAGS += -std=c++14
else
CXXFLAGS += -std=gnu++14
endif

# Source files
main_sources := $(filter-out test-%.cpp,$(wildcard *.cpp))
test_sources := $(filter-out $(main_sources),$(wildcard test-*.cpp))
headers := $(wildcard *.h *.hpp *.hxx)

# Objects
main_objects := $(patsubst %.cpp,out/%.o,$(main_sources))
test_objects := $(patsubst %.cpp,out/%.o,$(test_sources))
header_checks := $(addprefix out/,$(addsuffix .header,$(headers)))

# Targets
TARGET := out/matrix
TEST_TARGET := out/test-matrix

all: build

build: $(TARGET)

run: build
	$(hidecmd)$(if $(TIMEOUT),$(TIMEOUT_CMD) --signal=KILL $(TIMEOUT)s )$(if $(VALGRIND),valgrind $(VALGRIND) )$(TARGET) $(ARGS)

test: $(TEST_TARGET)
	$(hidecmd)$(if $(TIMEOUT),$(TIMEOUT_CMD) --signal=KILL $(TIMEOUT)s )$(if $(VALGRIND),valgrind $(VALGRIND) )$(TEST_TARGET) $(TEST_ARGS) || true

clean:
	@if [ -d out ] && [ "$$(ls -A out)" ]; then \
	  echo "[CLEAN] Removing build files..."; \
	  rm -rf out; \
	else \
	  echo "[CLEAN] Nothing to be done."; \
	fi

$(TARGET): $(main_objects) $(header_checks) | out/.dir
	$(if $(SILENT),,@echo [LINK] $(notdir $@))
	$(hidecmd)$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $(filter-out %.header,$^)

$(TEST_TARGET): $(test_objects) $(filter-out out/main.o,$(main_objects)) | out/.dir
	$(if $(SILENT),,@echo [LINK] $(notdir $@))
	$(hidecmd)$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ $^

out/%.o: %.cpp | out/.dir
	$(if $(SILENT),,@echo [C++ ] $<)
	$(hidecmd)$(CXX) $(CPPFLAGS) $(CXXFLAGS) -MMD -MP -c $< -o $@

out/%.header: % | out/.dir
	$(if $(SILENT),,@echo [HDR ] $<)
	$(hidecmd)$(CXX) $(CPPFLAGS) $(CXXFLAGS) -Wno-unused-const-variable -fsyntax-only $<
	@touch $@

out/.dir:
	@mkdir -p out && touch $@

-include $(wildcard out/*.d)

