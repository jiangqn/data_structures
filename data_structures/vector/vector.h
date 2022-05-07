#ifndef _INT_VECTOR_
#define _INT_VECTOR_

#include <iostream>
#include <assert.h>

namespace data_structures
{

    const int vector_default_memory_size = 32;

    class vector
    {
    public:
        vector();
        vector(const vector &v);
        ~vector();
        int size() const { return _size; }
        int memory_size() const { return _memory_size; }
        bool empty() const { return _size == 0; }
        void push_back(int item);
        void pop_back();
        int back() const;
        void clear();
        int &operator[](int index) const
        {
            assert(index >= 0 && index < _size);
            return _data[index];
        }
        vector &operator=(const vector &v);
        bool operator==(const vector &v) const;
        bool operator!=(const vector &v) const { return !(*this == v); }

        friend std::ostream &operator<<(std::ostream &os, const vector &v);

    private:
        int _size;
        int _memory_size;
        int *_data;

        void expand();
        void shrink();
    };

} // end of namespace

#endif