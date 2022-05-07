#include "stack.h"

namespace data_structures
{
    std::ostream &operator<<(std::ostream &os, const stack &v)
    {
        os << "\nstack with " << v._data.size() << " items. (from bottom to top)\n";
        os << (*v._data.begin()) << '\n';
        return os;
    }
} // end of namespace