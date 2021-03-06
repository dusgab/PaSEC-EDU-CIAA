# Copyright 2018, Gassmann Dustin
# All rights reserved.
#
#

-include project.mk

PROJECT ?= examples/blinky
TARGET ?= lpc4337_m4
BOARD ?= edu_ciaa_nxp

include $(PROJECT)/Makefile

include etc/target/$(TARGET).mk

SYMBOLS += -D$(TARGET) -D$(BOARD)

include $(foreach MOD,$(PROJECT_MODULES),$(MOD)/Makefile)

PROJECT_OBJ_FILES := $(addprefix $(OBJ_PATH)/,$(notdir $(PROJECT_C_FILES:.c=.o)))

PROJECT_OBJ_FILES += $(addprefix $(OBJ_PATH)/,$(notdir $(PROJECT_ASM_FILES:.S=.o)))

PROJECT_OBJS := $(notdir $(PROJECT_OBJ_FILES))

INCLUDES := $(addprefix -I,$(PROJECT_INC_FOLDERS)) \
            $(addprefix -I,$(foreach MOD,$(notdir $(PROJECT_MODULES)),$($(MOD)_INC_FOLDERS)))

vpath %.o $(OBJ_PATH)
vpath %.c $(PROJECT_SRC_FOLDERS) $(foreach MOD,$(notdir $(PROJECT_MODULES)),$($(MOD)_SRC_FOLDERS))
vpath %.S $(PROJECT_SRC_FOLDERS) $(foreach MOD,$(notdir $(PROJECT_MODULES)),$($(MOD)_SRC_FOLDERS))
vpath %.a $(OUT_PATH)

all : $(PROJECT_NAME)

define makemod
lib$(1).a: $(2)
	@echo "*** archiving static library $(1) ***"
	@$(CROSS_PREFIX)ar rcs $(OUT_PATH)/lib$(1).a $(addprefix $(OBJ_PATH)/,$(2))
	@$(CROSS_PREFIX)size $(OUT_PATH)/lib$(1).a
endef

$(foreach MOD,$(notdir $(PROJECT_MODULES)), $(eval $(call makemod,$(MOD),$(notdir $(patsubst %.c,%.o,$(patsubst %.S,%.o,$($(MOD)_SRC_FILES)))))))

%.o: %.c
	@echo "*** compiling C file $< ***"
	@$(CROSS_PREFIX)gcc $(SYMBOLS) $(CFLAGS) $(INCLUDES) -c $< -o $(OBJ_PATH)/$@
	@$(CROSS_PREFIX)gcc $(SYMBOLS) $(CFLAGS) $(INCLUDES) -c $< -MM > $(OBJ_PATH)/$(@:.o=.d)

%.o: %.S
	@echo "*** compiling asm file $< ***"
	@$(CROSS_PREFIX)gcc $(SYMBOLS) $(CFLAGS) $(INCLUDES) -c $< -o $(OBJ_PATH)/$@
	@$(CROSS_PREFIX)gcc $(SYMBOLS) $(CFLAGS) $(INCLUDES) -c $< -MM > $(OBJ_PATH)/$(@:.o=.d)

-include $(wildcard $(OBJ_PATH)/*.d)

all : $(PROJECT_NAME)

$(PROJECT_NAME): $(foreach MOD,$(notdir $(PROJECT_MODULES)),lib$(MOD).a) $(PROJECT_OBJS)
	@echo "*** linking project $@ ***"
	@$(CROSS_PREFIX)gcc $(LFLAGS) $(LD_FILE) -o $(OUT_PATH)/$(PROJECT_NAME).axf $(PROJECT_OBJ_FILES) $(SLAVE_OBJ_FILE) -L$(OUT_PATH) $(addprefix -l,$(notdir $(PROJECT_MODULES))) $(addprefix -L,$(EXTERN_LIB_FOLDERS)) $(addprefix -l,$(notdir $(EXTERN_LIBS)))
	@$(CROSS_PREFIX)size $(OUT_PATH)/$(PROJECT_NAME).axf
	@$(CROSS_PREFIX)objcopy -v -O binary $(OUT_PATH)/$(PROJECT_NAME).axf $(OUT_PATH)/$(PROJECT_NAME).bin
	@echo "*** post-build ***"
	@$(POST_BUILD_CMD)

doc:
	doxygen doxyfile

clean:
	rm -f $(OBJ_PATH)/*.*
	rm -f $(OUT_PATH)/*.*
	rm -f *.launch

clean_all:
	@make TARGET=lpc1769 clean --no-print-directory
	@make TARGET=lpc4337_m0 clean --no-print-directory
	@make TARGET=lpc4337_m4 clean --no-print-directory
	@make TARGET=lpc54102_m0 clean --no-print-directory
	@make TARGET=lpc54102_m4 clean --no-print-directory

openocd:
	@echo "Starting OpenOCD for $(TARGET)..."
	@openocd -f $(CFG_FILE)

download: $(PROJECT_NAME)
	@echo "Downloading $(PROJECT_NAME).bin to $(TARGET)..."
	@$(DOWNLOAD_CMD)
	@echo "Download done."

erase:
	@echo "Erasing flash memory..."
	@$(ERASE_CMD)
	@echo "Erase done."

info:
	@echo PROJECT_NAME: $(PROJECT_NAME)
	@echo TARGET: $(TARGET)
	@echo PROJECT_MODULES: $(PROJECT_MODULES)
	@echo OBJS: $(PROJECT_OBJS)
	@echo INCLUDES: $(INCLUDES)
	@echo PROJECT_SRC_FOLDERS: $(PROJECT_SRC_FOLDERS)

ctags:
	@echo "Generating tags file."
	ctags -R .

generate:
	php $(osek_PATH)/generator/generator.php --cmdline -l -v \
	-DARCH=cortexM4 -DCPUTYPE=lpc43xx -DCPU=lpc4337 \
	-c  $(PROJECT)/$(PROJECT_NAME).oil -f $(osek_GEN_FILES) -o $(PROJECT)/gen

