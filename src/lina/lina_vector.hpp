#pragma once

// vector realization
// count "lines": 
// size = n
// default:
//                  |  a[0]  |
//  vector-column = |   ..   |
//                  | a[n-1] |

namespace lina
{
	template<typename L>
	class vector
	{
	private:
		L* _contents;
		size_t _size;
		bool _t_status;

	public:
		void T(){
			_t_status = !_t_status;
		}

		bool t_status() const{
			return _t_status;
		}

		size_t size() const{
			return _size;
		}

	public:
		const L& operator[] (size_t index) const
		{
			if ((index >= 0) && (index < _size))
				return _contents[index];
			else
				throw std::out_of_range("index out of range");
		}

		void operator= (_initlist<L> input)
		{
			_size = input.size();
			_t_status = false;

			_contents = (L*)input.begin();
		}

	public:
		vector() : 
			_size(lina_init), _t_status(lina_init) 
		{}

		vector(_initlist<L> input)
		{
			_size = input.size();
			_t_status = false;

			_contents = (L*)input.begin();
		}
	};
}

template <typename T>
std::ostream& operator << (std::ostream& os, const lina::vector<T>& vector)
{
	auto last_elem = vector.size() - 1;

	os << "{";

	for (auto i = 0; i <= last_elem; i++)
	{
		os << vector[i];
		if (i < last_elem)
			os << " ";
	}

	os << "}";

	if (!vector.t_status())
		os << "^T";

	return os;
}