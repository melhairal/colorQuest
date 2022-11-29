#pragma once
#include <functional>

namespace tnl {

	template <class T>
	class Sequence final {
	private:
		T* object_;
		std::function<bool(T*, const float)> now_;
		std::function<bool(T*, const float)> next_;
		bool (T::*p_now_)(const float);
		bool (T::*p_next_)(const float);
		bool is_start_ = true;
		bool is_change_ = false;
		float sum_time_ = 0;
		Sequence() {}
	public:

		//===================================================================================
		// �R���X�g���N�^
		// arg1... ��܃N���X�� this �|�C���^���w��
		// arg2... �R�[���o�b�N�ŌĂяo��������܃N���X�̃����o���\�b�h�܂��̓����_���w��
		//===================================================================================
		Sequence(T* obj, bool (T::*func)(const float))
			: object_(obj)
			, next_(func)
			, now_(func)
			, p_now_(func)
			, p_next_(func)
		{}

		~Sequence() {}

		//===================================================================================
		// �V�[�P���X�̃A�b�v�f�[�g ( ���t���[���Ăяo����OK )
		// arg1... �t���[���Ԃ̌o�ߎ���( �b�̃f���^�^�C�� )
		//===================================================================================
		inline bool update(const float deltatime) {
			sum_time_ += deltatime;
			bool ret = now_(object_, deltatime);
			if (!is_change_) {
				is_start_ = false;
				return ret;
			}
			now_ = next_;
			p_now_ = p_next_;
			is_start_ = true;
			sum_time_ = 0;
			is_change_ = false;
			return ret;
		}

		//===================================================================================
		// ��r
		//===================================================================================
		inline bool isComparable(bool (T::*func)(const float)) const { return p_now_ == func; }

		//===================================================================================
		// �������p�@�V�[�P���X�̍ŏ��̂P�t���[������ true ���A��
		//===================================================================================
		inline bool isStart() const { return is_start_; }

		//===================================================================================
		// �V�[�P���X�̌o�ߎ��Ԃ��擾 ( �b )
		//===================================================================================
		inline float getProgressTime() const { return sum_time_; }

		//===================================================================================
		// �V�[�P���X�̕ύX
		// arg1... ���̃t���[��������s�������܃N���X�̃��\�b�h���w��
		//===================================================================================
		inline void change(bool (T::*func)(const float)) {
			next_ = func;
			p_next_ = func;
			is_change_ = true;
		}

		//===================================================================================
		// �V�[�P���X�𑦍��ɕύX
		// arg1... ���s�������܃N���X�̃��\�b�h���w��
		// tisp... ���t���[����҂��������ɃV�[�P���X��ύX����
		//===================================================================================
		inline void immediatelyChange(bool (T::*func)(const float)) {
			now_ = func;
			p_now_ = func;
			is_start_ = true;
			sum_time_ = 0;
			is_change_ = false;
		}

	};

}

