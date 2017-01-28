#pragma once
//a
namespace rk
{
	template <class T, class Compare_Less = std::less<T> >
	class RBT;

	//Class - Node
	template <class T, class Compare_Less = std::less<T>>
	class RBTNode
	{
	protected:
		friend class RBT<T, Compare_Less>;
		//data
		const T data;
		bool bred;
		RBTNode<T, Compare_Less> * left;
		RBTNode<T, Compare_Less> * right;
		//functions
		RBTNode(const T &val, bool bred=false) : data(val), left(0), right(0), bred(bred) {};
	};

	//Class - Binary search tree 
	template <class T, class Compare_Less >
	class RBT
	{
	protected:
		//data
		RBTNode<T, Compare_Less> * root;
		T fail_val;
		//functions
		RBTNode<T, Compare_Less> ** find_ptr(const T& val) const;
		RBTNode<T, Compare_Less> ** find_Max_from_Node_ptr(const RBTNode<T, Compare_Less> * const * Node) const;
		RBTNode<T, Compare_Less> ** find_Min_from_Node_ptr(const RBTNode<T, Compare_Less> * const * Node) const;
		void destroy_Subtree(RBTNode<T, Compare_Less> * Node_start);
		RBTNode<T, Compare_Less> * copy_Subtree(const RBTNode<T, Compare_Less> * original_Node);
	public:
		RBT(const T& fail_d = T()) : root(0), fail_val(fail_d) {};
		RBT(const RBT<T, Compare_Less> &RBT) : fail_val(RBT.fail_val) { root = copy_Subtree(RBT.root); };
		~RBT();
		void insert(const T& val);
		const T& find(const T& val) const;
		bool isEmpty() const { return root == 0; };
		const T& find_Max() const;
		const T& find_Min() const;
		void erase(const T& val);
		void clear();
		RBT& operator= (const RBT<T, Compare_Less> & rhs);
		/*const T& change_Not_Found_value(const T& fail_val) { this->fail_val = fail_val; };*/
		T& get_Not_Found_value() { return this->fail_val; };
	};


