/*
 * Copyright (C) 2012  Samuel Hug
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H

#include <algorithm> // for std::min
#include <cassert>
#include <cstring>

template <class T>
class CircularBuffer
{
    public:
        CircularBuffer(size_t capacity);
        ~CircularBuffer();

        size_t size() const { return size_; }
        size_t capacity() const { return capacity_; }

        // Return number of items written.
        size_t write(const T *data, size_t count);

        T* at(size_t offset);

        // Return number of items read.
        size_t read(T *data, size_t count);

        // If del is false, will do a non-destructive read.
        size_t read(T *data, size_t count, bool del);

    private:
        size_t size_;
        size_t capacity_;
        
        T *cursor_beg_ptr, *cursor_end_ptr;

        T *data_beg_ptr;
        T *data_end_ptr;
};

template <class T>
CircularBuffer<T>::CircularBuffer(size_t capacity) :
    size_(0), 
    capacity_(capacity)
{
    data_beg_ptr = new T[capacity];
    data_end_ptr = data_beg_ptr + capacity;

    cursor_beg_ptr = data_beg_ptr;
    cursor_end_ptr = cursor_beg_ptr;
}

template <class T>
CircularBuffer<T>::~CircularBuffer()
{
    delete [] data_beg_ptr;
}

template <class T>
size_t CircularBuffer<T>::write(const T *data, size_t count)
{
    if (count == 0) return 0;

    assert (count <= capacity() - size());

    // Write in a single step
    if (cursor_end_ptr + count <= data_end_ptr)
    {
        memcpy(cursor_end_ptr, data, count*sizeof(T));
        cursor_end_ptr += count;
        if (cursor_end_ptr == data_end_ptr) cursor_end_ptr = data_beg_ptr;
    }

    // Write in two steps
    else
    {
        // 1st step
        size_t n_items_1 = data_end_ptr - cursor_end_ptr;
        memcpy(cursor_end_ptr, data, n_items_1*sizeof(T));

        // 2nd step
        size_t n_items_2 = count - n_items_1;
        memcpy(data_beg_ptr, data + n_items_1, n_items_2*sizeof(T));

        cursor_end_ptr = data_beg_ptr + n_items_2;
    }

    //TODO: Fix this
    size_ += count;
    return count;
}

template <class T>
T* CircularBuffer<T>::at(size_t offset)
{
    assert(offset <= size());

    return data_beg_ptr + offset;
}

template <class T>
size_t CircularBuffer<T>::read(T *data, size_t count)
{
    return read(data, count, true);
}

template <class T>
size_t CircularBuffer<T>::read(T *data, size_t count, bool del)
{
    if (count == 0) return 0;

    assert (count <= size());

    // Read in a single step
    if (count <= data_end_ptr - cursor_beg_ptr)
    {
        memcpy(data, cursor_beg_ptr, count*sizeof(T));

        // If this is a destructive read
        if (del) {
            cursor_beg_ptr += count;
            if (cursor_beg_ptr == data_end_ptr) cursor_beg_ptr = data_beg_ptr;
        }
    }

    // Read in two steps
    else
    {
        // 1st step
        size_t n_items_1 = data_end_ptr - cursor_beg_ptr;
        memcpy(data, cursor_beg_ptr, n_items_1*sizeof(T));

        // 2nd step
        size_t n_items_2 = count - n_items_1;
        memcpy(data + n_items_1, data_beg_ptr, n_items_2*sizeof(T));

        // If this is a destructive read
        if (del) {
            cursor_beg_ptr = data_beg_ptr + n_items_2;
        }
    }

    if (del) {
        size_ -= count;
    }

    return count;
}

#endif
