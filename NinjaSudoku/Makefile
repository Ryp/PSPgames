TARGET = $(PSP_EBOOT_TITLE)
OBJS = main.o routines.o Ressource.o Sudoku.o Sudokusolver.o Randgenerator.o

BUILD_PRX = 1
PSP_FW_VERSION = 371

CUSTOMFLAGS = -Wextra -Woverloaded-virtual -Wfloat-equal -Wpointer-arith -Wcast-align -Wshadow -Wundef
CFLAGS = -O2 -G0 -Wall $(CUSTOMFLAGS)
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)


EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = NinjaSudoku
PSP_EBOOT_ICON =
PSP_EBOOT_ICON1 = 
PSP_EBOOT_UNKPNG =
PSP_EBOOT_PIC1 =
PSP_EBOOT_SND0 =

PSPSDK = $(shell psp-config --pspsdk-path)
PSPDIR=$(shell psp-config --psp-prefix)

MYLIBS = -losl -lpspgum -lpspgu -lfreetype -lpspaudiolib -lpspaudio -lpsppower -lpsphprm
STDLIBS = -lpng -lz -ljpeg $(shell $(PSPDIR)/bin/sdl-config --libs)
LIBS= -lstdc++ $(MYLIBS) $(STDLIBS)

include $(PSPSDK)/lib/build.mak

PSP_DEVICE_NAME = PANDORA

transfer:
	mkdir -p /media/$(PSP_DEVICE_NAME)/PSP/GAME/$(PSP_EBOOT_TITLE) 
	cp EBOOT.PBP /media/$(PSP_DEVICE_NAME)/PSP/GAME/$(PSP_EBOOT_TITLE)
	cp -r media /media/$(PSP_DEVICE_NAME)/PSP/GAME/$(PSP_EBOOT_TITLE)
	sudo rm -f -r /media/$(PSP_DEVICE_NAME)/PSP/GAME/$(PSP_EBOOT_TITLE)/media/.svn
	umount /media/$(PSP_DEVICE_NAME)
	make clr
        
msdata-transfert:
	mkdir -p /media/$(PSP_DEVICE_NAME)/PSP/GAME/$(PSP_EBOOT_TITLE) 
	cp ms.data /media/$(PSP_DEVICE_NAME)/PSP/GAME/$(PSP_EBOOT_TITLE)
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
