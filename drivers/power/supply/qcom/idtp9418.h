/**
 * @file   idtp9220.h
 * @author  <roy@ROY-PC>
 * @date   Sun Nov 22 11:49:55 2015
 *
 * @brief
 *
 *
 */
#ifndef __IDTP9220_H__
#define __IDTP9220_H__

#include <linux/types.h>
#include <linux/device.h>
#include <linux/workqueue.h>
#include "idtp9418_fw.h"
#define IDT_DRIVER_NAME      "idtp9418"
#define IDT_I2C_ADDR         0x3b

#define HSCLK                60000

#define ADJUST_METE_MV       35
#define IDTP9220_DELAY       2000
#define CHARGING_FULL        100
#define CHARGING_NEED        95

/* status low regiter bits define */
#define STATUS_VOUT_ON       (1 << 7)
#define STATUS_VOUT_OFF      (1 << 6)
#define STATUS_TX_DATA_RECV  (1 << 4)
#define STATUS_OV_TEMP       (1 << 2)
#define STATUS_OV_VOL        (1 << 1)
#define STATUS_OV_CURR       (1 << 0)

#define OVER_EVENT_OCCUR     (STATUS_OV_TEMP | STATUS_OV_VOL | STATUS_OV_CURR)
#define TOGGLE_LDO_ON_OFF    (1 << 1)

/* interrupt register bits define */
#define INT_RXREADY				(1<<22)
#define INT_POWER_LOSS			(1<<21)
#define INT_OVERCURRENT_HIGH	(1 << 20)
#define RENEG_FAIL        (1 << 19)
#define RENEG_SUCCESS     (1 << 18)
#define INT_RPP_READ      (1 << 17)
#define INT_EXT5V_FAIL    (1 << 16)
#define INT_VSWITCH_FAIL  (1 << 15)
#define INT_SLEEPMODE     (1 << 14)
#define INT_IDAUTH_SUCESS (1 << 13)
#define INT_IDAUTH_FAIL   (1 << 12)
#define INT_SEND_SUCESS   (1 << 11)
#define INT_SEND_TIMEOUT  (1 << 10)
#define INT_AUTH_SUCESS   (1 << 9)
#define INT_AUTH_FAIL     (1 << 8)
#define INT_VOUT_OFF      (1 << 7)
#define INT_VOUT_ON       (1 << 6)
#define INT_MODE_CHANGE   (1 << 5)
#define INT_TX_DATA_RECV  (1 << 4)
#define INT_VSWITCH_SUCESS  (1 << 3)
#define INT_OV_TEMP       (1 << 2)
#define INT_OV_VOL        (1 << 1)
#define INT_OV_CURR       (1 << 0)

/*TRX int bits define*/
#define INT_GET_BLE_ADDR	(1 << 8)
#define INT_INIT_TX        (1 << 7)
#define INT_GET_DPING      (1 << 6)
#define INT_GET_PPP        (1 << 5)
#define INT_GET_CFG        (1 << 4)
#define INT_GET_ID         (1 << 3)
#define INT_GET_SS         (1 << 2)
#define INT_START_DPING    (1 << 1)
#define INT_EPT_TYPE       (1 << 0)

#define TX_TOGGLE          BIT(6) // toggle work mode(148K or 190K)
#define TX_FOD_EN          BIT(5) // enable FOD
#define TX_WD              BIT(4) // enable WD
#define TX_SEND_FSK        BIT(3) // SEND_FSK
#define TX_DIS             BIT(2) // disable tx
#define TX_CLRINT          BIT(1) // clr int
#define TX_EN              BIT(0) // enable tx mode

