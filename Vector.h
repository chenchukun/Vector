#ifndef VECTOR_H
#define VECTOR_H
#define NDEBUG
#include <iostream>
#include <stdexcept>
#include <cstring>
using std::out_of_range;
using std::endl;
using std::cout;
using std::initializer_list;
//typedef unsigned int size_t;  //下标和大小类型

#define DEFAULT_CAPACITY 10

template<typename T> class Vector
{
public:
	using size_type = size_t;     //容量大小和下标类型
	using difference_type = int;   //迭代器之差类型
	using value_type = T;         //元素类型
	using reference = T&;         //元素左值类型
	using const_reference = const T&;   //元素const左值类型
	using const_iterator = const T*;   //只读迭代器类型
	using iterator = T*;               //迭代器类型

	T& operator[](size_t index) const; //必须是const
	Vector<T>& operator=(const Vector<T> &data);
	bool operator==(const Vector<T> &data) const;
	bool operator!=(const Vector<T> &data) const{return !(*this == data);}
	bool operator>(const Vector<T> &data) const;
	bool operator<(const Vector<T> &data) const{return (*this==data || *this>data)?false:true;}
	bool operator>=(const Vector<T> &data) const{return (*this==data || *this>data)?true:false;}
	bool operator<=(const Vector<T> &data) const{return (*this==data || *this<data)?true:false;}

	Vector();                     //默认构造函数
	Vector(size_t len);	      //接受一个参数作为容器大小的构造函数
	Vector(size_t len, T val);
	Vector(const Vector<T> &data); //拷贝构造函数
	Vector(Vector<T>::const_iterator begin, Vector<T>::const_iterator end); //通过迭代器初始化的构造函数
	Vector(initializer_list<T> il);    //通过列表初始化


	~Vector(){delete [] _elem;}   //析构函数
	
	size_t size() const {return _size;}           //返回当前容器大小
	size_t capacity() const {return _capacity;}    //返回容器总容量
	bool empty(){return !_size;}
	void clear(){_size = 0;}            //清楚所有元素
	T& get(size_t index)                    //返回指定下标的元素
	{
		if(index>=_size || index<0)
		{
			throw out_of_range("out_of_range");
		}
		return _elem[index];
	}
	void push_back(const T &val);         //在容器尾部插入元素
	void traverse() const;                //遍历容器
	size_t insert(size_t r, const T &val);//在r处插入元素val
	T remove(size_t r);                   //删除r处的元素
	size_t remove(size_t lo, size_t hi);  //删除lo到hi之间的元素
	int find(const T &e, size_t lo, size_t hi) const;       //无序查找,在区间[lo,hi)上
	int find(const T &e) const {return find(e, 0, _size);}    //无序查找，在容器中
	int search(const T &e, size_t lo, size_t hi) const {return BinarySearch(e, lo, hi);} //在区间[lo, hi)之间查找元素e，返回下标
	int search(const T &e) const {return BinarySearch(e, 0, _size);} //在容器中查找元素e，返回下标
	void sort(size_t lo, size_t hi){quickSort(lo, hi-1);} //将lo到hi之间的元素排序
	void sort(){sort(0, _size);}         //排序
	void reverse(size_t lo, size_t hi);   //将区间[lo, hi)元素倒置
	void reverse(){reverse(0, _size);}   //将容器倒置
	bool disordered() const;   //判断容器是否有序
	void uniquify();  //删除重复元素，有序容器
	void deduplicate();  //删除重复元素， 无序容器

	const_iterator cbegin(){return _elem;}     //返回const类型首迭代器
	const_iterator cend(){return _elem+_size;}  //返回const类型尾后迭代器
	iterator begin(){return _elem;}            //返回首迭代器
	iterator end(){return _elem+_size;}        //返回尾后迭代器

private:
	size_t _size, _capacity; //容器当前大小，容器容量
	T *_elem;                //数据区
	void quickSort(size_t lo, size_t hi);  //快速排序实现
	int BinarySearch(const T &e, size_t lo, size_t hi) const; //二分查找实现
};

template<typename T> Vector<T>::Vector()
{
	_elem = new T[DEFAULT_CAPACITY];
	_size = 0;
	_capacity = DEFAULT_CAPACITY;
}

template<typename T> Vector<T>::Vector(size_t len)
{
	_elem = new T[len];
	_size = len;
	_capacity = len;
}

template<typename T> Vector<T>::Vector(const Vector<T> &data)
{
	_size = data.size();
	_capacity = data.capacity();
	_elem = new T[_capacity];
	for(size_t index=0; index<_size; ++index)
	{
		_elem[index] = data[index];
	}
}

template<typename T> Vector<T>& Vector<T>::operator=(const Vector<T> &data)
{
	_size = data.size();
	_capacity = data.capacity();
	_elem = new T[_capacity];
	for(size_t index=0; index<_size; ++index)
	{
		_elem[index] = data[index];
	}
	return *this;
}

template<typename T> void Vector<T>::push_back(const T &val)
{
#ifndef NDEBUG
	cout << "push_back" << endl;
#endif
	if(_size >= _capacity)
	{
		T *temp = new T[_capacity*2];
		memcpy(temp, _elem, sizeof(T)*_capacity);
		delete [] _elem;
		_elem = temp;
		_capacity *= 2;
	}
	_elem[_size++] = val;
}

template<typename T> T& Vector<T>::operator[](size_t index) const
{
	if(index>=_size || index<0)
	{
		throw out_of_range("out_of_range");
	}
	return _elem[index];
}

