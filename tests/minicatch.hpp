#pragma once
#include <vector>
#include <functional>
#include <iostream>
#include <stdexcept>
namespace minicatch {
struct Test { const char* name; std::function<void()> func; };
inline std::vector<Test>& registry() { static std::vector<Test> r; return r; }
struct Registrar {
  Registrar(const char* name, std::function<void()> func) { registry().push_back({name, func}); }
};
inline int run() {
  int failed = 0;
  for(auto& t : registry()) {
    try { t.func(); std::cout << t.name << ": OK\n"; }
    catch(const std::exception& e){ std::cout << t.name << ": FAIL (" << e.what() << ")\n"; ++failed; }
    catch(...) { std::cout << t.name << ": FAIL" << std::endl; ++failed; }
  }
  return failed;
}
}
#define TEST_CASE(name) static void name(); static minicatch::Registrar reg_##name(#name, name); static void name()
#define REQUIRE(cond) do{ if(!(cond)) throw std::runtime_error(#cond); }while(0)
#ifdef CATCH_CONFIG_MAIN
int main(){ return minicatch::run(); }
#endif
