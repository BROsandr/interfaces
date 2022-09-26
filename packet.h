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

  void LoadFromData(std::string& ss, int index);
  void LoadFromPacket(std::string& ss);

  Byte start{0xFF};
  OctoPayload payload1;
  OctoPayload payload2;
  Byte crc{0};
  Byte end{0x00};
};

static Byte CalculateHash(const std::string& str) {
  return CRC::Calculate(str.c_str(), str.length(), CRC::CRC_8());
}

inline void Packet::LoadFromData(std::string& str, int index) {
  std::stringstream ss{str};

  ss >> payload1.data;
  payload1.number = index;
  ss >> payload2.data;
  payload2.number = index + 1;

  crc = CalculateHash(payload1 + payload2);
}

inline void Packet::LoadFromPacket(std::string& str) {
  std::stringstream ss{str};

  ss >> start;
  ss >> payload1.data;
  ss >> payload1.number;
  ss >> payload2.data;
  ss >> payload2.number;
  ss >> crc;
  ss >> end;
}

inline std::ostream& operator<<(std::ostream& os, const Packet& packet) {
  os << packet.start;
//  os << ' ';
  os << packet.payload1;
//  os << ' ';
  os << packet.payload2;
//  os << ' ';
  os << packet.crc;
//  os << ' ';
  os << packet.end;

  os << std::endl;
}

#endif //INTERFACES__PACKET_H_
