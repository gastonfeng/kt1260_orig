wget https://github.com/gastonfeng/bootloader_stm32/releases/download/untagged-f16f1c7c13d338eaa915/firmware.bin boot.bin
wget https://github.com/gastonfeng/bootloader_stm32/releases/download/untagged-f16f1c7c13d338eaa915/firmware.bin test.bin
stlink\ST-LINK_CLI.exe -P boot.bin 0x08000000
stlink\ST-LINK_CLI.exe -P test.bin 0x080A0000