	template <class T, class Compare_Less >
	void RBT<T, Compare_Less>::insert(const T& val)
	{
		if (root == 0)
		{
			root = new RBTNode<T, Compare_Less>(val);
			return;
		}
		else
		{

			RBTNode<T, Compare_Less> ** grandparent_Node_location = NULL;
			RBTNode<T, Compare_Less> ** parent_Node_location = &root;
			//RBTNode<T, Compare_Less> ** parent_Node = Node_Location;
			bool bparent_left_of_grandparent = false;
			bool bcurrent_left_of_parent = false;

			bool brep = true;
			while (brep)
			{
				RBTNode<T, Compare_Less> * parent_Node = *parent_Node_location;

				Compare_Less less;
				if (less(val, parent_Node->data))
				{
					if (parent_Node->left == 0)
					{
						bcurrent_left_of_parent = true;
						brep = false;
					}
					else
					{
						grandparent_Node_location = parent_Node_location;
						parent_Node_location = &parent_Node->left;
						bparent_left_of_grandparent = true;
					}
				}
				else if (less(parent_Node->data, val))
				{
					if (parent_Node->right == 0)
					{
						bcurrent_left_of_parent = false;
						brep = false;
					}
					else
					{
						grandparent_Node_location = parent_Node_location;
						parent_Node_location = &parent_Node->right;
						bparent_left_of_grandparent = false;
					}

				}
				else
				{
					return;
				}
			}

			RBTNode<T, Compare_Less> * parent_Node = *parent_Node_location;
			RBTNode<T, Compare_Less> * grandparent_Node = *grandparent_Node_location;

			if (parent_Node->bred == false)
			{
				if (bcurrent_left_of_parent)
				{
					parent_Node->left = new RBTNode<T, Compare_Less>(val, true);
				}
				else
				{
					parent_Node->right = new RBTNode<T, Compare_Less>(val, true);
				}
			}
			else //parent is red
			{
				if (grandparent_Node->left->bred && grandparent_Node->right->bred) //parent and uncle red
				{
					if (bcurrent_left_of_parent)
					{
						parent_Node->left = new RBTNode<T, Compare_Less>(val, true);
					}
					else
					{
						parent_Node->right = new RBTNode<T, Compare_Less>(val, true);
					}

					grandparent_Node->left->bred = false;
					grandparent_Node->right->bred = false;
					grandparent_Node->bred = true;
				}
				else
				{
					if (bparent_left_of_grandparent == bcurrent_left_of_parent) // both left or right
					{
						if (bparent_left_of_grandparent)
						{
							grandparent_Node->bred = true;
							grandparent_Node->left = parent_Node->right;
							parent_Node->bred = false;
							parent_Node->right = grandparent_Node;

							*grandparent_Node_location = parent_Node;

							parent_Node->left = new RBTNode<T, Compare_Less>(val, true);
						}
						else
						{
							grandparent_Node->bred = true;
							grandparent_Node->right = parent_Node->left;
							parent_Node->bred = false;
							parent_Node->left = grandparent_Node;

							*grandparent_Node_location = parent_Node;

							parent_Node->right = new RBTNode<T, Compare_Less>(val, true);
						}
					}
					else
					{
						if (bparent_left_of_grandparent)
						{
							grandparent_Node->left = NULL;
							grandparent_Node->bred = true;
							
							auto New_Node = new RBTNode<T, Compare_Less>(val, false);
							*grandparent_Node_location = New_Node;
							New_Node->left = parent_Node;
							New_Node->right = grandparent_Node;
						}
						else
						{
							grandparent_Node->right = NULL;
							grandparent_Node->bred = true;

							auto New_Node = new RBTNode<T, Compare_Less>(val, false);
							*grandparent_Node_location = New_Node;
							New_Node->right = parent_Node;
							New_Node->left = grandparent_Node;

						}

					}
				}

			}




		}

		/////////////////
		/*if (root == 0)
		{
			return (RBTNode<T, Compare_Less> **) &root;
		}

		RBTNode<T, Compare_Less> ** curr_node_ptr = (RBTNode<T, Compare_Less> **) &root;
		while (true)
		{
			Compare_Less less;
			RBTNode<T, Compare_Less> * curr_node = *curr_node_ptr;

			if (less(val, curr_node->data))
			{
				if (curr_node->left == 0)
					return &curr_node->left;
				else
					curr_node_ptr = &(curr_node->left);
			}
			else if (less(curr_node->data, val))
			{
				if (curr_node->right == 0)
					return &curr_node->right;
				else
					curr_node_ptr = &(curr_node->right);
			}
			else
			{
				return curr_node_ptr;
			}
		}*/
		////////////////////

	}

	template <class T, class Compare_Less >
	inline const T& RBT<T, Compare_Less>::find(const T& val) const
	{
		RBTNode<T, Compare_Less> ** found = find_ptr(val);

		if (*found == 0)
			return fail_val;
		else
			return (*found)->data;
	}


	template <class T, class Compare_Less >
	RBTNode<T, Compare_Less> ** RBT<T, Compare_Less>::find_ptr(const T& val) const
	{
		if (root == 0)
		{
			return (RBTNode<T, Compare_Less> **) &root;
		}

		RBTNode<T, Compare_Less> ** curr_node_ptr = (RBTNode<T, Compare_Less> **) &root;
		while (true)
		{
			Compare_Less less;
			RBTNode<T, Compare_Less> * curr_node = *curr_node_ptr;

			if (less(val, curr_node->data))
			{
				if (curr_node->left == 0)
					return &curr_node->left;
				else
					curr_node_ptr = &(curr_node->left);
			}
			else if (less(curr_node->data, val))
			{
				if (curr_node->right == 0)
					return &curr_node->right;
				else
					curr_node_ptr = &(curr_node->right);
			}
			else
			{
				return curr_node_ptr;
			}
		}
	}

	template<class T, class Compare_Less>
	RBTNode<T, Compare_Less>** RBT<T, Compare_Less>::find_Max_from_Node_ptr(const RBTNode<T, Compare_Less>* const * Node) const
	{
		const RBTNode<T, Compare_Less> * const * curr_node_ptr = Node;
		while (true)
		{
			if ((*curr_node_ptr)->right == 0)
				return (RBTNode<T, Compare_Less> **) curr_node_ptr;
			else
				curr_node_ptr = (const RBTNode<T, Compare_Less> **) &((*curr_node_ptr)->right);

		}
	}