/* used registers define */
#define REG_CHIP_ID_L        0x0000
#define REG_CHIP_ID_H        0x0001
#define REG_CHIP_REV         0x0002
#define REG_CTM_ID           0x0003
#define REG_OTPFWVER_ADDR    0x0004 // OTP firmware version
#define REG_EPRFWVER_ADDR    0x001c // EEPROM firmware version
#define REG_SYS_INT_CLR      0x0028 // int clear
#define REG_SYS_INT          0x0030 // interrupt
#define REG_STATUS_L         0x0034
#define REG_STATUS_H         0x0035
#define REG_INTR_L           0x0036
#define REG_INTR_H           0x0037
#define REG_INTR_EN_L        0x0038
#define REG_INTR_EN_H        0x0039
#define REG_CHG_STATUS       0x003A
#define REG_ADC_VOUT_L       0x003C
#define REG_ADC_VOUT_H       0x003D
#define REG_VOUT_SET         0x003E
#define REG_VRECT_ADJ        0x003F
#define REG_ADC_VRECT        0x0040
#define REG_RX_LOUT_L        0x0044
#define REG_RX_LOUT_H        0x0045
#define REG_RX_DIE_TEMP      0x0046
#define REG_FREQ_ADDR        0x0048 // Operating Frequency, Fop(KHz) = 64 * 6000 /value * 256)
#define REG_ILIM_SET         0x004A
#define REG_SIGNAL_STRENGTH  0x004B
#define REG_WPC_MODE         0x004D
#define REG_SSCMND           0x004e // Command Register, COM (0x4E)
#define REG_RX_RESET         0x004F
#define REG_PROPPKT          0x0050 // Proprietary Packet Header Register, PPP_Header (0x50)
#define REG_PPPDATA          0x0051 // PPP Data Value Register(0X51, 0x52, 0x53, 0x54, 0x55)
#define REG_SSINTCLR         0x0056 // Interrupt Clear Registers, INT_Clear_L (0x56)
#define REG_BCHEADER         0x0058 // Back Channel Packet Register (0x58)
#define REG_BCDATA           0x0059 // Back Channel Packet Register (0x59, 0x5A, 0x5B, 0x5C)
#define REG_FC_VOLTAGE_L     0x0078 // Fast Charging Voltage Register
#define REG_FC_VOLTAGE_H     0x0079
#define REG_REGULATOR_L      0x000C
#define REG_REGULATOR_H      0x000d
#define REG_POWER_MAX        0x0084 //Get the TX power on EPP mode.
#define REG_TX_TYPE          0x00A2 //Get the TX type.
#define REG_BLE_FLAG         0x00A4 //Get the rx ble flag.
#define REG_CEP              0x00A5 //Get the CEP.
#define REG_RPP              0x00A6 //Get the RPP.
#define REG_MAX_POWER        0x008E
#define REG_OCP_CONFIG       0x00F1
#define REG_TEMPTER          0x00F2

/*add for reverse charge*/
#define REG_EPT_TYPE         0x0074
#define REG_TX_CMD           0x0076
#define REG_TX_DATA          0x0078
#define REG_WROK_MODE        0x007B
#define REG_VRECT_TAEGET     0x0090
#define REG_FOD_LOW          0x0092
#define REG_FOD_HIGH         0x0093
#define REG_MAC_ADDR	0x00be

#define REG_REVERSE_IIN_LOW  0x006e
#define REG_REVERSE_IIN_HIGH 0x006f
#define REG_REVERSE_VIN_LOW  0x0070
#define REG_REVERSE_VIN_HIGH 0x0071
#define REG_REVERSE_TEMP     0x007a

#define EPT_POCP             BIT(15)
#define EPT_OTP              BIT(14)
#define EPT_FOD              BIT(13)
#define EPT_LVP              BIT(12)
#define EPT_OVP              BIT(11)
#define EPT_OCP              BIT(10)
#define EPT_RPP_TIMEOUT      BIT(9)
#define EPT_CEP_TIMEOUT      BIT(8)
#define EPT_CMD              BIT(0)

#define REG_EXTERNAL_5V      0x00dc //external 5v enable

// RX -> TX
#define PROPRIETARY18        0x18
#define PROPRIETARY28        0x28
#define PROPRIETARY38        0x38
#define PROPRIETARY48        0x48
#define PROPRIETARY58        0x58

// bitmap for customer command
#define BC_NONE               0x00
#define BC_SET_FREQ           0x03
#define BC_GET_FREQ           0x04
#define BC_READ_FW_VER        0x05
#define BC_READ_Iin           0x06
#define BC_READ_Vin           0x07
#define BC_SET_Vin            0x0a

#define BC_ADAPTER_TYPE       0x0b
#define BC_RESET              0x0c
#define BC_READ_I2C           0x0d
#define BC_WRITE_I2C          0x0e
#define BC_VI2C_INIT          0x10
#define BC_RX_ID_AUTH         0x3b
#define BC_TX_COMPATIBLE_HWID 0x3f
#define BC_TX_HWID            0x4c
#define BC_TX_TOGGLE          0xc4
#define CMD_GET_BLEMAC_2_0    0xb6
#define CMD_GET_BLEMAC_5_3    0xb7
#define CMD_FACOTRY_REVERSE   0x30


//Factory test command
#define BC_READ_IOUT          0x12
#define BC_READ_VOUT          0x13
#define BC_RX_CHIP_VERSION    0x23
#define BC_RX_FW_VERSION      0x24
#define BC_START_CHARGE       0x30
#define BC_SET_AP_OVERLOAD    0x31
#define BC_ENABLE_FAST_CHARGE 0x32

