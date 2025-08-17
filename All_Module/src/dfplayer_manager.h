#ifndef __DFPLAYER_MANAGER_H__
#define __DFPLAYER_MANAGER_H__

#include <Arduino.h>
#include <DFRobotDFPlayerMini.h>

#define DFPLAYER_RX_PIN 16
#define DFPLAYER_TX_PIN 17

class DFPlayerManager {
  private:
    HardwareSerial my_serial;          // UART1
    DFRobotDFPlayerMini df_player;
    bool initialized = false;

  public:
    DFPlayerManager();                // constructor không tham số
    virtual ~DFPlayerManager();

    bool Init(uint32_t baud = 9600);
    void Set_Volume(uint8_t volume);   // 0–30
    void Play(uint16_t fileIndex);    // Play file by index
    void Stop();
    void Next();
    void Prev();
    bool Is_Ready();
};
#endif  // __DFPLAYER_MANAGER_H__