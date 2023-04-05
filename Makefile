SHELL  = /bin/sh

.PHONY: all

all:
	meson buildir --prefix=/usr/local --buildtype=plain -Ddeprecated_warnings=false -Ddjvu=true -Ddvi=true -Dt1lib=true -Dpixbuf=true -Dcomics=true -Dintrospection=true -Dmathjax-directory=/usr/share/mathjax2
	ninja -C buildir
	ninja -C buildir install
