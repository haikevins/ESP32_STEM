#include "dfplayer_manager.h"

DFPlayerManager::DFPlayerManager()
  : my_serial(1)  // dùng UART1
{
}

DFPlayerManager::~DFPlayerManager() {
}

bool DFPlayerManager::Init(uint32_t baud) {
  my_serial.begin(baud, SERIAL_8N1, DFPLAYER_RX_PIN, DFPLAYER_TX_PIN);

  if (!df_player.begin(my_serial)) {
    initialized = false;
    return false;
  }

  initialized = true;
  return true;
}

void DFPlayerManager::Set_Volume(uint8_t volume) {
  if (initialized) {
    df_player.volume(volume);
  }
}

void DFPlayerManager::Play(uint16_t fileIndex) {
  if (initialized) {
    df_player.play(fileIndex);
  }
}

void DFPlayerManager::Stop() {
  if (initialized) {
    df_player.stop();
  }
}

void DFPlayerManager::Next() {
  if (initialized) {
    df_player.next();
  }
}

void DFPlayerManager::Prev() {
  if (initialized) {
    df_player.previous();
  }
}

bool DFPlayerManager::Is_Ready() {
  return initialized;
}
