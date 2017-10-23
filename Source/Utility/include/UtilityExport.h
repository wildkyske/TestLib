
#ifdef WIN32
#ifdef UTILITY_EXPORTS 
#define UTILITY_EXPORT __declspec(dllexport)
#else
#define UTILITY_EXPORT __declspec(dllimport)
#endif
#else
#define UTILITY_EXPORT
#endif

