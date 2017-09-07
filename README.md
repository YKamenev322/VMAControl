# VMAControl
Source code for 8 VMA-drivers

Папка CommonSRC - общие исходники для bootloader и stm32f10rct6(сам проект).
Папка stm32Flasher - терминальное гуи-приложение для отладки и загрузки проекта.

Проект можно зашивать 2 способами: напрямую через SWD или по RS485 с использованием stm32Flasher, предварительно накатив бутлоадер по SWD. 
Для 1 способа необходимо проект stm32f10rct6 собрать с дефайнами в main.h :
  #define VMADRIVER_ESC30
  #define DEBUG
Для 2 способа нужно изменить дефайны в main.h :
  #define VMADRIVER_ESC30
  //#define DEBUG
А также зайти в options-Target-IROM1- выставить значение 0х8006400 (адрес, с которого будет стартовать основная программа)
И собрать проект stm32f10rct6. 
Далее воспользоваться программой stm32Flasher.
