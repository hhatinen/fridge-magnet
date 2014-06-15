CC=gcc
CFLAGS =-DFM_EGL -Ilib/freetype/include -Isrc/framework/include -I$(SDKSTAGE)/opt/vc/include -I$(SDKSTAGE)/opt/vc/include/interface/vcos/pthreads -I$(SDKSTAGE)/opt/vc/include/interface/vmcs_host/linux

_SRCS_FRAMEWORK=gfx.c gl.c raspi/gfx_raspi.c raspi/time_raspi.c
SRCS_FRAMEWORK=$(patsubst %.c, src/framework/src/%.c, $(_SRCS_FRAMEWORK))

SRCS=$(SRCS_FRAMEWORK)

#OBJS=$(patsubst %.c, obj/%.o, $(notdir $(SRCS)))
#OBJS=$(patsubst %.c, obj/%.o, $(notdir $(SRCS)))
OBJS=$(patsubst %.c, %.o, $(SRCS))

all: output fridge-magnet

output:
	@echo $(SRCS)

fridge-magnet: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

$(OBJS): %.o: %.c
	$(CC) $< -c -o obj/$(notdir $@) $(CFLAGS)

clean:
	rm $(patsubst %.c, obj/%.o, $(notdir $(SRCS)))

