#pragma once
namespace lina {

	// mathobj = true
	// index1 - lines
	// index2 - columns
	template <typename T>
	lina::_obj<T>& randfill(size_t lines, size_t columns) {
		lina::_obj<T> obj;
		obj.set_size(lines, columns);
		for (size_t line = 0; line < lines; line++) {
			for (size_t column = 0; column < columns; column++) {
				obj.set_elem((rand() & 0xf) + 1, line, column);
			}
		}

		if (lina::mathobj_mode)
			obj.tr();

		return obj;
	}

	namespace test {
		// init obj
		template <typename T>
		void init() {
			lina::_obj<T> t1;
			lina::_obj<T> t2 = lina::randfill<T>(1, 3);
			lina::_obj<T> t3 = lina::randfill<T>(4, 3);

			std::vector<T> vector = 
			{ 
				2, 2, 2 
			};
			
			std::vector<std::vector<T>> matrix = 
			{
				{ 1,2,3,8},
				{ 1,2,4,7},
				{ 1,2,5,6} 
			};

			lina::_obj<T> t4(vector);
			lina::_obj<T> t5(matrix);
			lina::_obj<T> t6(t2);
			lina::_obj<T> t7(t3);

			lina::_obj<T> t8 = vector;
			lina::_obj<T> t9 = matrix;
			lina::_obj<T> t10 = t2;
			lina::_obj<T> t11 = t3;

			std::cout << "init-test\n";
			std::cout << "t1:\n" << t1;
			std::cout << "t2:\n" << t2;
			std::cout << "t3:\n" << t3;
			std::cout << "t4:\n" << t4;
			std::cout << "t5:\n" << t5;
			std::cout << "t6:\n" << t6;
			std::cout << "t7:\n" << t7;
			std::cout << "t8:\n" << t8;
			std::cout << "t9:\n" << t9;
			std::cout << "t10:\n" << t10;
			std::cout << "t11:\n" << t11;
		}

		// init obj + tr
		template <typename T>
		void init_tr() {
			lina::_obj<T> t1;
			lina::_obj<T> t2 = lina::randfill<T>(1, 3);
			lina::_obj<T> t3 = lina::randfill<T>(4, 3);

			std::vector<T> vector =
			{
				2, 2, 2
			};

			std::vector<std::vector<T>> matrix =
			{
				{ 1,2,3,8},
				{ 1,2,4,7},
				{ 1,2,5,6}
			};

			lina::_obj<T> t4(vector);
			lina::_obj<T> t5(matrix);
			lina::_obj<T> t6(t2);
			lina::_obj<T> t7(t3);

			lina::_obj<T> t8 = vector;
			lina::_obj<T> t9 = matrix;
			lina::_obj<T> t10 = t2;
			lina::_obj<T> t11 = t3;

			t1.tr();
			t2.tr();
			t3.tr();
			t4.tr();
			t5.tr();
			t6.tr();
			t7.tr();
			t8.tr();
			t9.tr();
			t10.tr();
			t11.tr();

			std::cout << "init-test-tr\n";
			std::cout << "t1:\n" << t1;
			std::cout << "t2:\n" << t2;
			std::cout << "t3:\n" << t3;
			std::cout << "t4:\n" << t4;
			std::cout << "t5:\n" << t5;
			std::cout << "t6:\n" << t6;
			std::cout << "t7:\n" << t7;
			std::cout << "t8:\n" << t8;
			std::cout << "t9:\n" << t9;
			std::cout << "t10:\n" << t10;
			std::cout << "t11:\n" << t11;
		}

		template <typename T>
		void summ() {
			lina::_obj<T> t1 = lina::randfill<T>(1, 4);
			lina::_obj<T> t2 = lina::randfill<T>(1, 4);
			lina::_obj<T> t3 = t1 + t2;

			std::cout << "summ-test\n";
			std::cout << "t1:\n" << t1;
			std::cout << "t2:\n" << t2;

			t1.tr();
			t2.tr();

			lina::_obj<T> t4 = t1 + t2;

			std::cout << "t3:\n" << t3;
			std::cout << "t4:\n" << t4;
		}

		template <typename T>
		void mult() {
			lina::_obj<T> t1 = lina::randfill<T>(5, 3);
			lina::_obj<T> t2 = lina::randfill<T>(3, 2);

			if (lina::mathobj_mode)
				t2 = lina::randfill<T>(2, 5);

			lina::_obj<T> t3 = t1 * t2;

			std::cout << "mult-test\n";
			std::cout << "t1:\n" << t1;
			std::cout << "t2:\n" << t2;
			std::cout << "t3:\n" << t3;
		}

		template <typename T>
		void tr() {
			lina::_obj<T> t1 = { 1,7,3 };
			lina::_obj<T> t2 = lina::tr(t1);

			std::cout << "tr-test\n";
			std::cout << "t1:\n" << t1;
			std::cout << "t2:\n" << t2;
		}

		template <typename T>
		void p_inv() {
			lina::_obj<T> t1 = lina::randfill<T>(4, 4);
			lina::_obj<T> t2 = lina::pseudoinverse(t1);
			lina::_obj<T> t3 = !t1;
			std::cout << "psevdoinverse-test\n";
			std::cout << "t1:\n" << t1; // reclear obj ?
			std::cout << "t2:\n" << t2;
			std::cout << "t3:\n" << t3;
		}
	}
}