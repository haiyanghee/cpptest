#include <bits/stdc++.h>

int main(){
    const std::unordered_map<int, std::unordered_map<int,int>> m { {1, {{2, 69}}}};
    const auto iter = m.find(1);

    const auto& map = iter->second;
    const auto b  = map.find(2);
    std::cout<< b->second << "\n";
}
