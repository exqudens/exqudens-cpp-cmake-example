#ifndef EXQUDENS_EXAMPLE_TEST_RUNNER_HPP
#define EXQUDENS_EXAMPLE_TEST_RUNNER_HPP

#include <string>
#include <vector>
#include <map>

namespace exqudens::example::test {

  using Test   = void(*)();
  using String = std::string;

  template<typename T>
  using Vector = std::vector<T>;

  template<typename K, typename V>
  using Map = std::map<K, V>;

  class Runner {

    public:
    static int run(int argc, char** argv);

    private:
    static int run(Vector<String> vector);

    private:
    static Map<String, Test> createTestMap();

    public:
    Runner() = delete;

    public:
    ~Runner() = delete;

  };

}

#endif // EXQUDENS_EXAMPLE_TEST_RUNNER_HPP
