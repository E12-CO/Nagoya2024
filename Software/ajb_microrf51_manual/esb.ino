// Based on https://github.com/honnet/twi/tree/TX
#define BASE_ADDR_LEN   4
#define PACKET_LEN      32

uint32_t *packet_ptr;
uint8_t poll_fsm = 0;
bool rxne_flag, txe_flag;

#define RX_TIMEOUT  3000  // 10000ms RX wait timeout
unsigned long rx_timeout_millis;

// Taken from : https://github.com/NordicPlayground/nrf51-micro-esb/blob/master/common/micro_esb.c
static uint32_t bytewise_bit_swap(uint32_t inp)
{
  inp = (inp & 0xF0F0F0F0) >> 4 | (inp & 0x0F0F0F0F) << 4;
  inp = (inp & 0xCCCCCCCC) >> 2 | (inp & 0x33333333) << 2;
  return (inp & 0xAAAAAAAA) >> 1 | (inp & 0x55555555) << 1;
}

void nrf51_esb_init(uint64_t write_pipe, uint64_t read_pipe, uint8_t radio_chan) {
  // Enable HSE
  NRF_CLOCK->EVENTS_HFCLKSTARTED  = 0;
  NRF_CLOCK->TASKS_HFCLKSTART     = 1;
  while (NRF_CLOCK->EVENTS_HFCLKSTARTED == 0);

  // Update Radio parameter
  // 1. TX power
  NRF_RADIO->TXPOWER = RADIO_TXPOWER_TXPOWER_Neg30dBm << RADIO_TXPOWER_TXPOWER_Pos;

  // 2. Frequency channel 2400 + FREQUENCY Mhz
  NRF_RADIO->FREQUENCY  = (uint32_t)radio_chan;

  // 3. Bit rate
  NRF_RADIO->MODE = RADIO_MODE_MODE_Nrf_1Mbit << RADIO_MODE_MODE_Pos;

  // 4. 16 bit crc
  NRF_RADIO->CRCCNF = RADIO_CRCCNF_LEN_Two << RADIO_CRCCNF_LEN_Pos;
  NRF_RADIO->CRCINIT = (uint32_t)0xFFFF;
  NRF_RADIO->CRCPOLY = (uint32_t)0x11021;

  // 5. Packet configuration
  NRF_RADIO->PCNF0 =
    (1 << RADIO_PCNF0_S0LEN_Pos) |
    (0 << RADIO_PCNF0_LFLEN_Pos) |
    (1 << RADIO_PCNF0_S1LEN_Pos);

  NRF_RADIO->PCNF1 =
    (RADIO_PCNF1_WHITEEN_Disabled << RADIO_PCNF1_WHITEEN_Pos) |
    (RADIO_PCNF1_ENDIAN_Big << RADIO_PCNF1_ENDIAN_Pos) |
    (BASE_ADDR_LEN << RADIO_PCNF1_BALEN_Pos) |
    (PACKET_LEN << RADIO_PCNF1_STATLEN_Pos) |
    (PACKET_LEN << RADIO_PCNF1_MAXLEN_Pos);

  // 6. Radio address
  // 1 byte PREFIX address + 4 bytes BASE address = 5 bytes address compatible with nRF24
  // TX address (PREFIX0.AP0 and logical adddr 0 of BASE0):
  NRF_RADIO->PREFIX0  = (uint8_t)bytewise_bit_swap(write_pipe & 0xFF);
  NRF_RADIO->BASE0    = bytewise_bit_swap((uint32_t)(write_pipe >> 8));
  NRF_RADIO->TXADDRESS = 0;// Use BASE0 as TX address
  // RX address (PREFIX1.AP4 and logical addr 4 of BASE1):
  NRF_RADIO->PREFIX1  = (uint8_t)bytewise_bit_swap(read_pipe & 0xFF);
  NRF_RADIO->BASE1    = bytewise_bit_swap((uint32_t)(read_pipe >> 8));
  NRF_RADIO->RXADDRESSES  = 1 << 4;// use BASE1 as RX address

}

void nrf51_esb_setPTR(uint8_t *packetptr) {
  packet_ptr = (uint32_t *)packetptr;
}

void nrf51_esb_poll() {

  if ((millis() - rx_timeout_millis) > RX_TIMEOUT) {
    poll_fsm = 255;
    rx_timeout_millis = millis();
  }

  switch (poll_fsm) {
    case 0:// Ramp up RX radio
      {
        NRF_RADIO->PACKETPTR = (uint32_t)packet_ptr;
        NRF_RADIO->EVENTS_READY = 0;
        NRF_RADIO->TASKS_RXEN = 1;
        poll_fsm = 1;
        //Serial.println("Starting RX");
      }
      break;

    case 1:// Wait for RX Ramp up
      {
        if (NRF_RADIO->EVENTS_READY == 1) {
          rx_timeout_millis = millis();
          rxne_flag = 0;
          NRF_RADIO->EVENTS_END = 0;
          NRF_RADIO->TASKS_START = 1;
          poll_fsm = 2;
          //Serial.println("RX Ramp up done");
        }
      }
      break;

    case 2:// Wait for RX reception
      {
        if (NRF_RADIO->EVENTS_END == 1) {
          rx_timeout_millis = millis();
          poll_fsm = 3;
          //Serial.println("RX data received");
        }
      }
      break;

    case 3:// Check CRC match
      {
        if (NRF_RADIO->CRCSTATUS == 1) {
          //matched
          poll_fsm = 4;
          //Serial.println("CRC matched");
        } else {
          poll_fsm = 4;
          //Serial.println("CRC mismatched");
        }
      }
      break;

    case 4:// Disable Radio
      {
        NRF_RADIO->EVENTS_DISABLED = 0;
        NRF_RADIO->TASKS_DISABLE    = 1;
        poll_fsm = 5;
        //Serial.println("Disabling Radio");
      }
      break;

    case 5:// Wait until radio is stopped
      {
        rx_timeout_millis = millis();
        if (NRF_RADIO->EVENTS_DISABLED == 1) {
          rxne_flag = 1;
          poll_fsm = 0;
          //Serial.println("Radio disabled");
        }
      }
      break;

    case 255:// Stop
      {
        poll_fsm = 4;

      }
      break;

  }
}

uint8_t nrf51_esb_rx_available() {
  uint8_t temp = rxne_flag;
  rxne_flag = rxne_flag ? 0 : rxne_flag;
  return temp;
}

uint8_t nrf51_esb_tx_available() {
  uint8_t temp = txe_flag;
  txe_flag = txe_flag ? 0 : txe_flag;
  return temp;
}
