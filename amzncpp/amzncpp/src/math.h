#pragma once
#include <vector>

namespace Math {
  inline unsigned powOf3(int n) {
    static std::vector<unsigned> pows = { 1u, 3u, 9u, 27u, 81u };
    while (pows.size() <= n) {
      pows.push_back(pows[pows.size() - 1] * 3u);
    }
    return pows[n];
  }
}
