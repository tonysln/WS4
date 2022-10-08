OBJDIR = obj
SRCDIR = src
BINDIR = bin

TARGET = WS4

# Which object files that the executable consists of
OBJS  = $(OBJDIR)/main.o
OBJS += $(OBJDIR)/GfxLoader.o
OBJS += $(OBJDIR)/GfxScreen.o
OBJS += $(OBJDIR)/GfxManager.o
OBJS += $(OBJDIR)/AnimIcon.o
OBJS += $(OBJDIR)/TextLabel.o
OBJS += $(OBJDIR)/MapCity.o
OBJS += $(OBJDIR)/GfxLDL.o
OBJS += $(OBJDIR)/WS4.o
OBJS += $(OBJDIR)/DataProc.o

# What compiler to use
CC = g++

# Compiler flags, -g for debug, -c to make an object file
CFLAGS = -c -Wall -std=c++17 -g

# Directories containing header files other than /usr/include
INCLUDES = #-I/extlibs/include/

# Directory with SFML libs (non-standard)
LDFLAGS = #-L/extlibs/

# SFML components
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio


all: $(TARGET)

# Link the target with all objects and libraries
$(TARGET) : $(OBJS)
	$(CC) -o $(BINDIR)/$(TARGET) $(OBJS) $(LDFLAGS) $(INCLUDES) $(LIBS)

# Compile the source files into object files
$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	$(RM) $(BINDIR)/$(TARGET) $(OBJDIR)/*.o