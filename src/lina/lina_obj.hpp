#pragma once

namespace lina {
	bool mathobj_mode = true;
	void set_mathobj_mode(bool value) {
		mathobj_mode = value;
	}
}

// SetLinaMode - true: default init-lines
// SetLinaMode - false: default init-columns
#define SetLinaMode(value) lina::set_mathobj_mode(value);

namespace lina {
	template<typename T> constexpr T** clear_pointer = nullptr;
	template<typename T> constexpr T error_value = (T)0;

	constexpr size_t clear_value = 0;
	constexpr size_t frst_index = 0;
	constexpr size_t init_value = 0;
	constexpr size_t init_column = 1;

	constexpr size_t init_flag = true;
	constexpr size_t init_tr = false;
	constexpr size_t clear_tr = false;
	constexpr size_t clear_flag = false;

	template<typename T>
	class _obj
	{
	private:
		T** _cnt;
		size_t _columns;
		size_t _lines;
		bool _tr;
		bool _vf;

	private:
		void clear() {
			_cnt = clear_pointer<T>;
			_columns = clear_value;
			_lines = clear_value;
			_tr = clear_tr;
			_vf = clear_flag;
		}

		void vrftypes() {
			_vf = init_flag;
			if (typeid(T) == typeid(float)) return;
			if (typeid(T) == typeid(double)) return;
			_vf = !init_flag;
		}

		void malloc_line() {
			if (!_vf) return;
			_cnt = (T**)std::malloc(_lines * sizeof(T*));
			if (!_cnt)
				clear();
		}

		void malloc_column() {
			if (!_vf) return;
			for (auto line = 0; line < _lines; line++) {
				if (!_vf) 
					return;
				_cnt[line] = (T*)std::malloc(_columns * sizeof(T));
				if (!_cnt)
					clear();
			}
		}

		void cnt_fill() {
			if (!_vf) return;
			for (auto line = 0; line < _lines; line++) {
				for (auto column = 0; column < _columns; column++) {
					_cnt[line][column] = init_value;
				}
			}
		}

		void cnt_fill(vect<T>& input) {
			if (!_vf) return;
			for (auto line = 0; line < _lines; line++) {
				for (auto column = 0; column < _columns; column++) {
					_cnt[line][column] = input[line];
				}
			}
		}

		void cnt_fill(vect<vect<T>>& input) {
			if (!_vf) return;
			for (auto line = 0; line < _lines; line++) {
				for (auto column = 0; column < _columns; column++) {
					_cnt[line][column] = input[column][line];
				}
			}
		}

		void cnt_fill(list<T> input) {
			if (!_vf) return;
			T* column_ptr = (T*)input.begin();
			for (auto line = 0; line < _lines; line++) {
				for (auto column = 0; column < _columns; column++) {
					_cnt[line][column] = *column_ptr++;
				}
			}
		}

		void cnt_fill(list<list<T>> input) {
			if (!_vf) return;
			list<T>* line_ptr = (list<T>*)input.begin();
			for (auto line = 0; line < _lines; line++) {
				T* column_ptr = (T*)line_ptr->begin();
				for (auto column = 0; column < _columns; column++) {
					_cnt[line][column] = *column_ptr++;
				}
				line_ptr++;
			}
		}

		void cnt_fill(_obj<T>& input) {
			if (!_vf) return;
			for (auto line = 0; line < _lines; line++) {
				for (auto column = 0; column < _columns; column++) {
					_cnt[line][column] = input._cnt[line][column];
				}
			}
		}

		void post_init(){
			if (!_vf) return;
			if (mathobj_mode) 
				line_column_swap();
		}

		void line_column_swap()
		{
			size_t tmp = _columns;
			_columns = _lines;
			_lines = tmp;
		}

		bool seltr(){
			return mathobj_mode ? _tr : !_tr;
		}

	private:
		bool bad_index(size_t index_line, size_t index_column) {
			bool result = true;

			if ((index_line >= frst_index) && (index_column >= frst_index))
				if ((index_line < _lines) && (index_column < _columns))
					result = false;

			result |= (!_vf);
			return result;
		}

	public:
		void tr() {
			if (!_vf) return;
			line_column_swap();
			_tr ^= true;
		}

