import time
import random

from time import sleep

# Import RTD emulator classes
from OptoOutModRegs import *
from OptoOutMod import *

# Rename definition of register names for shorter usage
from OptoOutModRegs import OptoOutModRegs as Reg


if __name__ == "__main__":
    period = 60
    total = 60 * 60 * 24

    dev = OptoOutMod()

    t_end = time.time() + total

    # while time.time() < t_end:
    #     dev.write(Reg.OUT_SET, 0xffff)
    #     sleep(period)
    #     dev.write(Reg.OUT_CLEAR, 0xffff)
    #     sleep(period)

    while time.time() < t_end:
        dev.write(Reg.OUT_STATE, random.randint(1, 0xffff))
        sleep(0.1)

