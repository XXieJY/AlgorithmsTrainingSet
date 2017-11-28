//先构建一个只分配内存而不初始化内存的vector base class
//这样的好处是：1.使得exception的处理更加容易；2.封装了allocator之间的差异
//重要成员：
//	1.内存分配 allocator; 2.vector管理 _M_start _M_finish _M_end_of_storage
//  2.构造函数：调用调用allocator的allocate方法；
//  3.析构函数: 调用deallocate方法，传入_M_start,以及capacity=_M_end_of_storage - _M_start;
template <class _Tp, class _Alloc>
class _Vector_base {
public:
	typedef _Alloc allocator_type;
	allocator_type get_allocator() const { return allocator_type(); }

	_Vector_base(const _Alloc&)
		: _M_start(0), _M_finish(0), _M_end_of_storage(0) {}
	_Vector_base(size_t __n, const _Alloc&)
		: _M_start(0), _M_finish(0), _M_end_of_storage(0)
	{
		_M_start = _M_allocate(__n);
		_M_finish = _M_start;
		_M_end_of_storage = _M_start + __n;
	}

	~_Vector_base() { _M_deallocate(_M_start, _M_end_of_storage - _M_start); }

protected:
	_Tp* _M_start;
	_Tp* _M_finish;
	_Tp* _M_end_of_storage;

	typedef simple_alloc<_Tp, _Alloc> _M_data_allocator;
	_Tp* _M_allocate(size_t __n)
	{
		return _M_data_allocator::allocate(__n);
	}
	void _M_deallocate(_Tp* __p, size_t __n)
	{
		_M_data_allocator::deallocate(__p, __n);
	}
};

//vector实现的数据结构部分
//重要成员:
//	1.vector迭代器iterator
//  2.内存分配器类型宏 __STL_DEFAULT_ALLOCATOR(_Tp)

template <class _Tp, class _Alloc = __STL_DEFAULT_ALLOCATOR(_Tp) >
class vector : protected _Vector_base<_Tp, _Alloc>
{
private:
	typedef _Vector_base<_Tp, _Alloc> _Base;
public:
	typedef _Tp value_type;
	typedef value_type* pointer;
	typedef const value_type* const_pointer;
	typedef value_type* iterator;
	typedef const value_type* const_iterator;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;

	typedef typename _Base::allocator_type allocator_type;
	allocator_type get_allocator() const { return _Base::get_allocator(); }
}

//构造函数
//先调用基类构造函数，基类构造函数调用allocator为vector分配内存
//然后为内存赋值
vector(size_type __n, const _Tp& __value,
	const allocator_type& __a = allocator_type())
	: _Base(__n, __a)
{
	_M_finish = uninitialized_fill_n(_M_start, __n, __value);
}

vector(const _Tp* __first, const _Tp* __last,
	const allocator_type& __a = allocator_type())
	: _Base(__last - __first, __a)
{
	_M_finish = uninitialized_copy(__first, __last, _M_start);
}

//析构函数
//调用destroy函数
~vector() { destroy(_M_start, _M_finish); }
