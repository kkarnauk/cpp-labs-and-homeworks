CXX = g++
CXXFLAGS = -O2 -Wall -Werror -std=c++11 -Iinclude
LDFLAGS =

EXE = lab_10
SRCDIR = src
OBJDIR = obj
BINDIR = bin

OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(wildcard $(SRCDIR)/*.cpp))

all: $(EXE)

$(EXE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(BINDIR)/$(EXE) $(LDFLAGS)
	
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c -MMD -o $@ $<

include $(wildcard $(OBJDIR)/*.d)

$(OBJDIR):
	mkdir -p $(OBJDIR) $(BINDIR)

clean:
	rm -rf $(OBJDIR) $(BINDIR) 

.PHONY: clean all
