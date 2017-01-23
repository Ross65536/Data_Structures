#pragma once
namespace rk
{
	template <class T, class Compare_Less = std::less<T> >
	class BST;

	//Node
	template <class T, class Compare_Less = std::less<T>>
	class BSTNode
	{
	private:
		friend class BST<T, Compare_Less>;
		T data;
		BSTNode<T, Compare_Less> * left;
		BSTNode<T, Compare_Less> * right;
		BSTNode(const T &val) : data(val), left(0), right(0) {};
	};

	template <class T, class Compare_Less >
	class BST
	{
	private:
		BSTNode<T, Compare_Less> * root;
		BSTNode<T, Compare_Less> * fail;
		BSTNode<T, Compare_Less> ** find_ptr(const T& val);
	public:
		BST(const T& fail_d = T()) : root(0) { fail = new BSTNode<T, Compare_Less>(fail_d); }
		void insert(const T& val);
		T& find(const T& val);
	};

	//Binary search tree class
	template <class T, class Compare_Less >
	void BST<T, Compare_Less>::insert(const T& val)
	{
		BSTNode<T, Compare_Less> ** found = find_ptr(val);

		if (*found == 0)
		{
			*found = new BSTNode<T, Compare_Less>(val);
		}
		else
		{
			return;
		}
	}

	template <class T, class Compare_Less >
	T& BST<T, Compare_Less>::find(const T& val)
	{
		BSTNode<T, Compare_Less> ** found = find_ptr(val);

		if (*found == 0)
			return fail->data;
		else
			return (*found)->data;
	}


	template <class T, class Compare_Less >
	BSTNode<T, Compare_Less> ** BST<T, Compare_Less>::find_ptr(const T& val)
	{
		if (root == 0)
		{
			return &root;
		}

		BSTNode<T, Compare_Less> * curr_node = root;
		while (true)
		{
			Compare_Less less;
			if (less(val, curr_node->data))
			{
				if (curr_node->left == 0)
					return &curr_node->left;
				else
					curr_node = curr_node->left;
			}
			else if (less(curr_node->data, val))
			{
				if (curr_node->right == 0)
					return &curr_node->right;
				else
					curr_node = curr_node->right;
			}
			else
			{
				return &curr_node;
			}
		}
	}















}