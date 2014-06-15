CC=gcc
CFLAGS =-DFM_EGL -Ilib/freetype/include -Isrc/framework/include -I$(SDKSTAGE)/opt/vc/include -I$(SDKSTAGE)/opt/vc/include/interface/vcos/pthreads -I$(SDKSTAGE)/opt/vc/include/interface/vmcs_host/linux
LFLAGS=-lfreetype -lGLESv2 -lEGL -lm -lbcm_host -L$(SDKSTAGE)/opt/vc/lib

_SRCS_FRAMEWORK=gfx.c gl.c raspi/gfx_raspi.c raspi/time_raspi.c
SRCS_FRAMEWORK=$(patsubst %.c, src/framework/src/%.c, $(_SRCS_FRAMEWORK))
_SRCS_APP=main.c
SRCS_APP=$(patsubst %.c, src/app/%.c, $(_SRCS_APP))

SRCS=$(SRCS_FRAMEWORK) $(SRCS_APP)

#OBJS=$(patsubst %.c, obj/%.o, $(notdir $(SRCS)))
#OBJS=$(patsubst %.c, obj/%.o, $(notdir $(SRCS)))
OBJS=$(patsubst %.c, %.o, $(SRCS))

all: output fridge-magnet

output:
	@echo $(SRCS)

fridge-magnet: $(OBJS)
	$(CC) -o $@ $(patsubst %.c, obj/%.o, $(notdir $(SRCS))) $(LFLAGS)

$(OBJS): %.o: %.c
	$(CC) $< -c -o obj/$(notdir $@) $(CFLAGS)

clean:
	rm $(patsubst %.c, obj/%.o, $(notdir $(SRCS)))

