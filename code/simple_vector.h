	
#ifndef SIMPLE_VECTOR_H
#define SIMPLE_VECTOR_H
#include <cstddef>
#include <memory>
#include <algorithm>
#include <iterator>

template <class T>
class simple_vector {
public:
	typedef T value_type;
	typedef std::size_t size_type;
	typedef std::ptrdiff_t difference_type;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef value_type* pointer;
	typedef const value_type* const_pointer;
	typedef pointer iterator;
	typedef const_pointer const_iterator;
	typedef std::reverse_iterator<pointer> reverse_iterator;
	typedef std::reverse_iterator<const_pointer> const_reverse_iterator;

	/* Constructor */
	simple_vector() : base(0), uptr(0), ebase(0)
	{
	}

	/* Copy-constructor */
	simple_vector(const simple_vector& other) : base(0), uptr(0), ebase(0)
	{
		reallocate_and_assign(other.size(), other.base, other.uptr);
	}

	/* Destructor */
	~simple_vector()
	{
		if (base != 0) {
			clear();
			::operator delete[](base);
		}
	}

	/* Copy-assignment operator (not optimized) */
	simple_vector& operator=(simple_vector other)
	{
		swap(other);
		return *this;
	}

	/* Replace contents with several copies of a value */
	void assign(size_type count, const T& value)
	{
		simple_vector temp;
	
		temp.reallocate_and_assign(count, uptr, uptr);
		temp.uptr = std::uninitialized_fill_n(temp.uptr, count, value);
		swap(temp);
	}

	/* Replace contents with range of values */
	template <class InputIt>
	void assign(InputIt first, InputIt last)
	{
		simple_vector temp;

		std::copy(first, last, std::back_inserter(temp));
		swap(temp);
	}

	/* Access an element from it's index */
	T& operator[](std::size_t index)
	{
		return base[index];
	}

	const T& operator[](std::size_t index) const
	{
		return base[index];
	}

	/* Returns a reference to the first element */
	T& front()
	{
		return *base;
	}

	const T& front() const
	{
		return *base;
	}

	/* Returns a reference to the last element */
	T& back()
	{
		T* temp = uptr;
		--temp;
		return *temp;
	}

	const T& back() const
	{
		T* temp = uptr;
		--temp;
		return *temp;
	}

	/* Returns an iterator to the first element */
	iterator begin()
	{
		return base;
	}

	const_iterator begin() const
	{
		return base;
	}

	/* Returns an iterator to the element following the last element */
	iterator end()
	{
		return uptr;
	}

	const_iterator end() const
	{
		return uptr;
	}

	/* Returns a reverse iterator to the first element in reverse */
	reverse_iterator rbegin()
	{
		return reverse_iterator(uptr);
	}

	const_reverse_iterator rbegin() const
	{
		return const_reverse_iterator(uptr);
	}

	/* Returns a reverse iterator to the element following the last element in reverse */
	reverse_iterator rend()
	{
		return reverse_iterator(base);
	}

	const_reverse_iterator rend() const
	{
		return const_reverse_iterator(base);
	}

	/* Returns true if this vector has no elements */
	bool empty() const
	{
		return base == uptr;
	}

	/* Returns the number of elements */
	std::size_t size() const
	{
		return uptr - base;
	}

	/* Reserves storage */
	void reserve(size_type new_cap)
	{
		if (ebase - base < new_cap) {
			simple_vector temp;

			temp.reallocate_and_assign(new_cap, base, uptr);
			swap(temp);
		}
	}

	/* 
	 * Returns the number of elements this vector can store before the 
	 * next reallocation
	 */
	std::size_t capacity() const
	{
		return ebase - base;
	}

	/* Deallocate unused memory */
	void shrink_to_fit()
	{
		size_type sz = size();

		if (sz != capacity()) {
			simple_vector temp;

			temp.reallocate_and_assign(sz, base, uptr);
			swap(temp);
		}
	}

	/* Erases all elements */
	void clear()
	{
		while (uptr != base) (--uptr)->T::~T();
	}

	/* Inserts an element (not optimized) */
	iterator insert(iterator pos, const T& value)
	{
		return insert(pos, size_type(1), value);
	}

	/* Inserts several copies of an element (not optimized) */
	iterator insert(iterator pos, size_type count, const T& value)
	{
		size_type i = pos - base;
		simple_vector temp;

		temp.reallocate_and_assign(size() + count, base, pos);
		temp.uptr = std::uninitialized_fill_n(temp.uptr, count, value);
		temp.uptr = std::uninitialized_copy(pos, uptr, temp.uptr);
		swap(temp);
		return base + i;
	}

	/* Inserts a range of elements */
	template <class InputIt>
	iterator insert(iterator pos, InputIt first, InputIt last)
	{
		size_type i = pos - base;
		simple_vector temp;

		temp.reallocate_and_assign(pos - base, base, pos);
		std::copy(first, last, std::back_inserter(temp));
		std::copy(pos, uptr, std::back_inserter(temp));
		swap(temp);
		return base + i;
	}

	/* Erases an element */
	iterator erase(iterator pos)
	{
		return erase(pos, pos + 1);
	}

	/* Erases a range of elements */
	iterator erase(iterator first, iterator last)
	{
		T* nuptr = uptr - (last - first);

		std::copy(last, uptr, first);
		while (uptr != nuptr) (--uptr)->T::~T();
		return last;
	}

	/* Inserts an element to the end */
	void push_back(const T& value)
	{
		if (uptr == ebase) {
			reallocate_and_assign(
					capacity() != 0 ? capacity() * 2 : 2,
					base, uptr);
		}
		::new((void*)uptr) T(value);
		++uptr;
	}

	/* Erases the last element */
	void pop_back()
	{
		(--uptr)->T::~T();
	}

	void resize(size_type count, T value = T())
	{
		size_type sz = size();

		if (count <= sz) {
			T* nuptr = base + count;
			while (uptr != nuptr) (--uptr)->T::~T();
		} else if (base + count <= ebase) {
			uptr = std::uninitialized_fill_n(uptr, count - sz, value);
		} else {
			simple_vector temp;

			temp.reallocate_and_assign(count, base, uptr);
			temp.uptr = std::uninitialized_fill_n(temp.uptr, count - sz, value);
			swap(temp);
		}
	}

	/* Exchanges the contents of this vector with another */
	void swap(simple_vector& other)
	{
		using std::swap;
		swap(base, other.base);
		swap(uptr, other.uptr);
		swap(ebase, other.ebase);
	}
private:
	/* Pointer to the dynamic storage array */
	T* base;
	/* Pointer to the unused elements */
	T* uptr;
	/* Pointer to the end of the dynamic storage array */
	T* ebase;

	/*
	 * Reallocates this vector to a new capacity and assigns the values 
	 * from the range [first, last)
	 */
	template <class InputIt>
	void reallocate_and_assign(std::size_t new_capacity, InputIt first,
							InputIt last)
	{
		simple_vector temp;

		temp.base = (T*)::operator new[](new_capacity * sizeof(T));
		temp.uptr = std::uninitialized_copy(first, last, temp.base);
		temp.ebase = temp.base + new_capacity;
		swap(temp);
	}
};

template <class T>
void swap(simple_vector<T>& a, simple_vector<T>& b)
{
	a.swap(b);
}

#endif
