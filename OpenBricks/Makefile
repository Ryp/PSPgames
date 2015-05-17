EXTRA_TARGETS = EBOOT.PBP
TARGET = $(PSP_EBOOT_TITLE)
PSP_EBOOT_TITLE = OpenBricks
PSP_EBOOT_ICON = eboot/ICON0.png
PSP_EBOOT_ICON1 =
PSP_EBOOT_UNKPNG =
PSP_EBOOT_PIC1 = eboot/PIC1.png
PSP_EBOOT_SND0 =

OBJS =	main.o		\
	routines.o	\
	mp3player.o	\
	datamgr.o	\
	gfx.o		\
	Randgenerator.o	\
	Vector.o	\
	Particle.o	\
	Emitter.o	\
	BatteryIcon.o	\
	Item.o		\
	SelectList.o	\
	ScoreBoard.o	\
	Text.o		\
	Switch.o	\
	ProgressBar.o	\
	Menu.o		\
	Game.o

IPATH =	-I./include

BUILD_PRX = 1
PSP_FW_VERSION = 371

CFLAGS = -O2 -G0 -Wall -Wextra -Wfloat-equal -Wpointer-arith -Wcast-align -Wshadow $(IPATH)
CXXFLAGS = $(CFLAGS) -fno-exceptions -Woverloaded-virtual -fno-strict-aliasing -fno-rtti
ASFLAGS = $(CFLAGS)

PSPSDK = $(shell psp-config --pspsdk-path)
PSPDIR=$(shell psp-config --psp-prefix)

MYLIBS = -L./lib -lm -losl -lmad -lpng -lz -ljpeg -lpspgum -lfreetype -lpspaudiolib -lpsppower -lpspgu -lpspaudio -lpsphprm
STDLIBS = $(shell $(PSPDIR)/bin/sdl-config --libs)
LIBS= -lstdc++ $(MYLIBS) $(STDLIBS)

include $(PSPSDK)/lib/build.mak

PSP_DEVICE_NAME = PANDORA
PSP_MOUNT_POINT = /run/media/ryp
HB_VITANAME = OPNBRICK
HB_FOLDERS = media sfx cfg font

RM = rm -f

re:	clean all

transfer:
	mkdir -p $(PSP_MOUNT_POINT)/$(PSP_DEVICE_NAME)/PSP/GAME/$(PSP_EBOOT_TITLE)
	cp $(EXTRA_TARGETS) $(PSP_MOUNT_POINT)/$(PSP_DEVICE_NAME)/PSP/GAME/$(PSP_EBOOT_TITLE)
	cp -r $(HB_FOLDERS) $(PSP_MOUNT_POINT)/$(PSP_DEVICE_NAME)/PSP/GAME/$(PSP_EBOOT_TITLE)
	sync
	umount $(PSP_MOUNT_POINT)/$(PSP_DEVICE_NAME)
	make clr

eboot-transfer:
	mkdir -p $(PSP_MOUNT_POINT)/$(PSP_DEVICE_NAME)/PSP/GAME/$(PSP_EBOOT_TITLE)
	cp $(EXTRA_TARGETS) $(PSP_MOUNT_POINT)/$(PSP_DEVICE_NAME)/PSP/GAME/$(PSP_EBOOT_TITLE)
	umount $(PSP_MOUNT_POINT)/$(PSP_DEVICE_NAME)
	sync
	make clr

clr:
	$(RM) PARAM.SFO
	$(RM) $(TARGET).elf
	$(RM) $(TARGET).prx *.zip *.ZIP
	$(RM) -r *.o *~

zip:
	zip -r9 $(PSP_EBOOT_TITLE)-Unsigned.zip $(EXTRA_TARGETS) $(HB_FOLDERS)
	zip -r9 $(PSP_EBOOT_TITLE)-PreSigned.zip $(EXTRA_TARGETS) $(PSP_EBOOT_TITLE).prx $(HB_FOLDERS)
	zip -r0 $(HB_VITANAME).ZIP $(EXTRA_TARGETS) $(PSP_EBOOT_TITLE).prx $(HB_FOLDERS)
