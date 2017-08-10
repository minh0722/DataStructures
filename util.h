#ifndef UTIL
#define UTIL

namespace Util
{
    template <typename T>
    void Swap(T& left, T& right)
    {
        T temp = left;
        left = right;
        right = temp;
    }
}

#endif // UTIL