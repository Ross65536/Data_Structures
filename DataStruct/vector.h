#ifndef __VECTORrk
#define __VECTORrk

#include <cstddef>
#include <initializer_list>
#include <iterator>


typedef std::size_t integer_type;

namespace rk
{
	template <class data_type, class ret_value = data_type>
	class vector_Iterator;

	class vector_Exception
	{
	};

	template <class T>
	class vector
	{
	private:
		friend vector_Iterator<T>;
		friend vector_Iterator<T, const T>;
		//data
		T* data_array;
		integer_type array_size;
		integer_type num_elems;
		//functions
		void increase_storage(integer_type min_elems);
		void fit_to_size_storage();
	public:
		typedef vector_Iterator<T> iterator;
		typedef vector_Iterator<T, const T> const_iterator;
		//typedef	std::reverse_iterator<iterator>	reverse_iterator;
		//typedef	std::reverse_iterator<const_iterator> const_reverse_iterator;
		vector();
		vector(integer_type count);
		vector(integer_type count, const T& copy_value);
		vector(const vector<T> &vec);
		vector(const std::initializer_list<T> &list);
		vector<T>& operator=(const vector<T> &vec);
		~vector() { delete[] data_array; };
		T& operator[](integer_type index) { return data_array[index]; };
		integer_type size() const { return num_elems; };
		bool empty() const { return num_elems == 0; };
		integer_type capacity() const { return array_size; }
		void push_back(const T& val);
		void pop_back() { if (num_elems != 0) num_elems--; };
		T& front() const { if (num_elems == 0) throw rk::vector_Exception(); return data_array[0]; };
		T& back() const { if (num_elems == 0) throw rk::vector_Exception(); return data_array[num_elems - 1]; };
		T& at(integer_type index) const{ if (index >= num_elems) throw rk::vector_Exception(); return data_array[index]; };
		void clear() { num_elems = 0; };
		void resize(integer_type count);
		void resize(integer_type count, const T& val );
		void shrink_to_fit() { fit_to_size_storage(); };
		void reserve(integer_type count) { if (count > array_size) increase_storage(count); };
		iterator insert(vector_Iterator<T, T> itr, const T & val);
		iterator erase(vector_Iterator<T, T> itr);
		iterator begin() { return vector_Iterator<T>(this, 0); };
		iterator end() { return vector_Iterator<T>(this, num_elems); };
		const_iterator cbegin() const { return vector_Iterator<T, const T>(this, 0); };
		const_iterator cend() const { return vector_Iterator<T, const T>(this, num_elems); };
		//reverse_iterator rbegin() { return reverse_iterator(data_array); };
		//reverse_iterator rend() { return reverse_iterator(data_array + num_elems); };
		//const_reverse_iterator crbegin() { return const_reverse_iterator(data_array); };
		//const_reverse_iterator crend() { return const_reverse_iterator(data_array + num_elems); };

	};

	template<class T>
	void vector<T>::increase_storage(integer_type min_elems)
	{
		T* old_arr = data_array;

		while (min_elems > array_size)
		{
			array_size = array_size << 1;
		}
		data_array = new T[array_size];

		for (integer_type i = 0; i < num_elems; i++)
		{
			data_array[i] = old_arr[i];
		}

		delete[] old_arr;

	}

	template<class T>
	inline void vector<T>::fit_to_size_storage()
	{
		
		integer_type old_array_size = array_size;
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

			for (integer_type i = 0; i < num_elems; i++)
			{
				data_array[i] = old_arr[i];
			}

		delete[] old_arr;
	}

	template<class T>
	inline rk::vector<T>::vector() : num_elems(0), array_size(16)
	{
		data_array = new T[array_size];
	}

	template<class T>
	inline vector<T>::vector(integer_type count) : num_elems(count), array_size(16)
	{
		while (count > array_size)
		{
			array_size  = array_size << 1;
		}

		data_array = new T[array_size];
	}

	template<class T>
	inline vector<T>::vector(integer_type count, const T & copy_value ) : num_elems(count), array_size(16)
	{
		while (count > array_size)
		{
			array_size  = array_size << 1;
		}

		data_array = new T[array_size];

		
		for (integer_type i = 0; i < count; i++)
			data_array[i] = copy_value;

	}

	template<class T>
	inline vector<T>::vector(const vector<T>& vec) : num_elems(vec.num_elems), array_size(vec.array_size)
	{
		data_array = new T[array_size];

		for (integer_type i = 0; i < num_elems; i++)
			data_array[i] = vec.data_array[i]; 
	}

	template<class T>
	inline rk::vector<T>::vector(const std::initializer_list<T>& list) : num_elems(list.size()), array_size(32)
	{
		while (num_elems > array_size)
		{
			array_size = array_size << 1;
		}
		data_array = new T[array_size];

		auto itr = list.begin();
		for (integer_type i = 0; itr != list.end(); i++, itr++)
			data_array[i] = *itr;
	}

