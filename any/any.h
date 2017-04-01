#ifndef ANY_H
#define ANY_H

#include <bits/stdc++.h>
#include "any_helper.h"

struct any {
private:
    static const size_t MAX_SIZE = 16;

    enum object_type {SMALL, BIG, EMPTY};

    object_type state;
    std::aligned_storage<MAX_SIZE, MAX_SIZE>::type data;

    void (*deleter) (void*);
    void (*copier) (void*, void const*);
    void (*mover) (void*, void*);
    void* (*allocator) (void);

    void clear() {
        if (state == SMALL) {
            deleter(&data);
        }
        if (state == BIG) {
            deleter(*(void**) &data);
        }
        state = EMPTY;
    }

    void* get_ptr() const {
        switch(state) {
            case SMALL:
                return (void*) &data;
            case BIG:
                return *(void**) &data;
            default:
                return nullptr;
        }
    }

public:
    any() : state(EMPTY), deleter([](void*){}), copier([](void*, void const*){}),
        mover([](void*, void*){}), allocator([]() -> void* {return nullptr;}),
        data({}) 
    {};

    any(any const &other) : state(other.state), deleter(other.deleter), 
        copier(other.copier), mover(other.mover), allocator(other.allocator) {
        
        switch(state) {
            case SMALL:
                copier(&data, &other.data);
                break;
            case BIG:
                void* ptr = allocator();
                copier(ptr, *(void**) &other.data);
                *(void**) &data = ptr;
                break;
        }
    }

    any(any &&other) : state(other.state), deleter(other.deleter), 
        copier(other.copier), mover(other.mover), allocator(other.allocator) {
        
        switch(state) {
            case SMALL:
                mover(&data, &other.data);
                break;
            case BIG:
                void* ptr = allocator();
                mover(ptr, *(void**) &other.data);
                break;
        }   
    }

    template <typename T, typename UNUSED = typename std::enable_if<!std::is_same<std::decay_t<T>, any>::value>::type>
    any(T&& val) {
        using T_decay = std::decay_t<T>;

        if (sizeof(T_decay) <= MAX_SIZE && std::is_nothrow_move_constructible<T_decay>::value) {
            state = SMALL;
            new (&data) T_decay(std::forward<T>(val));
            deleter = any_helper::small_object_deleter<T_decay>;
        } else {
            state = BIG;
            void* ptr = new T_decay(std::forward<T>(val));
            *(void**) &data = ptr;
            deleter = any_helper::big_object_deleter<T_decay>;
        }

        copier = any_helper::my_copier<T_decay>;
        mover = any_helper::my_mover<T_decay>;
        allocator = any_helper::my_allocator<T_decay>;
    }

    any& operator=(any const &other) {
        any(other).swap(*this);
        return *this;
    }

    any& operator=(any&& other) {
        any(std::move(other)).swap(*this);
        return *this;
    }

    template <typename T, typename UNUSED = typename std::enable_if<!std::is_same<std::decay_t<T>, any>::value>::type>
    any& operator=(T&& other) {
        any(std::forward<T>(other)).swap(*this);
        return *this;
    }

    ~any() {
        clear();
    }

    void swap(any& other) {
        if (state == SMALL) {
            std::aligned_storage<MAX_SIZE, MAX_SIZE>::type temporary;
            if (other.state == SMALL) {
                mover(&temporary, &data);
                deleter(&data);

                other.mover(&data, &other.data); 
                other.deleter(&other.data);

                mover(&other.data, &temporary);
            } else {
                mover(&temporary, &data);
                deleter(&data);

                std::swap(*(void**) &data, *(void**) &other.data);

                mover(&other.data, &temporary);
            }
           	deleter(&temporary);
        } else {
            if (other.state == SMALL) {
                
                std::aligned_storage<MAX_SIZE, MAX_SIZE>::type temporary;
                other.mover(&temporary, &other.data);
                other.deleter(&other.data);

                std::swap(*(void**) &other.data, *(void**) &data);
                other.mover(&data, &temporary);
                
                other.deleter(&temporary);
            } else {
                std::swap(*(void**) &data, *(void**) &other.data);
            }
        }

        std::swap(state, other.state);
        std::swap(deleter, other.deleter);
        std::swap(copier, other.copier);
        std::swap(mover, other.mover);
        std::swap(allocator, other.allocator);
    }


    template <typename T>
    friend T any_cast(const any& obj);

    template <typename T>
    friend T any_cast(any& obj);

    template <typename T>
    friend T any_cast(any&& obj);

    template <typename T>
    friend T const * any_cast(any const *obj);

    template <typename T>
    friend T * any_cast(any *obj);
};


template <typename T>
T any_cast(const any& obj) {
    return *(std::add_const_t<std::remove_reference_t<T>>*) obj.get_ptr();
}

template <typename T>
T any_cast (any& obj) {
    return *(std::remove_reference_t<T> *) obj.get_ptr();
}

template <typename T>
T any_cast (any&& obj) {
    return *(std::remove_reference_t<T> *) obj.get_ptr();
}

template <typename T>
T const * any_cast(any const *obj) {
    return obj -> get_ptr();
}

template <typename T>
T * any_cast(any *obj) {
    T* result = obj -> get_ptr();
    return result;
}

#endif
