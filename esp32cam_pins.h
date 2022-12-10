// camera pins for CAMERA_MODEL_AI_THINKER
#define PWDN_GPIO_NUM      32
#define RESET_GPIO_NUM     -1
#define XCLK_GPIO_NUM       0
#define SIOD_GPIO_NUM      26
#define SIOC_GPIO_NUM      27

#define Y9_GPIO_NUM        35
#define Y8_GPIO_NUM        34
#define Y7_GPIO_NUM        39
#define Y6_GPIO_NUM        36
#define Y5_GPIO_NUM        21
#define Y4_GPIO_NUM        19
#define Y3_GPIO_NUM        18
#define Y2_GPIO_NUM         5
#define VSYNC_GPIO_NUM     25
#define HREF_GPIO_NUM      23
#define PCLK_GPIO_NUM      22

// pins for peripherals
#define BUILDIN_LED_PIN     4
#define I2C_SDA            14 //I2C connect to 2 will cause flash fails
#define I2C_SCL            15
#define WIFI_CONF_TRIGGER  12 // Trigger pin for WIFI Configuration

// I2C address
#define SLAVE_ADDR          8

// channels for PWM
#define LED_CHN             7
//PWM configs
#define PWM_FREQ         2000
#define PWM_RES             8 //value:0-255
