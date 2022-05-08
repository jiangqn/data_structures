#include <assert.h>

#include "vector.h"

namespace data_structures
{
    vector::vector()
    {
        _size = 0;
        _memory_size = vector_default_memory_size;
        _data = new int[_memory_size];
    }

    vector::vector(const vector &v)
    {
        _size = v._size;
        _memory_size = v._memory_size;
        _data = new int[_memory_size];
        for (int i = 0; i < _size; i++)
        {
            _data[i] = v._data[i];
        }
    }

    vector::~vector()
    {
        delete[] _data;
    }

    void vector::push_back(int item)
    {
        if (_size == _memory_size)
        {
            expand();
        }
        _data[_size] = item;
        _size += 1;
    }

    void vector::pop_back()
    {
        assert(_size > 0);
        _size -= 1;
        if (_memory_size >= _size * 2 && _memory_size > vector_default_memory_size)
        {
            shrink();
        }
    }

    int &vector::back() const
    {
        assert(_size > 0);
        return _data[_size - 1];
    }

    void vector::expand()
    {
        _memory_size = 2 * _memory_size;
        int *data = new int[_memory_size];
        for (int i = 0; i < _size; i++)
        {
            data[i] = _data[i];
        }
        delete[] _data;
        _data = data;
    }

    void vector::shrink()
    {
        assert(_memory_size >= _size * 2 && _memory_size > vector_default_memory_size);
        _memory_size = _memory_size / 2;
        int *data = new int[_memory_size];
        for (int i = 0; i < _size; i++)
        {
            data[i] = _data[i];
        }
        delete[] _data;
        _data = data;
    }

    void vector::clear()
    {
        _size = 0;
        if (_memory_size != vector_default_memory_size)
        {
            _memory_size = vector_default_memory_size;
            delete[] _data;
            _data = new int[_memory_size];
        }
    }

    vector &vector::operator=(const vector &v)
    {
        if (this != &v)
        {
            _size = v._size;
            _memory_size = v._memory_size;
            delete[] _data;
            _data = new int[_memory_size];
            for (int i = 0; i < _size; i++)
            {
                _data[i] = v._data[i];
            }
        }
        return *this;
    }

    bool vector::operator==(const vector &v) const
    {
        bool flag = true;
        if (this != &v)
        {
            if (_size == v._size)
            {
                for (int i = 0; i < _size; i++)
                {
                    if (_data[i] != v._data[i])
                    {
                        flag = false;
                        break;
                    }
                }
            }
            else
            {
                flag = false;
            }
        }
        return flag;
    }

    std::ostream &operator<<(std::ostream &os, const vector &v)
    {
        os << "\nvector with " << v._size << " items.\n";
        for (int i = 0; i < v._size; i++)
        {
            os << v._data[i] << (i == v._size - 1 ? '\n' : ' ');
        }
        return os;
    }
}