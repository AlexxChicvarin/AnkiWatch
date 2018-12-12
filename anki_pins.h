// SPI
#define SPI_SCL            NRF_GPIO_PIN_MAP(1,5)
#define SPI_MOSI           NRF_GPIO_PIN_MAP(1,6)
#define SPI_MISO           NRF_GPIO_PIN_MAP(1,3)

// TWI
#define TWI_SCL            NRF_GPIO_PIN_MAP(0,26)
#define TWI_SDA            NRF_GPIO_PIN_MAP(0,27)

// E-Paper display
#define EINK_CS            NRF_GPIO_PIN_MAP(1,12)
#define EINK_BUSY          NRF_GPIO_PIN_MAP(0,3)
#define EINK_RES           NRF_GPIO_PIN_MAP(1,15)
#define EINK_DC            NRF_GPIO_PIN_MAP(1,14)

// MPU-9250 (MEMS)
#define MPU_CS             NRF_GPIO_PIN_MAP(1,2)
#define MPU_INT            NRF_GPIO_PIN_MAP(1,0)

// APDS-9960 (Gesture)
#define AP_INT             NRF_GPIO_PIN_MAP(0,31)

// MT25QL memory, QSPI
#define Q_CLK              NRF_GPIO_PIN_MAP(0,12)
#define Q_CS               NRF_GPIO_PIN_MAP(0,13)
#define Q_D0               NRF_GPIO_PIN_MAP(1,8)
#define Q_D1               NRF_GPIO_PIN_MAP(0,6)
#define Q_D2               NRF_GPIO_PIN_MAP(0,7)
#define Q_D3               NRF_GPIO_PIN_MAP(1,9)

// MCP73831T-ACI/OT (accumulator)
#define BATT_M             NRF_GPIO_PIN_MAP(0,5)

// TLV73333PDBVT (power source)
#define DC_ON              NRF_GPIO_PIN_MAP(0,16)

// Buttons
#define BUTTON_1           NRF_GPIO_PIN_MAP(0,20)
#define BUTTON_2           NRF_GPIO_PIN_MAP(1,10)
#define BUTTON_3           NRF_GPIO_PIN_MAP(0,15)
#define BUTTON_4           NRF_GPIO_PIN_MAP(0,28)
#define BUTTON_MNU         NRF_GPIO_PIN_MAP(0,21)
#define BUTTON_RESET       NRF_GPIO_PIN_MAP(0,18)

#define LED_PIN            NRF_GPIO_PIN_MAP(0,29)

#define BUZZ_PIN           NRF_GPIO_PIN_MAP(0,23)

#define VIBRO_PIN          NRF_GPIO_PIN_MAP(0,24)

