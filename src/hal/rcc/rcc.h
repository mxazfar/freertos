#ifndef RCC_H
#define RCC

typedef enum {
    rccClkGpioA,
    rccClkGpioB,
    rccClkGpioC,
    rccClkGpioD,
    rccClkGpioE,
    rccClkGpioF,
    rccClkGpioG,
    rccClkGpioH,
    rccClkCrc = 12,
    rccClkBackupSram = 18,
    rccClkDma1 = 21,
    rccClkDma2,
    rccClkUsbOtgHg = 29,
    rccClkUsbOstgHsulpi,

    rccClkCamera = 32,
    rccClkUsbOtgFs = 39,

    rccClkFlexMemCtrl = 64,
    rccClkQuadSpi,

    rccClkTim2 = 96,
    rccClkTim3,
    rccClkTim4,
    rccClkTim5,
    rccClkTim6,
    rccClkTim7,
    rccClkTim12 = 102,
    rccClkTim13,
    rccClkTim14,
    rccClkWWdg = 107,
    rccClkSpi2 = 110,
    rccClkSpi3,
    rccClkSpdifRx,
    rccClkUsart2,
    rccClkUsart3,
    rccClkUart4,
    rccClkUart5,
    rccClkI2c1,
    rccClkI2c2,
    rccClkI2c3,
    rccClkFmpi2c1,
    rccClkCan1,
    rccClkCan2,
    rccClkCec,
    rccClkPwr,
    rccClkDac,

    rccClkTim1 = 128,
    rccClkTim8,
    rccClkUsart1 = 132,
    rccClkUsart6,
    rccClkAdc1 = 136,
    rccClkAdc2,
    rccClkAdc3,
    rccClkSdio,
    rccClkSpi1,
    rccClkSpi4,
    rccClkSyscfg,
    rccClkTim9 = 144,
    rccClkTim10,
    rccClkTim11,
    rccClkSai1 = 150,
    rccClkSai2
} rcc_peripheral_clk_t;

typedef enum {
    rccFail,
    rccSuccess
} rcc_ret_t;

#endif /* RCC_H */