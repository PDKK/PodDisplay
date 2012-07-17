MODULES := kazmath/kazmath src
C_SRC := $(shell find $(MODULES) -type f -name "*.c")
HDRFILES := $(shell find $(MODULES) -type f -name "*.h")
OBJFILES := $(patsubst %.c,%.o,$(C_SRC))
DEPFILES := $(patsubst %.c,%.d,$(C_SRC))

.PHONY: all clean tags

WARNINGS := -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align \
	        -Wwrite-strings -Wmissing-prototypes -Wmissing-declarations \
			-Wredundant-decls -Wnested-externs -Winline -Wno-long-long \
			-Wuninitialized -Wconversion -Wstrict-prototypes
CFLAGS := -g -std=c99 

PLATFORM=xorg
#PLATFORM=rpi
#PLATFORM=rpi_noX

####

ifeq ($(PLATFORM),xorg)
	CFLAGS := -D__FOR_XORG__ -c -std=gnu99 `pkg-config libpng --cflags` -Iinclude -Ikazmath/kazmath
	LIBS := -lX11 -lEGL -lGLESv2 `pkg-config libpng --libs` -lm
endif

ifeq ($(PLATFORM),rpi)
	CFLAGS:=-D__FOR_RPi__ -c -std=gnu99 `pkg-config libpng --cflags` -Iinclude -Ikazmath/kazmath
	CFLAGS+= -I/opt/vc/include/ -I/opt/vc/include/interface/vcos/pthreads/
	LIBS := -lX11 -lGLESv2 -lEGL -lm -lbcm_host -L/opt/vc/lib `pkg-config libpng --libs`
endif

ifeq ($(PLATFORM),rpi_noX)
	CFLAGS:=-D__FOR_RPi_noX__ -c -std=gnu99 `pkg-config libpng --cflags` -Iinclude -Ikazmath/kazmath
	CFLAGS+= -I/opt/vc/include/ -I/opt/vc/include/interface/vcos/pthreads/
	LIBS := -lX11 -lGLESv2 -lEGL -lm -lbcm_host -L/opt/vc/lib `pkg-config libpng --libs`
endif

#CFLAGS += $(patsubst %,-I%,$(MODULES))

all: doublepod

doublepod: $(OBJFILES)
	$(CC) -o $@ $(LIBS) $(OBJFILES)


clean:
	$(RM) $(wildcard $(OBJFILES) $(DEPFILES))

tags:
	ctags --sort=yes --c++-kinds=+p --fields=+iaS --extra=+q $(C_SRC) $(HDRFILES)

-include $(DEPFILES)

%.o: %.c Makefile
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