/* Adapter_list = {0x00:'ADAPTER_UNKNOWN',  */
/*            0x01:'SDP 500mA',  */
/*            0x02:'CDP 1.1A',  */
/*            0x03:'DCP 1.5A',  */
/*            0x05:'QC2.0',  */
/*            0x06:'QC3.0',  */
/*            0x07:'PD',} */
//define adapter type
#define ADAPTER_NONE 0x00
#define ADAPTER_SDP  0x01
#define ADAPTER_CDP  0x02
#define ADAPTER_DCP  0x03
#define ADAPTER_QC2  0x05
#define ADAPTER_QC3  0x06
#define ADAPTER_PD   0x07
#define ADAPTER_AUTH_FAILED   0x08
#define ADAPTER_XIAOMI_QC3    0x09
#define ADAPTER_XIAOMI_PD     0x0a
#define ADAPTER_ZIMI_CAR_POWER    0x0b
#define ADAPTER_XIAOMI_PD_40W     0x0c
#define ADAPTER_VOICE_BOX     0x0d
#define ADAPTER_XIAOMI_PD_45W     0x0e
#define ADAPTER_XIAOMI_PD_60W     0x0f


#define NORMAL_MODE 0x1
#define TAPER_MODE  0x2
#define FULL_MODE   0x3
#define RECHG_MODE  0x4

//fw version to update
#define FW_VERSION  0x1

//add for crc verify
#define CRC_VERIFY_LOW	0xB5
#define CRC_VERIFY_HIGH	0xA9


//add for reverse fod
#define REVERSE_FOD 500

/*CLRPOWERGOOD BIT(10), upper byte is 0x8*/
#define CLRPOWERGOOD		 0x04
// bitmap for status flags
// 1: indicates a pending interrupt for LDO Vout state change – from OFF to ON
#define VOUTCHANGED          BIT(7) // Stat_Vout_ON
// 1: indicates a pending interrupt for TX Data Received. (Change from “No Received Data” state to “Data Received” state)
#define TXDATARCVD           BIT(4) // TX Data Received

// bitmap for SSCmnd register 0x4e
#define VSWITCH              BIT(7)
// If AP sets this bit to "1" then IDTP9220 M0 clears the interrupt corresponding to the bit(s) which has a value of “1”
#define CLRINT               BIT(5) // Clear Interrupt
// If AP sets this bit to "1" then IDTP9220 M0 toggles LDO output once (from on to off, or from off to on), and then sets this bit to “0”
#define LDOTGL               BIT(1) // Toggle LDO On/OFF
// If AP sets this bit to “1” then IDTP9220 M0 sends the Proprietary Packet
#define SENDPROPP            BIT(0) //  SEND RX Data

#define SEND_DEVICE_AUTH     BIT(2)

enum VOUT_SET_VAL {
  VOUT_VAL_3500_MV = 0,
  VOUT_VAL_3600_MV,
  VOUT_VAL_3700_MV,
  VOUT_VAL_3800_MV,
  VOUT_VAL_3900_MV,
  VOUT_VAL_4000_MV,
  VOUT_VAL_4100_MV,
  VOUT_VAL_4200_MV,
  VOUT_VAL_4300_MV,
  VOUT_VAL_4400_MV,
  VOUT_VAL_4500_MV,
  VOUT_VAL_4600_MV,
  VOUT_VAL_4700_MV,
  VOUT_VAL_4800_MV,
  VOUT_VAL_4900_MV,
  VOUT_VAL_5000_MV,
  VOUT_VAL_5100_MV,
  VOUT_VAL_5200_MV,
  VOUT_VAL_5300_MV,
  VOUT_VAL_5400_MV,
  VOUT_VAL_5500_MV,
  VOUT_VAL_5600_MV,
  VOUT_VAL_5700_MV,
  VOUT_VAL_5800_MV,
  VOUT_VAL_5900_MV,
  VOUT_VAL_6000_MV,
  VOUT_VAL_6100_MV,
  VOUT_VAL_6200_MV,
  VOUT_VAL_6300_MV,
  VOUT_VAL_6400_MV,
  VOUT_VAL_6500_MV,
  VOUT_VAL_6600_MV,
  VOUT_VAL_6700_MV,
  VOUT_VAL_6800_MV,
  VOUT_VAL_6900_MV,
  VOUT_VAL_7000_MV,
  VOUT_VAL_7100_MV,
  VOUT_VAL_7200_MV,
  VOUT_VAL_7300_MV,
  VOUT_VAL_7400_MV,
  VOUT_VAL_7500_MV,
  VOUT_VAL_7600_MV,
  VOUT_VAL_7700_MV,
  VOUT_VAL_7800_MV,
  VOUT_VAL_7900_MV,
  VOUT_VAL_8000_MV,
};

enum IMIL_SET_VAL {
  CURR_VAL_100_MA = 0,
  CURR_VAL_200_MA,
  CURR_VAL_300_MA,
  CURR_VAL_400_MA,
  CURR_VAL_500_MA,
  CURR_VAL_600_MA,
  CURR_VAL_700_MA,
  CURR_VAL_800_MA,
  CURR_VAL_900_MA,
  CURR_VAL_1000_MA,
  CURR_VAL_1100_MA,
  CURR_VAL_1200_MA,
  CURR_VAL_1300_MA,
};

