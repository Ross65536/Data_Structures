#ifndef __HASHTABLErk
#define __HASHTABLErk

#include <cstddef>


using std::size_t;

namespace rk {

	static const size_t Hash_primes[] = { 67, 131, 263, 521, 1031, 2053, 4099, 8209, 16411, 32771, 65539, 131101, 262147, 524309, 1048583, 2097169, 4194319, 8388617, 16777259, 33554467, 67108879, 134217757, 268435459, 536870923, 1073741827, 4294967299, 4294967299, 8589934595, 17179869187, 34359738371, 68719476739, 137438953475, 274877906947, 549755813891, 1099511627779, 2199023255555, 4398046511107, 8796093022211, 17592186044419, 35184372088835, 70368744177667, 140737488355331, 281474976710659, 562949953421315, 1125899906842627, 2251799813685251, 4503599627370499, 9007199254740995, 18014398509481987, 36028797018963971, 72057594037927939, 144115188075855875, 288230376151711747, 576460752303423491, 1152921504606846979, 2305843009213693955, 4611686018427387907, 9223372036854775811 }; ///< primes for HashTable table size, all primes are the closest ones to the highest power of 2. goes up to about 2^63

	enum HashElementType { EMPTY, OCCUPIED, DELETED };

	template <class T>
	struct HashElement
	{
		//data
		HashElementType state;
		T value;
		//funcitons
		HashElement(const T &val = T(), HashElementType state = EMPTY) : value(val), state(state) {}
	};

	// class - HashTable
	template <class T, class HashFunction = std::hash<T>, class PredEqual = std::equal_to<T>>
	class HashTable
	{
	private:
		//data
		T Value_Not_Found;
		HashElement<T>* hash_array;
		size_t array_size;
		size_t num_elements;
		size_t Hash_primes_index;
		//functions
		HashElement<T>* find_location(const T &val, HashElement<T>* &first_deleted_ptr);
		void grow_table();
	public:
		HashTable(const T &Not_Found_Value = T (), size_t min_num_elems = 0);
		HashTable(const HashTable<T, HashFunction, PredEqual> &table);
		HashTable<T, HashFunction, PredEqual>& operator=(const HashTable<T, HashFunction, PredEqual> &table);
		~HashTable() { delete[] hash_array; };
		bool insert(const T &val);
		const T& find(const T&val);
		bool erase(const T &val);
		bool empty() { return num_elements == 0; }
		size_t size() { return num_elements; }
		size_t table_size() { return array_size; }
		void clear();
		
	};


	template<class T, class HashFunction, class PredEqual>
	inline HashElement<T>* HashTable<T, HashFunction, PredEqual>::find_location(const T & val, HashElement<T>* &first_deleted_ptr)
	{
		HashFunction hash;
		PredEqual eq;

		first_deleted_ptr = NULL;

		size_t hash_val = hash(val);

		for (size_t i = 0; ; i++)
		{
			size_t index = (hash_val + i*i) % array_size;
			
			switch (hash_array[index].state)
			{
				case EMPTY:
				{
					return &hash_array[index];
					break;
				}
				case OCCUPIED:
				{
					if (eq(val, hash_array[index].value))
					{
						return &hash_array[index];
					}
					break;
				}
				case DELETED:
				{
					if (first_deleted_ptr == NULL)
					{
						first_deleted_ptr = &hash_array[index];
					}
					break;
				}
			}
		}

		return NULL;
	}

	template<class T, class HashFunction, class PredEqual>
	inline HashTable<T, HashFunction, PredEqual>::HashTable(const T & Not_Found_Value= T(), size_t min_num_elems = 0) : Value_Not_Found(Not_Found_Value), Hash_primes_index(0), num_elements(0), array_size(0)
	{
		while (2*min_num_elems > Hash_primes[Hash_primes_index] )
		{
			Hash_primes_index++;
		}

		array_size = Hash_primes[Hash_primes_index];

		hash_array = new HashElement<T>[array_size];

 	}

