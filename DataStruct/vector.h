#ifndef __VECTORrk
#define __VECTORrk

#include <cstddef>
#include <initializer_list>

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
		void increase_storage(size_t min_elems);
		void fit_to_size_storage();
	public:
		vector(size_t count =0);
		vector(size_t count, const T& copy_value);
		vector(vector<T> &vec);
		vector(std::initializer_list<T> list);
		vector<T>& operator=(vector<T> &vec);
		~vector() { delete[] data_array; };
		T& operator[](size_t index) { return data_array[index]; };
		size_t size() const { return num_elems; };
		bool empty() const { return num_elems == 0; };
		size_t capacity() const { return array_size; }
		void push_back(const T& val);
		void pop_back() { if (num_elems != 0) num_elems--; };
		T& front() const { if (num_elems == 0) throw rk::vector_Exception(); return data_array[0]; };
		T& back() const { if (num_elems == 0) throw rk::vector_Exception(); return data_array[num_elems - 1]; };
		T& at(size_t index) const{ if (index >= num_elems) throw rk::vector_Exception(); return data_array[index]; };
		void clear() { num_elems = 0; };
		void resize(size_t count);
		void resize(size_t count, const T& val );
		void shrink_to_fit() { fit_to_size_storage(); };
		void reserve(size_t count) { if (count > array_size) increase_storage(count); };
	};

	template<class T>
	void vector<T>::increase_storage(size_t min_elems)
	{
		T* old_arr = data_array;

		while (min_elems > array_size)
		{
			array_size = array_size << 1;
		}
		data_array = new T[array_size];

		for (size_t i = 0; i < num_elems; i++)
		{
			data_array[i] = old_arr[i];
		}

		delete[] old_arr;

	}

	template<class T>
	inline void vector<T>::fit_to_size_storage()
	{
		
		size_t old_array_size = array_size;
		while (num_elems <= array_size)
		{
			array_size = array_size >> 1;
		}
		array_size = array_size << 1;
		if (array_size < 32)
			array_size = 32;

		if (old_array_size == array_size)
			return;


		T* old_arr = data_array;

		data_array = new T[array_size];

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
	inline vector<T>::vector(vector<T>& vec) : num_elems(vec.num_elems), array_size(vec.array_size)
	{
		data_array = new T[array_size];

		for (size_t i = 0; i < num_elems; i++)
			data_array[i] = vec.data_array[i]; 
	}

	template<class T>
	inline vector<T>::vector(std::initializer_list<T> list) : num_elems(list.size()), array_size(32)
	{
		while (num_elems > array_size)
		{
			array_size = array_size << 1;
		}
		data_array = new T[array_size];

		auto itr = list.begin();
		for (size_t i = 0; itr != list.end(); i++, itr++)
			data_array[i] = *itr;
	}

	template<class T>
	inline vector<T>& vector<T>::operator=(vector<T>& vec)
	{
		if (this == &vec)
			return *this;

		delete[] this->data_array;

		array_size = vec.array_size;
		num_elems = vec.num_elems;

		data_array = new T[array_size];

		for (size_t i = 0; i < num_elems; i++)
			data_array[i] = vec.data_array[i];


		return *this;
	}

	template<class T>
	inline void vector<T>::push_back(const T & val)
	{
		if (num_elems == array_size)
		{
			increase_storage(num_elems+1);
		}

		data_array[num_elems] = val;
		num_elems++;

	}

	template<class T>
	inline void vector<T>::resize(size_t count)
	{
		if (count > array_size)
		{
			increase_storage(count);

		}
		
		
		if (count < num_elems)
		{
			num_elems = count;
			return;
		}
		else if (count > num_elems)
		{
			num_elems = count;
		}
	}

	template<class T>
	inline void vector<T>::resize(size_t count, const T & val)
	{
		size_t old_num_elems = num_elems;
		this->resize(count);

		if (count > old_num_elems)
			for (size_t i = old_num_elems; i < count; i++)
			{
				data_array[i] = val;
			}
	}






}



#endif