#include <bits/stdc++.h>
#ifndef ANY_HELPER_H
#define ANY_HELPER_H

namespace any_helper {


    template <typename TYPE>
    void big_object_deleter(void* obj) {
        delete ((TYPE*) obj);
    }

    template <typename TYPE>
    void* my_allocator() {
        return new typename std::aligned_storage<sizeof(TYPE), alignof(TYPE)>::type;
    }

    template <typename TYPE>
    void my_copier(void* dest, void const* src) {
        new (dest) TYPE(*(TYPE const*) src);
    }

    

    template <typename TYPE>
    void small_object_deleter(void* obj) {
        ((TYPE*) obj) -> ~TYPE();
    }

    template <typename TYPE>
    void my_mover(void* dst, void* src) {
        new (dst) TYPE(std::move(*(TYPE*)src));
    }
}

#endif