	template<class T>
	inline vector<T>& vector<T>::operator=(const vector<T>& vec)
	{
		if (this == &vec)
			return *this;

		delete[] this->data_array;

		array_size = vec.array_size;
		num_elems = vec.num_elems;

		data_array = new T[array_size];

		for (integer_type i = 0; i < num_elems; i++)
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
	inline void vector<T>::resize(integer_type count)
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
	inline void vector<T>::resize(integer_type count, const T & val)
	{
		integer_type old_num_elems = num_elems;
		this->resize(count);

		if (count > old_num_elems)
			for (integer_type i = old_num_elems; i < count; i++)
			{
				data_array[i] = val;
			}
	}

	template<class T>
	inline typename vector<T>::iterator vector<T>::insert(vector_Iterator<T, T> itr, const T & val)
	{
		if (itr.ptr < data_array || itr.ptr > data_array + num_elems)
			return this->end();

		auto ret = itr;
		T next_val = val;
		for (;itr != this->end(); itr++)
		{
			swap(next_val, *itr);
		}
		this->push_back(next_val);

		return ret;
	}

	template<class T>
	inline typename vector<T>::iterator vector<T>::erase(vector_Iterator<T, T> itr)
	{
		if (itr.ptr < data_array || itr.ptr >= data_array + num_elems)
			return this->end();

		

		auto ret = --this->end();
		T next_val = *ret;
		--ret;
		for (; ret >= itr; --ret)
		{
			swap(next_val, *ret);
		}
		
		--num_elems;

		return itr;
	}


	template <class data_type, class ret_value = data_type>
	class vector_Iterator : public std::iterator<std::random_access_iterator_tag, ret_value>
	{
		friend vector_Iterator<data_type, data_type>;
		friend vector_Iterator<data_type, const  data_type>;
		friend vector<data_type>;
	private:
		vector<data_type> * container_ptr;
		integer_type index;
		vector_Iterator(vector<data_type> * container_ptr, integer_type index) : container_ptr(container_ptr), index(index) {};
	public:
		vector_Iterator() : container_ptr(NULL), index(0) {};
		vector_Iterator(vector_Iterator<data_type, data_type> &itr) : container_ptr(itr.container_ptr), index(itr.index) {};
		vector_Iterator(vector_Iterator<data_type, const data_type> &itr) : container_ptr(itr.container_ptr), index(itr.index) {};
		vector_Iterator<data_type, ret_value>& operator=(vector_Iterator<data_type, ret_value> &itr);
		vector_Iterator<data_type, ret_value> operator++(int);
		vector_Iterator<data_type, ret_value>& operator++();
		vector_Iterator<data_type, ret_value> operator--(int);
		vector_Iterator<data_type, ret_value> operator--();
		vector_Iterator<data_type, ret_value> operator+(integer_type offset);
		vector_Iterator<data_type, ret_value> operator-(integer_type offset);
		std::ptrdiff_t operator-(vector_Iterator<data_type, ret_value> &itr) {return (container_ptr->data_array + index) - ((itr.container_ptr)->data_array + itr.index);};
		vector_Iterator<data_type, ret_value>& operator+=(integer_type offset);
		vector_Iterator<data_type, ret_value>& operator-=(integer_type offset);
		bool operator!=(vector_Iterator<data_type, ret_value> &itr) const { return !(*this == itr); };
		bool operator==(vector_Iterator<data_type, ret_value> &itr) const { return (container_ptr->data_array + index) == ((itr.container_ptr)->data_array + itr.index); };
		bool operator<(vector_Iterator<data_type, ret_value> &itr) const { return (container_ptr->data_array + index) < ((itr.container_ptr)->data_array + itr.index); };
		bool operator>=(vector_Iterator<data_type, ret_value> &itr) const { return !(*this < itr); };
		ret_value& operator*() const { return (*container_ptr)[index]; };
		ret_value* operator->() const { return &(*this); };

	};



	template <class data_type, class ret_value = data_type>
	inline vector_Iterator<data_type, ret_value>& vector_Iterator<data_type, ret_value>::operator=(vector_Iterator<data_type, ret_value>& itr)
	{
		if (this == &itr)
			return *this;

		container_ptr=itr.container_ptr;
		index=itr.index;

		return *this;
	}

	template <class data_type, class ret_value = data_type>
	inline vector_Iterator<data_type, ret_value> vector_Iterator<data_type, ret_value>::operator++(int)
	{
		vector_Iterator<data_type, ret_value> old = *this;
		++index;
		return old; 
	}

	template <class data_type, class ret_value = data_type>
	inline vector_Iterator<data_type, ret_value> vector_Iterator<data_type, ret_value>::operator+(integer_type offset)
	{
		vector_Iterator<data_type, ret_value> tmp = *this;
		tmp+=offset;
		return tmp;
	}

	template <class data_type, class ret_value = data_type>
	inline vector_Iterator<data_type, ret_value>& vector_Iterator<data_type, ret_value>::operator+=(integer_type offset)
	{
		index += offset;
		return *this;
	}

	template <class data_type, class ret_value = data_type>
	inline vector_Iterator<data_type, ret_value>& vector_Iterator<data_type, ret_value>::operator-=(integer_type offset)
	{
		index -= offset;
		return *this;
	}

	template <class data_type, class ret_value = data_type>
	inline vector_Iterator<data_type, ret_value> vector_Iterator<data_type, ret_value>::operator-(integer_type offset)
	{
		vector_Iterator<data_type, ret_value> tmp = *this;
		tmp -= offset;
		return tmp;
	}

	template <class data_type, class ret_value = data_type>
	inline vector_Iterator<data_type, ret_value> vector_Iterator<data_type, ret_value>::operator--(int)
	{
		vector_Iterator<data_type, ret_value> old = *this;
		--index;
		return old;
	}

	template <class data_type, class ret_value = data_type>
	inline vector_Iterator<data_type, ret_value>& vector_Iterator<data_type, ret_value>::operator++()
	{
		
		++index;
		return *this;
	}

	template <class data_type, class ret_value = data_type>
	inline vector_Iterator<data_type, ret_value> rk::vector_Iterator<data_type, ret_value>::operator--()
	{
		
		--index;
		return *this;
	}

}



#endif