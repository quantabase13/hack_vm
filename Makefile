BIN = main
CXXFLAGS = -std=c++11 -O2 -Wall -g

# SDL
CXXFLAGS += `sdl2-config --cflags `
LDFLAGS += `sdl2-config --libs` -lSDL2_image 

# Control the build verbosity
ifeq ("$(VERBOSE)","1")
	Q :=
	VECHO = @true
else
	Q := @
	VECHO = @printf
endif
.PHONY:all clean

all:$(BIN) 

OBJS := main.o cpu.o renderer.o

deps := $(OBJS:%.o=.%.o.d)

%.o: %.cpp
	$(VECHO) "  CXX\t$@\n"
	$(Q)$(CXX) -o $@ $(CXXFLAGS) -c -MMD -MF .$@.d $<
$(BIN): $(OBJS)
	$(Q)$(CXX)  -o $@ $^ $(LDFLAGS)

clean:
	$(RM) $(BIN) $(OBJS) $(deps)

-include $(deps)

