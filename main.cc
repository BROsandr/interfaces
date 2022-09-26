#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include "packet.h"

std::vector<std::string> ReadData() {
  std::vector<std::string> strings;
  std::string file_name{"data.txt"};
  std::ifstream file{file_name};

  while (!file.eof()) {
    std::string line;
    getline(file, line);
    strings.push_back(line);
  }

  return strings;
}

std::vector<Packet> MakePackets(std::vector<std::string>& strings)  {
  std::vector<Packet> packets;
  {
    int index{0};
    for (auto &str : strings) {
      Packet packet;
      packet.LoadFromData(str, index);
      packets.emplace_back(packet);
      index += 2;
    }
  }

  return packets;
}

void WritePackets(std::vector<Packet>& packets, const std::string& file_name) {
  std::ofstream file{file_name};

  for (auto &packet : packets) {
    file << packet;
  }
}

std::vector<Packet> ReadPackets() {
  std::vector<Packet> packets;

  std::string file_name{"packets.txt"};
  std::ifstream file{file_name};

  while (!file.eof()) {
    std::string line;
    getline(file, line);
    if (line.empty())
      break;
    Packet packet;
    packet.LoadFromPacket(line);
    packets.emplace_back(packet);
  }

  return packets;
}

int main() {
  std::vector<std::string> strings{ReadData()};
  std::vector<Packet> packets{MakePackets(strings)};
  WritePackets(packets, "packets.txt");

  packets = ReadPackets();
  WritePackets(packets, "packets_res.txt");

  return 0;
}
