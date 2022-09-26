//
// Created by alex on 26.09.22.
//

#ifndef INTERFACES__OCTOPAYLOAD_H_
#define INTERFACES__OCTOPAYLOAD_H_

#include "common.h"

struct OctoPayload {
  std::string operator+(OctoPayload& octo_payload);
  friend std::istream& operator>>(std::istream& is, OctoPayload& payload);
  friend std::ostream& operator<<(std::ostream& os, const OctoPayload& payload);

  std::string Content() const;

  Data& data();
  void set_data(std::bitset<5> data);
  Data& number();
  void set_number(std::bitset<3> number);

 private:
  Byte content{0};
};

inline std::string OctoPayload::Content() const {
  return std::to_string(content.to_ulong());
}

inline std::string OctoPayload::operator+(OctoPayload& octo_payload) {
  return Content() + octo_payload.Content();
}

std::istream& operator>>(std::stringstream& is, OctoPayload& packet) {
  std::bitset<5> data;
  is >> data;
  packet.set_data(data);

  std::bitset<3> number;
  is >> number;
  packet.set_number(number);

  return is;
}

std::ostream& operator<<(std::ostream& os, const OctoPayload& payload) {
  os << payload.content;
}

inline Data& OctoPayload::data() {
}

inline void OctoPayload::set_data(std::bitset<5> data) {
  content[3] = data[0];
  content[4] = data[1];
  content[5] = data[2];
  content[6] = data[3];
  content[7] = data[4];
}

inline Data& OctoPayload::number() {
}

inline void OctoPayload::set_number(std::bitset<3> number) {
  content[0] = number[0];
  content[0] = number[1];
  content[0] = number[2];
}

#endif //INTERFACES__OCTOPAYLOAD_H_
