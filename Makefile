include Makefile.param

TARGET := SmartVC

####### DIR NAME ##################
DIR_SRC := src
DIR_INTERFACE := $(DIR_SRC)/interface
DIR_LOG := $(DIR_SRC)/log
DIR_SYSTEM_SIGNAL := $(DIR_SRC)/system_signal
###################################

DIRS_C := 

DIRS_C += $(wildcard $(UTIL_TOOLS_DIR)/base64/*.c)
DIRS_C += $(wildcard $(UTIL_TOOLS_DIR)/cJSON/*.c)
DIRS_C += $(wildcard $(UTIL_TOOLS_DIR)/filefunc/*.c)
DIRS_C += $(wildcard $(UTIL_TOOLS_DIR)/inirw/*.c)
DIRS_C += $(wildcard $(UTIL_TOOLS_DIR)/list/*.c)
DIRS_C += $(wildcard $(UTIL_TOOLS_DIR)/log/*.c)
DIRS_C += $(wildcard $(UTIL_TOOLS_DIR)/strfunc/*.c)
DIRS_C += $(wildcard $(UTIL_TOOLS_DIR)/cross_platform/*c)
DIRS_C += $(wildcard $(UTIL_TOOLS_DIR)/error/*.c)

DIRS_C += $(wildcard $(DIR_SRC)/*.c)
DIRS_C += $(wildcard $(DIR_INTERFACE)/*.c)
DIRS_C += $(wildcard $(DIR_LOG)/*.c)
DIRS_C += $(wildcard $(DIR_SYSTEM_SIGNAL)/*.c)

DIRS_CPP := 

DIRS_CPP += $(wildcard $(UTIL_TOOLS_DIR)/base64/*.cpp)
DIRS_CPP += $(wildcard $(UTIL_TOOLS_DIR)/cJSON/*.cpp)
DIRS_CPP += $(wildcard $(UTIL_TOOLS_DIR)/filefunc/*.cpp)
DIRS_CPP += $(wildcard $(UTIL_TOOLS_DIR)/inirw/*.cpp)
DIRS_CPP += $(wildcard $(UTIL_TOOLS_DIR)/list/*.cpp)
DIRS_CPP += $(wildcard $(UTIL_TOOLS_DIR)/log/*.cpp)
DIRS_CPP += $(wildcard $(UTIL_TOOLS_DIR)/strfunc/*.cpp)
DIRS_CPP += $(wildcard $(UTIL_TOOLS_DIR)/cross_platform/*cpp)
DIRS_CPP += $(wildcard $(UTIL_TOOLS_DIR)/error/*.cpp)

DIRS_CPP += $(wildcard $(DIR_SRC)/*.cpp)
DIRS_CPP += $(wildcard $(DIR_INTERFACE)/*.cpp)
DIRS_CPP += $(wildcard $(DIR_LOG)/*.cpp)
DIRS_CPP += $(wildcard $(DIR_SYSTEM_SIGNAL)/*.cpp)

LIBOBJS_C := 
LIBOBJS_C += $(DIRS_C:%.c=%.o)

LIBOBJS_CPP := 
LIBOBJS_CPP += $(DIRS_CPP:%.cpp=%.o)

LIBRARY_DIRS += -L./
LIBRARY_DIRS += -L$(UTIL_TOOLS_DIR)
LIBRARY_DIRS += -L$(MDD_SDK_DIR)

LDFLAGSS += -lpthread


all:
	/bin/bash ./make_in_all_dirs.sh && $(MAKE) $(TARGET)


$(TARGET):
	$(CC) $(LIBRARY_DIRS) $(CFLAGS)  $(LIBOBJS_C) $(LIBOBJS_CPP) $(LDFLAGSS) -o  $@

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