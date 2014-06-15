CC=gcc
CFLAGS =-DEGL -Ilib/freetype/include -Isrc/framework/include

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

