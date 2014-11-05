#include <VirtualWire.h>

const int led_pin = 13;
const int transmit_pin = 12;
//const int receive_pin = 2;
//const int transmit_en_pin = 3;

void setup()
{
  pinMode(led_pin,OUTPUT);
  // Initialise the IO and ISR
  vw_set_tx_pin(transmit_pin);
//  vw_set_rx_pin(receive_pin);
//  vw_set_ptt_pin(transmit_en_pin);
//  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(2000);	 // Bits per sec
}

byte count = 1;

void loop()
{
  char msg[11] = {'h','e','l','l','o','6','7','8','9',' ','#'};

  msg[10] = count;
  digitalWrite(led_pin, HIGH); // Flash a light to show transmitting
  vw_send((uint8_t *)msg, 11);
  vw_wait_tx(); // Wait until the whole message is gone
  //delay(200);
  digitalWrite(led_pin, LOW);
  delay(700 - analogRead(1));
  count = count + 1;
}

