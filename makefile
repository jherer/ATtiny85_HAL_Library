MAKE = mingw32-make
MCU_MAKEFILE = makefile.mcu
SIM_MAKEFILE = makefile.sim

.PHONY: flash build_mcu clean_mcu sim build_sim clean_sim build clean 


# PHYSICAL
flash: build_mcu
	$(MAKE) -f $(MCU_MAKEFILE) flash

build_mcu:
	$(MAKE) -f $(MCU_MAKEFILE) build

clean_mcu:
	$(MAKE) -f $(MCU_MAKEFILE) clean


# SIMULATOR
sim: build_sim
	$(MAKE) -f $(SIM_MAKEFILE)

build_sim:
	$(MAKE) -f $(SIM_MAKEFILE) build

clean_sim:
	$(MAKE) -f $(SIM_MAKEFILE) clean


# ALL
build: build_mcu build_sim
clean: clean_mcu clean_sim