	template<class T, class Compare_Less>
	RBTNode<T, Compare_Less>** RBT<T, Compare_Less>::find_Min_from_Node_ptr(const RBTNode<T, Compare_Less>* const * Node) const
	{
		const RBTNode<T, Compare_Less> * const * curr_node_ptr = Node;
		while (true)
		{
			if ((*curr_node_ptr)->left == 0)
				return (RBTNode<T, Compare_Less> **) curr_node_ptr;
			else
				curr_node_ptr = (const RBTNode<T, Compare_Less> **) &((*curr_node_ptr)->left);

		}
	}

	template<class T, class Compare_Less>
	inline const T & RBT<T, Compare_Less>::find_Max() const
	{
		if (root == 0)
			return fail_val;
		else
			return (*find_Max_from_Node_ptr((const RBTNode<T, Compare_Less>**) &root))->data;
	}


	template<class T, class Compare_Less>
	void RBT<T, Compare_Less>::erase(const T & val)
	{
		auto node_ptr_ptr = find_ptr(val);
		auto node_ptr = *node_ptr_ptr;

		if (node_ptr == 0)
		{
			return;
		}
		else if (node_ptr->left == 0 && node_ptr->right == 0)
		{
			*node_ptr_ptr = NULL;
		}
		else if (node_ptr->left == 0)
		{
			*node_ptr_ptr = node_ptr->right;

		}
		else if (node_ptr->right == 0)
		{
			*node_ptr_ptr = node_ptr->left;

		}
		else
		{
			auto replacement_Node_ptr_ptr = find_Max_from_Node_ptr(&node_ptr->left);
			auto replacement_Node_ptr = *replacement_Node_ptr_ptr;

			if (replacement_Node_ptr->left != 0)
			{
				*replacement_Node_ptr_ptr = replacement_Node_ptr->left;
			}
			else
				*replacement_Node_ptr_ptr = 0;

			replacement_Node_ptr->left = node_ptr->left;
			replacement_Node_ptr->right = node_ptr->right;

			*node_ptr_ptr = replacement_Node_ptr;


		}

		delete node_ptr;

	}

	template<class T, class Compare_Less>
	inline RBT<T, Compare_Less>::~RBT()
	{
		if (root != 0)
		{
			destroy_Subtree(root);
		}
	}

	template<class T, class Compare_Less>
	void rk::RBT<T, Compare_Less>::destroy_Subtree(RBTNode<T, Compare_Less>* Node_start)
	{
		if (!(Node_start->left == 0 && Node_start->right == 0))
		{
			if (Node_start->left == 0)
			{
				destroy_Subtree(Node_start->right);

			}
			else if (Node_start->right == 0)
			{
				destroy_Subtree(Node_start->left);

			}
			else
			{
				destroy_Subtree(Node_start->left);
				destroy_Subtree(Node_start->right);
			}
		}

		delete Node_start;


	}

	template<class T, class Compare_Less>
	RBTNode<T, Compare_Less>* RBT<T, Compare_Less>::copy_Subtree(const RBTNode<T, Compare_Less>* original_Node)
	{
		if (original_Node == NULL)
			return NULL;

		auto copy_ptr = new RBTNode<T, Compare_Less>(original_Node->data, original_Node->bred);

		if (original_Node->left == NULL)
			copy_ptr->left = NULL;
		else
			copy_ptr->left = copy_Subtree(original_Node->left);

		if (original_Node->right == NULL)
			copy_ptr->right = NULL;
		else
			copy_ptr->right = copy_Subtree(original_Node->right);

		return copy_ptr;
	}


	template<class T, class Compare_Less>
	inline void rk::RBT<T, Compare_Less>::clear()
	{
		if (root != 0)
		{
			destroy_Subtree(root);
			root = 0;
		}

	}

	template<class T, class Compare_Less>
	inline RBT<T, Compare_Less> & RBT<T, Compare_Less>::operator=(const RBT<T, Compare_Less> & rhs)
	{
		if (this == &rhs)
			return *this;

		this->clear();
		this->fail_val = rhs.fail_val;
		this->root = copy_Subtree(rhs.root);

		return *this;
	}

	template<class T, class Compare_Less>
	inline const T & rk::RBT<T, Compare_Less>::find_Min() const
	{
		if (root == 0)
			return fail_val;
		else
			return (*find_Min_from_Node_ptr((const RBTNode<T, Compare_Less>**) &root))->data;
	}

}