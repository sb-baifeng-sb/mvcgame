PHONY := all package clean
rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))

CC := arm-vita-eabi-gcc
CXX := arm-vita-eabi-g++
STRIP := arm-vita-eabi-strip

PROJECT_TITLE := Lite2D
PROJECT_TITLEID := LITE2D001

LITE2D_ROOT := ../../src
THIRD_ROOT := ../../lib
APP_ROOT := ../../examples/hello

PROJECT := Lite2D
CXXFLAGS += -std=c++11 -I$(APP_ROOT) -I$(APP_ROOT)/.. -I$(LITE2D_ROOT) -I$(THIRD_ROOT) -I$(THIRD_ROOT)/spine/include -I./src -DPSVITA
CFLAGS += -I$(APP_ROOT) -I$(APP_ROOT)/.. -I$(LITE2D_ROOT) -I$(THIRD_ROOT) -I$(THIRD_ROOT)/spine/include -I./src -DPSVITA

LIBS := -lvita2d -lSceDisplay_stub -lSceGxm_stub \
	-lSceSysmodule_stub -lSceCtrl_stub -lSceTouch_stub -lScePgf_stub -lScePvf_stub \
	-lSceCommonDialog_stub -lpng -ljpeg -lz

SRC_C := $(call rwildcard, src/, *.c)
SRC_CPP := $(call rwildcard, src/, *.cpp)

LITE2D_CPP := $(wildcard $(LITE2D_ROOT)/mvcgame/action/*.cpp) \
				$(wildcard $(LITE2D_ROOT)/mvcgame/asset/*.cpp) \
				$(wildcard $(LITE2D_ROOT)/mvcgame/base/*.cpp) \
				$(wildcard $(LITE2D_ROOT)/mvcgame/controller/*.cpp) \
				$(wildcard $(LITE2D_ROOT)/mvcgame/event/*.cpp) \
				$(wildcard $(LITE2D_ROOT)/mvcgame/font/*.cpp) \
				$(wildcard $(LITE2D_ROOT)/mvcgame/platform/*.cpp) \
				$(wildcard $(LITE2D_ROOT)/mvcgame/platform/vita/*.cpp) \
				$(wildcard $(LITE2D_ROOT)/mvcgame/skeleton/*.cpp) \
				$(wildcard $(LITE2D_ROOT)/mvcgame/texture/*.cpp) \
				$(wildcard $(LITE2D_ROOT)/mvcgame/tile/*.cpp) \
				$(wildcard $(LITE2D_ROOT)/mvcgame/util/*.cpp) \
				$(wildcard $(LITE2D_ROOT)/mvcgame/view/*.cpp) \
				$(wildcard $(THIRD_ROOT)/spine/src/spine/*.c)

LITE2D_CPP += $(wildcard $(APP_ROOT)/base/*.cpp) \
				$(wildcard $(APP_ROOT)/controller/*.cpp)

LITE2D_OBJS := $(patsubst %.cpp, %.o, $(LITE2D_CPP))
LITE2D_OBJS := $(patsubst %.c, %.o, $(LITE2D_OBJS))

OBJ_DIRS := $(addprefix out/, $(dir $(SRC_C:src/%.c=%.o))) $(addprefix out/, $(dir $(SRC_CPP:src/%.cpp=%.o)))
OBJS := $(addprefix out/, $(SRC_C:src/%.c=%.o)) $(addprefix out/, $(SRC_CPP:src/%.cpp=%.o)) $(LITE2D_OBJS)

all: package

package: $(PROJECT).vpk

$(PROJECT).vpk: eboot.bin param.sfo
	vita-pack-vpk -s param.sfo -b eboot.bin $(PROJECT).vpk
	
eboot.bin: $(PROJECT).velf
	vita-make-fself $(PROJECT).velf eboot.bin

param.sfo:
	vita-mksfoex -s TITLE_ID="$(PROJECT_TITLEID)" "$(PROJECT_TITLE)" param.sfo

$(PROJECT).velf: $(PROJECT).elf
	$(STRIP) -g $<
	vita-elf-create $< $@

$(PROJECT).elf: $(OBJS)
	$(CXX) -Wl,-q $(CFLAGS) -o $@ $^ $(LIBS)

$(OBJ_DIRS):
	mkdir -p $@

out/%.o : src/%.cpp | $(OBJ_DIRS)
	arm-vita-eabi-g++ -c $(CXXFLAGS) -o $@ $<

out/%.o : src/%.c | $(OBJ_DIRS)
	arm-vita-eabi-g++ -c $(CFLAGS) -o $@ $<

vpksend: $(PROJECT).vpk
	curl -T $< ftp://$(PSVITAIP):1337/ux0:/
	@echo "Sent."

ressend: eboot.bin
	find $(APP_ROOT)/resources -type f -name '*.*' -exec curl --ftp-create-dirs -T {} ftp://$(PSVITAIP):1337/ux0:/app/$(PROJECT_TITLEID)/resources/ \;
	@echo "Sent."

clean:
	rm -f $(PROJECT).velf $(PROJECT).elf $(PROJECT).vpk param.sfo eboot.bin $(OBJS)
	rm -r $(abspath $(OBJ_DIRS))
