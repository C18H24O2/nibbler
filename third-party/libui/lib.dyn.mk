#! library declaration for dynmake
$(call declareLibrary,libui,libui.a)

_MODULES := $(shell find $(LIBDIR) -mindepth 1 -maxdepth 1 -type d -name "libui-*"  -exec basename {} \;)
_CPP_MODULE := libui-cpp
_MODULES_NO_CPP := $(filter-out $(_CPP_MODULE),$(_MODULES))

CFLAGS += $(foreach module,$(_MODULES_NO_CPP),-I$(LIBDIR)/$(module)/include)
CXXFLAGS += -I$(LIBDIR)/$(_CPP_MODULE)/include
LDFLAGS += -lSDL2 -lSDL2_ttf -lSDL2_image -lm
