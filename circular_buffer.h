#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H

#include <algorithm> // for std::min
#include <cstring>

template <class T>
class CircularBuffer
{
    public:
        CircularBuffer(size_t capacity);
        ~CircularBuffer();

        size_t size() const { return size_; }
        size_t capacity() const { return capacity_; }
        // Return number of bytes written.
        size_t write(const T *data, size_t count);
        // Return number of bytes read.
        size_t read(T *data, size_t count);

    private:
        size_t beg_index_, end_index_, size_, capacity_;
        T *data_;
};

template <class T>
CircularBuffer<T>::CircularBuffer(size_t capacity)
    : beg_index_(0)
    , end_index_(0)
    , size_(0)
    , capacity_(capacity)
{
    data_ = new T[capacity];
}

template <class T>
CircularBuffer<T>::~CircularBuffer()
{
    delete [] data_;
}

template <class T>
size_t CircularBuffer<T>::write(const T *data, size_t count)
{
    if (count == 0) return 0;

    size_t capacity = capacity_;
    size_t bytes_to_write = std::min(count, capacity - size_)*sizeof(T);

    // Write in a single step
    if (bytes_to_write <= capacity*sizeof(T) - end_index_)
    {
        memcpy((void*)data_ + end_index_, data, bytes_to_write);
        end_index_ += bytes_to_write;
        if (end_index_ == capacity*sizeof(T)) end_index_ = 0;
    }
    // Write in two steps
    else
    {
        size_t size_1 = capacity*sizeof(T) - end_index_;
        memcpy((void*)data_ + end_index_, data, size_1);
        size_t size_2 = bytes_to_write - size_1;
        memcpy(data_, (void*)data + size_1, size_2);
        end_index_ = size_2;
    }

    size_ += bytes_to_write;
    return bytes_to_write;
}

template <class T>
size_t CircularBuffer<T>::read(T *data, size_t count)
{
    if (count == 0) return 0;

    size_t capacity = capacity_;
    size_t bytes_to_read = std::min(count, size_)*sizeof(T);

    // Read in a single step
    if (bytes_to_read <= capacity*sizeof(T) - beg_index_)
    {
        memcpy(data, (void*)data_ + beg_index_, bytes_to_read);
        beg_index_ += bytes_to_read;
        if (beg_index_ == capacity*sizeof(T)) beg_index_ = 0;
    }
    // Read in two steps
    else
    {
        size_t size_1 = capacity*sizeof(T) - beg_index_;
        memcpy(data, (void*)data_ + beg_index_, size_1);
        size_t size_2 = bytes_to_read - size_1;
        memcpy((void*)data + size_1, data_, size_2);
        beg_index_ = size_2;
    }

    size_ -= bytes_to_read;
    return bytes_to_read;
}

#endif
