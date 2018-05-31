#ifndef SIMPLE_LIST_H
#define SIMPLE_LIST_H

template <class T>
class simple_list {
private:

	struct node {
		node* before;
		node* after;
		T data;

		node() : before(0), after(0), data()
		{
		}

		node(const T& data_val) : before(0), after(0),
						data(data_val)
		{
		}
	};

public:

	class iterator {
		friend class simple_list;
	private:
		node* node_ptr;
		void f() {}
	public:
		iterator() : node_ptr(0)
		{
		}

		iterator(const iterator& other) : node_ptr(other.node_ptr)
		{
		}

		iterator(node* node_ptr_val) : node_ptr(node_ptr_val)
		{
		}

		iterator& operator=(const iterator& other)
		{
			node_ptr = other.node_ptr;
			return *this;
		}

		iterator& operator++()
		{
			node_ptr = node_ptr->after;
			return *this;
		}

		iterator operator++(int)
		{
			iterator tmp(*this);
			operator++();
			return tmp;
		}

		iterator& operator--()
		{
			node_ptr = node_ptr->before;
			return *this;
		}

		iterator operator--(int)
		{
			iterator tmp(*this);
			operator--();
			return tmp;
		}

		T& operator*() const
		{
			return node_ptr->data;
		}

		T* operator->() const
		{
			return &(node_ptr->data);
		}

		bool operator==(const iterator& other) const
		{
			return node_ptr == other.node_ptr;
		}

		bool operator!=(const iterator& other) const
		{
			return node_ptr != other.node_ptr;
		}
	};

	simple_list() : begin_node_ptr(&end_node), end_node(), sz(0)
	{
	}

	simple_list(const simple_list& other) : begin_node_ptr(&end_node),
							end_node(), sz(0)
	{
		operator=(other);
	}

	~simple_list() 
	{
		clear();
	}

	simple_list& operator=(const simple_list& other)
	{
		clear();
		for (iterator it = other.begin(); it != other.end(); ++it)
			push_back(*it);
		return *this;
	}

	T& front()
	{
		return begin_node_ptr->data;
	}

	T& back()
	{
		return end_node.before->data;
	}

	iterator begin()
	{
		return iterator(begin_node_ptr);
	}

	iterator end()
	{
		return iterator(&end_node);
	}

	bool empty() const
	{
		return sz == 0;
	}

	unsigned int size() const
	{
		return sz;
	}

	void clear()
	{
		while (!empty()) pop_back();
	}

	iterator insert(iterator pos, const T& value)
	{
		node* new_node_ptr = new node(value);
		node *before = pos.node_ptr->before, *after = pos.node_ptr;

		new_node_ptr->before = before;
		new_node_ptr->after = after;
		if (before == 0)
			begin_node_ptr = new_node_ptr;
		else
			before->after = new_node_ptr;
		after->before = new_node_ptr;
		++sz;
		return iterator(new_node_ptr);
	}

	iterator erase(iterator pos)
	{
		node *before = pos.node_ptr->before,
			*after = pos.node_ptr->after;
		iterator result(after);

		after->before = before;
		if (before == 0)
			begin_node_ptr = after;
		else
			before->after = after;
		delete pos.node_ptr;
		--sz;
		return result;
	}

	void push_back(const T& value)
	{
		insert(end(), value);
	}

	void pop_back()
	{
		iterator tmp = end();
		erase(--tmp);
	}

	void push_front(const T& value)
	{
		insert(begin(), value);
	}

	void pop_front()
	{
		erase(begin());
	}

	iterator find(const T& value)
	{
		iterator result;
		for (result = begin(); result != end(); ++result) {
			if (*result == value) break;
		}
		return result;
	}

	iterator self_org_find(const T& value)
	{
		iterator found = find(value);
		if (found == end()) return found;
		erase(found);
		push_front(value);
		return begin();
	}

private:
	node* begin_node_ptr;
	node end_node;
	unsigned int sz;
};

#endif
