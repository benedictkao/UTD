namespace utd {

	template <typename T>
	class vector
	{
	private:
		T* inner_array = nullptr;
		size_t array_size = 0;
		size_t vector_size = 0;

		void resize_array(size_t new_size, size_t cpy_len)
		{
			array_size = new_size;
			T* new_array = new T[new_size];
			memcpy(new_array, inner_array, cpy_len * sizeof(T));
			delete[] inner_array;
			inner_array = new_array;
		}

		void resize_to_fit_increment()
		{
			if (vector_size + 1 > array_size)
			{
				size_t new_size = array_size == 0 ? 1 : array_size * 2;
				resize_array(new_size, vector_size);
			}
		}

	public:
		vector() = default;

		vector(const vector& v)
		{
			this->array_size = v.array_size;
			this->vector_size = v.vector_size;
			this->inner_array = new T[array_size];
			memcpy(this->inner_array, v.inner_array, v.vector_size);
		}

		vector(vector&& v)
		{
			this->array_size = v.array_size;
			this->vector_size = v.vector_size;
			this->inner_array = v.inner_array;
			v.inner_array = nullptr;
			v.array_size = 0;
			v.vector_size = 0;
		}

		vector& operator=(const vector& v)
		{
			vector<T> new_vec;
			new_vec.array_size = v.array_size;
			new_vec.vector_size = v.vector_size;
			new_vec.inner_array = new T[array_size];
			memcpy(new_vec.inner_array, v.inner_array, v.vector_size);
			return new_vec;
		}

		vector& operator=(vector&& v)
		{
			vector<T> new_vec;
			new_vec.array_size = v.array_size;
			new_vec.vector_size = v.vector_size;
			new_vec.inner_array = v.inner_array;
			v.inner_array = nullptr;
			v.array_size = 0;
			v.vector_size = 0;
		}

		~vector()
		{
			delete[] inner_array;
		}

		void push_back(const T& val)
		{
			resize_to_fit_increment();
			inner_array[vector_size] = val;
			vector_size++;
		}

		void push_back(T&& val)
		{
			resize_to_fit_increment();
			inner_array[vector_size] = std::move(val);
			vector_size++;
		}

		void reserve(size_t new_size)
		{
			if (new_size <= array_size)
			{
				return;
			}
			resize_array(new_size, vector_size);
		}

		size_t size() const
		{
			return vector_size;
		}

		const T& operator[](size_t index) const
		{
			return inner_array[index];
		}

		T& operator[](size_t index)
		{
			return inner_array[index];
		}
	};
}