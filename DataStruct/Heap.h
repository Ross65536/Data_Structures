// Developed by Rostislav Khoptiy at liandtow@gmail.com
// contains an re-implementations of std::priority_queue


#ifndef __HEAPrk
#define __HEAPrk

#include "vector.h"
#include <cstddef>

typedef std::size_t integer_type;

namespace rk
{
	class Heap_Exception
	{

	};

	template <class T, class Container = rk::vector<T>, class LessComp = std::less<T>>
	class Heap // class - heap wich has max elemnt as top()
	{
	private:
		//data
		Container container;
		//functions

	public:
		Heap() {};
		Heap(const Heap<T, Container, LessComp> &heap) : container(heap) {};
		Heap<T, Container, LessComp> & operator= (const Heap<T, Container, LessComp> & heap) { if (this != &heap) container = heap.container; return *this; };
		bool empty() const{ return size() == 0; };
		const T& top() const { if (empty()) throw Heap_Exception(); return container.front(); };
		integer_type size() const { return container.size(); };
		void push(const T &val);
		void pop();
		void clear() { container.clear(); }
	};

	template<class T, class Container, class LessComp>
	inline void rk::Heap<T, Container, LessComp>::push(const T & val)
	{
		LessComp less_op;
		auto val_index = size(); // index of to be pushed value
		container.push_back(val);

		const auto begin_itr = container.begin();
		
		for (auto prev_elem_index = (val_index - 1) >> 1;
			prev_elem_index != (integer_type(-1) >> 1) && less_op(*(begin_itr + prev_elem_index), *(begin_itr + val_index));
			val_index = prev_elem_index, prev_elem_index = (prev_elem_index - 1 )>> 1)
		{
			swap(*(begin_itr + prev_elem_index),*(begin_itr + val_index));
		}

	}

	template<class T, class Container, class LessComp>
	inline void rk::Heap<T, Container, LessComp>::pop()
	{
		if (empty())
			throw Heap_Exception();

		LessComp less_op;
		const auto begin_itr = container.begin();
		const auto back_index = size() - 1;
		const T& back_val = *(begin_itr + back_index);

		for (integer_type i = 0; ;)
		{
			const auto left_index = (i << 1) + 1;
			const auto right_index = (i << 1) + 2;
			auto& parent_val = *(begin_itr + i);

			if (left_index >= back_index ) // implies also that right index is out of bounds
			{
				parent_val = back_val;
				break;
			}
			else if (right_index >= back_index)
			{
				auto& left_val = *(begin_itr + left_index);
				if (less_op(left_val, back_val))
				{
					parent_val = back_val;
					
				}
				else
				{
					parent_val = left_val;
					left_val = back_val;
				}
				break;
			}
			auto& left_val = *(begin_itr + left_index);
			auto& right_val = *(begin_itr + right_index);
			

			if (less_op(left_val, back_val) && less_op(right_val, back_val))
			{
				parent_val = back_val;
				break;
			}
			else if (less_op(left_val, right_val))
			{
				parent_val = right_val;
				i = right_index;
			}
			else
			{
				parent_val = left_val;
				i = left_index;
			}
		}

		container.pop_back();

	}

}


#endif

