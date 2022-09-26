//
// Created by alex on 26.09.22.
//

#ifndef INTERFACES__OCTOPAYLOAD_H_
#define INTERFACES__OCTOPAYLOAD_H_

#include <bitset>

struct OctoPayload {
  std::string operator+(OctoPayload& octo_payload);
  friend std::ostream& operator<<(std::ostream& os, const OctoPayload& payload);

  std::string Content() const;

  std::bitset<5> data{0};
  std::bitset<3> number{0};
};

inline std::string OctoPayload::Content() const {
  return data.to_string() + number.to_string();
}

inline std::string OctoPayload::operator+(OctoPayload& octo_payload) {
  return Content() + octo_payload.Content();
}

std::ostream& operator<<(std::ostream& os, const OctoPayload& payload) {
  os << std::bitset<8>{payload.Content()};
}

#endif //INTERFACES__OCTOPAYLOAD_H_
