DIR_PROJECT_ROOT := $(shell cd ../..;pwd)
DIR_MBED_OS := $(shell cd mbed-os;pwd)

VOLUMES += --mount type=bind,source=$(DIR_PROJECT_ROOT),destination=/mbed/lora_device_lib,readonly
VOLUMES += --mount type=bind,source=$(DIR_MBED_OS),destination=/mbed/mbed-os,readonly

DOCKER := docker run -ti --rm --user 1000:1000

PROFILE ?= debug
#PROFILE ?= release

JLINK_SPEED := 4000

GDB        ?= arm-none-eabi-gdb
GDB_SERVER ?= JLinkGDBServer
JLINK      ?= JLinkExe

APP ?= rtos_wl55

include targets/$(APP).mk

DIR_BUILD = BUILD/$(DEVICE)/GCC_ARM-$(shell echo $(PROFILE) | tr a-z A-Z)

# change the toolchain source for the container here
TOOLCHAIN_NAME := gcc-arm-none-eabi-9-2020-q2-update
TOOLCHAIN_URL := https://developer.arm.com/-/media/Files/downloads/gnu-rm/9-2020q2/gcc-arm-none-eabi-9-2020-q2-update-x86_64-linux.tar.bz2?revision=05382cca-1721-44e1-ae19-1e7c3dc96118&la=en&hash=D7C9D18FCA2DD9F894FD9F3C3DC9228498FA281A

# container name and tag
NAME := ldl_mbed
TAG := $(TOOLCHAIN_NAME)

default:
	@ echo use this makefile to build a container and orchestrate builds

.PHONY: default \
  clean \
  get_mbed_os \
  build_container \
  test_container \
  compile \
  gdb_server \
  $(DIR_APP)/upload_flash.jlink \
  $(DIR_APP)/.gdbinit

get_mbed_os:
	git clone https://github.com/ARMmbed/mbed-os

build_container:
	docker build --build-arg toolchain_name='$(TOOLCHAIN_NAME)' --build-arg toolchain_url='$(TOOLCHAIN_URL)' -t $(NAME):$(TAG) .

test_container:
	docker run -ti --rm --user 1000:1000 $(NAME):$(TAG) --help

compile:
	@ echo building $(APP)
	cd $(DIR_APP) && $(DOCKER) $(VOLUMES) -v $(DIR_APP):/mbed:cached $(NAME):$(TAG) compile -m $(DEVICE) -t GCC_ARM --profile $(PROFILE) -DRADIO='$(RADIO)'
	@ cd $(DIR_APP) && $(DOCKER) $(VOLUMES) -v $(DIR_APP):/mbed:cached --entrypoint arm-none-eabi-objcopy $(NAME):$(TAG) -O ihex $(DIR_BUILD)/mbed.elf $(DIR_BUILD)/mbed.hex

flash: $(DIR_APP)/upload_flash.jlink compile
	cd $(DIR_APP) && $(JLINK) -device $(JLINK_DEVICE) -if swd -speed $(JLINK_SPEED) -CommanderScript $<

gdb: $(DIR_APP)/.gdbinit flash
	cd $(DIR_APP) && $(GDB) --command=.gdbinit -tui -q $(DIR_BUILD)/mbed.elf

gdb_server:
	$(GDB_SERVER) -if swd -device $(JLINK_DEVICE) -vd -speed $(JLINK_SPEED) -endian little

$(DIR_APP)/upload_flash.jlink:
	@ rm -f $@
	@ touch $@
	@ echo r                          >> $@
	@ echo h                          >> $@
	@ echo loadfile $(DIR_BUILD)/mbed.hex >> $@
	@ echo r                          >> $@
	@ echo g                          >> $@
	@ echo q                          >> $@

$(DIR_APP)/.gdbinit:
	@ rm -f $@
	@ touch $@
	@ echo target remote localhost:2331  >> $@
	@ echo dir $(DIR_PROJECT_ROOT)/src  >> $@
	@ echo dir $(DIR_PROJECT_ROOT)/include  >> $@
	@ echo dir $(DIR_PROJECT_ROOT)/wrappers/mbed  >> $@
	@ echo monitor reset                 >> $@
	@ echo focus cmd                     >> $@

clean:
	rm -rf $(DIR_APP)/$(DIR_BUILD)
	rm -rf $(DIR_APP)/mbed-os
	rm -rf $(DIR_APP)/lora_device_lib

