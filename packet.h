//
// Created by alex on 26.09.22.
//

#ifndef INTERFACES__PACKET_H_
#define INTERFACES__PACKET_H_

#include <sstream>

#include "CRC.h"

#include "common.h"
#include "octopayload.h"

struct Packet {
  friend std::ostream& operator<<(std::ostream& os, const Packet& packet);

  void ReadFromData(std::string& ss, int index);

  Byte start{0xFF};
  OctoPayload payload1;
  OctoPayload payload2;
  Byte crc{0};
  Byte end{0x00};
};

static Byte ComputeHash(const std::string& str) {
  return CRC::Calculate(str.c_str(), str.length(), CRC::CRC_8());
}

inline void Packet::ReadFromData(std::string& str, int index) {
  std::stringstream ss{str};

  ss >> payload1;
  payload1.set_number(index);
  ss >> payload2;
  payload2.set_number(index + 1);

  crc = ComputeHash(payload1 + payload2);
}

inline void Packet::ReadFromPackets(std::string& str) {
  std::stringstream ss{str};

  ss >> payload1;
  payload1.set_number(index);
  ss >> payload2;
  payload2.set_number(index + 1);

  crc = ComputeHash(payload1 + payload2);
}

inline std::ostream& operator<<(std::ostream& os, const Packet& packet) {
  os << packet.start;
  os << ' ';
  os << packet.payload1;
  os << ' ';
  os << packet.payload2;
  os << ' ';
  os << packet.crc;
  os << ' ';
  os << packet.end;

  os << std::endl;
}

#endif //INTERFACES__PACKET_H_
