LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lpthread

INC = /usr/include/SFML/lib

CXXFLAGS = -L

# compiler and target program
CXX = g++
TARGET = game

# directories for .o and .d files
OBJDIR := obj/
DEPDIR := $(OBJDIR)deps/

# all source, object, and dependency files
SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:%.cpp=$(OBJDIR)%.o)
DEPS := $(SRCS:%.cpp=$(DEPDIR)%.d)

# root target for linking compiled .o files into one binary
$(TARGET) : $(OBJS)
	$(CXX) $^ -o $@ $(CXXFLAGS) $(INC) $(LIBS)
	
# target to compile all .cpp files, generating .d files in the process
$(OBJDIR)%.o : %.cpp $(DEPDIR)%.d | $(DEPDIR)
	$(CXX) -MMD -MT $@ -MP -MF $(DEPDIR)$*.d -o $@ -c $<

# empty targets for handling missing .d files
$(DEPS):

# target to create object and dependency directories if they don't exist
$(DEPDIR): ; @mkdir -p $@

# delete .d files, compiled .o files, and linked binary leaving just the code
clean:
	$(RM) -r $(OBJDIR) $(TARGET)

# include all the dependency files
include $(wildcard $(DEPS))

