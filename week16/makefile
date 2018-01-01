
# This make file was written by Viet Anh Nguyen
# Used for mid-term test - ICT K60 - 2017
# Email: vietanh.dev@gmail.com
# Website: vietanhdev.com

TARGET = app

CC=gcc

# Compiling flags here
CFLAGS= -g -Wall

# Define any directories containing header file other then /usr/include
INCLUDES = -I../lib/libfdr -I../lib/bt/inc

# define any libraries to link into executable:
# if I want to link in libraries
# (libx.so or libx.a) I use the -llibname (-lx -lx) = (-lx)
# libfdr => -lfdr
LIBS = -lfdr -lbt
# LIBS = -lm

# Define any directories containing implementation of the file in INCLUDES
LFLAGS = -L../lib/libfdr -L../lib/bt/lib

# This uses Suffix Replacement within a macro:
#   $(name:string1=string2)
# For each word in 'name' replace 'string1' with 'string2'
# Below we are replacing the suffix .c of all words in the macro SRCS
# with the .o suffix

SRCS = $(wildcard *.c)
ODIR = obj
_OBJS = $(SRCS:.c=.o)
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))

#_DEPS = fields.h jrb.h jval.h dllist.h
#DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))


.PHONY: depend clean
#action
all: 	$(TARGET) 

# This uses Suffix Replacement within a macro:
#   $@ = left-part of ":" ( == $(TARGET))
# 
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LFLAGS) $(LIBS)
	@echo "Linking complete!"

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "Compiled "$<" successfully!"


clean_lib:
	make -C lib/btree clean
	make -C lib/libfdr clean
	@echo "Cleanup complete!"

build_lib: clean_lib
	@echo "Making libs..."
	make -C lib/btree
	make -C lib/libfdr
	@echo "Making libs completed!"

clean:
	rm -f $(ODIR)/*.o *~ $(TARGET)
	# rm app
	rm *.dat
	@echo "Cleanup complete!"

run:
	./$(TARGET)


#depend: $(SRCS)
#        makedepend $(INCLUDES) $^