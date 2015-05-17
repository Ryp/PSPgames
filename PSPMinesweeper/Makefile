
OBJS = main.o routines.o Ressource.o Menu.o Game.o Mouse.o Board.o Save.o Timer.o

PSP_FW_VERSION = 371

CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = PSPMinesweeper
PSP_EBOOT_ICON = eboot/ICON0.png
PSP_EBOOT_ICON1 =
PSP_EBOOT_UNKPNG =
PSP_EBOOT_PIC1 =
PSP_EBOOT_SND0 =

PSPSDK = $(shell psp-config --pspsdk-path)
PSPDIR = $(shell psp-config --psp-prefix)

MYLIBS = -losl -lfreetype -lpspaudiolib -lpspaudio -lpsphprm -lpspgu -lpspgum -lpsppower
STDLIBS = -lpng -lz -ljpeg
LIBS= -lstdc++ $(MYLIBS) $(STDLIBS)

include $(PSPSDK)/lib/build.mak

PSP_DEVICE_NAME = PANDORA
PSP_MOUNT_POINT = /run/media/ryp

transfer:
	mkdir -p $(PSP_MOUNT_POINT)/$(PSP_DEVICE_NAME)/PSP/GAME/$(PSP_EBOOT_TITLE)
	cp EBOOT.PBP $(PSP_MOUNT_POINT)/$(PSP_DEVICE_NAME)/PSP/GAME/$(PSP_EBOOT_TITLE)
	cp ms.data $(PSP_MOUNT_POINT)/$(PSP_DEVICE_NAME)/PSP/GAME/$(PSP_EBOOT_TITLE)
	cp -r media $(PSP_MOUNT_POINT)/$(PSP_DEVICE_NAME)/PSP/GAME/$(PSP_EBOOT_TITLE)
	sudo rm -f -r $(PSP_MOUNT_POINT)/$(PSP_DEVICE_NAME)/PSP/GAME/$(PSP_EBOOT_TITLE)/media/.svn
	make clr


msdata-transfert:
	mkdir -p $(PSP_MOUNT_POINT)/$(PSP_DEVICE_NAME)/PSP/GAME/$(PSP_EBOOT_TITLE)
	cp ms.data $(PSP_MOUNT_POINT)/$(PSP_DEVICE_NAME)/PSP/GAME/$(PSP_EBOOT_TITLE)
	make clr

eboot-transfer:
	mkdir -p $(PSP_MOUNT_POINT)/$(PSP_DEVICE_NAME)/PSP/GAME/$(PSP_EBOOT_TITLE)
	cp EBOOT.PBP $(PSP_MOUNT_POINT)/$(PSP_DEVICE_NAME)/PSP/GAME/$(PSP_EBOOT_TITLE)
	umount $(PSP_MOUNT_POINT)/$(PSP_DEVICE_NAME)
	make clr

clr:
	rm -f PARAM.SFO
	rm -f $(TARGET).elf
	rm -f $(TARGET).prx
	rm -f $(OBJS)
