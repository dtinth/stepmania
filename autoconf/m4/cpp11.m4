# This is meant to ensure that the local compiler can utilize c++11 code.

AC_DEFUN([SM_CPP11], [
  AC_CACHE_CHECK(if your compiler supports C++11 features without additional flags,
  SM_cv_CPP11_NATIVE,
  [AC_LANG_SAVE
  AC_LANG_CPLUSPLUS
  AC_TRY_COMPILE([
  template <typename T>
    struct check final
    {
      static constexpr T value{ __cplusplus };
    };

    typedef check<check<bool>> right_angle_brackets;

    int a;
    decltype(a) b;

    typedef check<int> check_type;
    check_type c{};
    check_type&& cr = static_cast<check_type&&>(c);

    static_assert(check_type::value == 201103L, "C++11 compiler");],,
  SM_cv_CPP11_NATIVE=yes, SM_cv_CPP11_NATIVE=no)
  AC_LANG_RESTORE
  ])

  AC_CACHE_CHECK(if your compiler supports C++11 features with -std=c++11,
  SM_cv_CPP11_STDC11,
  [AC_LANG_SAVE
  AC_LANG_CPLUSPLUS
  ac_save_CXXFLAGS="$CXXFLAGS"
  CXXFLAGS="$CXXFLAGS -std=c++11"
  AC_TRY_COMPILE([
  template <typename T>
    struct check final
    {
      static constexpr T value{ __cplusplus };
    };

    typedef check<check<bool>> right_angle_brackets;

    int a;
    decltype(a) b;

    typedef check<int> check_type;
    check_type c{};
    check_type&& cr = static_cast<check_type&&>(c);

    static_assert(check_type::value == 201103L, "C++11 compiler");],,
  SM_cv_CPP11_STDC11=yes, SM_cv_CPP11_STDC11=no)
  CXXFLAGS="$ac_save_CXXFLAGS"
  AC_LANG_RESTORE
  ])


  if test "$SM_cv_CPP11_NATIVE" = yes ||
     test "$SM_cv_CPP11_STDC11" = yes; then
    AC_DEFINE(HAVE_STDCXX_11,,[Define if your compiler supports C++11 features. ])
  else
    AC_MSG_ERROR([You must have a compiler that supports c++11 constructs in order to build this program.])
  fi
])
