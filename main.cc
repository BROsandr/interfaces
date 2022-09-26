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

  file.close();

  return strings;
}

std::vector<Packet> MakePackets(std::vector<std::string>& strings)  {
  std::vector<Packet> packets;
  {
    int index{0};
    for (auto &str : strings) {
      packets.emplace_back(str, index);
      index += 2;
    }
  }

  return packets;
}

void WritePackets(std::vector<Packet>& packets) {
  std::string file_name{"packets.txt"};
  std::ofstream file{file_name};

  for (auto &packet : packets) {
    file << packet;
  }

  file.close();
}

int main() {
  std::vector<std::string> strings{ReadData()};
  std::vector<Packet> packets{MakePackets(strings)};
  WritePackets(packets);


  return 0;
}
