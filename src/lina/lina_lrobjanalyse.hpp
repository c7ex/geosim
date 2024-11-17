#pragma once

// _vf bitmap
// 7 6 5 4 3 2 1 0 bits
// 0 0 0 0 0 0 0 1 (state 0x01) - count lines right obj = count columns left obj ........ only multiply math
// 0 0 0 0 0 0 1 0 (state 0x02) - count lines left obj = count columns right obj
// 0 0 0 0 0 1 0 0 (state 0x04) - count lines left obj = count lines right obj
// 0 0 0 0 1 0 0 0 (state 0x08) - count columns left obj = count columns right obj
// 0 0 0 1 0 0 0 0 (state 0x10) - count lines right obj = count columns right obj ....... right square matrix
// 0 0 1 0 0 0 0 0 (state 0x20) - count lines left obj = count columns left obj ......... left square matrix

// realise math:
// only multiply ................: state 0x01
// only summation ...............: state 0x0C
// full math ....................: state 0x0D
// only right reverse ...........: state 0x10
// only left reverse ............: state 0x20

namespace lina {
	constexpr size_t init_mvf        = 0x0;
	constexpr size_t init_flag_mask  = 0x1;
	constexpr size_t init_flag_shift = 0x1;

	constexpr size_t only_multiply   = 0x01;
	constexpr size_t only_summation  = 0x0C;
	constexpr size_t full_math       = 0x0D;
	constexpr size_t only_right_rvs  = 0x10;
	constexpr size_t only_left_rvs   = 0x20;


	template <typename T>
	class lrobjanalyse {
	private:
		size_t _left_lines;
		size_t _left_columns;
		size_t _right_lines;
		size_t _right_columns;
		int8_t _mvf;

	private:

		void load_sizes(lina::_obj<T> left_obj, lina::_obj<T> right_obj) {
			_left_lines = left_obj.get_count_lines();
			_left_columns = left_obj.get_count_columns();
			_right_lines = right_obj.get_count_lines();
			_right_columns = right_obj.get_count_columns();
		}

		void init_flags() {
			_mvf = init_mvf;

			size_t mask = init_flag_mask;

			if (_right_lines == _left_columns)
				_mvf |= mask;
			mask <<= init_flag_shift;

			if (_right_columns == _left_lines)
				_mvf |= mask;
			mask <<= init_flag_shift;

			if (_left_lines ==_right_lines)
				_mvf |= mask;
			mask <<= init_flag_shift;

			if (_left_columns == _right_columns)
				_mvf |= mask;
			mask <<= init_flag_shift;

			if (_right_columns == _right_lines)
				_mvf |= mask;
			mask <<= init_flag_shift;

			if (_left_lines == _left_columns)
				_mvf |= mask;
			mask <<= init_flag_shift;
		}

		bool mvf_mask(size_t mask) {
			if ((_mvf & mask) == mask)
				return true;
			else
				return false;
		}

	public:
		bool mvf_onlymult(){
			return mvf_mask(only_multiply);
		}

		bool mvf_onlysumm() {
			return mvf_mask(only_summation);
		}

		bool mvf_fullmath() {
			return mvf_mask(full_math);
		}

		bool mvf_only_Rrvs() {
			return mvf_mask(only_right_rvs);
		}

		bool mvf_only_Lrvs() {
			return mvf_mask(only_left_rvs);
		}

	public:
		lrobjanalyse(lina::_obj<T> left_obj, lina::_obj<T> right_obj) {
			load_sizes(left_obj, right_obj);
			init_flags();
		}
	};
}