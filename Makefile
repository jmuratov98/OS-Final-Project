SOURCES := $(wildcard *.c)
TARGETS := $(SOURCES:.c=)

COMMON   := -O2 -Wall -Wformat=2 -march=native
CFLAGS   := $(CFLAGS) $(COMMON)
CXXFLAGS := $(CXXFLAGS) $(COMMON)
CC       := gcc
CXX      := g++
LD       := $(CC)   # probably want $(CXX) for cpp source
LDFLAGS  := $(LDFLAGS)  # -L/path/to/libs/
LDADD    :=  # -lrt
INCLUDE  :=  # -I../path/to/headers/
DEFS     :=  # -DLINUX

.PHONY : all
all : $(TARGETS)

# {{{ for debugging
DBGFLAGS := -g
debug : CFLAGS += $(DBGFLAGS)
debug : CXXFLAGS += $(DBGFLAGS)
debug : all
.PHONY : debug
# }}}

$(TARGETS) : % : %.c
	$(LD) $(LDFLAGS) -o $@ $^ $(LDADD)

.PHONY : clean
clean :
	rm -f $(TARGETS)

# vim:ft=make:foldmethod=marker:foldmarker={{{,}}}

