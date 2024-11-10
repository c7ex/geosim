#pragma once

// matrix realization
// count "lines": 
// size_l = n, 
// count "column":
// size_c = m
// default:
//          |  a[0][0]   ..   a[0][m-1]  |
// matrix = |    ..      ..      ..      |
//          | a[n-1][0]  ..  a[n-1][m-1] |

// "iniver" flag - non-uniform size lines (or vectors)
// "iniver" = 0 - not work math with matrix
// "size" - return count lines (or size line)

// "get_elem" - return element of matrix
// may be used if "iniver" flag = 1
// format:
//    get_elem(line,column)

// "_v_count" - count vectors objects

namespace lina
{
	template<typename L>
	class matrix
	{
	private:
		vector<L>* _contents;
		size_t _v_count;
		size_t _size_line;
		size_t _size_column;
		bool _t_status;
		bool _iniver;
		bool _error;

	public:
		void T() { 
			
			if (!_iniver)
				return;

			size_t temp = _size_line;
			_size_line = _size_column;
			_size_column = temp;

			_t_status = !_t_status;
		}

		size_t size_column() const {
			return _size_column;
		}

		size_t size_line() const {
			return _size_line;
		}

		bool t_status() const {
			return _t_status;
		}

		bool iniver() const{
			return _iniver;
		}

		bool error() const {
			return _error;
		}

		size_t size() const {
			return ;
		}

	public:
		const vector<L>& operator[] (size_t index) const
		{
			if ((index >= 0) && (index < _v_count))
				return _contents[index];
			else
				throw std::out_of_range("index out of range");
		}

	public:
		const L& get_elem(size_t index_line, size_t index_column)
		{
			if (!_iniver)
				_error = true;

			bool valid_index_line = false;
			bool valid_index_column = false;
			bool valid_size = false;

			if ((index_line >= 0) && (index_line < _size_line))
				valid_index_line = true;

			if ((index_column >= 0) && (index_column < _size_column))
				valid_index_column = true;

			if (valid_index_line && valid_index_column)
				valid_size = true;
			else
				_error = true;

			if (_error)
				return lina_error;

			if(!_t_status)
				return _contents[index_line][index_column];
			else
				return _contents[index_column][index_line];
		}

	private:
		// set initialization verification & try fill "_contents"
		void ivtf(_initlist<_initlist<L>> input)
		{
			_iniver = true;
			_size_line = input.size();

			_initlist<L>* v_ptr = (_initlist<L>*)input.begin();
			_contents = (vector<L>*)std::malloc(_size_line * sizeof(vector<L>));

			vector<L> v_refobj = *v_ptr;
			_size_column = v_refobj.size();

			for (auto i = 0; i < _size_line; i++)
			{
				if (v_ptr)
				{
					_contents[i] = *v_ptr++;

					if (_size_column != _contents[i].size())
						_iniver = false;
				}
			}

			// if good matrix - vectors it's lines
			// invert transposition
			if(_iniver)
				for (auto i = 0; i < _size_line; i++)
					_contents[i].T();
		}

	public:
		matrix(_initlist<_initlist<L>> input)
		{
			_contents = nullptr;
			_t_status = false;
			_error = false;
			_v_count = input.size();

			ivtf(input);
		}
	};
}

// io for valid matrix
template <typename T>
void iomatrix(std::ostream& os, lina::matrix<T>& matrix)
{
	auto last_elem = matrix.size_column() - 1;

	for (auto i = 0; i < matrix.size_line(); i++)
	{
		for (auto j = 0; j <= last_elem; j++) {

			if (!j) os << "{";

			os << matrix.get_elem(i,j);

			if (j < last_elem)
				os << " ";
			else
				os << "}";
		}

		if ((!i) && (matrix.t_status())) os << "T";

		os << "\n";
	}
}

template <typename T>
std::ostream& operator << (std::ostream& os, lina::matrix<T>& matrix)
{
	if (matrix.iniver())
		iomatrix<T>(os, matrix);
	else
	{
		// if iniver = 0
		// out just vectors objects
		os << "not valid matrix\n";
		for (auto i = 0; i < matrix.size_line(); i++)
			os << matrix[i] << "\n";
	}

	return os;
}