# Makefile Options

NAME = Solve
ICON = icon.png
DESCRIPTION = "Test"
COMPRESSED = YES
COMPRESSED_MODE = zx0

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

include $(shell cedev-config --makefile)