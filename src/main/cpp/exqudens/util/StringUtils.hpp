#pragma once

#include <string>

namespace exqudens::util {

  using String = std::string;

  class StringUtils {

    private:

      static const String WHITE_SPACES;

    public:

      StringUtils() = delete;

      /**
       * @brief - Replace leading whitespaces.
       * @param str - String for replace leading whitespaces.
       * @return - New string without leading whitespaces.
       */
      static String leftTrim(String string);

      /**
       * @brief - Replace trailing whitespaces.
       * @param str - String for replace trailing whitespaces.
       * @return - New string without trailing whitespaces.
       */
      static String rightTrim(String string);

      /**
       * @brief - Replace leading and trailing whitespaces.
       * @param str - String for replace leading and trailing whitespaces.
       * @return - New string without leading and trailing whitespaces.
       */
      static String trim(String string);

      ~StringUtils() = delete;

  };

}