template<typename T> void Vector<T>::traverse() const
{
	size_t index;
	for(index=0; index<_size; ++index)
	{
		cout << _elem[index] << " ";
	}
	cout << endl;
}

template<typename T> size_t Vector<T>::insert(size_t r, const T &val)
{
	if(r>_size || r<0)
	{
		throw out_of_range("out_of_range");
	}
	if(_size >= _capacity)
	{
		T *temp = new T[_capacity*2];
		memcpy(temp, _elem, sizeof(T)*_capacity);
		delete [] _elem;
		_elem = temp;
		_capacity *= 2;
	}
	size_t index;
	for(index=_size; index>r; --index)
	{
		_elem[index] = _elem[index-1];
	}
	_elem[index] = val;
	++_size;
	return index;
}

template<typename T> T Vector<T>::remove(size_t r)
{
	if(r<0 || r>=_size)
	{
		throw out_of_range("out_of_range");
	}	
	size_t index;
	T temp = _elem[r];
	for(index=r; index<_size-1; ++index)
	{
		_elem[index] = _elem[index+1];
	}
	--_size;
	return temp;
}

template<typename T> size_t Vector<T>::remove(size_t lo, size_t hi)
{
	if(lo>hi || lo<0 || lo>=_size || hi<0 || hi>=_size)
	{
		throw out_of_range("out_of_range");
	}
	while(hi < _size)
	{
		_elem[lo++] = _elem[hi++];	
	}
	_size -= hi-lo;
	return lo;
}

template<typename T> int Vector<T>::find(const T &e, size_t lo, size_t hi) const
{
	size_t index;
	for(index=lo; index<hi; ++index)
	{
		if(_elem[index] == e)
		{
			return index;
		}
	}
	return -1;
}

template<typename T> void Vector<T>::quickSort(size_t lo, size_t hi)
{
	if(lo < hi)
	{
		size_t l = lo;
		size_t h = hi;
		T temp = _elem[l];
		while(l < h)
		{
			while(l < h && _elem[h]>=temp)
			{
				--h;
			}
			_elem[l] = _elem[h];
			while(l < h && _elem[l]<temp)
			{
				++l;
			}
			_elem[h] = _elem[l];
		}
		_elem[l] = temp;
		quickSort(lo, l);
		quickSort(l+1, hi);	
	}
}

template<typename T> Vector<T>::Vector(Vector<T>::const_iterator beg, Vector<T>::const_iterator en)
{
	_capacity = (en-beg) + DEFAULT_CAPACITY;
	_size = en - beg;
	_elem = new T[_capacity];
	size_t index = 0;
	while(beg < en)
	{
		_elem[index++] = *beg;
		++beg;
	}
}

template<typename T> int Vector<T>::BinarySearch(const T &e, size_t lo, size_t hi) const
{
	size_t mid;
	
	while(hi - lo > 1)
	{
		mid = (lo + hi)/2;
		if(e < _elem[mid])
		{
			hi = mid;
		}
		else
		{
			lo = mid;
		}
	}
	return _elem[lo]==e?lo:-1;
}

template<typename T> bool Vector<T>::disordered() const
{
	for(size_t index=0; index<_size-1; ++index)
	{
		if(_elem[index] > _elem[index+1])
		{
			return false;
		}
	}
	return true;
}

template<typename T> void Vector<T>::uniquify()
{
	size_t index;
	for(index=_size-1; index>0; --index)
	{
		if(_elem[index] == _elem[index-1])
		{
			remove(index);
		}
	}
}

template<typename T> void Vector<T>::deduplicate()
{
	size_t index;
	for(index =0; index<_size; ++index)
	{
		while(1)
		{
			int ret = find(_elem[index], index+1, _size);
			if(ret == -1)
			{
				break;
			}
			remove(ret);	
		}
	}
}

template<typename T> void Vector<T>::reverse(size_t lo, size_t hi)
{
	size_t h = hi - 1;
	size_t l = lo;
	while(l < h)
	{
		T temp = _elem[l];
		_elem[l] = _elem[h];
		_elem[h] = temp;
		++l;
		--h;
	}
}

template<typename T> Vector<T>::Vector(initializer_list<T> il)
{
	auto begin = il.begin();
	auto end = il.end();
	_size = end - begin;
	_capacity = _size + DEFAULT_CAPACITY;
	_elem = new T[_capacity];
	size_t index = 0;
	while(begin < end)
	{
		_elem[index++] = *begin;
		++begin;
	}
}

template<typename T> Vector<T>::Vector(size_t len, T val)
{
	_size = len;
	_capacity = len + 10;
	_elem = new T[_capacity];
	for(size_t index=0; index<len; ++index)
	{
		_elem[index] = val;
	}
}

template<typename T> bool Vector<T>::operator==(const Vector<T> &data) const
{
	if(_size != data.size() || _capacity != data.capacity())
	{
		return false;
	}	
	size_t index = 0;
	while(index < _size)
	{
		if(_elem[index] != data[index])
		{
			return false;
		}
		++index;
	}
	return true;
}

template<typename T> bool Vector<T>::operator>(const Vector<T> &data) const
{
	size_t len = data.size();
	len = _size<len?_size:len;
	size_t index = 0;
	while(index < len)
	{
		if(_elem[index] < data[index])
		{
			return false;
		}
		else if(_elem[index] > data[index])
		{
			return true;
		}
		++index;
	}
	return len==_size?false:true;
}

#endif
