// ------------------------------------------------------------------------- //
//
// Type wrapper:  This is a wrapper to RTI Connext DDS types, which includes 
// a default constructor, a copy constructor, the = operator, and a 
// destructor.  This allows us to use RTI Connext DDS types in common C++
// patterns, and ensures that you do a deep copy of the contents of the data
// types.
//
// ------------------------------------------------------------------------- //

#ifndef DDS_TYPE_WRAPPER_H
#define DDS_TYPE_WRAPPER_H

template<typename T>
class DdsAutoType : public T {
public:

	// Constructor type for your generated data type
    DdsAutoType<T>() {
        if (T::TypeSupport::initialize_data(this) != DDS_RETCODE_OK) {
            throw std::bad_alloc("create_data");
        }
    }

	// Copy constructor that calls the TypeSupport::initialize_data for your
	// generated data type
    DdsAutoType<T>(const DdsAutoType<T> &rhs) {
        if (T::TypeSupport::initialize_data(this) != DDS_RETCODE_OK) {
            throw std::bad_alloc("initialize_data");
        }
        if (T::TypeSupport::copy_data(this, &rhs) != DDS_RETCODE_OK) {
            throw std::bad_alloc("copy_data");
        }
    }

	// = operator that allows assignment between two generated types.  
	// This calls FooTypeSupport::copy_data to do a deep copy of the 
	// data type, including pointers.
    DdsAutoType<T> operator=(const DdsAutoType<T> &rhs) {
        if (T::TypeSupport::copy_data(this, &rhs) != DDS_RETCODE_OK) {
            throw std::bad_alloc("copy_data");
        }
        return *this;
    }

	// Destory the data type, including any allocated pointers, etc.
    ~DdsAutoType<T>() {
        // in current implementation this never fails
        T::TypeSupport::finalize_data(this);
    }
};

#endif