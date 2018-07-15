include Makefile.param

TARGET := SmartVC

####### DIR NAME ##################
DIR_SRC := src
DIR_INTERFACE := $(DIR_SRC)/interface
DIR_LOG := $(DIR_SRC)/log
DIR_SYSTEM_SIGNAL := $(DIR_SRC)/system_signal
###################################

DIRS_C := 
DIRS_C += $(wildcard $(DIR_SRC)/*.c)
DIRS_C += $(wildcard $(DIR_INTERFACE)/*.c)
DIRS_C += $(wildcard $(DIR_LOG)/*.c)
DIRS_C += $(wildcard $(DIR_SYSTEM_SIGNAL)/*.c)

DIRS_CPP := 
DIRS_CPP += $(wildcard $(DIR_SRC)/*.cpp)
DIRS_CPP += $(wildcard $(DIR_INTERFACE)/*.cpp)
DIRS_CPP += $(wildcard $(DIR_LOG)/*.cpp)
DIRS_CPP += $(wildcard $(DIR_SYSTEM_SIGNAL)/*.cpp)

LIBOBJS_C := 
LIBOBJS_C += $(DIRS_C:%.c=%.o)

LIBOBJS_CPP := 
LIBOBJS_CPP += $(DIRS_CPP:%.cpp=%.o)

LDFLAGSS += -lpthread


all:
	/bin/bash ./make_in_all_dirs.sh && $(MAKE) $(TARGET)


$(TARGET):
	$(CC)  $(CFLAGS)  $(LIBOBJS_C) $(LIBOBJS_CPP) $(LDFLAGSS) -o  $@

clean: 
	/bin/bash ./clear_o_file.sh
	rm $(TARGET) -rf

depend:
	/bin/bash ./clear_d_file.sh
	rm $(TARGET) -rf

distclean:
	/bin/bash ./clear_o_d_file.sh
	rm $(TARGET) -rf
	

.PHONY:$(TARGET)
.PHONY: clean
.PHONY: depend
.PHONY: distclean 