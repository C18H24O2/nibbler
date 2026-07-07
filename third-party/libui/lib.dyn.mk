#! library declaration for dynmake
$(call declareLibrary,libui,libui.a)
EXTRA_LDFLAGS += -lSDL2 -lSDL2_ttf -lSDL2_image -lm
