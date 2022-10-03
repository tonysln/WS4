OBJDIR = obj
SRCDIR = src
BINDIR = bin

TARGET = WS4

# Which object files that the executable consists of
OBJS = $(OBJDIR)/WS4.o
OBJS += $(OBJDIR)/gfx_init.o
OBJS += $(OBJDIR)/data_proc.o

# What compiler to use
CC = g++

# Compiler flags, -g for debug, -c to make an object file
CFLAGS = -c -Wall -std=c++20 -g

# define any directories containing header files other than /usr/include
INCLUDES = #-I/home/newhall/include  -I../include

# Directory with SFML libs
LDFLAGS = #-L/home/dast/lib -L/usr/local/ssl/lib

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