	template<class T, class HashFunction, class PredEqual>
	HashTable<T, HashFunction, PredEqual>::HashTable(const HashTable<T, HashFunction, PredEqual> &table) : Hash_primes_index(table.Hash_primes_index), Value_Not_Found(table.Value_Not_Found), array_size(table.array_size), num_elements(0)
	{
		this->hash_array = new HashElement<T>[table.array_size];

		for (size_t i = 0, num = 0; num < table.num_elements; i++)
		{
			if (table.hash_array[i].state == OCCUPIED)
			{
				this->insert(table.hash_array[i].value);
				num++;
			}
		}


	}

	template<class T, class HashFunction, class PredEqual>
	HashTable<T, HashFunction, PredEqual>& HashTable<T, HashFunction, PredEqual>::operator=(const HashTable<T, HashFunction, PredEqual>& table)
	{
		if (this == &table)
			return *this;

		Hash_primes_index = table.Hash_primes_index;
		Value_Not_Found = table.Value_Not_Found;
		array_size = table.array_size;
		num_elements = 0;

		delete[] hash_array;

		this->hash_array = new HashElement<T>[table.array_size];

		for (size_t i = 0, num = 0; num < table.num_elements; i++)
		{
			if (table.hash_array[i].state == OCCUPIED)
			{
				this->insert(table.hash_array[i].value);
				num++;
			}
		}

		return *this;
	}

	template<class T, class HashFunction, class PredEqual>
	bool HashTable<T, HashFunction, PredEqual>::insert(const T & val)
	{
		if (num_elements >= array_size / 2)
		{
			this->grow_table();
		}

		HashElement<T>* first_deleted;
		auto find_ptr = find_location(val, first_deleted);

		if (find_ptr->state == EMPTY)
		{
			if (first_deleted != NULL)
			{
				find_ptr = first_deleted;
			}

			find_ptr->state = OCCUPIED;
			find_ptr->value = val;
			num_elements++;
			return true;
		}

		return false;

	}

	template<class T, class HashFunction, class PredEqual>
	const T & HashTable<T, HashFunction, PredEqual>::find(const T & val)
	{
		HashElement<T>* first_deleted;
		auto find_ptr = find_location(val, first_deleted);

		if (find_ptr->state == OCCUPIED)
		{
			return find_ptr->value = val;
		}

		return Value_Not_Found;
	}

	template<class T, class HashFunction, class PredEqual>
	bool HashTable<T, HashFunction, PredEqual>::erase(const T & val)
	{
		HashElement<T>* first_deleted;
		auto find_ptr = find_location(val, first_deleted);

		if (find_ptr->state == OCCUPIED)
		{
			find_ptr->state = DELETED;
			num_elements--;
			return true;
		}

		return false;
	}

	template<class T, class HashFunction, class PredEqual>
	void HashTable<T, HashFunction, PredEqual>::clear()
	{
		num_elements = 0;

		for (size_t i = 0; i < array_size; i++)
		{
			if (hash_array[i].state != EMPTY)
				hash_array[i].state = EMPTY;
		}
	}

	template<class T, class HashFunction, class PredEqual>
	inline void HashTable<T, HashFunction, PredEqual>::grow_table()
	{
		if (Hash_primes_index == sizeof(Hash_primes) - 1)
			return;

		Hash_primes_index++;
		auto old_size = array_size;
		auto old_array = hash_array;
		auto old_num_elems = num_elements;

		array_size = Hash_primes[Hash_primes_index];
		num_elements = 0;

		hash_array = new HashElement<T>[array_size];

		for (size_t i = 0, num = 0; num < old_num_elems; i++)
		{
			if (old_array[i].state == OCCUPIED)
			{
				this->insert(old_array[i].value);
				num++;
			}
		}

		delete[] old_array;


	}



}

#endif