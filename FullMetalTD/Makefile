TARGET = $(PSP_EBOOT_TITLE)
OBJS = main.o routines.o geometry.o Tower.o Cannon.o Target.o Enemy.o GameCell.o AINode.o GraphicObject.o InputMgr.o MapMgr.o PathFinder.o AudioEngine.o LogicEngine.o GraphicEngine.o
BUILD_PRX = 1
PSP_FW_VERSION = 371

CUSTOMFLAGS = -Wextra -Wfloat-equal -Wpointer-arith -Wcast-align -Wshadow
CFLAGS = -O2 -G0 -Wall -g $(CUSTOMFLAGS)
ASFLAGS = $(CFLAGS)

EXTRA_TARGETS = EBOOT.PBP
CXXFLAGS = $(CFLAGS) -fno-exceptions -Woverloaded-virtual -fno-strict-aliasing -fno-rtti
PSP_EBOOT_TITLE = FullMetalTD
PSP_EBOOT_ICON =
PSP_EBOOT_ICON1 =
PSP_EBOOT_UNKPNG =
PSP_EBOOT_PIC1 =
PSP_EBOOT_SND0 =

PSPSDK = $(shell psp-config --pspsdk-path)
PSPDIR = $(shell psp-config --psp-prefix)

MYLIBS =  -losl -lpng -lz -ljpeg -lpspgum -lfreetype -lpspaudiolib
STDLIBS = $(shell $(PSPDIR)/bin/sdl-config --libs)
LIBS= -lstdc++ $(MYLIBS) $(STDLIBS)

include $(PSPSDK)/lib/build.mak

PSP_DEVICE_NAME = PANDORA

transfer:
	mkdir -p /media/$(PSP_DEVICE_NAME)/PSP/GAME/$(PSP_EBOOT_TITLE)
	cp EBOOT.PBP /media/$(PSP_DEVICE_NAME)/PSP/GAME/$(PSP_EBOOT_TITLE)
	cp -r media /media/$(PSP_DEVICE_NAME)/PSP/GAME/$(PSP_EBOOT_TITLE)
	cp -r sfx /media/$(PSP_DEVICE_NAME)/PSP/GAME/$(PSP_EBOOT_TITLE)
	cp -r map /media/$(PSP_DEVICE_NAME)/PSP/GAME/$(PSP_EBOOT_TITLE)
	umount /media/$(PSP_DEVICE_NAME)
	make clr

eboot-transfer: 
	mkdir -p /media/$(PSP_DEVICE_NAME)/PSP/GAME/$(PSP_EBOOT_TITLE) 
	cp EBOOT.PBP /media/$(PSP_DEVICE_NAME)/PSP/GAME/$(PSP_EBOOT_TITLE)
	umount /media/$(PSP_DEVICE_NAME)
	make clr
        
clr:
	rm -f PARAM.SFO $(PSP_EBOOT_TITLE).zip
	rm -f $(TARGET).elf
	rm -f $(TARGET).prx
	rm -f *.o *~

zip:
	zip -r9 $(PSP_EBOOT_TITLE) README.TXT LICENSE.TXT Unsigned.zip $(EXTRA_TARGETS) media sfx map
