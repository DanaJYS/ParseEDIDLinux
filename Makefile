#Makefile for register tool

TARGET := parseEDID

DEBUG ?= 0
ISARM ?= 0

ifeq ($(ISARM), 1)
GCC := arm-none-linux-gnueabi-gcc
CFLAGS = -D ISARM
else
GCC := gcc
endif


ifeq ($(DEBUG), 1)
DEFINES = -DDEBUG -DDGB -D_DEBUG
CFLAGS = -g -O0
else
DEFINES = 
CFLAGS += -Wuninitialized -O0 -fno-strict-aliasing 
endif
CFLAGS += -static

INCLUDES = -I ./


CUR_DIR := $(shell pwd)

LD_OPTION = -static

SRCS := main.c edid.c

OBJS=$(SRCS:.c=.o)


default: $(TARGET)


# rules
.c.o:
	$(GCC) -c  $(INCLUDES) $(CFLAGS) $(DEFINES) -o $@ $<


$(TARGET):$(OBJS)
	$(GCC) $(LD_OPTION) -o $@ $(OBJS)

.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET)
