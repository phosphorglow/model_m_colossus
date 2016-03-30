BLUEFRUIT_DIR = bluefruit

SRC +=	$(BLUEFRUIT_DIR)/main.c \
	$(BLUEFRUIT_DIR)/bluefruit.c \
	serial_uart.c \


# Search Path
VPATH += $(BLUEFRUIT_DIR)

OPT_DEFS += -DPROTOCOL_BLUEFRUIT