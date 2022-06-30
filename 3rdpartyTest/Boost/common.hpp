#pragma once
#ifndef COMMON_HPP
#define  COMMON_HPP
#include <iostream>
#include <boost/bind.hpp>
#include <string>
#include <locale>
#include <clocale>
#include <vector>
#include <boost/convert.hpp>
#include <boost/algorithm/string.hpp>

template<typename out>
void print(const out& outPrint, const std::string& name) {
    std::cout << name << " : " << outPrint << "\n";
}

template<typename out>
void print(const std::vector<out>& outPrint, const std::string& name) {
    std::cout << name << " : ";
    for (const auto& iter : outPrint) {
        std::cout << iter << ",";
    }
    std::cout << "\n";
}
#endif