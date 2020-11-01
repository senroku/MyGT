#pragma once


/*
The Visual C++ compiler has historically had limited support for EBCO; however, in Visual Studio 2015 Update 2, we have added a new __declspec(empty_bases) attribute for class types that takes full advantage of this optimization
*/

#if defined(_MSC_VER) && _MSC_FULL_VER >= 190023918
#  define EMPTY_BASES __declspec(empty_bases) // VS2015 Update 2 à»ç~
#else
#  define EMPTY_BASES
#endif