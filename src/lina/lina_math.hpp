#pragma once

namespace lina {
	constexpr auto prec = 1e-10;
}

namespace lina {
	template<typename T>
	_obj<T>& tr(_obj<T>& input) {
		_obj<T> output = input;
		output.tr();
		return output;
	}
}

template <typename T>
lina::_obj<T> operator+ (lina::_obj<T>& l_obj, lina::_obj<T>& r_obj) {
	lina::lrobjanalyse<T> analyse(l_obj, r_obj);
	lina::_obj<T> result;
	if (analyse.mvf_onlysumm()) {
		result.set_size(l_obj);
		for (auto line = 0; line < result.get_count_lines(); line++) {
			for (auto column = 0; column < result.get_count_columns(); column++) {
				T value = lina::init_value;
				T l_value = l_obj.get_elem(line, column);
				T r_value = r_obj.get_elem(line, column);
				value = l_value + r_value;
				result.set_elem(value, line, column);
			}
		}
	}
	return result;
}

template <typename T>
lina::_obj<T> operator- (lina::_obj<T>& l_obj, lina::_obj<T>& r_obj) {
	lina::lrobjanalyse<T> analyse(l_obj, r_obj);
	lina::_obj<T> result;
	if (analyse.mvf_onlysumm()) {
		result.set_size(l_obj);
		for (auto line = 0; line < result.get_count_lines(); line++) {
			for (auto column = 0; column < result.get_count_columns(); column++) {
				T value = lina::init_value;
				T l_value = l_obj.get_elem(line, column);
				T r_value = r_obj.get_elem(line, column);
				value = l_value - r_value;
				result.set_elem(value, line, column);
			}
		}
	}
	return result;
}

template <typename T>
lina::_obj<T> operator* (lina::_obj<T>& l_obj, lina::_obj<T>& r_obj) {
	lina::lrobjanalyse<T> analyse(l_obj, r_obj);
	lina::_obj<T> result;
	if (analyse.mvf_onlymult()) {
		auto size_result_line = l_obj.get_count_lines();
		auto size_result_columns = r_obj.get_count_columns();
		auto size = l_obj.get_count_columns();
		result.set_size(size_result_line, size_result_columns);
		for (auto result_line = 0; result_line < size_result_line; result_line++) {
			for (auto result_column = 0; result_column < size_result_columns; result_column++) {
				T value = lina::init_value;
				for (auto index = 0; index < size; index++) {
					T l_value = l_obj.get_elem(result_line, index);
					T r_value = r_obj.get_elem(index, result_column);
					value += (l_value * r_value);
					result.set_elem(value, result_line, result_column);
				}
			}
		}
	}
	return result;
}

namespace lina {
	constexpr size_t init_e_matrix_value = 1;

	template <typename T>
	void init_e_matrix(lina::_obj<T>& obj, size_t size) {
		obj.set_size(size, size);
		for (auto index = 0; index < size; index++) {
			obj.set_elem(init_e_matrix_value, index, index);
		}
	}

	template <typename T>
	void line_subtraction(_obj<T>& obj, T multiplier, size_t ref_line, size_t sub_line, size_t size) {
		for (size_t column = ref_line < sub_line ? 0 : size - 1; column < size; ref_line < sub_line ? column++ : column--) {
			T value_idx = obj.get_elem(column, ref_line);
			T value_lne = obj.get_elem(column, sub_line);
			T value = value_lne - value_idx * multiplier;
			obj.set_elem(value, column, sub_line);
		}
	}

	template <typename T>
	bool valid_matrix(_obj<T>& obj) {
		for (auto line = 0; line < obj.get_count_lines(); line++) {
			T summary = 0;
			for (auto column = 0; column < obj.get_count_columns(); column++)
				summary += abs(obj.get_elem(line, column));
			if (summary < prec) 
				return false;
		}

		for (auto column = 0; column < obj.get_count_columns(); column++) {
			T summary = 0;
			for (auto line = 0; line < obj.get_count_lines(); line++)
				summary += abs(obj.get_elem(line, column));
			if (summary < prec)
				return false;
		}

		return true;
	}

	// udf - do "up" or "down" triangular matrix
	// upf = true - do "up"
	// upf = false - do "down"
	template <typename T>
	bool triangular_matrix(_obj<T>& c_obj, _obj<T>& e_obj, size_t size, bool udf) {
		for (auto index = udf ? 0 : size - 1; index < size; udf ? index++ : index--) {
			size_t curr_line = index;
			size_t next_line = udf ? index + 1 : index - 1;
			if (next_line >= size) break;

			T divider_value = c_obj.get_elem(index, index);
			if (!divider_value) return false;

			for (size_t column = 0; column < size; column++) {
				T value_c = c_obj.get_elem(column, index) / divider_value;
				c_obj.set_elem(value_c, column, index);
				T value_e = e_obj.get_elem(column, index) / divider_value;
				e_obj.set_elem(value_e, column, index);
			}

			for (size_t line = next_line; line < size; udf ? line++ : line--) {
				T multiplier = c_obj.get_elem(index, line);
				lina::line_subtraction(c_obj, multiplier, index, line, size);
				lina::line_subtraction(e_obj, multiplier, index, line, size);
			}
		}

		return valid_matrix<T>(c_obj);
	}
}

template <typename T>
lina::_obj<T> operator! (lina::_obj<T> obj) {
	lina::lrobjanalyse<T> analyse(obj, obj);
	lina::_obj<T> result;
	if (analyse.mvf_only_Lrvs()) {
		lina::_obj<T> e_matrix;
		lina::_obj<T> c_matrix;
		
		auto size = obj.get_count_lines();
		lina::init_e_matrix(e_matrix, size);
		c_matrix.set_obj(obj);

		if (!lina::triangular_matrix(c_matrix, e_matrix, size, true)) 	return result;
		if (!lina::triangular_matrix(c_matrix, e_matrix, size, false)) 	return result;

		result = e_matrix;
	}

	return result;
}

namespace lina {
	template <typename T>
	lina::_obj<T> pseudoinverse(lina::_obj<T>& obj) {

		lina::_obj<T> tmp1 = lina::tr(obj) * obj;
		lina::_obj<T> tmp2 = !tmp1;
		lina::_obj<T> result = tmp2 * lina::tr(obj);

		return result;
	}
}