struct vol_curr_table {
  int index;
  char *val;
};
/*
struct idtp9220_platform_data {
  enum VOUT_SET_VAL vout_val_default;
  enum IMIL_SET_VAL curr_val_default;
  unsigned long gpio_en;
};
*/
typedef struct {        // write to structure at SRAM address 0x0400
  u16 status;           // Read/Write by both 9220 and 9220 host
  u16 startAddr;        // OTP image address of the current packet
  u16 codeLength;       // The size of the OTP image data in the current packet
  u16 dataChksum;       // Checksum of the current packet
  u8  dataBuf[128];     // OTP image data of the current packet
} idtp9220_packet_t;

// proprietary packet type
typedef struct {
  u8 header;            // The header consists of a single byte that indicates the Packet type.
  u8 cmd;               // Back channel command
  u8 data[4];           // Send data buffer
} ProPkt_Type;

#if 1
static char bootloader_data[] = {
0x00, 0x02, 0x00, 0x20, 0x99, 0x00, 0x00, 0x00, 0x9D, 0x00, 0x00, 0x00, 0x9F, 0x00, 0x00, 0x00,
0x00, 0xF0, 0x02, 0xF8, 0x00, 0xF0, 0x30, 0xF8, 0x0C, 0xA0, 0x30, 0xC8, 0x08, 0x38, 0x24, 0x18,
0x2D, 0x18, 0xA2, 0x46, 0x67, 0x1E, 0xAB, 0x46, 0x54, 0x46, 0x5D, 0x46, 0xAC, 0x42, 0x01, 0xD1,
0x00, 0xF0, 0x22, 0xF8, 0x7E, 0x46, 0x0F, 0x3E, 0x0F, 0xCC, 0xB6, 0x46, 0x01, 0x26, 0x33, 0x42,
0x00, 0xD0, 0xFB, 0x1A, 0xA2, 0x46, 0xAB, 0x46, 0x33, 0x43, 0x18, 0x47, 0xA8, 0x06, 0x00, 0x00,
0xB8, 0x06, 0x00, 0x00, 0x00, 0x23, 0x00, 0x24, 0x00, 0x25, 0x00, 0x26, 0x10, 0x3A, 0x01, 0xD3,
0x78, 0xC1, 0xFB, 0xD8, 0x52, 0x07, 0x00, 0xD3, 0x30, 0xC1, 0x00, 0xD5, 0x0B, 0x60, 0x70, 0x47,
0x1F, 0xB5, 0x1F, 0xBD, 0x10, 0xB5, 0x10, 0xBD, 0x00, 0xF0, 0x09, 0xFB, 0x11, 0x46, 0xFF, 0xF7,
0xF7, 0xFF, 0x00, 0xF0, 0x45, 0xFA, 0x00, 0xF0, 0x21, 0xFB, 0x03, 0xB4, 0xFF, 0xF7, 0xF2, 0xFF,
0x03, 0xBC, 0x00, 0xF0, 0x27, 0xFB, 0x00, 0x00, 0x05, 0x48, 0x00, 0x47, 0xFE, 0xE7, 0xFE, 0xE7,
0xFE, 0xE7, 0x00, 0x00, 0x03, 0x48, 0x04, 0x49, 0x02, 0x4A, 0x04, 0x4B, 0x70, 0x47, 0x00, 0x00,
0x11, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x20, 0x60, 0x01, 0x00, 0x20, 0x60, 0x00, 0x00, 0x20,
0xFE, 0xB5, 0x04, 0x46, 0x00, 0x20, 0x02, 0x90, 0x10, 0x20, 0x20, 0x40, 0x00, 0x28, 0x64, 0xD0,
0x01, 0x20, 0xFA, 0x4E, 0x30, 0x80, 0x80, 0x1E, 0x30, 0x81, 0x01, 0x46, 0xF8, 0x4E, 0x31, 0x83,
0x08, 0x0C, 0x70, 0x83, 0x00, 0x22, 0x44, 0xE0, 0xF6, 0x48, 0x40, 0x88, 0x80, 0x18, 0x83, 0xB2,
0x01, 0x93, 0xD8, 0x13, 0x00, 0x28, 0x03, 0xD1, 0x01, 0x20, 0xC0, 0x03, 0x18, 0x43, 0x01, 0x90,
0xEF, 0x48, 0xC2, 0x81, 0x03, 0x80, 0xEE, 0x4E, 0x01, 0x98, 0x70, 0x80, 0x01, 0x98, 0x05, 0x78,
0xEA, 0x48, 0x85, 0x80, 0x30, 0x46, 0x85, 0x80, 0x30, 0x20, 0x20, 0x40, 0x10, 0x28, 0x07, 0xD1,
0x00, 0xBF, 0xE6, 0x48, 0x00, 0x88, 0x40, 0x06, 0xC0, 0x0F, 0x00, 0x28, 0xF9, 0xD1, 0x1E, 0xE0,
0x00, 0x20, 0x00, 0x90, 0x18, 0xE0, 0xC8, 0x0F, 0x07, 0x27, 0x00, 0x9E, 0xBE, 0x1B, 0x2F, 0x46,
0x37, 0x41, 0xFE, 0x07, 0xF6, 0x0F, 0x70, 0x40, 0x00, 0x28, 0x01, 0xD0, 0xDE, 0x48, 0x00, 0xE0,
0x00, 0x20, 0x4E, 0x00, 0x70, 0x40, 0x01, 0x46, 0xD9, 0x4E, 0x31, 0x83, 0x08, 0x0C, 0x70, 0x83,
0x00, 0x98, 0x40, 0x1C, 0xC0, 0xB2, 0x00, 0x90, 0x00, 0x98, 0x07, 0x28, 0xE3, 0xDD, 0x50, 0x1C,
0x82, 0xB2, 0xD4, 0x48, 0x80, 0x88, 0x90, 0x42, 0xB6, 0xDC, 0x30, 0x20, 0x20, 0x40, 0x10, 0x28,
0x13, 0xD1, 0xCE, 0x48, 0x00, 0x89, 0xCE, 0x4E, 0x70, 0x82, 0xCC, 0x48, 0x00, 0x89, 0xCD, 0x4E,
0xF6, 0x88, 0xB0, 0x42, 0x02, 0xD1, 0x00, 0x20, 0x02, 0x90, 0x2F, 0xE0, 0x01, 0x20, 0x02, 0x90,
0xC6, 0x48, 0x00, 0x89, 0xC7, 0x4E, 0xF0, 0x80, 0x28, 0xE0, 0x88, 0xB2, 0xC5, 0x4E, 0xF6, 0x88,
0xB0, 0x42, 0x01, 0xD1, 0x01, 0x20, 0x00, 0xE0, 0x00, 0x20, 0x0E, 0x02, 0x36, 0x0E, 0xC1, 0x4F,
0x3F, 0x7A, 0xBE, 0x42, 0x01, 0xD1, 0x01, 0x26, 0x00, 0xE0, 0x00, 0x26, 0x30, 0x40, 0x0E, 0x0E,
0xBC, 0x4F, 0x7F, 0x7A, 0xBE, 0x42, 0x01, 0xD1, 0x01, 0x26, 0x00, 0xE0, 0x00, 0x26, 0x30, 0x40,
0x00, 0x28, 0x02, 0xD0, 0x00, 0x20, 0x02, 0x90, 0x08, 0xE0, 0x01, 0x20, 0x02, 0x90, 0xB5, 0x4E,
0xF1, 0x80, 0x08, 0x02, 0x00, 0x0E, 0x30, 0x72, 0x08, 0x0E, 0x70, 0x72, 0x02, 0x98, 0xFE, 0xBD,
0x10, 0xB5, 0x02, 0x46, 0xAE, 0x4B, 0x1B, 0x8A, 0x04, 0x24, 0x23, 0x43, 0xAC, 0x4C, 0x23, 0x82,
0x63, 0x14, 0xAE, 0x4C, 0xA3, 0x81, 0x93, 0x00, 0x19, 0x60, 0xAD, 0x4B, 0x1B, 0x88, 0xA4, 0x14,
0x23, 0x40, 0x18, 0x46, 0xA6, 0x4B, 0x1B, 0x8A, 0x04, 0x24, 0xA3, 0x43, 0xA4, 0x4C, 0x23, 0x82,
0xA8, 0x4B, 0xA6, 0x4C, 0xA3, 0x81, 0x10, 0xBD, 0x10, 0xB5, 0x02, 0x46, 0xA0, 0x4B, 0x1B, 0x8A,
0x02, 0x24, 0x23, 0x43, 0x9E, 0x4C, 0x23, 0x82, 0x63, 0x14, 0xA0, 0x4C, 0xA3, 0x81, 0x11, 0x70,
0x9F, 0x4B, 0x1B, 0x88, 0xA4, 0x14, 0x23, 0x40, 0x18, 0x46, 0x99, 0x4B, 0x1B, 0x8A, 0x02, 0x24,
0xA3, 0x43, 0x97, 0x4C, 0x23, 0x82, 0x9B, 0x4B, 0x98, 0x4C, 0xA3, 0x81, 0x10, 0xBD, 0xF1, 0xB5,
0x88, 0xB0, 0x08, 0x9D, 0x00, 0x20, 0x00, 0x90, 0x91, 0x48, 0x00, 0x8A, 0x08, 0x21, 0x88, 0x43,
0x8F, 0x49, 0x08, 0x82, 0x8F, 0x48, 0x00, 0x88, 0x00, 0x07, 0x00, 0x0F, 0x03, 0x90, 0x8D, 0x48,
0x40, 0x88, 0x02, 0x90, 0x8B, 0x48, 0x80, 0x88, 0x01, 0x90, 0x01, 0x99, 0x02, 0x98, 0x40, 0x18,
0x40, 0x1E, 0x80, 0xB2, 0x05, 0x90, 0x05, 0x98, 0xC0, 0x13, 0x00, 0x28, 0x04, 0xD1, 0x01, 0x21,
0xC9, 0x03, 0x05, 0x98, 0x08, 0x43, 0x05, 0x90, 0x02, 0x98, 0x07, 0x90, 0x01, 0x99, 0x07, 0x98,
0x40, 0x18, 0x80, 0xB2, 0x07, 0x90, 0x00, 0x27, 0x08, 0xE0, 0x7E, 0x48, 0x08, 0x30, 0xC1, 0x5D,
0x07, 0x98, 0x08, 0x18, 0x80, 0xB2, 0x07, 0x90, 0x78, 0x1C, 0x87, 0xB2, 0x01, 0x98, 0x87, 0x42,
0xF3, 0xDB, 0x77, 0x49, 0x07, 0x98, 0x48, 0x82, 0x76, 0x48, 0xC1, 0x88, 0x07, 0x98, 0x81, 0x42,
0x73, 0xD1, 0x03, 0x98, 0x01, 0x28, 0x01, 0xD1, 0x00, 0x20, 0x0C, 0xE0, 0x03, 0x98, 0x03, 0x28,
0x01, 0xD1, 0x04, 0x20, 0x07, 0xE0, 0x03, 0x98, 0x05, 0x28, 0x01, 0xD1, 0x24, 0x20, 0x02, 0xE0,
0x6F, 0x48, 0x20, 0x30, 0x00, 0x89, 0x6E, 0x49, 0x20, 0x31, 0x08, 0x81, 0x00, 0x27, 0xBE, 0xE0,
0x02, 0x98, 0xC0, 0x19, 0x80, 0xB2, 0x06, 0x90, 0x30, 0x0A, 0x66, 0x49, 0x08, 0x31, 0xC9, 0x5D,
0x09, 0x06, 0x08, 0x43, 0x06, 0x46, 0x06, 0x9C, 0x61, 0x48, 0xC7, 0x81, 0x60, 0x49, 0x06, 0x98,
0x08, 0x80, 0x30, 0x0C, 0xC8, 0x80, 0x8E, 0x80, 0x06, 0x98, 0xC0, 0x13, 0x00, 0x28, 0x03, 0xD1,
0x89, 0x13, 0x06, 0x98, 0x08, 0x43, 0x04, 0x46, 0x04, 0x98, 0x00, 0x0A, 0x21, 0x78, 0x09, 0x06,
0x08, 0x43, 0x04, 0x90, 0x56, 0x48, 0x44, 0x80, 0x04, 0x98, 0x00, 0x0C, 0x54, 0x49, 0x48, 0x81,
0x04, 0x98, 0x08, 0x81, 0x03, 0x98, 0x01, 0x28, 0x02, 0xD0, 0x03, 0x98, 0x03, 0x28, 0x16, 0xD1,
0x04, 0x98, 0x00, 0x0E, 0x31, 0x0E, 0x88, 0x42, 0x0D, 0xD0, 0x31, 0x0E, 0x20, 0x46, 0xFF, 0xF7,
0x53, 0xFF, 0x00, 0x28, 0x08, 0xD1, 0x20, 0x78, 0x04, 0x90, 0x31, 0x0E, 0x04, 0x98, 0x81, 0x42,
0x79, 0xD0, 0x68, 0x1C, 0x85, 0xB2, 0x76, 0xE0, 0x68, 0x1C, 0x85, 0xB2, 0x73, 0xE0, 0x03, 0x98,
0x05, 0x28, 0x70, 0xD1, 0xA0, 0x07, 0x80, 0x0F, 0x00, 0x28, 0x07, 0xD1, 0x01, 0x20, 0x00, 0x90,
0x3F, 0x48, 0x00, 0x8A, 0x08, 0x21, 0x08, 0x43, 0x3D, 0x49, 0x08, 0x82, 0x42, 0x49, 0x05, 0x98,
0x08, 0x40, 0xA0, 0x42, 0x02, 0xD1, 0x01, 0x20, 0x01, 0xE0, 0x65, 0xE0, 0x00, 0x20, 0x05, 0x99,
0x89, 0x07, 0x89, 0x0F, 0x03, 0x29, 0x01, 0xD0, 0x01, 0x21, 0x00, 0xE0, 0x00, 0x21, 0x08, 0x40,
0x00, 0x28, 0x07, 0xD0, 0x00, 0x20, 0x00, 0x90, 0x31, 0x48, 0x00, 0x8A, 0x08, 0x21, 0x88, 0x43,
0x2F, 0x49, 0x08, 0x82, 0x00, 0x98, 0x00, 0x28, 0x20, 0xD1, 0x31, 0x48, 0x20, 0x30, 0x00, 0x89,
0x20, 0x21, 0x88, 0x43, 0x2E, 0x49, 0x20, 0x31, 0x08, 0x81, 0x08, 0x46, 0x00, 0x89, 0x04, 0x21,
0x08, 0x43, 0x2B, 0x49, 0x20, 0x31, 0x08, 0x81, 0x31, 0x0E, 0x20, 0x46, 0xFF, 0xF7, 0x04, 0xFF,
0x00, 0x28, 0x08, 0xD1, 0x20, 0x78, 0x04, 0x90, 0x31, 0x0E, 0x04, 0x98, 0x81, 0x42, 0x2A, 0xD0,
0x68, 0x1C, 0x85, 0xB2, 0x27, 0xE0, 0x68, 0x1C, 0x85, 0xB2, 0x24, 0xE0, 0xA0, 0x07, 0x80, 0x0F,
0x03, 0x28, 0x20, 0xD1, 0x1E, 0x48, 0x20, 0x30, 0x00, 0x89, 0x20, 0x21, 0x08, 0x43, 0x1C, 0x49,
0x20, 0x31, 0x08, 0x81, 0x08, 0x46, 0x00, 0x89, 0x04, 0x21, 0x08, 0x43, 0x18, 0x49, 0x20, 0x31,
0x08, 0x81, 0xA0, 0x10, 0x31, 0x46, 0xFF, 0xF7, 0xC3, 0xFE, 0x00, 0x28, 0x09, 0xD1, 0xA0, 0x10,
0x80, 0x00, 0x00, 0x68, 0x04, 0x90, 0x04, 0x98, 0xB0, 0x42, 0x04, 0xD0, 0x28, 0x1D, 0x85, 0xB2,
0x01, 0xE0, 0x28, 0x1D, 0x85, 0xB2, 0x0A, 0x48, 0x85, 0x81, 0x78, 0x1C, 0x87, 0xB2, 0x01, 0x98,
0x87, 0x42, 0x00, 0xDA, 0x3C, 0xE7, 0x06, 0xE0, 0x06, 0x48, 0x80, 0x88, 0x40, 0x19, 0x85, 0xB2,
0x01, 0x20, 0xC0, 0x03, 0x05, 0x43, 0x28, 0x46, 0x09, 0xB0, 0xF0, 0xBD, 0x00, 0x70, 0x00, 0x40,
0x00, 0x05, 0x00, 0x20, 0x00, 0x04, 0x00, 0x20, 0xB7, 0x1D, 0xC1, 0x04, 0x40, 0x30, 0x00, 0x40,
0x00, 0x5C, 0x00, 0x40, 0xFF, 0x1F, 0x00, 0x00, 0xFC, 0xFF, 0x00, 0x00, 0x0C, 0xB5, 0x00, 0x21,
0x01, 0x91, 0x10, 0xE0, 0x00, 0x21, 0x00, 0x91, 0x04, 0xE0, 0x69, 0x46, 0x09, 0x88, 0x49, 0x1C,
0x8A, 0xB2, 0x00, 0x92, 0x69, 0x46, 0x09, 0x88, 0x02, 0x29, 0xF6, 0xDB, 0x69, 0x46, 0x89, 0x88,
0x49, 0x1C, 0x8A, 0xB2, 0x01, 0x92, 0x69, 0x46, 0x89, 0x88, 0x81, 0x42, 0xEA, 0xDB, 0x0C, 0xBD,
0x5A, 0x20, 0x53, 0x49, 0x08, 0x80, 0x05, 0x20, 0x88, 0x80, 0x04, 0x20, 0x08, 0x81, 0x51, 0x48,
0x88, 0x81, 0x50, 0x20, 0xFF, 0xF7, 0xDA, 0xFF, 0x4F, 0x48, 0x4D, 0x49, 0x88, 0x82, 0x4F, 0x48,
0x08, 0x82, 0x18, 0x20, 0x88, 0x83, 0x08, 0x46, 0x00, 0x8B, 0x17, 0x21, 0x49, 0x02, 0x08, 0x43,
0x47, 0x49, 0x08, 0x83, 0x08, 0x46, 0x00, 0x8B, 0x2E, 0x21, 0x08, 0x43, 0x44, 0x49, 0x08, 0x83,
0x05, 0x20, 0xFF, 0xF7, 0xC3, 0xFF, 0x42, 0x48, 0x80, 0x8B, 0x01, 0x21, 0x08, 0x43, 0x40, 0x49,
0x88, 0x83, 0x32, 0x20, 0x42, 0x49, 0x08, 0x80, 0x94, 0x20, 0x42, 0x49, 0x08, 0x80, 0x15, 0x20,
0x08, 0x80, 0x08, 0x46, 0x80, 0x8A, 0x60, 0x21, 0x88, 0x43, 0x3E, 0x49, 0x88, 0x82, 0x00, 0x20,
0x3D, 0x49, 0x08, 0x80, 0x3D, 0x49, 0x08, 0x80, 0x48, 0x80, 0x00, 0x24, 0x00, 0x27, 0x01, 0x25,
0x00, 0x26, 0x06, 0xE0, 0x00, 0x20, 0x71, 0x00, 0x39, 0x4A, 0x89, 0x18, 0x08, 0x80, 0x70, 0x1C,
0x86, 0xB2, 0x10, 0x2E, 0xF6, 0xDB, 0x5A, 0xE0, 0x34, 0x48, 0x00, 0x88, 0xC0, 0x07, 0xC0, 0x0F,
0x00, 0x28, 0x54, 0xD0, 0x31, 0x48, 0x00, 0x88, 0xC0, 0xB2, 0x30, 0x49, 0x08, 0x80, 0x5A, 0x20,
0x30, 0x49, 0x08, 0x82, 0x00, 0x20, 0x26, 0x49, 0x60, 0x31, 0x08, 0x80, 0x2B, 0x48, 0x00, 0x88,
0x11, 0x21, 0x08, 0x40, 0x01, 0x28, 0x27, 0xD1, 0x01, 0x25, 0x28, 0x48, 0x00, 0x88, 0xC0, 0xB2,
0x29, 0x02, 0x08, 0x43, 0x25, 0x49, 0x08, 0x80, 0x25, 0x48, 0x00, 0x8A, 0x01, 0x21, 0x08, 0x43,
0x23, 0x49, 0x08, 0x82, 0x00, 0x20, 0xFF, 0xF7, 0x3A, 0xFE, 0x04, 0x46, 0x20, 0x48, 0x00, 0x8A,
0xA8, 0x43, 0x1F, 0x49, 0x08, 0x82, 0x60, 0x04, 0x40, 0x0C, 0xC0, 0x19, 0x87, 0xB2, 0x88, 0x13,
0x20, 0x40, 0x00, 0x28, 0x01, 0xD0, 0x08, 0x20, 0x04, 0xE0, 0x00, 0x2C, 0x01, 0xD0, 0x04, 0x20,
0x00, 0xE0, 0x02, 0x20, 0x05, 0x46, 0x11, 0xE0, 0x01, 0x25, 0x14, 0x48, 0x00, 0x88, 0xC0, 0xB2,
0x29, 0x02, 0x08, 0x43, 0x11, 0x49, 0x08, 0x80, 0x08, 0x88, 0xFF, 0xF7, 0x41, 0xFD, 0x04, 0x46,
0x00, 0x2C, 0x01, 0xD0, 0x08, 0x20, 0x00, 0xE0, 0x02, 0x20, 0x05, 0x46, 0x0B, 0x48, 0x47, 0x80,
0x00, 0x88, 0xFE, 0x21, 0x08, 0x40, 0x29, 0x02, 0x08, 0x43, 0x08, 0x49, 0x08, 0x80, 0xA3, 0xE7,
0x00, 0x30, 0x00, 0x40, 0x01, 0x04, 0x00, 0x00, 0x0A, 0x20, 0x00, 0x00, 0xFF, 0x07, 0x00, 0x00,
0x40, 0x54, 0x00, 0x40, 0x00, 0x58, 0x00, 0x40, 0x40, 0x6C, 0x00, 0x40, 0x00, 0x04, 0x00, 0x20,
0x00, 0x05, 0x00, 0x20, 0x40, 0x5C, 0x00, 0x40, 0x70, 0x47, 0x70, 0x47, 0x70, 0x47, 0x75, 0x46,
0x00, 0xF0, 0x24, 0xF8, 0xAE, 0x46, 0x05, 0x00, 0x69, 0x46, 0x53, 0x46, 0xC0, 0x08, 0xC0, 0x00,
0x85, 0x46, 0x18, 0xB0, 0x20, 0xB5, 0xFF, 0xF7, 0xFD, 0xFC, 0x60, 0xBC, 0x00, 0x27, 0x49, 0x08,
0xB6, 0x46, 0x00, 0x26, 0xC0, 0xC5, 0xC0, 0xC5, 0xC0, 0xC5, 0xC0, 0xC5, 0xC0, 0xC5, 0xC0, 0xC5,
0xC0, 0xC5, 0xC0, 0xC5, 0x40, 0x3D, 0x49, 0x00, 0x8D, 0x46, 0x70, 0x47, 0x10, 0xB5, 0x04, 0x46,
0xC0, 0x46, 0xC0, 0x46, 0x20, 0x46, 0xFF, 0xF7, 0xD8, 0xFC, 0x10, 0xBD, 0x00, 0x48, 0x70, 0x47,
0x00, 0x00, 0x00, 0x20, 0x01, 0x49, 0x18, 0x20, 0xAB, 0xBE, 0xFE, 0xE7, 0x26, 0x00, 0x02, 0x00,
0x70, 0x47, 0x00, 0x00, 0x04, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x60, 0x01, 0x00, 0x00,
0x54, 0x00, 0x00, 0x00
};

#endif

extern uint32_t get_hw_version_major(void);

#endif
