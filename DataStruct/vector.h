#ifndef __VECTORrk
#define __VECTORrk

#include <cstddef>

using std::size_t;



namespace rk
{
	class vector_Exception
	{
	};

	template <class T>
	class vector
	{
	private:
		//data
		T* data_array;
		size_t array_size;
		size_t num_elems;
		//functions
		void increase_storage();

	public:
		vector(size_t count =0);
		vector(size_t count, const T& copy_value);
		~vector() { delete[] data_array; };
		T& operator[](size_t index) { return data_array[index]; };
		size_t size() const { return num_elems; };
		bool empty() const { return num_elems == 0; };
		size_t capacity() const { return array_size; }
		void push_back(const T& val);
		void pop_back() { if (num_elems != 0) num_elems--; };
		T& front() const { if (num_elems == 0) throw rk::vector_Exception; return data_array[0]; };
		T& back() const { if (num_elems == 0) throw rk::vector_Exception; return data_array[num_elems - 1]; };
		T& at(size_t index) const{ if (index >= num_elems) throw rk::vector_Exception; return data_array[index]; };
		void clear() { num_elems = 0; };
		
	};

	template<class T>
	void vector<T>::increase_storage()
	{
		T* old_arr = data_array;

		array_size = array_size << 1;
		data_array = new T[array_size]

		for (size_t i = 0; i < num_elems; i++)
		{
			data_array[i] = old_arr[i];
		}

		delete[] old_arr;

	}

	template<class T>
	inline vector<T>::vector(size_t count) : num_elems(count), array_size(32)
	{
		while (count > array_size)
		{
			array_size  = array_size << 1;
		}

		data_array = new T[array_size];
	}

	template<class T>
	inline vector<T>::vector(size_t count, const T & copy_value ) : num_elems(count), array_size(32)
	{
		while (count > array_size)
		{
			array_size  = array_size << 1;
		}

		data_array = new T[array_size];

		
		for (size_t i = 0; i < count; i++)
			data_array[i] = copy_value;

	}

	template<class T>
	inline void vector<T>::push_back(const T & val)
	{
		if (num_elems == array_size)
		{
			increase_storage();
		}

		data_array[num_elems] = val;
		num_elems++;

	}




}



#endif