	public:
		bool get_vf() {
			return _vf;
		}

		bool get_tr() {
			return _tr;
		}

		size_t get_count_lines() {
			return _lines;
		}

		size_t get_count_columns() {
			return _columns;
		}

		T get_elem(size_t index_line, size_t index_column)
		{
			if (bad_index(index_line, index_column)) 
				return error_value<T>;

			if (seltr())
				return _cnt[index_line][index_column];
			else
				return _cnt[index_column][index_line];

		}

	public:
		void set_size(_obj<T>& other) {
			vrftypes();
			_columns = other.get_count_columns();
			_lines = other.get_count_lines();
			if (lina::mathobj_mode) 
				line_column_swap();
			malloc_line();
			malloc_column();
			cnt_fill();
			post_init();
		}

		void set_size(size_t lines, size_t columns) {
			vrftypes();
			_columns = columns;
			_lines = lines;
			if (lina::mathobj_mode)
				line_column_swap();
			malloc_line();
			malloc_column();
			cnt_fill();
			post_init();
		}

		void set_elem(T elem, size_t index_line, size_t index_column)
		{
			if (bad_index(index_line, index_column))
				return;

			if (seltr())
				_cnt[index_line][index_column] = elem;
			else
				_cnt[index_column][index_line] = elem;
		}

		void set_obj(_obj<T>& other)
		{
			_vf = other._vf;
			_tr = other._tr;
			_columns = other._columns;
			_lines = other._lines;
			malloc_line();
			malloc_column();
			cnt_fill(other);
		}

	public:
		void operator= (_obj<T>& other) {
			_vf = other._vf;
			_tr = other._tr;
			_columns = other._columns;
			_lines = other._lines;
			malloc_line();
			malloc_column();
			cnt_fill(other);
		}

		void operator= (vect<T>& input) {
			vrftypes();
			_columns = init_column;
			_lines = input.size();
			malloc_line();
			malloc_column();
			cnt_fill(input);
			post_init();
		}

		void operator= (vect<vect<T>>& input) {
			vrftypes();
			_columns = input.size();
			_lines = input[frst_index].size();
			malloc_line();
			malloc_column();
			cnt_fill(input);
			post_init();
		}

		void operator= (list<T> input) {
			vrftypes();
			_columns = init_column;
			_lines = input.size();
			malloc_line();
			malloc_column();
			cnt_fill(input);
			post_init();
		}

		void operator= (list<list<T>> input) {
			vrftypes();
			list<T>* ptr = (list<T>*)input.begin();
			_columns = ptr->size();
			_lines = input.size();
			malloc_line();
			malloc_column();
			cnt_fill(input);
			post_init();
		}

	public:
		_obj() {
			clear();
		}

		_obj(vect<T>& input) {
			vrftypes();
			_columns = init_column;
			_lines = input.size();
			malloc_line();
			malloc_column();
			cnt_fill(input);
			post_init();
		}

		_obj(vect<vect<T>>& input) {
			vrftypes();
			_columns = input.size();
			_lines = input[frst_index].size();
			malloc_line();
			malloc_column();
			cnt_fill(input);
			post_init();
		}

		_obj(list<T> input) {
			vrftypes();
			_columns = init_column;
			_lines = input.size();
			malloc_line();
			malloc_column();
			cnt_fill(input);
			post_init();
		}

		_obj(list<list<T>> input) {
			vrftypes();
			list<T>* ptr = (list<T>*)input.begin();
			_columns = ptr->size();
			_lines = input.size();
			malloc_line();
			malloc_column();
			cnt_fill(input);
			post_init();
		}
	};
}

template <typename L>
std::ostream& operator << (std::ostream& os, lina::_obj<L> obj)
{
	if(obj.get_vf()) {
		size_t last_column = obj.get_count_columns() - 1;
		size_t last_line = obj.get_count_lines() - 1;
		for (auto line = 0; line <= last_line; line++) {
			os << "{";
			for (auto column = 0; column <= last_column; column++) {
				os << obj.get_elem(line, column);
				if (column != last_column)
					os << ", ";
			}
			os << "}\n";
		}
		os << "\n";
	}
	return os;
}