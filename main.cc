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
    if (line.empty())
      break;
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

std::string FileToString() {
  std::string file_name{"packets_to_transfer.txt"};
  std::ifstream file{file_name};

  std::string file_string;
  while (!file.eof()) {
    std::string line;
    getline(file, line);
    file_string += line;
  }

  return file_string;
}

std::vector<Packet> ReadPackets(std::string& file_string) {
  std::vector<Packet> packets;

  std::string start{"11111111"};
  std::string end{"00000000"};

  while (file_string.find(end) != std::string::npos && file_string.find(start) != std::string::npos &&
         file_string.length() >= 40) {
    file_string.erase(0, file_string.find(start));
    Packet packet;
    packet.LoadFromPacket(file_string);
    if (packet.IsValid()) {
      packets.emplace_back(packet);
      file_string.erase(0, 40);
    } else {
      file_string.erase(0, 1);
    }
  }

  return packets;
}

void PrintPacketNumbers(std::vector<Packet>& packets) {
  std::cout << "Packets: " << std::endl;

  for (auto& packet : packets) {
    std::cout << packet.payload1.number.to_ulong() << std::endl;
  }
}

int main() {
  std::vector<std::string> strings{ReadData()};
  std::vector<Packet> packets{MakePackets(strings)};
  WritePackets(packets, "packets_to_transfer.txt");

  std::string str;
  std::cout << "Waiting, press enter";
  getline(std::cin, str);
  std::string file_string{FileToString()};
  packets = ReadPackets(file_string);
  WritePackets(packets, "packets_to_receive.txt");

  PrintPacketNumbers(packets);

  return 0;
}
